//////////////////////////////////////////////////////////
//
//	MglGraphicManager
//		- DirectX Graphics 管理クラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglGraphicManager.h"
#include "MglTexture.h"
#include "MglD3dCapsDumper.h"

/*
//	VRAMサイズ取得用
#include <DDraw.h>
#pragma comment(lib,"ddraw.lib")
*/

/*
#include "MglManager.h"
_EXTERN_MGL_MANAGER;
*/

int g_nSfcCount=0;
int g_2dgCount=0;
CMglGraphicManager *g_pDefaultGd=NULL;

//	コンストラクタ
CMglGraphicManager::CMglGraphicManager()
{
	_MGL_DEBUGLOG( "CMglGraphicManager のインスタンスが生成されました。" );
	CMglStackInstance("CMglGraphicManager::CMglGraphicManager");

	m_pD3d = NULL;
	m_pD3dDev = NULL;
	m_nDispX = 0;
	m_nDispY = 0;
	ZeroMemory( &m_formatTexture, sizeof(m_formatTexture) ); 
	m_dwD3dDeviceFlg = 0;
	m_dwAlphaOption = MGL_ALPHA_OPT_TRANSLUCENCE;

	m_nTexMem = 0;
	m_dwMaxTextureHeight = 0;
	m_dwMaxTextureWidth = 0;

	//	2007/01/11  なんかスプライトとかSurfaceごとにいちいち作んなくてもインデネ
	m_pSprite = NULL;
	m_bSpriteBegun = FALSE;
	EnableSupportSprite(); //m_bUseSprite = TRUE;
	//m_bSpriteCenterDraw = FALSE;

	g_2dgCount++;
}

//	デストラクタ
CMglGraphicManager::~CMglGraphicManager()
{
	_MGL_DEBUGLOG( "+ CMglGraphicManager::デストラクタ" );
	CMglStackInstance("CMglGraphicManager::~CMglGraphicManager");
	Release();
	_MGL_DEBUGLOG( "- CMglGraphicManager::デストラクタ" );
	g_2dgCount--;
}

