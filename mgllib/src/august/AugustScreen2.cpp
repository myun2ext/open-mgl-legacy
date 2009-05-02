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

/*
//	�R���X�g���N�^
CAugustScreen2::CAugustScreen2()
{
}

//	�f�X�g���N�^
CAugustScreen2::~CAugustScreen2()
{
}
*/

//////////////////////////////////////////////////

//�\������O����������ƁA���̊֐����Ă΂��
void _MglAugust2_se_translator_function(unsigned int code, struct _EXCEPTION_POINTERS* ep)
{
	throw ep; //�W��C++�̗�O�𔭐�������
}

bool CAugustScreen2::ThreadFunc()
{
	m_bEndFlg = false;

	if ( OnInitFirst() == false )
		return false;

	_set_se_translator(_MglAugust2_se_translator_function);

	//__try{
		try	//	��O�����󂯕t���J�n
		{
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

			MainLoop();
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
	//if ( m_bEnabledAudio )	<- �ʂ�Init���ĂȂ��Ȃ炵�ĂȂ���Release���Ă����Ȃ���łˁE�E�E�H
/*	audio.Release();
	input.Release();
	input.FinalRelease();
	m_txtDebug.Release();*/
	m_grp.Release();

	m_bEndFlg = false;

	return true;
}

void CAugustScreen2::MainLoop()
{
	for(;;)
	{
		DoFrame();

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

	//	�X�v���C�g�I��
	m_grp.GetMglGrp()->SpriteEnd();

	//	�X�N���[���̃A�b�v�f�[�g
	m_grp.GetMglGrp()->UpdateScreen();

	//	�҂��
	m_fps.DoWait();

	//	�L�[�{�[�h���͂̍X�V
	/*input.Update();

	if ( m_bEscEnd ){
		if ( input.GetOnKey(ASCII_ESC) )
			return FALSE;
	}*/

	//	�X�v���C�g�J�n
	m_grp.GetMglGrp()->SpriteBegin();

	return true;
}

bool CAugustScreen2::OnClose()
{
	m_bEndFlg = true;
	return true;
}

void CAugustScreen2::OnDraw()
{

	m_grp.OnDraw();
}

//	�t���[������
bool CAugustScreen2::DoFrame()
{
	//	2009/01/23 �}�E�X�̃n���h���͖����ɏo����悤�ɁB
	//	�i���\�����������A��������N���b�N�Ƃ��ŗ]�v�ȏ�������Ƃ܂������E�E�E�j
	if ( m_bUseMouseHandle == true )
	{
		//OnFrameMouseInput();	//	�Ȃ񂩏E��Ȃ���false��Ԃ��d�l�ɂȂ��Ă���ۂ��E�E�E
		/*if ( OnFrameMouseInput() != true )
			return false;*/
	}

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
		it->OnFrame();
		//(*it)->OnFrame();
		//((CControlBase*)it)->OnFrame();
		//m_ctrlPtrAry[i]->OnFrame();
		//GetVCtrlPtr(i)->Draw();
	}

	return true;
}
