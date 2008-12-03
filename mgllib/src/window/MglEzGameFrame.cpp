#include "stdafx.h"
#include "MglEzGameFrame.h"
#include "MyuFunctions.h"

/*
//	static�ϐ��̎���
MGL_EZGAME_FRAME_FUNCPTR	CMglEzGameFrame::m_userMainThread;
CMyuEzWindow		CMglEzGameFrame::m_window;
CMglText	CMglEzGameFrame::m_txtFps;
CMglText	CMglEzGameFrame::m_txtDebug;
CMglGraphicManager		CMglEzGameFrame::grp;
CMyuFPS				CMglEzGameFrame::fps;
CMglInput			CMglEzGameFrame::input;
string	CMglEzGameFrame::m_strCaption;
string	CMglEzGameFrame::m_strDebugText;
int		CMglEzGameFrame::m_nWidth=0;
int		CMglEzGameFrame::m_nHeight=0;
BOOL	CMglEzGameFrame::m_bFpsShow = TRUE;
*/
int		CMglEzGameFrame::ms_nInstanceCount=0;

//	MainMethod���Ăяo��
/*DWORD CallMainThread( DWORD dwInstancePtr )
{
	CMglEzGameFrame *pInstance = (CMglEzGameFrame*)(dwInstancePtr);
	return (DWORD)( pInstance->PrivateMainMethod() );
}*/

//	�������g�̃��C���X���b�h���Ăяo��
DWORD CallMainThread( CMglEzGameFrame *pFrameInstance )
{
	return (DWORD)( pFrameInstance->PrivateMainMethod() );
}

//	2008/01/22  ���[�U�p�����[�^�Ή�
typedef struct {
	CMglEzGameFrame *pFrameInstance;
	DWORD dwUserParam;
}
CALL_THREAD_EX_PARAM;

//
DWORD CallMainThreadEx( CALL_THREAD_EX_PARAM *pParam )
{
	return (DWORD)( pParam->pFrameInstance->PrivateMainMethod(pParam->dwUserParam) );
}


//	�R���X�g���N�^
CMglEzGameFrame::CMglEzGameFrame()
{
	ms_nInstanceCount++;
	//m_strCaption = "MGL Apprication";
	m_bBreak = FALSE;
	m_bEscEnd = FALSE;
	m_bFpsShow = FALSE;	//	2007/01/02 ���������̂�����ǁc
	m_bFullscreen = FALSE;
	m_bEnabledAudio = FALSE;
}

//	�f�X�g���N�^
CMglEzGameFrame::~CMglEzGameFrame()
{
	ms_nInstanceCount--;
}

//	�E�C���h�E�̊J�n
int CMglEzGameFrame::StartWindowEx( int nWinWidthSize, int nWinHeightSize,
//	MGL_EZGAME_FRAME_FUNCPTR mainThreadFuncPtr )
	LPTHREAD_START_ROUTINE mainThreadFuncPtr, void* threadFuncParam, const char *szWindowTitle, BOOL bFullscreen )
{
	_MGL_DEBUGLOG("StartWindowEx() start." );
	CMglStackInstance("CMglEzGameFrame::StartWindowEx");

	if ( ms_nInstanceCount >= 2 )
	{
		::MessageBox( NULL, "CMglEzGameFrame �̃C���X�^���X����������܂��B", "MyuGameLibrary", MB_ICONERROR );
		return -1;
	}
	
	m_nWidth = nWinWidthSize;
	m_nHeight = nWinHeightSize;
	m_userMainThread = mainThreadFuncPtr;
	m_bFullscreen = bFullscreen;
	m_bBreak = FALSE;

	//	��ʃT�C�Y�擾
	int nScreenWidth=0;
	int nScreenHeight=0;
	int nWinStartPosX=100;
	int nWinStartPosY=150;
	if ( GetScreenSize( &nScreenWidth, &nScreenHeight ) == TRUE )
	{
		nWinStartPosX = (nScreenWidth/2)-(m_nWidth/2);
		nWinStartPosY = (nScreenHeight/2)-(m_nHeight/2)-16;
	}

	if ( m_strWindowClassName == "" ){
		//	WindowClass�������i"MGL Appllication WindowClass"�{�^�C�g���j
		m_strWindowClassName = "MGL Appllication WindowClass";
		m_strWindowClassName += szWindowTitle;
		/*string strWindowClassName = "MGL Appllication WindowClass";
		strWindowClassName += szWindowTitle;*/
	}

	CALL_THREAD_EX_PARAM param;
	param.pFrameInstance = this;
	param.dwUserParam = (DWORD)threadFuncParam;

	//	�Ȉ�Window�����Ăяo��
	_MGL_DEBUGLOG("m_window.StartWindow()" );
	return m_window.StartWindow(
		szWindowTitle, m_strWindowClassName.c_str(),
		nWinStartPosX, nWinStartPosY, m_nWidth, m_nHeight,
		WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		(LPTHREAD_START_ROUTINE)CallMainThreadEx, &param );
//		(LPTHREAD_START_ROUTINE)CallMainThread, (DWORD)(this) );
}

