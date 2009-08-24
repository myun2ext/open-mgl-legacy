//////////////////////////////////////////////////////////
//
//	AugustSound
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustSound.h"

#include "MglAudio.h"

using namespace agh;
using namespace std;

///////////////////////////////////////////////////////////////////////

//	コンストラクタ
CAugustSound::CAugustSound()
{
	m_pCore = new _MGL_AUGUST_SOUND_CORE_IMPL();
}

//	デストラクタ
CAugustSound::~CAugustSound()
{
	delete m_pCore;
}

//	登録時にInitを呼び出す
void CAugustSound::OnRegist()
{
	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_ROOT_WINDOW_HWND),
		"CAugustSound::Init()  ウインドウハンドルの取得に失敗");

	((CMglSound*)m_pCore)->Init(hWnd);
}

//	毎フレーム毎にUpdate()呼び出すの忘れてた・・・
/*bool CAugustSound::OnFrame()
{
	//	スーパークラスのOnFrame()呼び出し
	return agh::CKeyboardBase::OnFrame();
}*/



void CAugustSound::Load( const char* szAudioFile, const char* szAlias ){ m_pCore->Load(szAudioFile, szAlias); }
void CAugustSound::Play( const char* szName ){ m_pCore->Load(szName); }
void CAugustSound::LoopPlay( const char* szName, unsigned long nLoopCount ){ m_pCore->LoopPlay(szName, nLoopCount); }
void CAugustSound::Stop( const char* szName ){ m_pCore->Stop(szName); }
void CAugustSound::SetVolume( int nVolume ){ m_pCore->SetVolume(nVolume); }
void CAugustSound::Disable(){ m_pCore->Disable(); }
void CAugustSound::Enable(){ m_pCore->Enable(); }