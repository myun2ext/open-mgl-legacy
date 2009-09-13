//////////////////////////////////////////////////////////
//
//	AugustScreen2
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustScreen2.h"
#include "MglGraphicManager.h"
#include "MyuFPS.h"


//#define _NO_CATCH_EXCEPTION		//	�f�o�b�O��ƒ��ɁA��O���L���b�`���������Ȃ��ꍇ�ɗL���ɂ���


using namespace agh;
using namespace std;

//////////////////////////////////////////////////

CAugustFpsManager::CAugustFpsManager()
{
	m_pInternal = new CMyuFPS();
}

CAugustFpsManager::~CAugustFpsManager()
{
	delete m_pInternal;
}

void CAugustFpsManager::SetFps(int nFps){
	m_pInternal->SetFPS(nFps);
}
float CAugustFpsManager::GetAveFps(){
	return m_pInternal->GetAveFps();
}
float CAugustFpsManager::GetFps(){
	return m_pInternal->GetFps();
}

void CAugustFpsManager::DoWait(){
	m_pInternal->Sleep();
}

//////////////////////////////////////////////////


#define m_hWnd (HWND)m_vphWnd



//�\������O����������ƁA���̊֐����Ă΂��
void _MglAugust2_se_translator_function(unsigned int code, struct _EXCEPTION_POINTERS* ep)
{
	throw ep; //�W��C++�̗�O�𔭐�������
}


/*	DLL���A�_���I��΁I�I

//	�R���X�g���N�^
CAugustScreen2::CAugustScreen2()
{
}

//	�f�X�g���N�^
CAugustScreen2::~CAugustScreen2()
{
}
*/

///////////////////////////////////////////////////////


bool CAugustScreen2::ThreadFunc(int anyParam)
{
	m_bEndFlg = false;

	_set_se_translator(_MglAugust2_se_translator_function);

	///////////////////////////////////////////

	//	2009/05/17  ����
	bool bRet = ThreadFuncMain();

	///////////////////////////////////////////

	m_grp.Release();

	//m_bEndFlg = false; <- �Ⴍ�Ȃ��H
	m_bEndFlg = true;

	ExitWindow();

	return bRet;
}

