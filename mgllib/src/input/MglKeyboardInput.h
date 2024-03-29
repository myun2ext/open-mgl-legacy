//////////////////////////////////////////////////////////
//
//	MglKeyboardInput  v0.60.00 06/01/02
//		- キーボード入力クラス
//
//	v0.10.10 04/12/13
//	・m_stateBufゼロクリアしてねぇ(;´Д`)ゞ
//
//	v0.10.25 05/03/02
//	・GetDeviceState()に失敗した時、
//	　m_stateBufはゼロクリアしとかないとマズいっぽい。
//	・Init()の引数に dwCooperativeFlag 追加。
//
//	v0.10.26 05/03/04
//	・変数名等ちょこちょこ
//
//	v0.20.00 06/01/02
//	・CMglKeyboardInputBaseに分離したり色々
//
//////////////////////////////////////////////////////////

#ifndef __MglKeyboardInput_H__
#define __MglKeyboardInput_H__

#include "msl.h"
#include "MglKeyboardInputBase.h"

#define FAST_RT_ARY_SIZE	(128)

#define ASCII_BS		(0x08)
#define ASCII_BACKSPACE	(0x08)
/*#define ASCII_TAB		(0x09)
#define ASCII_HTAB		(0x09)*/
#define ASCII_RETURN	(0x0A)
#define ASCII_ENTER		(0x0A)
#define ASCII_ESC		(0x1B)
#define ASCII_ESCAPE	(0x1B)
/*#define ASCII_SP		(0x20)
#define ASCII_SPACE		(0x20)*/
#define ASCII_DELETE	(0x7F)

#define DIK_ERR			(0x00)
#define DIK_NULL		(0x00)
#define ASCII_NULL		(0x00)

//	クラス宣言
class DLL_EXP CMglKeyboardInput : public CMglKeyboardInputBase
{
private:
	//	m_kbFastRtAry 生成
	static void GenRtAry();

	//	OnEvent系用
	//BYTE m_prevStateBuf[STATEBUF_SIZE];
	//CMglTimer m_timers[STATEBUF_SIZE];	<-- やっぱメモリとか食いすぎですよネー…
	//DWORD m_dwTimes[STATEBUF_SIZE];

protected:
	//	キーボードのコード関連配列
	static int m_kbFastRtAry[FAST_RT_ARY_SIZE];	//	本当は CMglKeyboardInput にあるべきな気が…
	static bool m_kbFastRtAryInited;
	//	↑本当はstaticであるべきなんだがとりあえず保留・・・

public:
	//	コンストラクタ・デストラクタ
	CMglKeyboardInput(){
		/*ZeroMemoryAS( m_kbFastRtAry );
		ZeroMemoryAS( m_prevStateBuf );*/
	}
	virtual ~CMglKeyboardInput(){}

	//	初期化
	void Init( HWND hWnd, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND ){
		CMglKeyboardInputBase::Init( hWnd, dwCooperativeFlag );
		//GenRtAry();
	}

	static BYTE GetDik( char c ){GenRtAry(); return m_kbFastRtAry[c]; }
	static BYTE GetAsciiToDik( char c ){GenRtAry(); return m_kbFastRtAry[c]; }
	static BYTE GetAscii2Dik( char c ){GenRtAry(); return m_kbFastRtAry[c]; }
	static BYTE AsciiToDik( char c ){GenRtAry(); return m_kbFastRtAry[c]; }
	static BYTE Ascii2Dik( char c ){GenRtAry(); return m_kbFastRtAry[c]; }
	static BYTE ASCII_TO_DIK( char c ){GenRtAry(); return m_kbFastRtAry[c]; }
	static BYTE ASCII2DIK( char c ){GenRtAry(); return m_kbFastRtAry[c]; }

	//	オーバーライド
	/*void UpdateStateBuf(){
		memcpy( m_prevStateBuf, m_stateBuf, sizeof(m_stateBuf) );
		CMglKeyboardInputBase::UpdateStateBuf();
	}*/
	void Update(){ UpdateStateBuf(); }

	//	入力取得
	int GetPressDikeyList( vector<BYTE> &keyListOut );
	int GetPressKeyList( vector<char> &keyListOut );
	char GetPressKey(){	//	最初の一つだけ
		vector<char> keylist;
		if ( GetPressKeyList(keylist) == 0 )
			return EOF;
		else
			return keylist[0];
	}

	//	Update()必要
	int GetOnDikey();
	//int GetOnDikey( BYTE nDik );
	int GetOnKey();
	int GetOnKey( char cAsciiKeyCode );

	//	*****
	int GetOnDikey(BYTE nDik){ return IsOnDownKey(nDik); }

	/////////////////////////////////////////////////////////////////////
	
	//	押されたイベント
	BOOL IsOnDownKey(BYTE nDik){
		if( GetStateChanged(nDik) > 0 ) 
			return TRUE;
		else
			return FALSE;
	}

	//	離されたイベント
	BOOL IsOnUpKey(BYTE nDik){
		if( GetStateChanged(nDik) < 0 ) 
			return TRUE;
		else
			return FALSE;
	}
};


#endif//__MglKeyboardInput_H__