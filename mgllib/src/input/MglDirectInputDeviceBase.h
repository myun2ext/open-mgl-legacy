//////////////////////////////////////////////////////////
//
//	MglDirectInputDeviceBase - マウス入力クラス
//
//	2008/09/29 古いバッファ記憶対応
//////////////////////////////////////////////////////////

#ifndef __MglDirectInputDeviceBase_H__
#define __MglDirectInputDeviceBase_H__

#include "MglDirectInputBase.h"

//	クラス宣言
class DLL_EXP CMglDirectInputDeviceBase : public CMglDirectInputBase
{
protected:
	_MGL_IDirectInputDevice *m_pDevice;
	//BYTE m_stateBuf[STATEBUF_SIZE];
	BYTE *m_pStateBuf;
	BYTE *m_pOldStateBuf;	//	2008/09/29 古いバッファ記憶対応
	int m_nStateBufSize;
	HWND m_hWnd;

	void Acquire();
	void Unacquire();

	virtual void InitCheck()
	{
		if ( m_pDevice == NULL )
			MyuThrow(20, "CMglDirectInputDeviceBase: Init()を呼び出してください。");
	}
	int GetStateChanged(int nIndex); //	0:変化なし  正の値:押された  負の値:離された

public:
	//	コンストラクタ・デストラクタ
	CMglDirectInputDeviceBase();
	virtual ~CMglDirectInputDeviceBase();

	//	初期化と開放
	void Init(  REFGUID rguid, LPCDIDATAFORMAT dataFormat, int nStateBufSize,
		HWND hWnd=NULL, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	void Release();

	BYTE* UpdateStateBuf();
	BYTE* GetStateBuf(){ return m_pStateBuf; }
	BYTE* GetOldStateBuf(){ return m_pOldStateBuf; }
	//BYTE* GetStateBuf(){ return UpdateStateBuf(); }
};


#endif//__MglDirectInputDeviceBase_H__