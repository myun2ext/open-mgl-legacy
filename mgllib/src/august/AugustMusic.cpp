//////////////////////////////////////////////////////////
//
//	AugustMusic
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustMusic.h"

#include "MglCoManager.h"
#include "AugustScreen2.h"

using namespace agh;
using namespace std;

///////////////////////////////////////////////////////////////////////

//	コンストラクタ
CAugustMusic::CAugustMusic()
 : _BASE ("CAugustMusic")
{
	m_pCore = new _MGL_AUGUST_MUSIC_CORE_IMPL();
}

//	デストラクタ
CAugustMusic::~CAugustMusic()
{
	delete m_pCore;
}

//	登録時にInitを呼び出す
void CAugustMusic::OnRegist()
{
	//CoInitialize(NULL);
	g_coManager.Init();

	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_ROOT_WINDOW_HWND),
		"CAugustMusic::OnRegist()  ウインドウハンドルのGetValPtr()に失敗");

#ifdef _AGM_USE_INHERIT
	CMglBgm::Init(hWnd);
#else
	m_pCore->Init(hWnd);
#endif

	//	2009/09/05  ウインドウを閉じる前にReleaseしてもらうようにする
	CAugustScreen2_X* pScreen = (CAugustScreen2_X*)MyuAssertNull(GetValPtr(AUGUST_VALKEY_SCREEN),
		"CAugustMusic::OnRegist()  CAugustScreen2のGetValPtr()に失敗");
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
