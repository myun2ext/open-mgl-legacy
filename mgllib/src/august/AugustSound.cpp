//////////////////////////////////////////////////////////
//
//	AugustSound
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustSound.h"

#include "MglAudio.h"
#include "MglCoManager.h"
#include "AugustScreen2.h"

using namespace agh;
using namespace std;

///////////////////////////////////////////////////////////////////////

//	コンストラクタ
CAugustSoundManager::CAugustSoundManager()
{
	m_pCore = new _MGL_AUGUST_SOUND_CORE_IMPL();
}

//	デストラクタ
CAugustSoundManager::~CAugustSoundManager()
{
	delete m_pCore;
}

//	登録時にInitを呼び出す
void CAugustSoundManager::OnRegist()
{
	//CoInitialize(NULL);
	g_coManager.Init();

	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_ROOT_WINDOW_HWND),
		"CAugustSoundManager::OnRegist()  ウインドウハンドルのGetValPtr()に失敗");

	((_MGL_AUGUST_SOUND_CORE_IMPL*)m_pCore)->Init(hWnd);

	//	2009/09/05  ウインドウを閉じる前にReleaseしてもらうようにする
	CAugustScreen2_X* pScreen = (CAugustScreen2_X*)MyuAssertNull(GetValPtr(AUGUST_VALKEY_SCREEN),
		"CAugustSoundManager::OnRegist()  CAugustScreen2のGetValPtr()に失敗");
	pScreen->AddToReleaseList( m_pCore );
}

void CAugustSoundManager::Load( const char* szAudioFile, const char* szAlias ){ m_pCore->Load(szAudioFile, szAlias); }
void CAugustSoundManager::Play( const char* szName ){ m_pCore->Play(szName); }
void CAugustSoundManager::LoopPlay( const char* szName, unsigned long nLoopCount ){ m_pCore->LoopPlay(szName, nLoopCount); }
void CAugustSoundManager::Stop( const char* szName ){ m_pCore->Stop(szName); }
void CAugustSoundManager::SetVolume( float fVolume ){ m_pCore->SetVolume((fVolume-100)*10); }
void CAugustSoundManager::Disable(){ m_pCore->Disable(); }
void CAugustSoundManager::Enable(){ m_pCore->Enable(); }
