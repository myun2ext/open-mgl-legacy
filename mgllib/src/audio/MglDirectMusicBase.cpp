//////////////////////////////////////////////////////////
//
//	MglDirectMusicBase
//		- DirectMusic�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglDirectMusicBase.h"

//template class DLL_EXP std::map<std::string,IDirectMusicSegment8*>;

#define ENBL_CHK()	if(m_flgEnable!=TRUE)return;
	

//	�R���X�g���N�^
CMglDirectMusicBase::CMglDirectMusicBase()
{
	m_pLoader = NULL;
	m_pPerformance = NULL;
	//m_segments = NULL;
	m_flgEnable = TRUE;
}

//	�f�X�g���N�^
CMglDirectMusicBase::~CMglDirectMusicBase()
{
	Release();
}

//	������
void CMglDirectMusicBase::InitEx( HWND hWnd, const char *szBaseDirectory,
								  DWORD dwDefaultPathType, DWORD dwPerformanceChannelCount, DWORD dwFlags )
{
	//ENBL_CHK(); <-- �R�������ɂ̓_������Ȃ����c�H(2007/02/18)

	if ( hWnd == NULL )
		hWnd = GetDefaultHwnd();

	/*
	MyuAssert( CoInitialize(NULL), S_OK,
		"CMglDirectMusicBase::Init()  CoInitialize()�Ɏ��s�B" );
	*/

	MyuAssert( CoCreateInstance(CLSID_DirectMusicLoader, NULL, 
                     CLSCTX_INPROC, IID_IDirectMusicLoader8,
                     (void**)&m_pLoader), S_OK,
		"CMglDirectMusicBase::Init()  CoCreateInstance(DirectMusicLoader)�Ɏ��s�B" );

    MyuAssert( CoCreateInstance(CLSID_DirectMusicPerformance, NULL,
                     CLSCTX_INPROC, IID_IDirectMusicPerformance8,
                     (void**)&m_pPerformance ), S_OK,
		"CMglDirectMusicBase::Init()  CoCreateInstance(DirectMusicPerformance)�Ɏ��s�B" );

	MyuAssert( m_pPerformance->InitAudio( 
			NULL,                  // IDirectMusic �C���^�[�t�F�C�X�͕s�v�B
			NULL,                  // IDirectSound �C���^�[�t�F�C�X�͕s�v�B
			hWnd,                  // �E�B���h�E�̃n���h���B
			dwDefaultPathType,	   // �f�t�H���g�̃I�[�f�B�I�p�X �^�C�v
//			DMUS_APATH_DYNAMIC_STEREO,  // �f�t�H���g�̃I�[�f�B�I�p�X �^�C�v
//			DMUS_APATH_SHARED_STEREOPLUSREVERB,  // �f�t�H���g�̃I�[�f�B�I�p�X �^�C�v
			dwPerformanceChannelCount, // �p�t�H�[�}���X �`�����l���̐��B
			dwFlags,       // �V���Z�T�C�U�̋@�\�B
			NULL                   // �I�[�f�B�I �p�����[�^�ɂ̓f�t�H���g���g�p�B
		), S_OK,
		"CMglDirectMusicBase::Init()  m_pPerformance->InitAudio()�Ɏ��s�B" ); 

 
	// Unicode �ɕϊ�����B
	WCHAR wstrSearchPath[MAX_PATH];
	MultiByteToWideChar( CP_ACP, 0, szBaseDirectory, -1, wstrSearchPath, MAX_PATH );
 
	// �����f�B���N�g����ݒ肷��B
	MyuAssert( m_pLoader->SetSearchDirectory( GUID_DirectMusicAllTypes, wstrSearchPath, FALSE ), S_OK,
		"CMglDirectMusicBase::Init()  m_pLoader->SetSearchDirectory()�Ɏ��s�B" ); 
}

//	�J��
void CMglDirectMusicBase::Release()
{
	if ( m_pLoader == NULL )
		return;

	/*for( SEG_ITR it=m_segments.begin(); it != m_segments.end(); it++ )
		StopSegment( it->second );*/
    m_pPerformance->Stop(
        NULL,   // ���ׂẴZ�O�����g���~����B
        NULL,   // ���ׂẴZ�O�����g��Ԃ��~����B
        0,      // �����Ɏ��s����B
        0       // �t���O�B
    );

	m_pPerformance->CloseDown();

	/*m_pLoader->Release(); 
    m_pPerformance->Release();*/
	SAFE_RELEASE(m_pLoader); 
    SAFE_RELEASE(m_pPerformance);

	for( SEG_ITR it=m_segments.begin(); it != m_segments.end(); it++ )
		SAFE_RELEASE( it->second );
	m_segments.clear();
 
    //CoUninitialize();

	/*
	//	�J�����������K�v
	for( SEG_ITR it=m_segments.begin(); it != m_segments.end(); it++ )
		m_pLoader->ReleaseObject( it->second );
	*/
}

