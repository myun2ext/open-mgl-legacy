//////////////////////////////////////////////////////////
//
//	MglKeyboardInputBase  v0.60.00 06/01/02
//		- DirectInput��{�N���X
//
//	v0.10.10 04/12/13
//	�Em_stateBuf�[���N���A���Ă˂�(;�L�D`)�U
//
//	v0.10.25 05/03/02
//	�EGetDeviceState()�Ɏ��s�������A
//	�@m_stateBuf�̓[���N���A���Ƃ��Ȃ��ƃ}�Y�����ۂ��B
//	�EInit()�̈����� dwCooperativeFlag �ǉ��B
//
//	v0.10.26 05/03/04
//	�E�ϐ��������傱���傱
//
//	v0.20.00 06/01/02
//	�ECMglKeyboardInputBase�ɕ���������F�X
//
//////////////////////////////////////////////////////////

#ifndef __MglKeyboardInputBase_H__
#define __MglKeyboardInputBase_H__

#include "msl.h"
#include "MglDirectInputBase.h"

#define STATEBUF_SIZE	(256)

//	�N���X�錾
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
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglKeyboardInputBase();
	virtual ~CMglKeyboardInputBase();

	//	�������ƊJ��
	void Init( HWND hWnd=NULL, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	void Release();

	void UpdateStateBuf();
	BOOL IsPressKey( BYTE keyCode );		//	Is???
	BOOL IsPressDikey( BYTE keyCode ){ return IsPressKey(keyCode); }
};


#endif//__MglKeyboardInputBase_H__