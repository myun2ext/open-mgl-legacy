#include "stdafx.h"
#include "MglMp3Dshow.h"

typedef Vox* __stdcall CreateVox();
#define USE_CHK()		if(m_useFlg!=TRUE)return;

//	�R���X�g���N�^
CMglMp3Dshow::CMglMp3Dshow()
{
	m_hDll = NULL;
	m_pDriver = NULL;
	m_loadFlg = FALSE;
	m_useFlg = TRUE;
	m_fNowVolume = VOX_DEFAULT_VOLUME;
}

//	�f�X�g���N�^
CMglMp3Dshow::~CMglMp3Dshow()
{
	Release();
}

//	������
void CMglMp3Dshow::Init()
{
	USE_CHK();

	m_hDll = LoadLibrary( VOX_DLL_NAME );
	if ( m_hDll == NULL )
		MyuThrow( 0, "CMglMp3Dshow::Init()  %s �̃��[�h�Ɏ��s���܂����B", VOX_DLL_NAME );

	CreateVox *pCreateVox = (CreateVox *)GetProcAddress( m_hDll,"CreateVox" );
	m_pDriver = pCreateVox();
}

//	�J��
void CMglMp3Dshow::Release()
{
	if ( m_pDriver != NULL )
	{
		UnLoad();
		m_pDriver->Delete();
		m_pDriver = NULL;
	}
	if ( m_hDll != NULL )
	{
		FreeLibrary( m_hDll );
		m_hDll = NULL;
	}
}

//	�ǂݍ���
void CMglMp3Dshow::Load( const char* szOggFile )
{
	//	�`�F�b�N
	USE_CHK();
	InitCheck();

	//	�ǂݍ���
	if ( m_pDriver->Load( (char*)szOggFile ) != true )
		MyuThrow( 0, "CMglMp3Dshow::Load()  %s �̓ǂݍ��݂Ɏ��s���܂����B", szOggFile );

	m_loadFlg = TRUE;
}

//	�J��
void CMglMp3Dshow::UnLoad()
{
	//	�`�F�b�N
	USE_CHK();
	InitCheck();

	m_pDriver->Release();
	m_loadFlg = FALSE;
}

//	�Đ�
void CMglMp3Dshow::Play( int nLoopCnt )
{
	//	�`�F�b�N
	USE_CHK();
	LoadCheck();

	//	���[�v�Đ�
	if ( m_pDriver->SetLoop(nLoopCnt) != true )
		MyuThrow( 0, "CMglMp3Dshow::SetLoop()  ���[�v�񐔂̐ݒ�Ɏ��s���܂����B" );

	//	�Đ�
	if ( m_pDriver->Play() != true )
		MyuThrow( 0, "CMglMp3Dshow::Play()  �Đ��Ɏ��s���܂����B" );
}

//	���[�v�Đ����X�g�b�v
void CMglMp3Dshow::StopLoop()
{
	//	�`�F�b�N
	USE_CHK();
	LoadCheck();

	//	���[�v�Đ�
	if ( m_pDriver->SetLoop(0) != true )
		MyuThrow( 0, "CMglMp3Dshow::SetLoop()  ���[�v�񐔂̐ݒ�Ɏ��s���܂����B" );
}

//	�|�[�Y
void CMglMp3Dshow::Pause()
{
	//	�`�F�b�N
	USE_CHK();
	LoadCheck();

	//	���[�v�Đ�
	if ( m_pDriver->Pause() != true )
		MyuThrow( 0, "CMglMp3Dshow::Pause()  �|�[�Y�Ɏ��s���܂����B" );
}

//	�{�����[���̐ݒ�
void CMglMp3Dshow::SetVolume( float fVolume )
{
	//	�`�F�b�N
	USE_CHK();
	LoadCheck();

	//	���[�v�Đ�
	if ( m_pDriver->SetVolume( fVolume ) != true )
		MyuThrow( 0, "CMglMp3Dshow::SetVolume()  �{�����[���̐ݒ�Ɏ��s���܂����B" );

	m_fNowVolume = fVolume;
}

//	�t�F�[�h
void CMglMp3Dshow::Fade( float fTargetVolume, int nFadeTime )
{
	//	�`�F�b�N
	USE_CHK();
	LoadCheck();

	//	�Đ�
	if ( m_pDriver->Fade( m_fNowVolume, fTargetVolume, nFadeTime ) != true )
		MyuThrow( 0, "CMglMp3Dshow::Fade()  �t�F�[�h�����Ɏ��s���܂����B" );

	m_fNowVolume = fTargetVolume;
}
