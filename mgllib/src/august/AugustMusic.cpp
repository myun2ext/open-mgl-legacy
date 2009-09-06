//////////////////////////////////////////////////////////
//
//	AugustMusic
//		- MglGraphicManager ���C���[�N���X
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

//	�R���X�g���N�^
CAugustMusic::CAugustMusic()
{
	m_pCore = new _MGL_AUGUST_SOUND_CORE_IMPL();
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

	((CMglSound*)m_pCore)->Init(hWnd);

	//	2009/09/05  �E�C���h�E�����O��Release���Ă��炤�悤�ɂ���
	CAugustScreen2_X* pScreen = (CAugustScreen2_X*)MyuAssertNull(GetValPtr(AUGUST_VALKEY_SCREEN),
		"CAugustMusic::OnRegist()  CAugustScreen2��GetValPtr()�Ɏ��s");
	pScreen->AddToReleaseList( m_pCore );
}

//	���t���[������Update()�Ăяo���̖Y��Ă��E�E�E
/*bool CAugustMusic::OnFrame()
{
	//	�X�[�p�[�N���X��OnFrame()�Ăяo��
	return agh::CKeyboardBase::OnFrame();
}*/



void CAugustMusic::Load( const char* szAudioFile, const char* szAlias ){ m_pCore->Load(szAudioFile, szAlias); }
void CAugustMusic::Play( const char* szName ){ m_pCore->Play(szName); }
void CAugustMusic::LoopPlay( const char* szName, unsigned long nLoopCount ){ m_pCore->LoopPlay(szName, nLoopCount); }
void CAugustMusic::Stop( const char* szName ){ m_pCore->Stop(szName); }
void CAugustMusic::SetVolume( float fVolume ){ m_pCore->SetVolume((fVolume-100)*10); }
void CAugustMusic::Disable(){ m_pCore->Disable(); }
void CAugustMusic::Enable(){ m_pCore->Enable(); }