//	開放
void CMglGraphicManager::Release()
{
	_MGL_DEBUGLOG( "+ CMglGraphicManager::Release()" );
	CMglStackInstance("CMglGraphicManager::Release");

	//	シーンを終了しておく
	if ( m_pD3dDev != NULL )
		m_pD3dDev->EndScene();

	//	自動開放処理
	_MGL_DEBUGLOG( "自動開放処理を開始します。（リファレンス数：%d）", m_autoReleaseAry.size() );
	for ( ; m_autoReleaseAry.size() > 0; )
	{
		m_autoReleaseAry.begin()->second->Release();
	}
	_MGL_DEBUGLOG( "自動開放処理を完了しました。" );
	/*for( AUTO_RELESE_ITR itr = m_autoReleaseAry.end(); itr != m_autoReleaseAry.begin(); itr-- )
	{
		_MGL_DEBUGLOG( "itr->second->Release()" );
		itr->second->Release();

		//	で、Release() の中で RmRefOfAutoRelease() が呼ばれて itrの対象は消される、と。
	}*/

	SAFE_RELEASE( m_pD3dDev );
	SAFE_RELEASE( m_pD3d );
	_MGL_DEBUGLOG( "- CMglGraphicManager::Release()" );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////


//	初期化及び開始
void CMglGraphicManager::Init( HWND hWnd, int nDispX, int nDispY, BOOL bFullscreen,
							  D3DFORMAT formatTexture, DWORD dwD3dDeviceMode, UINT nAdapterNo )
{
	_MGL_DEBUGLOG( "+ CMglGraphicManager::Init()" );
	CMglStackInstance("CMglGraphicManager::Init");

	//	2008/07/06 追加
	Release();

	/*	InitEx()へ移動
	m_nDispX = nDispX;
	m_nDispY = nDispY;
	m_formatTexture = format;
	*/

	//	D3Dオブジェクトの生成
	Direct3DCreate();

	//	デバイス情報の取得
	/*
		2007/07/15  HALが成功したらREFは要らないし、HALに失敗したらREFを使用しないと…

	D3DCAPS8 capsHal;
	D3DCAPS8 capsRef;

	_MGL_DEBUGLOG( "HALデバイスの取得" );
	MyuAssert( m_pD3d->GetDeviceCaps( nAdapterNo, D3DDEVTYPE_HAL, &capsHal ), D3D_OK,
		"CMglGraphicManager::Init()  HALデバイス情報の取得に失敗。" );

	_MGL_DEBUGLOG( "REFデバイスの取得" );
	MyuAssert( m_pD3d->GetDeviceCaps( nAdapterNo, D3DDEVTYPE_REF, &capsRef ), D3D_OK,
		"CMglGraphicManager::Init()  REFデバイス情報の取得に失敗。" );
	DumpAdapterInfo( &capsHal, &capsRef );
	*/
	D3DCAPS8 caps;
	_MGL_DEBUGLOG( "HALデバイスの取得..." );
	if ( m_pD3d->GetDeviceCaps( nAdapterNo, D3DDEVTYPE_HAL, &caps ) != D3D_OK )
	{
		_MGL_DEBUGLOG( "HALデバイス情報の取得に失敗。REFでリトライ" );

		//_MGL_DEBUGLOG( "REFデバイスの取得" );
		MyuAssert( m_pD3d->GetDeviceCaps( nAdapterNo, D3DDEVTYPE_REF, &caps ), D3D_OK,
			"CMglGraphicManager::Init()  HAL/REFデバイス情報の取得に失敗。" );
		_MGL_DEBUGLOG( "REFデバイスの取得に成功" );

		//	dwD3dDeviceModeをREFに設定（Autoなら）
		if ( dwD3dDeviceMode == D3D_DEVICE_MODE_AUTO ){
			_MGL_DEBUGLOG( "dwD3dDeviceModeをD3D_DEVICE_FLG_REFに設定します" );
			dwD3dDeviceMode = D3D_DEVICE_FLG_REF;
		}
	}
	else
		_MGL_DEBUGLOG( "HALデバイスの取得に成功" );
	//DumpAdapterInfo( &caps );
	CMglD3dCapsDumper dumper;
	dumper.DumpAdapterInfo( m_pD3d, &caps );

	//	2007/07/15  D3D_DEVICE_MODE_AUTO対応
	if ( dwD3dDeviceMode == D3D_DEVICE_MODE_AUTO ){
		dwD3dDeviceMode = D3D_DEVICE_MODE_DEFAULT;
		_MGL_DEBUGLOG( "dwD3dDeviceModeをD3D_DEVICE_MODE_DEFAULTに設定します" );
	}

	//	ディスプレイモードの取得
	D3DDISPLAYMODE dispMode;
	MyuAssert( this->m_pD3d->GetAdapterDisplayMode( nAdapterNo, &dispMode ), D3D_OK,
		"CMglGraphicManager::Init()  ディスプレイモードの取得に失敗。" );

	if ( dispMode.Format == D3DFMT_X8R8G8B8 )
		_MGL_DEBUGLOG( "dispMode.Format = D3DFMT_X8R8G8B8(32bit)" );
	else if ( dispMode.Format == D3DFMT_R8G8B8 )
		_MGL_DEBUGLOG( "dispMode.Format = D3DFMT_R8G8B8(24bit)" );
	else if ( dispMode.Format == D3DFMT_R5G6B5 )
		_MGL_DEBUGLOG( "dispMode.Format = D3DFMT_R5G6B5(16bit)" );
	else if ( dispMode.Format == D3DFMT_R3G3B2 )
		_MGL_DEBUGLOG( "dispMode.Format = D3DFMT_R3G3B2(256)" );
	else
		_MGL_DEBUGLOG( "dispMode.Format = Unknown(%u)", dispMode.Format );

	if ( dispMode.Format == D3DFMT_R3G3B2 )
		MyuThrow( 0, "画面の色を16bit以上にしてください。" );

	D3DPRESENT_PARAMETERS presentParam; 
	ZeroMemory( &presentParam, sizeof(D3DPRESENT_PARAMETERS) );

	//	D3Dデバイスのパラメタを設定
	presentParam.BackBufferWidth = nDispX; // GetRealTexSize(nDispX);
	presentParam.BackBufferHeight = nDispY; // GetRealTexSize(nDispY);
	presentParam.BackBufferFormat = dispMode.Format;
	presentParam.BackBufferCount = 1;
	presentParam.MultiSampleType = D3DMULTISAMPLE_NONE;
	presentParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParam.hDeviceWindow = hWnd;
	presentParam.FullScreen_RefreshRateInHz  = D3DPRESENT_RATE_DEFAULT;

	if ( bFullscreen == TRUE )
		presentParam.Windowed = FALSE;
	else
		presentParam.Windowed = TRUE;

	//BOOL            EnableAutoDepthStencil;
    //D3DFORMAT       AutoDepthStencilFormat;
    //DWORD           Flags;
    //UINT            FullScreen_PresentationInterval;

	//	Ex版の呼び出し
	InitEx( &presentParam, dwD3dDeviceMode, formatTexture, nAdapterNo );

	//	g_pDefaultGdへの設定
	if ( g_2dgCount == 1 )
		g_pDefaultGd = this;
	else
		g_pDefaultGd = NULL;	//	複数あるよ…？どれ・・？

	/*
	//	2007/01/11  スプライト作成
	if ( m_bUseSprite )
		MyuAssert( D3DXCreateSprite( m_pD3dDev, &m_pSprite ), D3D_OK,
			"CMglGraphicManager::Init()  D3DXCreateSprite()に失敗" );
	*/
	InitSprite();

	_MGL_DEBUGLOG( "- CMglGraphicManager::Init()" );
}
void CMglGraphicManager::InitSprite()
{
	if ( m_pD3dDev == NULL )
		MyuThrow( 0, "CMglGraphicManager::InitSprite()  m_pD3dDevがNULL" );
	if ( m_pSprite != NULL )	//	既にあればスキップ
		return;

	MyuAssert( D3DXCreateSprite( m_pD3dDev, &m_pSprite ), D3D_OK,
		"CMglGraphicManager::Init()  D3DXCreateSprite()に失敗" );
}

//	D3Dオブジェクトの生成（InitEx()用に分離）
void CMglGraphicManager::Direct3DCreate()
{
	CMglStackInstance("CMglGraphicManager::Direct3DCreate");

	if ( m_pD3d != NULL )
		//MyuThrow2( 0, 0x0201, "CMglGraphicManager::Direct3DCreate()  D3Dオブジェクトは既あります。" );
		//	2007/07/15  既にあったら何もしないんでいんでない・・・？
		return;

	//	D3Dオブジェクトの生成
	m_pD3d = Direct3DCreate8( D3D_SDK_VERSION );
	if ( NULL == m_pD3d )
		MyuThrow2( 0, MGLMSGNO_GRP_MANAGER_D3DCREATE_FAILED,
			"CMglGraphicManager::Direct3DCreate()  Direct3DCreate8()に失敗。" );
}

//	初期化及び開始のEx版
void CMglGraphicManager::InitEx( D3DPRESENT_PARAMETERS* pPresentParam, DWORD dwD3dDeviceMode, D3DFORMAT formatTexture, int nAdapterNo, HWND hFocusWindow )
{
	_MGL_DEBUGLOG( "+ CMglGraphicManager::InitEx()" );
	CMglStackInstance("CMglGraphicManager::InitEx");

	m_nDispX = pPresentParam->BackBufferWidth;
	m_nDispY = pPresentParam->BackBufferHeight;
	m_formatTexture = formatTexture;

	if ( hFocusWindow == NULL )
		hFocusWindow = pPresentParam->hDeviceWindow;

/*
	//	ステンシル系
	MyuAssert( this->m_pD3d->CheckDeviceFormat( nAdapterNo, D3DDEVTYPE_HAL, dispMode.Format,
		D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16 ), D3D_OK,
		"ステンシル不可" );

	MyuAssert( this->m_pD3d->CheckDeviceFormat( nAdapterNo, D3DDEVTYPE_HAL, dispMode.Format,
		D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, dispMode.Format ), D3D_OK,
		"レンダー不可" );
	 
	presentParam.EnableAutoDepthStencil = TRUE;
	presentParam.AutoDepthStencilFormat = D3DFMT_D16;
*/

	//	2007/07/15  REFサポート
	if ( dwD3dDeviceMode == D3D_DEVICE_FLG_REF ){
		_MGL_DEBUGLOG( "dwD3dDeviceModeはD3D_DEVICE_FLG_REFです。" );
		if ( D3dCreateDevice( D3D_DEVICE_FLG_REF, pPresentParam, nAdapterNo, hFocusWindow ) != TRUE )
			//MyuThrow( 0, "指定されたデバイスモード(dwD3dDeviceMode=0x%08X)はサポートされていません。\r\nDirect3Dデバイスの生成に失敗しました。", dwD3dDeviceMode );
			MyuThrow( 0, "Direct3Dデバイスの生成に失敗しました。\r\n"
				"dwD3dDeviceMode=0x%08X", dwD3dDeviceMode );
	}
	else
	{

		//	D3Dデバイス生成
		DWORD dwWork=dwD3dDeviceMode;
		for( DWORD dwMask=1; dwWork != 0; dwMask <<= 1 )
		{
			DWORD dwFlag = dwWork & dwMask;
			if ( dwFlag != 0 )
			{
				if ( D3dCreateDevice( dwFlag, pPresentParam, nAdapterNo, hFocusWindow ) == TRUE )
				{
					m_dwD3dDeviceFlg = dwFlag;
					break;
				}
			}

			//	フラグを潰す
			dwWork -= dwMask;
		}
		if ( dwWork == 0 )
			//MyuThrow( 0, "指定されたデバイスモード(dwD3dDeviceMode=0x%08X)はサポートされていません。\r\nDirect3Dデバイスの生成に失敗しました。", dwD3dDeviceMode );
			MyuThrow( 0, "Direct3Dデバイスの生成に失敗しました。\r\n"
				"dwD3dDeviceMode=0x%08X", dwD3dDeviceMode );
	}


	//	VRAM情報をログに出力
	m_nTexMem = m_pD3dDev->GetAvailableTextureMem();
	_MGL_DEBUGLOG( "AvailableTextureMemory = %u KB", (int)(m_nTexMem/1024) );

	//	Vertexを設定
	SetupMyuVertex();

	//	バックバッファの情報を取得
	MyuAssert( GetBackBuffer()->GetDesc( &backBufferDesc ), D3D_OK,
		"CMglGraphicManager::Init()  GetBackBuffer()->GetDesc()に失敗" );

	//	アルファブレンドを有効にしておく
	SetAlphaMode();

	//	シーンを開始しておく
	MyuAssert( m_pD3dDev->BeginScene(), D3D_OK,
		"CMglGraphicManager::Init()  シーンの開始に失敗。" );

	//	バックバッファをクリアしておく
	Clear();


	_MGL_DEBUGLOG( "- CMglGraphicManager::InitEx()" );
}

//	Vertexを設定
void CMglGraphicManager::SetupMyuVertex(){
	MyuAssert( this->m_pD3dDev->SetVertexShader( FVF_MYU_VERTEX ), D3D_OK,
		"CMglGraphicManager::Init()  SetVertexShader()に失敗" );
}

//	Direct3D の CreateDevice()を独自フラグにより呼び出す
BOOL CMglGraphicManager::D3dCreateDevice( DWORD dwD3dDeviceFlg, D3DPRESENT_PARAMETERS* pPresentParam, int nAdapterNo, HWND hFocusWindow )
{
	//_MGL_DEBUGLOG( "+ CMglGraphicManager::D3dCreateDevice()" );
	CMglStackInstance("CMglGraphicManager::D3dCreateDevice");

	D3DDEVTYPE deviceType=D3DDEVTYPE_FORCE_DWORD;
	DWORD vertexFlag=0;

	switch( dwD3dDeviceFlg )
	{
	//	REF
	case D3D_DEVICE_FLG_REF:
		deviceType = D3DDEVTYPE_REF;
		vertexFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		_MGL_DEBUGLOG( "CMglGraphicManager::D3dCreateDevice()  REFにて試行します。" );
		break;

	//	HAL
	case D3D_DEVICE_FLG_HAL:
		deviceType = D3DDEVTYPE_HAL;
		vertexFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		_MGL_DEBUGLOG( "CMglGraphicManager::D3dCreateDevice()  HALにて試行します。" );
		break;

	//	T&L HAL
	case D3D_DEVICE_FLG_T_AND_L_HAL:
		deviceType = D3DDEVTYPE_HAL;
		vertexFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		_MGL_DEBUGLOG( "CMglGraphicManager::D3dCreateDevice()  T&L HALにて試行します。" );
		break;

	//	ソフト＆ハードの混合頂点処理
	case D3D_DEVICE_FLG_HW_SW_MIX:
		deviceType = D3DDEVTYPE_HAL;
		vertexFlag = D3DCREATE_MIXED_VERTEXPROCESSING;
		_MGL_DEBUGLOG( "CMglGraphicManager::D3dCreateDevice()  ソフト＆ハードの混合にて試行します。" );
		break;

	//	不明な定数
	default:
		MyuThrow( 0, "CMglGraphicManager::D3dCreateDevice() 不明なデバイスフラグです。(dwD3dDeviceFlg=0x%08X)", dwD3dDeviceFlg );
	}

	//	D3Dデバイス生成
	if( FAILED( this->m_pD3d->CreateDevice(
		nAdapterNo, deviceType, hFocusWindow, vertexFlag | D3DCREATE_MULTITHREADED, pPresentParam, &this->m_pD3dDev ) ) )
    {
		_MGL_DEBUGLOG( "CMglGraphicManager::D3dCreateDevice()  失敗。" );
		return FALSE;
	}
	else
	{
		_MGL_DEBUGLOG( "CMglGraphicManager::D3dCreateDevice()  成功。" );
		return TRUE;
	}
}

//	フルスクリーン時のディスプレイモードが可能かどうかチェックする
void CMglGraphicManager::IsValidDisplayMode( int nWidth, int nHeight, D3DFORMAT Format, int nRefreshRate )
{

}

/////////////////////////////////////////////////////////////////////////////////

void CMglGraphicManager::Clear( D3DCOLOR color )
{
	CMglStackInstance("CMglGraphicManager::Clear");
   //m_pD3dDev->Clear( 0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0 );// ZBufferもクリアする
	Paint( NULL, color );
}

void CMglGraphicManager::Paint( RECT* rect, D3DCOLOR color )
{
	CMglStackInstance("CMglGraphicManager::Paint");
	if ( m_pD3dDev == NULL )
		MyuThrow( 0, "CMglGraphicManager::Paint()  m_pD3dDevがNULL" );

	int rectCount = 0;
	if ( rect != NULL )
		rectCount = 1;
	//	良く分かんないけど多分これキャストしちゃってもええんちゃう…？
    m_pD3dDev->Clear( rectCount, (D3DRECT*)rect, D3DCLEAR_TARGET, color, 1.0f, 0 );// ZBufferもクリアする
}

////////////////////////////////////////////////////////////////////////
//
//		拡張便利系メソッド
//
////////////////////////////////////////////////////////////////////////


/*	意味が分からんので廃止、もとい SetAlphaMode() へ統合

//	アルファブレンドに関するセッティングを行う
//	alphaOp は D3DTEXTUREOP
void CMglGraphicManager::SetAlphaBlendSetting( DWORD alphaOp )
{
	m_pD3dDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, alphaOp);
	m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//	アルファブレンドを有効にしておく
	EnabledAlphaBlend();
}

//	アルファブレンドを有効にする
void CMglGraphicManager::EnabledAlphaBlend() {
	m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}

//	アルファブレンドを無効にする
void CMglGraphicManager::DisableAlphaBlend() {
	m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
*/

//	アルファ値をどう処理するか設定する
void CMglGraphicManager::SetAlphaMode( DWORD dwAlphaOption )
{
	if ( m_pD3dDev == NULL )
		MyuThrow( 0, "CMglGraphicManager::SetAlphaMode()  m_pD3dDevがNULL" );

	//	無し
	if ( dwAlphaOption == MGL_ALPHA_OPT_NOTUSE )
	{
		m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}

	//	半透明
	else if ( dwAlphaOption == MGL_ALPHA_OPT_TRANSLUCENCE )
	{
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_BLENDCURRENTALPHA);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		m_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	//	加算
	else if ( dwAlphaOption == MGL_ALPHA_OPT_ADD )
	{
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_BLENDCURRENTALPHA);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		m_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		m_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	//	減算
	else if ( dwAlphaOption == MGL_ALPHA_OPT_SUBTRACT )
	{
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_BLENDCURRENTALPHA);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		m_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		m_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCCOLOR);
		m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	//	半加算
	else if ( dwAlphaOption == MGL_ALPHA_OPT_HALFADD )
	{
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_BLENDCURRENTALPHA);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pD3dDev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		m_pD3dDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		m_pD3dDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCCOLOR);
		m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	//	DDS
	else if ( dwAlphaOption == MGL_ALPHA_OPT_DDS )
	{
		m_pD3dDev->SetRenderState(D3DRS_ALPHAREF, 0x00000001);
		m_pD3dDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		m_pD3dDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	else
	{
		MyuThrow( 0, "CMglGraphicManager::SetAlphaMode()  アルファオプション %u は不明なオプションです。", dwAlphaOption );
	}

	m_dwAlphaOption=dwAlphaOption;
}


