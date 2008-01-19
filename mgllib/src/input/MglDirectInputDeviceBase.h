//////////////////////////////////////////////////////////
//
//	MglDirectInputDeviceBase - �}�E�X���̓N���X
//
//////////////////////////////////////////////////////////

#ifndef __MglDirectInputDeviceBase_H__
#define __MglDirectInputDeviceBase_H__

#include "MglDirectInputBase.h"

#define STATEBUF_SIZE	(256)

//	�N���X�錾
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
			MyuThrow(20, "CMglDirectInputDeviceBase: Init()���Ăяo���Ă��������B");
	}

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglDirectInputDeviceBase();
	virtual ~CMglDirectInputDeviceBase();

	//	�������ƊJ��
	void Init(  REFGUID rguid, LPCDIDATAFORMAT dataFormat, HWND hWnd=NULL, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	void Release();

	void UpdateStateBuf();
};


#endif//__MglDirectInputDeviceBase_H__