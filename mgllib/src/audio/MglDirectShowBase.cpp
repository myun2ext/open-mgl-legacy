//////////////////////////////////////////////////////////
//
//	MglDirectShowBase
//		- DirectMusic�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglDirectShowBase.h"

#ifdef _DEBUG
	#pragma comment(lib, "Strmbasd.lib")
#else
	#pragma comment(lib, "Strmbase.lib")
#endif//_DEBUG

//template class DLL_EXP std::map<std::string,IDirectMusicSegment8*>;

#define ENBL_CHK()	if(m_flgEnable!=TRUE)return;
	

//	�R���X�g���N�^
CMglDirectShowBase::CMglDirectShowBase()
{
	m_pGraph = NULL;
	m_pControl = NULL;
	m_pEvent = NULL;
	m_pSeeking = NULL;
	m_pAudioRendererFilter = NULL;
	m_pBasicAudio = NULL;
	m_bRunReady = FALSE;
}

//	�f�X�g���N�^
CMglDirectShowBase::~CMglDirectShowBase()
{
	Release();
}

//	�J��
void CMglDirectShowBase::Release()
{
	SAFE_RELEASE(m_pGraph);
	SAFE_RELEASE(m_pControl);
	SAFE_RELEASE(m_pEvent);
	SAFE_RELEASE(m_pSeeking);
	SAFE_RELEASE(m_pAudioRendererFilter);
	SAFE_RELEASE(m_pBasicAudio);
}

//	������
void CMglDirectShowBase::Init( HWND hWnd )
{
	CMglStackInstance("CMglDirectShowBase::Init");

	if ( hWnd == NULL )
		hWnd = GetDefaultHwnd();

	//	�t�B���^�O���t�̃C���X�^���X�𐶐�
	MyuAssert( CoCreateInstance(CLSID_FilterGraph, NULL, 
                     CLSCTX_INPROC_SERVER, IID_IGraphBuilder,
                     (void**)&m_pGraph), S_OK,
		"CMglDirectShowBase::Init()  CoCreateInstance(IGraphBuilder)�Ɏ��s�B" );

	//	�t�B���^�O���t����IMediaControl���擾����
	MyuAssert( m_pGraph->QueryInterface(IID_IMediaControl, (void **)&m_pControl), S_OK,
		"CMglDirectShowBase::Init()  QueryInterface(IMediaControl)�Ɏ��s�B" );

	//	�t�B���^�O���t����IMediaEvent���擾����
	MyuAssert( m_pGraph->QueryInterface(IID_IMediaEvent, (void **)&m_pEvent), S_OK,
		"CMglDirectShowBase::Init()  QueryInterface(IMediaEvent)�Ɏ��s�B" );

	//	�t�B���^�O���t����IMediaSeeking���擾����
	MyuAssert( m_pGraph->QueryInterface(IID_IMediaSeeking, (void **)&m_pSeeking), S_OK,
		"CMglDirectShowBase::Init()  QueryInterface(IMediaSeeking)�Ɏ��s�B" );
	
	EnableAudioExControl();
}

//	�ǂݍ���
void CMglDirectShowBase::Load( const char* szMediaFile )
{
	InitCheck();

	WCHAR wstrFileName[32000*2+1];
	ZeroMemory( wstrFileName, sizeof(wstrFileName) );
	MultiByteToWideChar(CP_ACP, 0, szMediaFile, strlen(szMediaFile), wstrFileName, sizeof(wstrFileName));

	//	�Đ�����t�@�C�����w�肷��
	HRESULT hRet = m_pGraph->RenderFile(wstrFileName, NULL);

	switch( hRet )
	{
	case S_OK:
		break;
	case VFW_S_AUDIO_NOT_RENDERED:	//	�I�[�f�B�I �X�g���[�����Đ��ł��Ȃ��B�K�؂ȃ����_����������Ȃ������B
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �t�@�C�� \"%s\" �̓T�|�[�g���Ă��Ȃ��I�[�f�B�I�X�g���[���ł��B", szMediaFile );

	case VFW_S_VIDEO_NOT_RENDERED:	//	�r�f�I �X�g���[�����Đ��ł��Ȃ��B�K�؂ȃ����_����������Ȃ������B
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �t�@�C�� \"%s\" �̓T�|�[�g���Ă��Ȃ��r�f�I�X�g���[���ł��B", szMediaFile );

	case VFW_S_PARTIAL_RENDER:		//	���̃��[�r�[�ɃT�|�[�g����Ȃ��t�H�[�}�b�g�̃X�g���[�����܂܂�Ă���B
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �t�@�C�� \"%s\" �̓T�|�[�g���Ă��Ȃ����[�r�[�X�g���[�����܂݂܂��B", szMediaFile );

	case E_INVALIDARG:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �������ُ�ł��B" );

	case E_OUTOFMEMORY:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �t�@�C�� \"%s\" ���Đ�����̂ɏ\���ȃ�����������܂���B", szMediaFile );

	case VFW_E_CANNOT_CONNECT:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �t�@�C�� \"%s\" �ڑ����m�����钆�ԃt�B���^�̑g�ݍ��킹��������Ȃ������B", szMediaFile );

	case VFW_E_CANNOT_LOAD_SOURCE_FILTER:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �t�@�C�� \"%s\" �̃\�[�X �t�B���^�����[�h�ł��Ȃ��B", szMediaFile );

	case VFW_E_CANNOT_RENDER:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �t�@�C�� \"%s\" �X�g���[���������_�����O����t�B���^�̑g�ݍ��킹��������Ȃ������B", szMediaFile );

	case VFW_E_INVALID_FILE_FORMAT:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �t�@�C���t�H�[�}�b�g�������ł��B %s", szMediaFile );

	case VFW_E_NOT_FOUND:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �t�@�C�� \"%s\" ��������܂���B", szMediaFile );

	case VFW_E_NOT_IN_GRAPH:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �t�@�C�� \"%s\" �t�B���^ �O���t�ɑ��݂��Ȃ��I�u�W�F�N�g�ɗv�����ꂽ�֐������s�ł��Ȃ��B", szMediaFile );

	case VFW_E_UNKNOWN_FILE_TYPE:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �t�@�C�� \"%s\" �̃��f�B�A�^�C�v���F���o���܂���B", szMediaFile );

	case VFW_E_UNSUPPORTED_STREAM:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  �t�@�C�� \"%s\" �̓T�|�[�g����Ă��Ȃ����f�B�A�`���ł��B", szMediaFile );

	default:
		MyuThrow( hRet, "�t�@�C�� \"%s\" �̓ǂݍ��݂Ɏ��s�B", szMediaFile );
	}
}

