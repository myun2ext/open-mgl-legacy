#ifndef __MglInput_H__
#define __MglInput_H__

#include "MglKeyboardInput.h"
#include "MglJoyManager.h"
#include "MglJoyInput.h"
#include "MglMouseInput.h"

//	関連付け配列用アイテム
typedef struct {
	char cName;
	BYTE diKeycode;
} KB_FAST_RT_ARY_ITEM;


//	クラス宣言
class DLL_EXP CMglInput : public CMglExceptionThrowerBase, public CMglKeyboardInput
{
protected:
	//	各デバイスのクラス
	//CMglKeyboardInput m_keyboard;
	CMglJoyManager m_joyMgr;
	vector<CMglJoyInput> m_joyAry;

	//	初期化フラグ
	BOOL m_bInitFlg;

	//	OnEvent用
	map<string,BOOL> m_onEventMap;
	typedef map<string,BOOL>::iterator EVEMAP_ITR;
	//	内部メソッド
	//void GenRtAry(); -> CMglKeyboardInput へ移動 (2007/01/01)
	BOOL IsOnJoy( CMglJoyInput* pJoy, const char* szJoyInputName );
	BOOL IsOnKbd( const char* szInputName );
	void CHKJOYNO( int n ){ if(n>=m_joyAry.size()) MyuThrow( 0343, "%d のJOYは存在しません。" ); }

public:
	//	コンストラクタとデストラクタ
	CMglInput();
	virtual ~CMglInput();

	//	初期化
	void Init( HWND hWnd=NULL, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	/*void Init( DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND ){
		Init( GetDefaultHwnd(), dwCooperativeFlag ); }*/

	//	情報取得
	BOOL IsOn( const char* szInputName );			//	現在押されているか
	BOOL GetIsOnEvent( const char* szInputName );	//	押された瞬間を取得
	void ResetOnEvent( const char* szInputName ){ SetOnEvent( szInputName, FALSE ); }
	void SetOnEvent( const char* szInputName, BOOL bEvent );	//	イベントの設定

	//	拡張設定
	void SetJoyStickInfo( int nDeviceNo, long nNeutralX, long nNeutralY, long nMargin );

	/*	ステータスを毎回更新しないようにロックする (未実装)
	void StateUpdateLock();
	*/

	void KeyboardUpdate(){ CMglKeyboardInput::Update(); }

	//	リファレンスの取得
	int GetJoyCount(){ return m_joyAry.size(); }
	CMglJoyInput& GetJoyRef( int nDeviceNo ){ CHKJOYNO(nDeviceNo); return m_joyAry[nDeviceNo]; }
};

#endif//__MglInput_H__
