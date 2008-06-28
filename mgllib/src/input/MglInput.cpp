#include "stdafx.h"
#include "MglInput.h"
#include "MyuFunctions.h"
#include "MyuDebugLog.h"

#define GET_MSGNO(V)	(MGLMSGNO_INPUT((V)+0x0300))

//	������錾
#define JOY_FIRST_STR	"JOY"
#define JOY_BOTTON_STR	"BTN"
#define KB_FIRST_STR	"KBD"
#define KB_FIRST_STR2	"KB"

//	�R���X�g���N�^
CMglInput::CMglInput()
{
	m_bInitFlg = FALSE;
	SetEtClass("CMglInput");
}

//	�f�X�g���N�^
CMglInput::~CMglInput()
{

}

//	����������
void CMglInput::Init( HWND hWnd, DWORD dwCooperativeFlag )
{
	//	�`�F�b�N
	if ( m_bInitFlg == TRUE )
		MglThrow( GET_MSGNO(9), "CMglInput::Init()  ���̃��\�b�h�͊��ɌĂяo����Ă��܂��B" );

	//	�f�t�H���g��hWnd�擾
	if ( hWnd == NULL )
		hWnd = GetDefaultHwnd();

	m_joyAry.clear();

	//	�e�N���X��������
	//m_keyboard.ExInit( hWnd, dwCooperativeFlag );
	CMglKeyboardInput::Init( hWnd, dwCooperativeFlag );
	m_joyMgr.ExInit( hWnd, dwCooperativeFlag );

	//	Joy��Attach
	for( int i=0; i<m_joyMgr.GetJoyCount(); i++ )
	{
		CMglJoyInput joy;
		joy.Attach( m_joyMgr.GetJoyDevice(i) );
		m_joyAry.push_back(joy);
	}

	//	�L�[�{�[�h�̊֘A�t���z�񐶐�
	//m_keyboard.GenRtAry();

	//	2008/06/28  �}�E�X�Ή�
	mouse.Init(hWnd);

	//	�t���O�𗧂Ă�
	m_bInitFlg = TRUE;
}

//	���̓��͂���������Ă����Ԃɂ��邩
//	�`���FJOY0-BTN0, KBD-A, KBD-ESC
BOOL CMglInput::IsOn( const char* szInputName )
{
	SetEtMethod("IsOn");

	if ( m_bInitFlg != TRUE )
		MglThrow( GET_MSGNO(9), "Init()�����s����܂ł��̃��\�b�h���Ăяo�����Ƃ͏o���܂���B" );

	//	�啶���������𑵂���
	char szWorkInputName[256];
	safe_strcpy( szWorkInputName, szInputName, sizeof(szWorkInputName) );
	strtoupper( szWorkInputName, szWorkInputName );

	const char *pSz = szWorkInputName;

	//	Joy�n�H
	if ( strncmp( pSz, JOY_FIRST_STR, strlen(JOY_FIRST_STR) ) == 0 )
	{
		pSz += strlen(JOY_FIRST_STR);

		//	���Ԃ́H
		int nJoyDevNum = *pSz - '0';
		if ( nJoyDevNum < 0 || nJoyDevNum > 9 )
			MglThrow( GET_MSGNO(1), "szInputName \"%s\" �͕s���ł��B", szInputName );
		pSz++;

		//	"-"��"_"�ɂȂ��Ă��邩�`�F�b�N
		if ( *pSz != '_' && *pSz != '-' )
			MglThrow( GET_MSGNO(2), "szInputName \"%s\" �͕s���ł��B", szInputName );
		pSz++;

		//	����Joy���Ă���̂��H
		CHKJOYNO(nJoyDevNum);

		return IsOnJoy( &m_joyAry[nJoyDevNum], pSz );
	}

	//	�L�[�{�[�h�n�H
	else if ( strncmp( pSz, KB_FIRST_STR, strlen(KB_FIRST_STR) ) == 0 )
	{
		pSz += strlen(KB_FIRST_STR);

		//	"-"��"_"�ɂȂ��Ă��邩�`�F�b�N
		if ( *pSz != '_' && *pSz != '-' )
			MglThrow( GET_MSGNO(5), "szInputName \"%s\" �͕s���ł��B", szInputName );
		pSz++;

		return IsOnKbd( pSz );
	}
	//	�L�[�{�[�h�n�H2
	else if ( strncmp( pSz, KB_FIRST_STR2, strlen(KB_FIRST_STR2) ) == 0 )
	{
		pSz += strlen(KB_FIRST_STR2);

		//	"-"��"_"�ɂȂ��Ă��邩�`�F�b�N
		if ( *pSz != '_' && *pSz != '-' )
			MglThrow( GET_MSGNO(5), "szInputName \"%s\" �͕s���ł��B", szInputName );
		pSz++;

		return IsOnKbd( pSz );
	}

	else
	{
		MglThrow( GET_MSGNO(9), "szInputName \"%s\" �͕s���ł��B", szInputName );
	}

	return FALSE;
}