////////////////////////////////////////////////////////////////////////
//
//		シーン系メソッド
//
////////////////////////////////////////////////////////////////////////

//	画面への反映を行う
void CMglGraphicManager::UpdateScreen()
{
	if ( m_pD3dDev == NULL )
		MyuThrow( 0, "CMglGraphicManager::UpdateScreen()  m_pD3dDevがNULL" );

	//	シーンを終了
	m_pD3dDev->EndScene();

	//	画面への反映
	m_pD3dDev->Present( NULL, NULL, NULL, NULL );

	//	シーンの開始
	MyuAssert( m_pD3dDev->BeginScene(), D3D_OK,
		"CMglGraphicManager::BeginScene()  シーンの開始に失敗。" );
}

/*
//	シーンの開始
void CMglGraphicManager::BeginScene()
{
	MyuAssert( m_pD3dDev->BeginScene(), D3D_OK,
		"CMglGraphicManager::BeginScene()  シーンの開始に失敗。" );
}

//	シーンの終了
void CMglGraphicManager::EndScene()
{
	m_pD3dDev->EndScene();
}

//	画面への反映
void CMglGraphicManager::Present()
{
	m_pD3dDev->Present( NULL, NULL, NULL, NULL );
}
*/

//	自動開放用
void CMglGraphicManager::AddRefOfAutoRelease( CMyuReleaseBase* pRef )
{
	//	既に無いかチェック
	if ( m_autoReleaseAry.find( pRef ) != m_autoReleaseAry.end() )
		MyuThrow( 0, "既にリファレンス 0x%08x は存在します。", pRef );

	//DEBUGLOG( "AutoRelease 用0x%08x を追加します。", pRef );
	m_autoReleaseAry[pRef] = pRef;
}
void CMglGraphicManager::RmRefOfAutoRelease( CMyuReleaseBase* pRef )
{
	//	存在するかチェック
	AUTO_RELESE_ITR itr = m_autoReleaseAry.find( pRef );
	if ( itr == m_autoReleaseAry.end() )
	{
		/*
		char szWork[256];
		sprintf( szWork, "CMglGraphicManager::RmRefOfAutoRelease()  0x%08x のリファレンスは存在しません。", pRef );
		MessageBox( NULL, szWork, NULL, NULL );
		*/
		return;
		//MyuThrow( 0, "CMglGraphicManager::RmRefOfAutoRelease()  0x%08x のリファレンスは存在しません。", pRef );
	}

	//DEBUGLOG( "AutoRelease 用リファレンス 0x%08x を削除します。", pRef );
	m_autoReleaseAry.erase( pRef );
}