//	�X���b�h
int CMglEzGameFrame::PrivateMainMethod(){
	return PrivateMainMethod((DWORD)this);
}

//�\������O����������ƁA���̊֐����Ă΂��
void se_translator_function(unsigned int code, struct _EXCEPTION_POINTERS* ep)
{
	throw ep; //�W��C++�̗�O�𔭐�������
}

//	�X���b�h - 2008/01/22
int CMglEzGameFrame::PrivateMainMethod(DWORD dwUserThreadParam)
{
	_set_se_translator(se_translator_function);

	//__try{
		try	//	��O�����󂯕t���J�n
		{
			_MGL_DEBUGLOG("+ CMglEzGameFrame::PrivateMainMethod()" );
			CMglStackInstance("CMglEzGameFrame::PrivateMainMethod");

			_MGL_DEBUGLOG("CoInitialize()..." );
			CoInitialize(NULL);

			_MGL_DEBUGLOG("grp.Init()..." );
			grp.Init( m_window.GetWindowHandle(), m_nWidth, m_nHeight, m_bFullscreen );
			grp.Clear();

			//	2008/10/14
			OnGraphicInitializeEnded();

			_MGL_DEBUGLOG("input.Init()..." );
			input.Init( m_window.GetWindowHandle() );

			//	2008/11/29
			_MGL_DEBUGLOG("audio.Init()..." );
			//audio.Init( m_window.GetWindowHandle() );

			m_txtDebug.InitAndEzCreate( &grp, 14 );
			m_txtFps.InitAndEzCreate( &grp, 14 );
			//fps.SetFPS(60); <- ����ɏ㏑�������Ⴞ�߁I�Ă��f�t�H���g60�Ȃ��Ă邵
			//grp.Clear();

			//	MGL S3.1����͌Ăяo�������ɂ���i���[�v�͂��̒��ł���Ă��炤�j- 2006/11/25
			_MGL_DEBUGLOG("Call User MainMethod." );
			m_userMainThread((void*)dwUserThreadParam);
			//�� ����ς�� -> �Ȃ��I�i�ǂ�������F�΁j

			/*
			//	MGL 3.0�܂�
			for(;;)
			{
				//	���[�U���\�b�h���Ăяo��
				//if ( m_userMainThread() == 1 )
				//if ( m_userMainThread(this) == FALSE )
				if ( m_userMainThread(this) == TRUE )
					break;

				//	�t���[�����҂��
				if ( DoFpsWait() == FALSE )
					break;
			}
			*/
		}
		//	��O���� V3.0
		catch( MglException exp )
		{
			char work[1024];
			snprintf( work, sizeof(work),
				"Myu Game Library Error :\r\n"
				"  Location : %s::%s()   Error Code : 0x%08X\r\n"
				"\r\n"
				"%s",
				exp.szClass, exp.szMethod, exp.nInternalCode, exp.szMsg );

			::MessageBox( NULL, work, NULL, MB_ICONERROR );
		}
		//	��O����
		catch( MyuCommonException except )
		{
			char work[512];
			//snprintf( work,sizeof(work), "ErrNo : 0x%08X\r\n%s", except.nErrCode, except.szErrMsg );
			snprintf( work,sizeof(work),
				"ErrNo : 0x%08X\r\n%s\r\n"
				"\r\n"
				"%s",
				except.nErrCode, except.szErrMsg,
				g_stackTrace.Dump().c_str() );
			::MessageBox( NULL, work, NULL, MB_ICONERROR );
		}
#ifndef _DEBUG
		//	VC++�̗�O��
		catch(_EXCEPTION_POINTERS *ep)
		{
			//_EXCEPTION_POINTERS *ep = GetExceptionInformation();
			PEXCEPTION_RECORD rec = ep->ExceptionRecord;

			switch(rec->ExceptionCode){
			case 0xc0000094:
				::MessageBox( NULL, "0 �ŏ��Z����܂����B", NULL, MB_ICONERROR ); break;
			}

			char work[1024];
			snprintf(work,sizeof(work), ("�����A�N�Z�X�ی�ᔽ�ł��B\r\n"
					"code:%x flag:%x addr:%p params:%d\n"),
				rec->ExceptionCode,
				rec->ExceptionFlags,
				rec->ExceptionAddress,
				rec->NumberParameters
			);
			::MessageBox( NULL, work, NULL, MB_ICONERROR );
		}
		//	VC++�̗�O��
		catch(...)
		{
			::MessageBox( NULL, "fdssdff", NULL, MB_ICONERROR );
		}
#endif//_DEBUG
	/*}
	__except(_EXCEPTION_POINTERS *ep = GetExceptionInformation())
	{
		_EXCEPTION_POINTERS *ep = GetExceptionInformation();
		PEXCEPTION_RECORD rec = ep->ExceptionRecord;

		char work[1024];
		snprintf(work,sizeof(work), ("�����A�N�Z�X�ی�ᔽ�ł��B\r\n"
				"code:%x flag:%x addr:%p params:%d\n"),
			rec->ExceptionCode,
			rec->ExceptionFlags,
			rec->ExceptionAddress,
			rec->NumberParameters
		);
		::MessageBox( NULL, work, NULL, MB_ICONERROR );
	}*/

	//	��try-catch���łȂ��Ă����̂��c�H
	//	�����ŊJ�����Ƃ��Ȃ��ƃX���b�h�O�ŊJ������ė�����
	audio.Release();
	input.Release();
	input.FinalRelease();
	m_txtDebug.Release();
	grp.Release();

	CoUninitialize();

	return 0;
}

