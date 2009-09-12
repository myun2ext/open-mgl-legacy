#include "stdafx.h"
#include "MglOgg.h"

typedef Vox* __stdcall CreateVox();
#define USE_CHK()		if(m_useFlg!=TRUE)return;

//	�R���X�g���N�^
CMglOgg::CMglOgg()
{
	m_hDll = NULL;
	m_pDriver = NULL;
	m_loadFlg = FALSE;
	m_useFlg = TRUE;
	m_fNowVolume = VOX_DEFAULT_VOLUME;
}

//	�f�X�g���N�^
CMglOgg::~CMglOgg()
{
	Release();
}

//	������
void CMglOgg::Init( HWND hWnd )
{
	USE_CHK();

	m_hDll = LoadLibrary( VOX_DLL_NAME );
	if ( m_hDll == NULL )
		MyuThrow( 0, "CMglOgg::Init()  %s �̃��[�h�Ɏ��s���܂����B", VOX_DLL_NAME );

	CreateVox *pCreateVox = (CreateVox *)GetProcAddress( m_hDll,"CreateVox" );
	m_pDriver = pCreateVox();
}

//	�J��
void CMglOgg::Release()
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
void CMglOgg::Load( const char* szOggFile )
{
	//	�`�F�b�N
	USE_CHK();
	InitCheck();

	//	�ǂݍ���
	if ( m_pDriver->Load( (char*)szOggFile ) != true )
		MyuThrow( 0, "CMglOgg::Load()  %s �̓ǂݍ��݂Ɏ��s���܂����B", szOggFile );

	m_loadFlg = TRUE;
}

//	�J��
void CMglOgg::UnLoad()
{
	//	�`�F�b�N
	USE_CHK();
	InitCheck();

	m_pDriver->Release();
	m_loadFlg = FALSE;
}

//	�Đ�
void CMglOgg::Play( int nLoopCnt )
{
	//	�`�F�b�N
	USE_CHK();
	LoadCheck();

	//	���[�v�Đ�
	if ( m_pDriver->SetLoop(nLoopCnt) != true )
		MyuThrow( 0, "CMglOgg::SetLoop()  ���[�v�񐔂̐ݒ�Ɏ��s���܂����B" );

	//	�Đ�
	if ( m_pDriver->Play() != true )
		MyuThrow( 0, "CMglOgg::Play()  �Đ��Ɏ��s���܂����B" );
}

//	���[�v�Đ����X�g�b�v
void CMglOgg::StopLoop()
{
	//	�`�F�b�N
	USE_CHK();
	LoadCheck();

	//	���[�v�Đ�
	if ( m_pDriver->SetLoop(0) != true )
		MyuThrow( 0, "CMglOgg::SetLoop()  ���[�v�񐔂̐ݒ�Ɏ��s���܂����B" );
}

//	�|�[�Y
void CMglOgg::Pause()
{
	//	�`�F�b�N
	USE_CHK();
	LoadCheck();

	//	���[�v�Đ�
	if ( m_pDriver->Pause() != true )
		MyuThrow( 0, "CMglOgg::Pause()  �|�[�Y�Ɏ��s���܂����B" );
}

//	�{�����[���̐ݒ�
void CMglOgg::SetVolume( float fVolume )
{
	//	�`�F�b�N
	USE_CHK();
	LoadCheck();

	//	���[�v�Đ�
	if ( m_pDriver->SetVolume( fVolume ) != true )
		MyuThrow( 0, "CMglOgg::SetVolume()  �{�����[���̐ݒ�Ɏ��s���܂����B" );

	m_fNowVolume = fVolume;
}

//	�t�F�[�h
void CMglOgg::Fade( float fTargetVolume, int nFadeTime )
{
	//	�`�F�b�N
	USE_CHK();
	LoadCheck();

	//	�Đ�
	if ( m_pDriver->Fade( m_fNowVolume, fTargetVolume, nFadeTime ) != true )
		MyuThrow( 0, "CMglOgg::Fade()  �t�F�[�h�����Ɏ��s���܂����B" );

	m_fNowVolume = fTargetVolume;
}
