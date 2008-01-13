#ifndef __MglJoyManager_H__
#define __MglJoyManager_H__

#include "MglDirectInputBase.h"

//	クラス宣言
class DLL_EXP CMglJoyManager : public CMglDirectInputBase
{
protected:
	vector<_MGL_IDirectInputDevice*> m_joystkDevAry;

	//BOOL bInitFlg;

	//void CHKINIT(){ if(bInitFlg!=TRUE) ExInit(); }

public:
	//	コンストラクタとデストラクタ
	CMglJoyManager();
	virtual ~CMglJoyManager();

	//	初期化処理。通常は自動的に呼ばれるが、自分で細かなオプションを指定することも可能
	void ExInit( DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	void ExInit( HWND hWnd, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	void Release();	//	開放

	//	デバイス数を取得する
	int GetJoyCount(){ return m_joystkDevAry.size(); }

	//	デバイスを取得する
	_MGL_IDirectInputDevice* GetJoyDevice( int nDeviceNo )
	{
		if ( nDeviceNo > GetJoyCount()-1 )
			MyuThrow( 0, "CMglJoyInput::IsPushBotton  ジョイデバイス番号 %d は存在しません。", nDeviceNo );
		return m_joystkDevAry[nDeviceNo];
	}
};

#endif//__MglJoyManager_H__
