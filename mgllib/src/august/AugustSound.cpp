//////////////////////////////////////////////////////////
//
//	AugustSound
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustSound.h"

#include "MglAudio.h"
#include "MglCoManager.h"
#include "AugustScreen2.h"

#include <time.h>

using namespace agh;
using namespace std;

///////////////////////////////////////////////////////////////////////

//	�R���X�g���N�^
CAugustSoundManager::CAugustSoundManager()
{
	m_pCore = new _MGL_AUGUST_SOUND_CORE_IMPL();
}

//	�f�X�g���N�^
CAugustSoundManager::~CAugustSoundManager()
{
	delete m_pCore;
}

//	�o�^����Init���Ăяo��
void CAugustSoundManager::OnRegist()
{
	//CoInitialize(NULL);
	g_coManager.Init();

	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_ROOT_WINDOW_HWND),
		"CAugustSoundManager::OnRegist()  �E�C���h�E�n���h����GetValPtr()�Ɏ��s");

	((_MGL_AUGUST_SOUND_CORE_IMPL*)m_pCore)->Init(hWnd);

	//	2009/09/05  �E�C���h�E�����O��Release���Ă��炤�悤�ɂ���
	CAugustScreen2_X* pScreen = (CAugustScreen2_X*)MyuAssertNull(GetValPtr(AUGUST_VALKEY_SCREEN),
		"CAugustSoundManager::OnRegist()  CAugustScreen2��GetValPtr()�Ɏ��s");
	pScreen->AddToReleaseList( m_pCore );

	//	2009/09/26
	SetValPtr(AUGUST_VALKEY_P_SOUNDMGR, this);
}

void CAugustSoundManager::Load( const char* szAudioFile, const char* szAlias ){ m_pCore->Load(szAudioFile, szAlias); }
void CAugustSoundManager::Play( const char* szName ){ m_pCore->Play(szName); }
void CAugustSoundManager::LoopPlay( const char* szName, unsigned long nLoopCount ){ m_pCore->LoopPlay(szName, nLoopCount); }
void CAugustSoundManager::Stop( const char* szName ){ m_pCore->Stop(szName); }
void CAugustSoundManager::SetVolume( float fVolume ){ m_pCore->SetVolume((fVolume-100)*10); }
void CAugustSoundManager::Disable(){ m_pCore->Disable(); }
void CAugustSoundManager::Enable(){ m_pCore->Enable(); }
bool CAugustSoundManager::IsAlreadyUsedAlias( const char* szName ){ return WINBOOL_TO_CPPBOOL( m_pCore->IsExist(szName) ); }



/**************************************************************************************************/

//	�R���X�g���N�^
CAugustSound::CAugustSound()
	: CAugustControlBase("CAugustSound")
{
	m_pMgr = NULL;
}

//	�o�^����Init���Ăяo��
void CAugustSound::OnRegist()
{
	m_pMgr = (CAugustSoundManager*)MyuAssertNull(GetValPtr(AUGUST_VALKEY_P_SOUNDMGR),
		"CAugustSound::OnRegist()  AUGUST_VALKEY_P_SOUNDMGR ��GetValPtr()�Ɏ��s");
}

void CAugustSound::Load( const char* szAudioFile )
{
	RegistedCheck();

	m_name = szAudioFile;
	mtsrand();
	SelectUniqueName( /*szAudioFile*/ );

	m_pMgr->Load(szAudioFile);
}

void CAugustSound::SelectUniqueName( /*const char* szName*/ )
{
	if ( m_pMgr->IsAlreadyUsedAlias( m_name.c_str() ) )
	{
		m_name += mtrand();

		SelectUniqueName( /*szAudioFile*/ );
	}
}