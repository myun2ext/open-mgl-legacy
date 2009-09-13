//////////////////////////////////////////////////////////
//
//	MglDirectShowBase
//		- DirectMusicクラス
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
	

//	コンストラクタ
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

//	デストラクタ
CMglDirectShowBase::~CMglDirectShowBase()
{
	Release();
}

//	開放
void CMglDirectShowBase::Release()
{
	SAFE_RELEASE(m_pGraph);
	SAFE_RELEASE(m_pControl);
	SAFE_RELEASE(m_pEvent);
	SAFE_RELEASE(m_pSeeking);
	SAFE_RELEASE(m_pAudioRendererFilter);
	SAFE_RELEASE(m_pBasicAudio);
}

//	初期化
void CMglDirectShowBase::Init( HWND hWnd )
{
	CMglStackInstance("CMglDirectShowBase::Init");

	if ( hWnd == NULL )
		hWnd = GetDefaultHwnd();

	//	フィルタグラフのインスタンスを生成
	MyuAssert( CoCreateInstance(CLSID_FilterGraph, NULL, 
                     CLSCTX_INPROC_SERVER, IID_IGraphBuilder,
                     (void**)&m_pGraph), S_OK,
		"CMglDirectShowBase::Init()  CoCreateInstance(IGraphBuilder)に失敗。" );

	//	フィルタグラフからIMediaControlを取得する
	MyuAssert( m_pGraph->QueryInterface(IID_IMediaControl, (void **)&m_pControl), S_OK,
		"CMglDirectShowBase::Init()  QueryInterface(IMediaControl)に失敗。" );

	//	フィルタグラフからIMediaEventを取得する
	MyuAssert( m_pGraph->QueryInterface(IID_IMediaEvent, (void **)&m_pEvent), S_OK,
		"CMglDirectShowBase::Init()  QueryInterface(IMediaEvent)に失敗。" );

	//	フィルタグラフからIMediaSeekingを取得する
	MyuAssert( m_pGraph->QueryInterface(IID_IMediaSeeking, (void **)&m_pSeeking), S_OK,
		"CMglDirectShowBase::Init()  QueryInterface(IMediaSeeking)に失敗。" );
	
	EnableAudioExControl();
}

//	読み込み
void CMglDirectShowBase::Load( const char* szMediaFile )
{
	InitCheck();

	WCHAR wstrFileName[32000*2+1];
	ZeroMemory( wstrFileName, sizeof(wstrFileName) );
	MultiByteToWideChar(CP_ACP, 0, szMediaFile, strlen(szMediaFile), wstrFileName, sizeof(wstrFileName));

	//	再生するファイルを指定する
	HRESULT hRet = m_pGraph->RenderFile(wstrFileName, NULL);

	switch( hRet )
	{
	case S_OK:
		break;
	case VFW_S_AUDIO_NOT_RENDERED:	//	オーディオ ストリームを再生できない。適切なレンダラが見つからなかった。
		MyuThrow( hRet, "CMglDirectShowBase::Load()  ファイル \"%s\" はサポートしていないオーディオストリームです。", szMediaFile );

	case VFW_S_VIDEO_NOT_RENDERED:	//	ビデオ ストリームを再生できない。適切なレンダラが見つからなかった。
		MyuThrow( hRet, "CMglDirectShowBase::Load()  ファイル \"%s\" はサポートしていないビデオストリームです。", szMediaFile );

	case VFW_S_PARTIAL_RENDER:		//	このムービーにサポートされないフォーマットのストリームが含まれている。
		MyuThrow( hRet, "CMglDirectShowBase::Load()  ファイル \"%s\" はサポートしていないムービーストリームを含みます。", szMediaFile );

	case E_INVALIDARG:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  引数が異常です。" );

	case E_OUTOFMEMORY:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  ファイル \"%s\" を再生するのに十分なメモリがありません。", szMediaFile );

	case VFW_E_CANNOT_CONNECT:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  ファイル \"%s\" 接続を確立する中間フィルタの組み合わせが見つからなかった。", szMediaFile );

	case VFW_E_CANNOT_LOAD_SOURCE_FILTER:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  ファイル \"%s\" のソース フィルタをロードできない。", szMediaFile );

	case VFW_E_CANNOT_RENDER:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  ファイル \"%s\" ストリームをレンダリングするフィルタの組み合わせが見つからなかった。", szMediaFile );

	case VFW_E_INVALID_FILE_FORMAT:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  ファイルフォーマットが無効です。 %s", szMediaFile );

	case VFW_E_NOT_FOUND:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  ファイル \"%s\" が見つかりません。", szMediaFile );

	case VFW_E_NOT_IN_GRAPH:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  ファイル \"%s\" フィルタ グラフに存在しないオブジェクトに要求された関数を実行できない。", szMediaFile );

	case VFW_E_UNKNOWN_FILE_TYPE:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  ファイル \"%s\" のメディアタイプが認識出来ません。", szMediaFile );

	case VFW_E_UNSUPPORTED_STREAM:
		MyuThrow( hRet, "CMglDirectShowBase::Load()  ファイル \"%s\" はサポートされていないメディア形式です。", szMediaFile );

	default:
		MyuThrow( hRet, "ファイル \"%s\" の読み込みに失敗。", szMediaFile );
	}
}

