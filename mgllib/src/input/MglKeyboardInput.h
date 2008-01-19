//////////////////////////////////////////////////////////
//
//	MglKeyboardInput  v0.60.00 06/01/02
//		- �L�[�{�[�h���̓N���X
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

//	�N���X�錾
class DLL_EXP CMglKeyboardInput : public CMglKeyboardInputBase
{
private:
	//	m_kbFastRtAry ����
	void GenRtAry();

	//	OnEvent�n�p
	BYTE m_prevStateBuf[STATEBUF_SIZE];
	//CMglTimer m_timers[STATEBUF_SIZE];	<-- ����σ������Ƃ��H�������ł���l�[�c
	DWORD m_dwTimes[STATEBUF_SIZE];

protected:
	//	�L�[�{�[�h�̃R�[�h�֘A�z��
	int m_kbFastRtAry[FAST_RT_ARY_SIZE];	//	�{���� CMglKeyboardInput �ɂ���ׂ��ȋC���c

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglKeyboardInput(){
		ZeroMemoryAS( m_kbFastRtAry );
		ZeroMemoryAS( m_prevStateBuf );
	}
	virtual ~CMglKeyboardInput(){}

	//	������
	void Init( HWND hWnd, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND ){
		CMglKeyboardInputBase::Init( hWnd, dwCooperativeFlag );
		GenRtAry();
	}

	BYTE GetDik( char c ){ return m_kbFastRtAry[c]; }

	//	�I�[�o�[���C�h
	void UpdateStateBuf(){
		memcpy( m_prevStateBuf, m_stateBuf, sizeof(m_stateBuf) );
		CMglKeyboardInputBase::UpdateStateBuf();
	}
	void Update(){ UpdateStateBuf(); }

	//	���͎擾
	int GetPressDikeyList( vector<BYTE> &keyListOut );
	int GetPressKeyList( vector<char> &keyListOut );
	char GetPressKey(){	//	�ŏ��̈����
		vector<char> keylist;
		if ( GetPressKeyList(keylist) == 0 )
			return EOF;
		else
			return keylist[0];
	}

	//	Update()�K�v
	int GetOnDikey();
	int GetOnDikey( BYTE nDik );
	int GetOnKey();
	int GetOnKey( char cAsciiKeyCode );
};


#endif//__MglKeyboardInput_H__