//	�L�����ǂ������A���܂��iFALSE�ɂȂ�����I�����邱�ƁI�j
BOOL CMglEzGameFrame::DoFpsWait()
{
	//	�E�C���h�E�������Ă邩�̃`�F�b�N
	if ( m_window.IsAlive() != TRUE )
		return FALSE;

	//	������H
	if ( m_bBreak )
		return FALSE;

	//	FPS/�f�o�b�O������o��
	if ( m_bFpsShow == TRUE )
	{
		char szFps[64];
		sprintf( szFps, "FPS : %.01f", fps.GetAveFps() );
		m_txtFps.Draw( szFps, 6, 6, D3DCOLORW_XRGB(0,0,0) );
		m_txtFps.Draw( szFps, 5, 5, D3DCOLORW_XRGB(255,255,255) );
	}
	m_txtDebug.Draw( m_strDebugText.c_str(), 6, 21, D3DCOLORW_XRGB(0,0,0) );
	m_txtDebug.Draw( m_strDebugText.c_str(), 5, 20, D3DCOLORW_XRGB(255,255,255) );

	//	�X�v���C�g�I��
	grp.SpriteEnd();

	//	�X�N���[���̃A�b�v�f�[�g
	grp.UpdateScreen();

	//	�҂��
	fps.Sleep();

	//	�L�[�{�[�h���͂̍X�V
	input.Update();

	if ( m_bEscEnd ){
		if ( input.GetOnKey(ASCII_ESC) )
			return FALSE;
	}

	//	�X�v���C�g�J�n
	grp.SpriteBegin();

	return TRUE;
}

//	�E�C���h�E�^�C�g���̐ݒ�
//void CMglEzGameFrame::SetWindowTitle( const char *szCaption ){ m_strCaption = szCaption; }

//	�f�o�b�O�o��
void CMglEzGameFrame::PrintDebug( const char* szFormat, ... )
{
	char work[512];
	va_list vl;
	va_start( vl, szFormat );
	vsnprintf( work, sizeof(work), szFormat, vl );
	va_end( vl );
	m_strDebugText = work;
}
