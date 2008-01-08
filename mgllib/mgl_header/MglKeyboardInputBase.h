//////////////////////////////////////////////////////////
//
//	MglKeyboardInputBase  v0.60.00 06/01/02
//		- DirectInput基本クラス
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

#ifndef __MglKeyboardInputBase_H__
#define __MglKeyboardInputBase_H__

#include "msl.h"
#include "MglDirectInputBase.h"

#define STATEBUF_SIZE	(256)

//	クラス宣言
class DLL_EXP CMglKeyboardInputBase : public CMglDirectInputBase
{
protected:
	IDirectInputDevice8 *m_pDevice;
	BYTE m_stateBuf[STATEBUF_SIZE];

	void Acquire();
	void Unacquire();

	void InitCheck()
	{
		if ( m_pDevice == NULL )
			Init();
	}

public:
	//	コンストラクタ・デストラクタ
	CMglKeyboardInputBase();
	virtual ~CMglKeyboardInputBase();

	//	初期化と開放
	void Init( HWND hWnd=NULL, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	void Release();

	void UpdateStateBuf();
	BOOL IsPressKey( BYTE keyCode );		//	Is???
	BOOL IsPressDikey( BYTE keyCode ){ return IsPressKey(keyCode); }
};


#endif//__MglKeyboardInputBase_H__