//	�ǂݍ���
void CMglDirectMusicBase::Load( const char* szAudioFile, const char* szAlias )
{
	//ENBL_CHK(); <-- �R�������ɂ̓_������Ȃ����c�H(2007/02/18)

	InitCheck();

	if ( szAlias == NULL )
		szAlias = szAudioFile;

	//	���ɖ������`�F�b�N
	if ( IsExist(szAlias) == TRUE )
		MyuThrow( 0, "CMglDirectMusicBase::Load()  ����\"%s\"�̖��O�̃Z�O�����g�͑��݂��܂��B", szAlias );

	/* <-- szBaseDirectory���L�����Ȃ��Ƃ����Ȃ��B�߂�ǂ��̂Ō��
	//	�t�@�C���̑��݂����O�`�F�b�N
	if ( exist_file( szAudioFile ) == false )
		MyuThrow( hret, "CMglDirectMusicBase::Load()  �t�@�C�� \"%s\" ��������܂���B", szAudioFile );
	*/

	WCHAR wstrFileName[32000*2+1];
	ZeroMemory( wstrFileName, sizeof(wstrFileName) );

	m_segments[szAlias] = NULL;
	MultiByteToWideChar(CP_ACP, 0, szAudioFile, strlen(szAudioFile), wstrFileName, sizeof(wstrFileName));
	//mbsrtowcs( wstrFileName, &szAlias, MAX_PATH+1, ps != 0 ? ps : &internal );

    /*MyuAssert( m_pLoader->LoadObjectFromFile(
        CLSID_DirectMusicSegment,   // �N���X���ʎq�B
        IID_IDirectMusicSegment8,   // �ړI�̃C���^�[�t�F�C�X�� ID�B
        wstrFileName,               // �t�@�C�����B
        (LPVOID*) &m_segments[szAlias]       // �C���^�[�t�F�C�X���󂯎��|�C���^�B
		), S_OK,
		"Audio�t�@�C�� %s (name:%s)�̓ǂݍ��݂Ɏ��s�B", szAudioFile, szAlias );*/

    HRESULT hret = m_pLoader->LoadObjectFromFile(
        CLSID_DirectMusicSegment,   // �N���X���ʎq�B
        IID_IDirectMusicSegment8,   // �ړI�̃C���^�[�t�F�C�X�� ID�B
        wstrFileName,               // �t�@�C�����B
        (LPVOID*) &m_segments[szAlias]       // �C���^�[�t�F�C�X���󂯎��|�C���^�B
		);
	switch( hret )
	{
	case S_OK:
		break;
	case DMUS_E_LOADER_FAILEDOPEN:
		MyuThrow( hret, "CMglDirectMusicBase::Load()  �t�@�C�� \"%s\" �͌�����Ȃ����L����Media�t�@�C���ł͂���܂���B", szAudioFile );
		//MyuThrow( hret, "CMglDirectMusicBase::Load()  �t�@�C�� \"%s\" �͗L����Media�t�@�C���ł͂���܂���B", szAudioFile );
	case DMUS_E_LOADER_FORMATNOTSUPPORTED:
	case DMUS_E_UNSUPPORTED_STREAM:
		MyuThrow( hret, "CMglDirectMusicBase::Load()  �t�@�C�� \"%s\" �̓T�|�[�g����Ă��Ȃ�Audio�`���ł��B", szAudioFile );
	default:
		MyuThrow( hret, "Audio�t�@�C�� \"%s\" �̓ǂݍ��݂Ɏ��s�B", szAudioFile );
	}

    MyuAssert( m_segments[szAlias]->Download( m_pPerformance ), S_OK,
		"CMglDirectMusicBase::Load()  m_segments[szAlias]->Download()�Ɏ��s�B" );
}

//	�Đ�
inline void CMglDirectMusicBase::PlaySegment( const char* szAliasName )
{
	ENBL_CHK();
	LoopPlaySegment( szAliasName, 0 );
}

//	���[�v�Đ�
void CMglDirectMusicBase::LoopPlaySegment( const char* szAliasName, DWORD dwLoopCount )
{
	ENBL_CHK();
	InitCheck();
	ExistChk(szAliasName);

	m_segments[szAliasName]->SetRepeats( dwLoopCount );
	MyuAssert( m_pPerformance->PlaySegmentEx(
        m_segments[szAliasName],  // �Đ�����Z�O�����g�B
        NULL,        // �\���O�Ɏg�p����p�����[�^�B��������Ă��Ȃ��B
        NULL,        // �g�����W�V�����Ɋւ���p�����[�^�B 
        DMUS_SEGF_SECONDARY,           // �t���O�B
        0,           // �J�n�^�C���B0 �͒����ɊJ�n�B
        NULL,        // �Z�O�����g��Ԃ��󂯎��|�C���^�B
        NULL,        // ��~����I�u�W�F�N�g�B
        NULL )       // �f�t�H���g�łȂ��ꍇ�̓I�[�f�B�I�p�X�B
		,S_OK, "CMglDirectMusicBase::PlaySegment()  m_pPerformance->PlaySegmentEx()�Ɏ��s�B" );
}

//	�~�߂�
void CMglDirectMusicBase::Stop( const char* szAliasName )
{
	ENBL_CHK();
	InitCheck();
	ExistChk(szAliasName);
	StopSegment( m_segments[szAliasName] );
}

//	�~�߂�2
void CMglDirectMusicBase::StopSegment( IDirectMusicSegment* pSegment )
{
	ENBL_CHK();
	InitCheck();

	MyuAssert( m_pPerformance->StopEx( pSegment, 0, 0 ),
		S_OK, "CMglDirectMusicBase::StopSegment()  m_pPerformance->StopEx()�Ɏ��s�B" );
}

//	�{�����[���̐ݒ�
void CMglDirectMusicBase::SetVolume( int nVolume )
{    
	//ENBL_CHK(); <-- �R�������ɂ̓_������Ȃ����c�H(2007/02/18)
	InitCheck();
	MyuAssert( m_pPerformance->SetGlobalParam( GUID_PerfMasterVolume, (VOID*)&nVolume, sizeof(long) ), S_OK,
		"CMglDirectMusicBase::SetVolume()  m_pPerformance->SetGlobalParam()�Ɏ��s�B" );
}

//	�|�C���^�擾
IDirectMusicSegment8* CMglDirectMusicBase::GetSegmentPtr( const char* szAliasName )
{
	InitCheck();
	ExistChk(szAliasName);
	return m_segments[szAliasName];
}
