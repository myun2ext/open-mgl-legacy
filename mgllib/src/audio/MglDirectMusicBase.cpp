//////////////////////////////////////////////////////////
//
//	MglDirectMusicBase
//		- DirectMusicクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglDirectMusicBase.h"

//template class DLL_EXP std::map<std::string,IDirectMusicSegment8*>;

#define ENBL_CHK()	if(m_flgEnable!=TRUE)return;
	

//	コンストラクタ
CMglDirectMusicBase::CMglDirectMusicBase()
{
	m_pLoader = NULL;
	m_pPerformance = NULL;
	//m_segments = NULL;
	m_flgEnable = TRUE;
}

//	デストラクタ
CMglDirectMusicBase::~CMglDirectMusicBase()
{
	Release();
}

//	初期化
void CMglDirectMusicBase::InitEx( HWND hWnd, const char *szBaseDirectory,
								  DWORD dwDefaultPathType, DWORD dwPerformanceChannelCount, DWORD dwFlags )
{
	//ENBL_CHK(); <-- コレここにはダメじゃないか…？(2007/02/18)

	if ( hWnd == NULL )
		hWnd = GetDefaultHwnd();

	/*
	MyuAssert( CoInitialize(NULL), S_OK,
		"CMglDirectMusicBase::Init()  CoInitialize()に失敗。" );
	*/

	MyuAssert( CoCreateInstance(CLSID_DirectMusicLoader, NULL, 
                     CLSCTX_INPROC, IID_IDirectMusicLoader8,
                     (void**)&m_pLoader), S_OK,
		"CMglDirectMusicBase::Init()  CoCreateInstance(DirectMusicLoader)に失敗。" );

    MyuAssert( CoCreateInstance(CLSID_DirectMusicPerformance, NULL,
                     CLSCTX_INPROC, IID_IDirectMusicPerformance8,
                     (void**)&m_pPerformance ), S_OK,
		"CMglDirectMusicBase::Init()  CoCreateInstance(DirectMusicPerformance)に失敗。" );

	MyuAssert( m_pPerformance->InitAudio( 
			NULL,                  // IDirectMusic インターフェイスは不要。
			NULL,                  // IDirectSound インターフェイスは不要。
			hWnd,                  // ウィンドウのハンドル。
			dwDefaultPathType,	   // デフォルトのオーディオパス タイプ
//			DMUS_APATH_DYNAMIC_STEREO,  // デフォルトのオーディオパス タイプ
//			DMUS_APATH_SHARED_STEREOPLUSREVERB,  // デフォルトのオーディオパス タイプ
			dwPerformanceChannelCount, // パフォーマンス チャンネルの数。
			dwFlags,       // シンセサイザの機能。
			NULL                   // オーディオ パラメータにはデフォルトを使用。
		), S_OK,
		"CMglDirectMusicBase::Init()  m_pPerformance->InitAudio()に失敗。" ); 

 
	// Unicode に変換する。
	WCHAR wstrSearchPath[MAX_PATH];
	MultiByteToWideChar( CP_ACP, 0, szBaseDirectory, -1, wstrSearchPath, MAX_PATH );
 
	// 検索ディレクトリを設定する。
	MyuAssert( m_pLoader->SetSearchDirectory( GUID_DirectMusicAllTypes, wstrSearchPath, FALSE ), S_OK,
		"CMglDirectMusicBase::Init()  m_pLoader->SetSearchDirectory()に失敗。" ); 
}

