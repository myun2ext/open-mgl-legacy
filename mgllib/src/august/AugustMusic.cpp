//////////////////////////////////////////////////////////
//
//	AugustMusic
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustMusic.h"

#include "MglCoManager.h"
#include "AugustScreen2.h"

using namespace agh;
using namespace std;

///////////////////////////////////////////////////////////////////////

//	�R���X�g���N�^
CAugustMusic::CAugustMusic()
 : _BASE ("CAugustMusic")
{
	m_pCore = new _MGL_AUGUST_MUSIC_CORE_IMPL();
}

//	�f�X�g���N�^
CAugustMusic::~CAugustMusic()
{
	delete m_pCore;
}

//	�o�^����Init���Ăяo��
void CAugustMusic::OnRegist()
{
	//CoInitialize(NULL);
	g_coManager.Init();

	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_ROOT_WINDOW_HWND),
		"CAugustMusic::OnRegist()  �E�C���h�E�n���h����GetValPtr()�Ɏ��s");

#ifdef _AGM_USE_INHERIT
	CMglBgm::Init(hWnd);
#else
	m_pCore->Init(hWnd);
#endif

	//	2009/09/05  �E�C���h�E�����O��Release���Ă��炤�悤�ɂ���
	CAugustScreen2_X* pScreen = (CAugustScreen2_X*)MyuAssertNull(GetValPtr(AUGUST_VALKEY_SCREEN),
		"CAugustMusic::OnRegist()  CAugustScreen2��GetValPtr()�Ɏ��s");
#ifdef _AGM_USE_INHERIT
	pScreen->AddToReleaseList( this );
#else
	pScreen->AddToReleaseList( m_pCore );
#endif
}

#ifndef _AGM_USE_INHERIT
void CAugustMusic::Load( const char* szAudioFile){ RegistedCheck(); m_pCore->Load(szAudioFile); }
void CAugustMusic::Unload(){ RegistedCheck(); m_pCore->Unload(); }

void CAugustMusic::Play(){ RegistedCheck(); m_pCore->Play(); }
void CAugustMusic::LoopPlay( int nLoopCnt ){ RegistedCheck(); m_pCore->LoopPlay(nLoopCnt); }
void CAugustMusic::Stop(){ RegistedCheck(); m_pCore->Stop(); }
void CAugustMusic::SetLastLoop(){ RegistedCheck(); m_pCore->SetLastLoop(); }
void CAugustMusic::Pause(){ RegistedCheck(); m_pCore->Pause(); }

void CAugustMusic::SetVolume( int nVolume ){ RegistedCheck(); m_pCore->SetVolume(nVolume); }
void CAugustMusic::SetBalance( int nBalance ){ RegistedCheck(); m_pCore->SetBalance(nBalance); }
#endif
