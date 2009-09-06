//////////////////////////////////////////////////////////
//
//	AugustMusic
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustMusic.h"

#include "MglAudio.h"
#include "MglCoManager.h"
#include "AugustScreen2.h"

using namespace agh;
using namespace std;

///////////////////////////////////////////////////////////////////////

//	コンストラクタ
CAugustMusic::CAugustMusic()
{
	m_pCore = new _MGL_AUGUST_SOUND_CORE_IMPL();
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

	((CMglSound*)m_pCore)->Init(hWnd);

	//	2009/09/05  ウインドウを閉じる前にReleaseしてもらうようにする
	CAugustScreen2_X* pScreen = (CAugustScreen2_X*)MyuAssertNull(GetValPtr(AUGUST_VALKEY_SCREEN),
		"CAugustMusic::OnRegist()  CAugustScreen2のGetValPtr()に失敗");
	pScreen->AddToReleaseList( m_pCore );
}

//	毎フレーム毎にUpdate()呼び出すの忘れてた・・・
/*bool CAugustMusic::OnFrame()
{
	//	スーパークラスのOnFrame()呼び出し
	return agh::CKeyboardBase::OnFrame();
}*/



void CAugustMusic::Load( const char* szAudioFile, const char* szAlias ){ m_pCore->Load(szAudioFile, szAlias); }
void CAugustMusic::Play( const char* szName ){ m_pCore->Play(szName); }
void CAugustMusic::LoopPlay( const char* szName, unsigned long nLoopCount ){ m_pCore->LoopPlay(szName, nLoopCount); }
void CAugustMusic::Stop( const char* szName ){ m_pCore->Stop(szName); }
void CAugustMusic::SetVolume( float fVolume ){ m_pCore->SetVolume((fVolume-100)*10); }
void CAugustMusic::Disable(){ m_pCore->Disable(); }
void CAugustMusic::Enable(){ m_pCore->Enable(); }