bool CAugustScreen2::ThreadFuncMain()
{
	/*
	m_bEndFlg = false;

	_set_se_translator(_MglAugust2_se_translator_function);
	*/

	///////////////////////////////////////////////////////////

	//__try{
	{
#ifndef _NO_CATCH_EXCEPTION
		try	//	��O�����󂯕t���J�n
#endif
		{
			if ( OnInit() == false )
				return false;

			if ( OnInitFirst() == false )
				return false;

			CMglStackInstance("CAugustEzGameFrame::PrivateMainMethod");

			m_grp.Init();

			//	���[�U�R�[���o�b�N
			if ( OnGraphicInitEnded() == false )
				return false;

			/*
			_MGL_DEBUGLOG("input.Init()..." );
			input.Init( m_window.GetWindowHandle() );
			_MGL_DEBUGLOG("input.Init() end." );

			//	2008/11/29
			if ( m_bEnabledAudio ){
				_MGL_DEBUGLOG("audio.Init()..." );
				InitAudio();
				_MGL_DEBUGLOG("audio.Init() end." );
			}

			_MGL_DEBUGLOG("Create Debug/FPS Fonts..." );
			//m_txtDebug.InitAndEzCreate( &grp, 14 );
			//m_txtFps.InitAndEzCreate( &grp, 14 );
			m_txtDebug.Init( &grp );
			m_txtFps.Init( &grp );
			m_txtDebug.Create( 14 );
			m_txtFps.Create( 14 );
			//fps.SetFPS(60); <- ����ɏ㏑�������Ⴞ�߁I�Ă��f�t�H���g60�Ȃ��Ă邵
			//grp.Clear();
			_MGL_DEBUGLOG("end." );

			//	2009/01/23  CAugustWindow����OnInit()�Ăяo��
			_MGL_DEBUGLOG("EzFrame_OnInit()..." );
			EzFrame_OnInit();

			//	MGL S3.1����͌Ăяo�������ɂ���i���[�v�͂��̒��ł���Ă��炤�j- 2006/11/25
			_MGL_DEBUGLOG("Call User MainMethod." );
			m_userMainThread((void*)dwUserThreadParam);
			//�� ����ς�� -> �Ȃ��I�i�ǂ�������F�΁j
			*/

			//	���[�U�R�[���o�b�N
			if ( OnInited() == false )
				return false;

			MainLoop();
		}
#ifndef _NO_CATCH_EXCEPTION
		//	��O���� V3.0
		catch( MglException& exp )
		{
			char work[1024];
			snprintf( work, sizeof(work),
				"Myu Game Library Error :\r\n"
				"  Location : %s::%s()   Error Code : 0x%08X\r\n"
				"\r\n"
				"%s",
				exp.szClass, exp.szMethod, exp.nInternalCode, exp.szMsg );

			::MessageBox( m_hWnd, work, NULL, MB_ICONERROR );
		}
		//	��O����
		catch( MyuCommonException& except )
		{
			char work[512];
			//snprintf( work,sizeof(work), "ErrNo : 0x%08X\r\n%s", except.nErrCode, except.szErrMsg );
			snprintf( work,sizeof(work),
				"ErrNo : 0x%08X\r\n%s\r\n"
				"\r\n"
				"%s",
				except.nErrCode, except.szErrMsg,
				g_stackTrace.Dump().c_str() );
			::MessageBox( m_hWnd, work, NULL, MB_ICONERROR );
		}
		//	��O����
		catch( AugustException& except )
		{
			char work[1024+200];
			//snprintf( work,sizeof(work), "ErrNo : 0x%08X\r\n%s", except.nErrCode, except.szErrMsg );
			snprintf( work,sizeof(work),
				"ErrNo : 0x%08X\r\n"
				"\r\n"
				"%s",
				except.nCode, except.szMsg );
			::MessageBox( m_hWnd, work, NULL, MB_ICONERROR );
		}
		//	��O����
		catch( MglException2& e )
		{
			char work[2048+600];
			//snprintf( work,sizeof(work), "ErrNo : 0x%08X\r\n%s", except.nErrCode, except.szErrMsg );
			snprintf( work,sizeof(work),
				"ErrNo : 0x%08X"
				"\r\n\r\n"
				"%s"
				"\r\n\r\n"
				"File(Line):\r\n"
				"%s(%d)"
				,
				e.nErrCode, e.szErrMsg, e.szpFile, e.nLine );
			::MessageBox( m_hWnd, work, NULL, MB_ICONERROR );
		}
#ifndef _DEBUG
		//	VC++�̗�O��
		catch(_EXCEPTION_POINTERS *ep)
		{
			//_EXCEPTION_POINTERS *ep = GetExceptionInformation();
			PEXCEPTION_RECORD rec = ep->ExceptionRecord;

			switch(rec->ExceptionCode){
			case 0xc0000094:
				::MessageBox( m_hWnd, "0 �ŏ��Z����܂����B", NULL, MB_ICONERROR ); break;
			}

			char work[1024];
			snprintf(work,sizeof(work), ("�����A�N�Z�X�ی�ᔽ�ł��B\r\n"
					"code:%x flag:%x addr:%p params:%d\n"),
				rec->ExceptionCode,
				rec->ExceptionFlags,
				rec->ExceptionAddress,
				rec->NumberParameters
			);
			::MessageBox( m_hWnd, work, NULL, MB_ICONERROR );
		}
		//	VC++�̗�O��
		catch(...)
		{
			::MessageBox( m_hWnd, "fdssdff", NULL, MB_ICONERROR );
		}
#endif//_DEBUG
#endif//_NO_CATCH_EXCEPTION
	}
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
	//if ( m_bEnabledAudio )	<- �ʂ�Init���ĂȂ��Ȃ炵�ĂȂ���Release���Ă����Ȃ���łˁE�E�E�H
/*	audio.Release();
	input.Release();
	input.FinalRelease();
	m_txtDebug.Release();*/

	///////////////////////////////////////////////////////////

	/*
	m_grp.Release();

	//m_bEndFlg = false; <- �Ⴍ�Ȃ��H
	m_bEndFlg = true;

	ExitWindow();
	*/

	PreWindowCloseRelease();

	return true;
}