//	スプライト描画
void CMglGraphicManager::SpriteDraw( CMglTexture *pTexture, float x, float y, CONST RECT* pSrcRect, D3DCOLOR color,
		float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle )
{
	//	チェック
	if ( m_pSprite == NULL )
		MyuThrow( 99, "CMglGraphicManage::SpriteDraw()  スプライトが無効になっているか、スプライトの初期化に失敗しました。" );
	if ( pTexture->GetDirect3dTexturePtr() == NULL )
		MyuThrow( 99, "CMglGraphicManage::SpriteDraw()  IDirect3DTexture8 がNULLです。テクスチャが初期化されていない可能性があります。" );

	//	2009/01/07
	SpriteBegin();

	////// 計算処理 /////////////////////////////////

	//	srcRectにNULLを指定された場合はBMP全てをRECTに指定
	RECT texFullRect;
	if ( pSrcRect == NULL )
	{
		ZeroMemory(&texFullRect,sizeof(texFullRect));

		//	サイズ設定
		texFullRect.left = 0;
		texFullRect.top = 0;
		texFullRect.right = pTexture->GetBmpWidth();
		texFullRect.bottom = pTexture->GetBmpHeight();

		//	pSrcRect にポインタを設定
		pSrcRect = &texFullRect;
	}

	//	中心基点絵画機能
	/*if ( m_bSpriteCenterDraw == TRUE )
	{
		int nSizeX = pSrcRect->right - pSrcRect->left;
		int nSizeY = pSrcRect->bottom - pSrcRect->top;
		x -= (nSizeX/2) * fScaleX;
		y -= (nSizeY/2) * fScaleY;
	}*/

	/* 2007/02/12 これは多分要らない（0.5f指定すればいい）
	//	中心基点絵画機能
	if ( fRotationCenterX == -1 )	{
		int nSizeX = pSrcRect->right - pSrcRect->left;
		x -= (nSizeX/2) * fScaleX;
	}
	if ( fRotationCenterY == -1 )	{
		int nSizeY = pSrcRect->bottom - pSrcRect->top;
		y -= (nSizeY/2) * fScaleY;
	}
	*/

	//	x, yをD3DXVECTOR2構造体に格納
	D3DXVECTOR2 vctPos;
	vctPos.x = x;
	vctPos.y = y;

	//	スケール
	D3DXVECTOR2 vctScale;
	vctScale.x = fScaleX;
	vctScale.y = fScaleY;

	//	回転の中心
	D3DXVECTOR2 vctRtCenter;
	vctRtCenter.x = (pSrcRect->right - pSrcRect->left) * fRotationCenterX * fScaleX;
	vctRtCenter.y = (pSrcRect->bottom - pSrcRect->top) * fRotationCenterY * fScaleY;

	/*	スプライトはアルファオプション効かないっぽい
	//	アルファオプション
	DWORD dwAlphaOptionBkup=0;
	if ( dwAlphaOption != MGL_ALPHA_OPT_NOCHANGE )
	{
		//	戻す時のためにバックアップを取っておく
		dwAlphaOptionBkup = m_myudg->GetAlphaMode();
		m_myudg->SetAlphaMode( dwAlphaOption );
	}*/

	//	角度からRadianに。更に左回転になっているので右回転に
	float fRad = AngleToRad(-fAngle);

	//////////////////////////////////////////////////////////////////////////////

	//	絵画
	MyuAssert( m_pSprite->Draw( pTexture->GetDirect3dTexturePtr(),
		pSrcRect, &vctScale, &vctRtCenter, fRad, &vctPos, color ), D3D_OK,
		"CMglGraphicManager::SpriteDraw()  m_pSprite->Draw()に失敗" );
}

