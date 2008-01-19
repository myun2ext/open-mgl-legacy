//////////////////////////////////////////////////////////
//
//	MglMouseInput - �}�E�X���̓N���X
//
//////////////////////////////////////////////////////////

#ifndef __MglMouseInput_H__
#define __MglMouseInput_H__

#include "MglDirectInputBase.h"

#define STATEBUF_SIZE	(256)

//	�N���X�錾
class DLL_EXP CMglMouseInput : public CMglDirectInputBase
{
protected:
	_MGL_IDirectInputDevice *m_pDevice;
	BYTE m_stateBuf[STATEBUF_SIZE];

	void Acquire();
	void Unacquire();

	void InitCheck()
	{
		if ( m_pDevice == NULL )
			Init();
	}

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglMouseInput();
	virtual ~CMglMouseInput();

	//	�������ƊJ��
	void Init( HWND hWnd=NULL, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	void Release();

	void UpdateStateBuf();
	BOOL IsPressKey( BYTE keyCode );		//	Is???
	BOOL IsPressDikey( BYTE keyCode ){ return IsPressKey(keyCode); }
};


#endif//__MglMouseInput_H__