void CAugustScreen2::PreWindowCloseRelease()
{
	for(int i=0; i<m_releaseList.size(); i++)
		m_releaseList[i]->Release();
}

void CAugustScreen2::MainLoop()
{
	for(;;)
	{
		if ( DoFrame() == false )
			break;

		//	�t���[�����҂��
		if ( DoFpsWait() == false )
			break;
	}
}

//	�L�����ǂ������A���܂��iFALSE�ɂȂ�����I�����邱�ƁI�j
bool CAugustScreen2::DoFpsWait()
{
	//	�E�C���h�E�������Ă邩�̃`�F�b�N
	//if ( m_window.IsAlive() != TRUE )
	if ( m_bEndFlg )
		return false;

	/*
	//	������H
	if ( m_bBreak )
		return FALSE;
	*/

	m_grp.FrameEnd();

	//	�҂��
	m_fps.DoWait();

	//	�L�[�{�[�h���͂̍X�V
	/*input.Update();

	if ( m_bEscEnd ){
		if ( input.GetOnKey(ASCII_ESC) )
			return FALSE;
	}*/

	m_grp.FrameStart();

	return true;
}

//	����[
bool CAugustScreen2::OnClose()
{
	m_bEndFlg = true;
	return true;
}

//	�`��[
void CAugustScreen2::OnDraw()
{
	//	CAugustGraphicsManager �� CControlBase ���p�������N���X�Ȃ�ł��˂��[�B
	m_grp.OnDraw();
}

//	�t���[������
bool CAugustScreen2::DoFrame()
{
	//m_grp.OnDraw();	//	�Ƃ肠�����[	//	2009/05/17 �R�����g�A�E�g

	//	�L�[�{�[�h�̃n���h������
	/*if ( OnFrameKeyboardInput() != true )
		return false;*/

	//	2008/11/02 ���[�U�C�x���g����
	if ( OnFrameDoUser() != true )
		return false;

	//	�e�R���g���[���̃t���[������
	//for(int i=0; i<m_ctrlPtrAry.size(); i++)
	//for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	for(citr it=cbegin(); it != cend(); it++)
	//for(vector<CControlBase*>::iterator it=cbegin(); it != cend(); it++)
	{
		if ( it->OnFrame() == false )
			return false;
		//(*it)->OnFrame();
		//((CControlBase*)it)->OnFrame();
		//m_ctrlPtrAry[i]->OnFrame();
		//GetVCtrlPtr(i)->Draw();

		/*	2009/05/10  �������x�I�ɂ̓A�������ǁAOnFrame()���S�ďI����Ă���OnDraw()�Ăяo�����ق��������ł��傤�E�E�E
		if ( it->IsVisual() )
			((agh::CVisualControlBase*)it.get())->OnDraw();
			//((agh::CVisualControlBase*)it.operator ->())->OnDraw();
		*/
	}

	this->OnDraw();

	//	�e�R���g���[���̃t���[������
	//for(int i=0; i<m_ctrlPtrAry.size(); i++)
	//for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	for(vcitr it2=vcbegin(); it2 != vcend(); it2++)
	//for(vector<CControlBase*>::iterator it=cbegin(); it != cend(); it++)
	{
		it2->OnDraw();
	}

	return true;
}