//	スプライトのBegin()
void CMglGraphicManager::SpriteBegin()
{
	if( m_pSprite != NULL && m_bSpriteBegun == FALSE ){
		MyuAssert( m_pSprite->Begin(), D3D_OK,
			"CMglGraphicManager::SpriteBegin()  m_pSprite->Begin()に失敗" );
		m_bSpriteBegun = TRUE;
	}
}
//	スプライトのEnd()
void CMglGraphicManager::SpriteEnd()
{
	if( m_pSprite != NULL && m_bSpriteBegun == TRUE ){
		MyuAssert( m_pSprite->End(), D3D_OK,
			"CMglGraphicManager::SpriteEnd()  m_pSprite->End()に失敗" );
		m_bSpriteBegun = FALSE;
	}
}

void CMglGraphicManager::DrawPrimitiveUpMyuVertex(MGL_VERTEX *pMglVertexs, int nVertexCount, D3DPRIMITIVETYPE primitiveType)
{
	MyuAssert( m_pD3dDev->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, nVertexCount, pMglVertexs, sizeof(MGL_VERTEX)), D3D_OK,
			"CMglGraphicManager::DrawPrimitiveUpMyuVertexSquare()  DrawPrimitiveUP()に失敗" );
}
														

////////////////////////////////////////////////////////////
//
//	デフォルト CMglGraphicManager インスタンス関連
//
CMglGraphicManager* GetDefaultGd()
{
	CMglStackInstance("CMglGraphicManager::GetDefaultGd");
	if ( g_pDefaultGd == NULL )
	{
		MyuThrow2( 0, MGLMSGNO_GRP_MANAGER_MULTI_INSTANCE,
			"CMglGraphicManager のインスタンスが存在しないか複数存在するため省略する事は出来ません。" );
	}
	return g_pDefaultGd;
}
