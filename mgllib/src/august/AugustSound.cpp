//////////////////////////////////////////////////////////
//
//	AugustSound
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustSound.h"

#include "MglAudio.h"

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
	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_ROOT_WINDOW_HWND),
		"CAugustSound::Init()  �E�C���h�E�n���h���̎擾�Ɏ��s");

	((CMglSound*)m_pCore)->Init(hWnd);
}

//	���t���[������Update()�Ăяo���̖Y��Ă��E�E�E
/*bool CAugustSound::OnFrame()
{
	//	�X�[�p�[�N���X��OnFrame()�Ăяo��
	return agh::CKeyboardBase::OnFrame();
}*/



void CAugustSound::Load( const char* szAudioFile, const char* szAlias ){ m_pCore->Load(szAudioFile, szAlias); }
void CAugustSound::Play( const char* szName ){ m_pCore->Load(szName); }
void CAugustSound::LoopPlay( const char* szName, unsigned long nLoopCount ){ m_pCore->LoopPlay(szName, nLoopCount); }
void CAugustSound::Stop( const char* szName ){ m_pCore->Stop(szName); }
void CAugustSound::SetVolume( int nVolume ){ m_pCore->SetVolume(nVolume); }
void CAugustSound::Disable(){ m_pCore->Disable(); }
void CAugustSound::Enable(){ m_pCore->Enable(); }