//	Joy�̓���
BOOL CMglInput::IsOnJoy( CMglJoyInput* pJoy, const char* szJoyInputName )
{
	const char *pSz = szJoyInputName;

	//	�{�^��
	if ( strncmp( pSz, JOY_BOTTON_STR, strlen(JOY_BOTTON_STR) ) == 0 )
	{
		pSz += strlen(JOY_BOTTON_STR);

		//	�{�^���ԍ�
		int nBottonNo=0;
		if ( ec_atoi( pSz, &nBottonNo ) != TRUE )
			MglThrow( GET_MSGNO(3), "CMglInput::IsOnJoy() JOYx-\"%s\" �͕s���ł��B", szJoyInputName );

		return pJoy->IsPushBotton( nBottonNo );
	}
	else
	{
		//	��������(������)
		if ( strcmp( pSz, "UP" ) == 0 )
			return pJoy->IsUp();
		else if ( strcmp( pSz, "DOWN" ) == 0 )
			return pJoy->IsDown();
		else if ( strcmp( pSz, "LEFT" ) == 0 )
			return pJoy->IsLeft();
		else if ( strcmp( pSz, "RIGHT" ) == 0 )
			return pJoy->IsRight();

		else
			MglThrow( GET_MSGNO(4), "CMglInput::IsOnJoy() JOYx-\"%s\" �͕s���ł��B", szJoyInputName );
		
		return 999;	//	���ۂ͒ʂ�Ȃ�����VC�̃R���p�C�����\������
	}
}

//	�L�[�{�[�h�̓���
BOOL CMglInput::IsOnKbd( const char* szInputName )
{
	const char *pSz = szInputName;

	//	�ꕶ���ȏ゠�邩�̃`�F�b�N
	if ( *pSz == '\0' )
		MglThrow( GET_MSGNO(6), "szInputName (KBD) \"%s\" �͕s���ł��B", szInputName );

	//	�ꕶ�����H��������(������)���H
	BYTE diKeycode = 0x00;
	if ( *(pSz+1) == '\0' )
	{
		//	�ꕶ��
		//char cName = *pSz;
		//diKeycode = m_kbFastRtAry[ cName ];
		//diKeycode = m_keyboard.GetDik(*pSz);
		diKeycode = GetDik(*pSz);

		if ( diKeycode == 0x00 )
			MglThrow( GET_MSGNO(10), "szInputName (KBD) \"%s\" �͕s���ȃL�[�{�[�h������\�����Ă��܂��B", szInputName );
	}
	else
	{

//	�}�N���ŒZ������[
#define STRTODI( NAME, DIKEYCODE )	else if ( strcmp( pSz, NAME ) == 0 ) diKeycode = DIKEYCODE

		//	��������(������)
		if ( 0 == 1 );
		STRTODI( "ESC",				DIK_ESCAPE );
		STRTODI( "ESCAPE",			DIK_ESCAPE );
		STRTODI( "ENTER",			DIK_RETURN );
		STRTODI( "RETURN",			DIK_RETURN );
		STRTODI( "SPACE",			DIK_SPACE );
		STRTODI( "LCTRL",			DIK_LCONTROL );
		STRTODI( "DIK_LCONTROL",	DIK_LCONTROL );

		STRTODI( "UP",		DIK_UP );
		STRTODI( "DOWN",	DIK_DOWN );
		STRTODI( "LEFT",	DIK_LEFT );
		STRTODI( "RIGHT",	DIK_RIGHT );

#undef STRTODI

		else
			MglThrow( GET_MSGNO(11), "szInputName (KBD) \"%s\" �͕s���ȃL�[�{�[�h������\�����Ă��܂��B", szInputName );
	}

	//	����Ƃ����X�e�[�g���擾
	//m_keyboard.UpdateStateBuf();	//	1000�񂭂炢���s���Ă��S�R���C������
	CMglKeyboardInput::UpdateStateBuf();	//	1000�񂭂炢���s���Ă��S�R���C������
	//return m_keyboard.IsOnKey( diKeycode );
	return CMglKeyboardInput::IsPressKey( diKeycode );
}

//	�����ꂽ�u�ԂȂ�TRUE���A�����łȂ��ꍇ��FALSE��Ԃ�
BOOL CMglInput::GetIsOnEvent( const char* szInputName )
{
	EVEMAP_ITR itrEveMap = m_onEventMap.find( szInputName );

	//	�Ƃ肠�����擾���Ƃ�
	BOOL bNowFlg = IsOn( szInputName );

	//	����H
	if ( itrEveMap != m_onEventMap.end() )
	{
		BOOL bPrevFlg = itrEveMap->second;
		if ( bPrevFlg == TRUE )
		{
			//	�O���TRUE
			m_onEventMap[szInputName] = bNowFlg;
			return FALSE;
		}
		else
		{
			//	�O���FALSE
			m_onEventMap[szInputName] = bNowFlg;
			return bNowFlg;
		}
	}
	else
	{
		//	����Ȃ̂Ŏ擾���ꂽ�l�����̂܂ܕ��A
		m_onEventMap[szInputName] = bNowFlg;	//	�L��
		return bNowFlg;
	}
}

//	�C�x���g�̐ݒ�
void CMglInput::SetOnEvent( const char* szInputName, BOOL bEvent )
{
	EVEMAP_ITR itrEveMap = m_onEventMap.find( szInputName );

	//	����܂���I
	if ( itrEveMap == m_onEventMap.end() )
		MglThrow( GET_MSGNO(7), "szInputName \"%s\" �͑��݂��܂���B", szInputName );

	m_onEventMap[szInputName] = bEvent;
}

//	Joy�̐ݒ�
void CMglInput::SetJoyStickInfo( int nDeviceNo, long nNeutralX, long nNeutralY, long nMargin )
{
	CHKJOYNO(nDeviceNo);
	m_joyAry[nDeviceNo].SetJoyStickInfo( nNeutralX, nNeutralY, nMargin );
}
