//////////////////////////////////////////////////////////
//
//	MglDirectInputDeviceBase - マウス入力クラス
//
//////////////////////////////////////////////////////////

#ifndef __MglDirectInputDeviceBase_H__
#define __MglDirectInputDeviceBase_H__

#include "MglDirectInputBase.h"

#define STATEBUF_SIZE	(256)

//	クラス宣言
class DLL_EXP CMglDirectInputDeviceBase : public CMglDirectInputBase
{
protected:
	_MGL_IDirectInputDevice *m_pDevice;
	BYTE m_stateBuf[STATEBUF_SIZE];

	void Acquire();
	void Unacquire();

	void InitCheck()
	{
		if ( m_pDevice == NULL )
			MyuThrow(20, "CMglDirectInputDeviceBase: Init()を呼び出してください。");
	}

public:
	//	コンストラクタ・デストラクタ
	CMglDirectInputDeviceBase();
	virtual ~CMglDirectInputDeviceBase();

	//	初期化と開放
	void Init(  REFGUID rguid, LPCDIDATAFORMAT dataFormat, HWND hWnd=NULL, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	void Release();

	void UpdateStateBuf();
};


#endif//__MglDirectInputDeviceBase_H__