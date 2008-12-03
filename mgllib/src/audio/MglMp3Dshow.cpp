#include "stdafx.h"
#include "MglMp3Dshow.h"

typedef Vox* __stdcall CreateVox();
#define USE_CHK()		if(m_useFlg!=TRUE)return;

//	コンストラクタ
CMglMp3Dshow::CMglMp3Dshow()
{
	m_hDll = NULL;
	m_pDriver = NULL;
	m_loadFlg = FALSE;
	m_useFlg = TRUE;
	m_fNowVolume = VOX_DEFAULT_VOLUME;
}

//	デストラクタ
CMglMp3Dshow::~CMglMp3Dshow()
{
	Release();
}

//	初期化
void CMglMp3Dshow::Init()
{
	USE_CHK();

	m_hDll = LoadLibrary( VOX_DLL_NAME );
	if ( m_hDll == NULL )
		MyuThrow( 0, "CMglMp3Dshow::Init()  %s のロードに失敗しました。", VOX_DLL_NAME );

	CreateVox *pCreateVox = (CreateVox *)GetProcAddress( m_hDll,"CreateVox" );
	m_pDriver = pCreateVox();
}

//	開放
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

//	読み込み
void CMglMp3Dshow::Load( const char* szOggFile )
{
	//	チェック
	USE_CHK();
	InitCheck();

	//	読み込み
	if ( m_pDriver->Load( (char*)szOggFile ) != true )
		MyuThrow( 0, "CMglMp3Dshow::Load()  %s の読み込みに失敗しました。", szOggFile );

	m_loadFlg = TRUE;
}

//	開放
void CMglMp3Dshow::UnLoad()
{
	//	チェック
	USE_CHK();
	InitCheck();

	m_pDriver->Release();
	m_loadFlg = FALSE;
}

//	再生
void CMglMp3Dshow::Play( int nLoopCnt )
{
	//	チェック
	USE_CHK();
	LoadCheck();

	//	ループ再生
	if ( m_pDriver->SetLoop(nLoopCnt) != true )
		MyuThrow( 0, "CMglMp3Dshow::SetLoop()  ループ回数の設定に失敗しました。" );

	//	再生
	if ( m_pDriver->Play() != true )
		MyuThrow( 0, "CMglMp3Dshow::Play()  再生に失敗しました。" );
}

//	ループ再生をストップ
void CMglMp3Dshow::StopLoop()
{
	//	チェック
	USE_CHK();
	LoadCheck();

	//	ループ再生
	if ( m_pDriver->SetLoop(0) != true )
		MyuThrow( 0, "CMglMp3Dshow::SetLoop()  ループ回数の設定に失敗しました。" );
}

//	ポーズ
void CMglMp3Dshow::Pause()
{
	//	チェック
	USE_CHK();
	LoadCheck();

	//	ループ再生
	if ( m_pDriver->Pause() != true )
		MyuThrow( 0, "CMglMp3Dshow::Pause()  ポーズに失敗しました。" );
}

//	ボリュームの設定
void CMglMp3Dshow::SetVolume( float fVolume )
{
	//	チェック
	USE_CHK();
	LoadCheck();

	//	ループ再生
	if ( m_pDriver->SetVolume( fVolume ) != true )
		MyuThrow( 0, "CMglMp3Dshow::SetVolume()  ボリュームの設定に失敗しました。" );

	m_fNowVolume = fVolume;
}

//	フェード
void CMglMp3Dshow::Fade( float fTargetVolume, int nFadeTime )
{
	//	チェック
	USE_CHK();
	LoadCheck();

	//	再生
	if ( m_pDriver->Fade( m_fNowVolume, fTargetVolume, nFadeTime ) != true )
		MyuThrow( 0, "CMglMp3Dshow::Fade()  フェード処理に失敗しました。" );

	m_fNowVolume = fTargetVolume;
}
