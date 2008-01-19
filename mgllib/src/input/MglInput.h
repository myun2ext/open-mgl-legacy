#ifndef __MglInput_H__
#define __MglInput_H__

#include "MglKeyboardInput.h"
#include "MglJoyManager.h"
#include "MglJoyInput.h"
#include "MglMouseInput.h"

//	�֘A�t���z��p�A�C�e��
typedef struct {
	char cName;
	BYTE diKeycode;
} KB_FAST_RT_ARY_ITEM;


//	�N���X�錾
class DLL_EXP CMglInput : public CMglExceptionThrowerBase, public CMglKeyboardInput
{
protected:
	//	�e�f�o�C�X�̃N���X
	//CMglKeyboardInput m_keyboard;
	CMglJoyManager m_joyMgr;
	vector<CMglJoyInput> m_joyAry;

	//	�������t���O
	BOOL m_bInitFlg;

	//	OnEvent�p
	map<string,BOOL> m_onEventMap;
	typedef map<string,BOOL>::iterator EVEMAP_ITR;
	//	�������\�b�h
	//void GenRtAry(); -> CMglKeyboardInput �ֈړ� (2007/01/01)
	BOOL IsOnJoy( CMglJoyInput* pJoy, const char* szJoyInputName );
	BOOL IsOnKbd( const char* szInputName );
	void CHKJOYNO( int n ){ if(n>=m_joyAry.size()) MyuThrow( 0343, "%d ��JOY�͑��݂��܂���B" ); }

public:
	//	�R���X�g���N�^�ƃf�X�g���N�^
	CMglInput();
	virtual ~CMglInput();

	//	������
	void Init( HWND hWnd=NULL, DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND );
	/*void Init( DWORD dwCooperativeFlag=DISCL_NONEXCLUSIVE|DISCL_FOREGROUND ){
		Init( GetDefaultHwnd(), dwCooperativeFlag ); }*/

	//	���擾
	BOOL IsOn( const char* szInputName );			//	���݉�����Ă��邩
	BOOL GetIsOnEvent( const char* szInputName );	//	�����ꂽ�u�Ԃ��擾
	void ResetOnEvent( const char* szInputName ){ SetOnEvent( szInputName, FALSE ); }
	void SetOnEvent( const char* szInputName, BOOL bEvent );	//	�C�x���g�̐ݒ�

	//	�g���ݒ�
	void SetJoyStickInfo( int nDeviceNo, long nNeutralX, long nNeutralY, long nMargin );

	/*	�X�e�[�^�X�𖈉�X�V���Ȃ��悤�Ƀ��b�N���� (������)
	void StateUpdateLock();
	*/

	void KeyboardUpdate(){ CMglKeyboardInput::Update(); }

	//	���t�@�����X�̎擾
	int GetJoyCount(){ return m_joyAry.size(); }
	CMglJoyInput& GetJoyRef( int nDeviceNo ){ CHKJOYNO(nDeviceNo); return m_joyAry[nDeviceNo]; }
};

#endif//__MglInput_H__
