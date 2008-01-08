#ifndef __MglJoyInput_H__
#define __MglJoyInput_H__

//#include "CMglJoyManager.h"

#define ERR_STICK_VALUE		(0xFFFFFFFF)

//	�N���X�錾
class DLL_EXP CMglJoyInput
{
protected:
	//DIDEVCAPS m_devCaps;
	IDirectInputDevice8* m_pDevice;	//	Attach����邾���Ȃ̂ŊJ���͂��Ȃ����

	//	JOY�̐ݒ�
	long m_nNeutralX;
	long m_nNeutralY;
	long m_nMargin;
	BOOL m_bJoySetupFlg;

	void Acquire();

	void CHKINIT(){ if(m_pDevice==NULL) MyuThrow( 2121, "CMglJoyInput::Attach()�����s���Ă��������B" ); }
	void CHKINFOSET(){ if(m_bJoySetupFlg!=TRUE) MyuThrow( 2121, "CMglJoyInput::SetJoyStickInfo()�����s���Ă��������B" ); }

public:
	//	�R���X�g���N�^�ƃf�X�g���N�^
	CMglJoyInput();
	virtual ~CMglJoyInput();

	//	Attach����
	void Attach( IDirectInputDevice8* pDevice ){ m_pDevice = pDevice; }

	//	�e�擾���\�b�h
	BOOL IsPushBotton( int nBottomNo );
	BOOL IsUp();
	BOOL IsDown();
	BOOL IsLeft();
	BOOL IsRight();
	BOOL GetX( long* pnX );
	BOOL GetY( long* pnY );

	DIJOYSTATE2* GetState( DIJOYSTATE2* pStateBuf );

	//	Joy�̐ݒ�
	void SetJoyStickInfo( long nNeutralX, long nNeutralY, long nMargin )
	{
		m_nNeutralX = nNeutralX;
		m_nNeutralY = nNeutralY;
		m_nMargin = nMargin;
		m_bJoySetupFlg = TRUE;
	}

	//	���� DIJOYSTATE2 ���擾
};

#endif//__MglJoyInput_H__