//	開放
void CMglDirectMusicBase::Release()
{
	if ( m_pLoader == NULL )
		return;

	/*for( SEG_ITR it=m_segments.begin(); it != m_segments.end(); it++ )
		StopSegment( it->second );*/
    m_pPerformance->Stop(
        NULL,   // すべてのセグメントを停止する。
        NULL,   // すべてのセグメント状態を停止する。
        0,      // 直ちに実行する。
        0       // フラグ。
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
	//	開放処理多分必要
	for( SEG_ITR it=m_segments.begin(); it != m_segments.end(); it++ )
		m_pLoader->ReleaseObject( it->second );
	*/
}

//	読み込み
void CMglDirectMusicBase::Load( const char* szAudioFile, const char* szAlias )
{
	//ENBL_CHK(); <-- コレここにはダメじゃないか…？(2007/02/18)

	InitCheck();

	if ( szAlias == NULL )
		szAlias = szAudioFile;

	//	既に無いかチェック
	if ( IsExist(szAlias) == TRUE )
		MyuThrow( 0, "CMglDirectMusicBase::Load()  既に\"%s\"の名前のセグメントは存在します。", szAlias );

	/* <-- szBaseDirectoryを記憶しないといけない。めんどいので後回し
	//	ファイルの存在を事前チェック
	if ( exist_file( szAudioFile ) == false )
		MyuThrow( hret, "CMglDirectMusicBase::Load()  ファイル \"%s\" が見つかりません。", szAudioFile );
	*/

	WCHAR wstrFileName[32000*2+1];
	ZeroMemory( wstrFileName, sizeof(wstrFileName) );

	m_segments[szAlias] = NULL;
	MultiByteToWideChar(CP_ACP, 0, szAudioFile, strlen(szAudioFile), wstrFileName, sizeof(wstrFileName));
	//mbsrtowcs( wstrFileName, &szAlias, MAX_PATH+1, ps != 0 ? ps : &internal );

    /*MyuAssert( m_pLoader->LoadObjectFromFile(
        CLSID_DirectMusicSegment,   // クラス識別子。
        IID_IDirectMusicSegment8,   // 目的のインターフェイスの ID。
        wstrFileName,               // ファイル名。
        (LPVOID*) &m_segments[szAlias]       // インターフェイスを受け取るポインタ。
		), S_OK,
		"Audioファイル %s (name:%s)の読み込みに失敗。", szAudioFile, szAlias );*/

    HRESULT hret = m_pLoader->LoadObjectFromFile(
        CLSID_DirectMusicSegment,   // クラス識別子。
        IID_IDirectMusicSegment8,   // 目的のインターフェイスの ID。
        wstrFileName,               // ファイル名。
        (LPVOID*) &m_segments[szAlias]       // インターフェイスを受け取るポインタ。
		);
	switch( hret )
	{
	case S_OK:
		break;
	case DMUS_E_LOADER_FAILEDOPEN:
		MyuThrow( hret, "CMglDirectMusicBase::Load()  ファイル \"%s\" は見つからないか有効なMediaファイルではありません。", szAudioFile );
		//MyuThrow( hret, "CMglDirectMusicBase::Load()  ファイル \"%s\" は有効なMediaファイルではありません。", szAudioFile );
	case DMUS_E_LOADER_FORMATNOTSUPPORTED:
	case DMUS_E_UNSUPPORTED_STREAM:
		MyuThrow( hret, "CMglDirectMusicBase::Load()  ファイル \"%s\" はサポートされていないAudio形式です。", szAudioFile );
	default:
		MyuThrow( hret, "Audioファイル \"%s\" の読み込みに失敗。", szAudioFile );
	}

    MyuAssert( m_segments[szAlias]->Download( m_pPerformance ), S_OK,
		"CMglDirectMusicBase::Load()  m_segments[szAlias]->Download()に失敗。" );
}

//	再生
inline void CMglDirectMusicBase::PlaySegment( const char* szAliasName )
{
	ENBL_CHK();
	LoopPlaySegment( szAliasName, 0 );
}

//	ループ再生
void CMglDirectMusicBase::LoopPlaySegment( const char* szAliasName, DWORD dwLoopCount )
{
	ENBL_CHK();
	InitCheck();
	ExistChk(szAliasName);

	m_segments[szAliasName]->SetRepeats( dwLoopCount );
	MyuAssert( m_pPerformance->PlaySegmentEx(
        m_segments[szAliasName],  // 再生するセグメント。
        NULL,        // ソングに使用するパラメータ。実装されていない。
        NULL,        // トランジションに関するパラメータ。 
        DMUS_SEGF_SECONDARY,           // フラグ。
        0,           // 開始タイム。0 は直ちに開始。
        NULL,        // セグメント状態を受け取るポインタ。
        NULL,        // 停止するオブジェクト。
        NULL )       // デフォルトでない場合はオーディオパス。
		,S_OK, "CMglDirectMusicBase::PlaySegment()  m_pPerformance->PlaySegmentEx()に失敗。" );
}

//	止める
void CMglDirectMusicBase::Stop( const char* szAliasName )
{
	ENBL_CHK();
	InitCheck();
	ExistChk(szAliasName);
	StopSegment( m_segments[szAliasName] );
}

//	止める2
void CMglDirectMusicBase::StopSegment( IDirectMusicSegment* pSegment )
{
	ENBL_CHK();
	InitCheck();

	MyuAssert( m_pPerformance->StopEx( pSegment, 0, 0 ),
		S_OK, "CMglDirectMusicBase::StopSegment()  m_pPerformance->StopEx()に失敗。" );
}

//	ボリュームの設定
void CMglDirectMusicBase::SetVolume( int nVolume )
{    
	//ENBL_CHK(); <-- コレここにはダメじゃないか…？(2007/02/18)
	InitCheck();
	MyuAssert( m_pPerformance->SetGlobalParam( GUID_PerfMasterVolume, (VOID*)&nVolume, sizeof(long) ), S_OK,
		"CMglDirectMusicBase::SetVolume()  m_pPerformance->SetGlobalParam()に失敗。" );
}

//	ポインタ取得
IDirectMusicSegment8* CMglDirectMusicBase::GetSegmentPtr( const char* szAliasName )
{
	InitCheck();
	ExistChk(szAliasName);
	return m_segments[szAliasName];
}