//	再生
inline void CMglDirectShowBase::Play()
{
	InitCheck();
	//ENBL_CHK();

	/*	2009/09/13  まぁ、再生を押したらもう一回最初っから、が普通かねぇ？	*/
	Stop();
	
	/*MyuAssert( m_pControl->Run(), S_OK,
		"CMglDirectShowBase::Play()  m_pControl->Run()に失敗。" );*/
	if ( m_pControl->Run() != S_OK ){
		/*OAFilterState fs;
		HRESULT hRet = S_FALSE;
		for(int i=0; i<50; i++, Sleep(100)){
			hRet = m_pControl->GetState(200,&fs);
			if ( hRet != S_OK )
				continue;
		}
		if ( hRet != S_OK ){
			MyuThrow( hRet, "CMglDirectShowBase::Play()  m_pControl->Run()に失敗。(GetState() failed.)" );
		}*/
		/*MyuAssert( m_pControl->GetState(1000,&fs), S_OK,
			"CMglDirectShowBase::Play()  m_pControl->GetState()に失敗。" );*/
		//MyuThrow( 0, "CMglDirectShowBase::Play()  m_pControl->Run()に失敗。" );
	}
}

//	停止
inline void CMglDirectShowBase::Stop()
{
	InitCheck();
	//ENBL_CHK();

	SeekToHead();
	
	MyuAssert( m_pControl->Stop(), S_OK,
		"CMglDirectShowBase::Stop()  m_pControl->Stop()に失敗。" );
}

//	一時停止
inline void CMglDirectShowBase::Pause()
{
	InitCheck();
	//ENBL_CHK();
	
	MyuAssert( m_pControl->Pause(), S_OK,
		"CMglDirectShowBase::Pause()  m_pControl->Pause()に失敗。" );
}

//	ボリュームの設定
inline void CMglDirectShowBase::SetVolume( int nVolume )
{
	EnableAudioExControl();
	m_pBasicAudio->put_Volume(nVolume*100-10000);
}

//	パン設定
inline void CMglDirectShowBase::SetBalance( int nBalance )
{
	EnableAudioExControl();
	m_pBasicAudio->put_Balance(nBalance*100);
}

inline void CMglDirectShowBase::EnableAudioExControl()
{
	if ( m_pAudioRendererFilter == NULL )
		// 音声レンダラフィルター所得
		MyuAssert( CoCreateInstance(CLSID_AudioRender, NULL,
			CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&m_pAudioRendererFilter), S_OK,
			"CMglDirectShowBase::SetVolume()  CoCreateInstance(IBaseFilter)に失敗。" );
	
	if ( m_pBasicAudio == NULL )
		// IBasicAudioインターフェースの所得
		MyuAssert( m_pAudioRendererFilter->QueryInterface(IID_IBasicAudio, (void**)&m_pBasicAudio), S_OK,
			"CMglDirectShowBase::SetVolume()  QueryInterface(IID_IBasicAudio)に失敗。" );
}


//	位置変更
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
		MyuThrow(41166, "CMglDirectShowBase::SeekTo()  dwFlg = %d は不明です。", dwFlg);
	}

	//先頭位置に設定する
	MyuAssert( m_pSeeking->SetPositions(&llSeekTime,
		dwCurrentFlags, NULL, AM_SEEKING_NoPositioning), S_OK,
		"CMglDirectShowBase::SeekTo()  m_pSeeking->SetPositions()に失敗。" );

}
