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

using namespace agh;
using namespace std;

///////////////////////////////////////////////////////////////////////

//	�R���X�g���N�^
CAugustSound::CAugustSound()
{
	m_pCore = new _MGL_AUGUST_SOUND_CORE_IMPL();
}

//	�f�X�g���N�^
CAugustSound::~CAugustSound()
{
	delete m_pCore;
}

//	�o�^����Init���Ăяo��
void CAugustSound::OnRegist()
{
	//CoInitialize(NULL);
	g_coManager.Init();

	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_ROOT_WINDOW_HWND),
		"CAugustSound::OnRegist()  �E�C���h�E�n���h����GetValPtr()�Ɏ��s");

	((CMglSound*)m_pCore)->Init(hWnd);

	//	2009/09/05  �E�C���h�E�����O��Release���Ă��炤�悤�ɂ���
	CAugustScreen2_X* pScreen = (CAugustScreen2_X*)MyuAssertNull(GetValPtr(AUGUST_VALKEY_SCREEN),
		"CAugustSound::OnRegist()  CAugustScreen2��GetValPtr()�Ɏ��s");
	pScreen->AddToReleaseList( m_pCore );
}

//	���t���[������Update()�Ăяo���̖Y��Ă��E�E�E
/*bool CAugustSound::OnFrame()
{
	//	�X�[�p�[�N���X��OnFrame()�Ăяo��
	return agh::CKeyboardBase::OnFrame();
}*/



void CAugustSound::Load( const char* szAudioFile, const char* szAlias ){ m_pCore->Load(szAudioFile, szAlias); }
void CAugustSound::Play( const char* szName ){ m_pCore->Play(szName); }
void CAugustSound::LoopPlay( const char* szName, unsigned long nLoopCount ){ m_pCore->LoopPlay(szName, nLoopCount); }
void CAugustSound::Stop( const char* szName ){ m_pCore->Stop(szName); }
void CAugustSound::SetVolume( float fVolume ){ m_pCore->SetVolume((fVolume-100)*10); }
void CAugustSound::Disable(){ m_pCore->Disable(); }
void CAugustSound::Enable(){ m_pCore->Enable(); }