//	�Đ�
inline void CMglDirectShowBase::Play()
{
	InitCheck();
	//ENBL_CHK();

	/*	2009/09/13  �܂��A�Đ�����������������ŏ�������A�����ʂ��˂��H	*/
	Stop();
	
	/*MyuAssert( m_pControl->Run(), S_OK,
		"CMglDirectShowBase::Play()  m_pControl->Run()�Ɏ��s�B" );*/
	if ( m_pControl->Run() != S_OK ){
		/*OAFilterState fs;
		HRESULT hRet = S_FALSE;
		for(int i=0; i<50; i++, Sleep(100)){
			hRet = m_pControl->GetState(200,&fs);
			if ( hRet != S_OK )
				continue;
		}
		if ( hRet != S_OK ){
			MyuThrow( hRet, "CMglDirectShowBase::Play()  m_pControl->Run()�Ɏ��s�B(GetState() failed.)" );
		}*/
		/*MyuAssert( m_pControl->GetState(1000,&fs), S_OK,
			"CMglDirectShowBase::Play()  m_pControl->GetState()�Ɏ��s�B" );*/
		//MyuThrow( 0, "CMglDirectShowBase::Play()  m_pControl->Run()�Ɏ��s�B" );
	}
}

//	��~
inline void CMglDirectShowBase::Stop()
{
	InitCheck();
	//ENBL_CHK();

	SeekToHead();
	
	MyuAssert( m_pControl->Stop(), S_OK,
		"CMglDirectShowBase::Stop()  m_pControl->Stop()�Ɏ��s�B" );
}

//	�ꎞ��~
inline void CMglDirectShowBase::Pause()
{
	InitCheck();
	//ENBL_CHK();
	
	MyuAssert( m_pControl->Pause(), S_OK,
		"CMglDirectShowBase::Pause()  m_pControl->Pause()�Ɏ��s�B" );
}

//	�{�����[���̐ݒ�
inline void CMglDirectShowBase::SetVolume( int nVolume )
{
	EnableAudioExControl();
	m_pBasicAudio->put_Volume(nVolume*100-10000);
}

//	�p���ݒ�
inline void CMglDirectShowBase::SetBalance( int nBalance )
{
	EnableAudioExControl();
	m_pBasicAudio->put_Balance(nBalance*100);
}

inline void CMglDirectShowBase::EnableAudioExControl()
{
	if ( m_pAudioRendererFilter == NULL )
		// ���������_���t�B���^�[����
		MyuAssert( CoCreateInstance(CLSID_AudioRender, NULL,
			CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&m_pAudioRendererFilter), S_OK,
			"CMglDirectShowBase::SetVolume()  CoCreateInstance(IBaseFilter)�Ɏ��s�B" );
	
	if ( m_pBasicAudio == NULL )
		// IBasicAudio�C���^�[�t�F�[�X�̏���
		MyuAssert( m_pAudioRendererFilter->QueryInterface(IID_IBasicAudio, (void**)&m_pBasicAudio), S_OK,
			"CMglDirectShowBase::SetVolume()  QueryInterface(IID_IBasicAudio)�Ɏ��s�B" );
}


//	�ʒu�ύX
void CMglDirectShowBase::SeekTo( long nSeekTime, DWORD dwFlg )
{
	InitCheck();

	LONGLONG llSeekTime = nSeekTime;
	DWORD dwCurrentFlags = 0;

	switch(dwFlg)
	{
	case SEEK_SET:	dwCurrentFlags = AM_SEEKING_AbsolutePositioning;	break;
	case SEEK_CUR:	dwCurrentFlags = AM_SEEKING_RelativePositioning;	break;
	default:
		MyuThrow(41166, "CMglDirectShowBase::SeekTo()  dwFlg = %d �͕s���ł��B", dwFlg);
	}

	//�擪�ʒu�ɐݒ肷��
	MyuAssert( m_pSeeking->SetPositions(&llSeekTime,
		dwCurrentFlags, NULL, AM_SEEKING_NoPositioning), S_OK,
		"CMglDirectShowBase::SeekTo()  m_pSeeking->SetPositions()�Ɏ��s�B" );

}
