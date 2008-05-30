//////////////////////////////////////////////////////////
//
//	MglLayers2
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglLayers2.h"


//	コンストラクタ
CMglLayers2::CMglLayers2()
{
	p_layerInfos = new LAYERINFOS_MAP;
	p_indexs = new INDEXS_MAP;

	m_pPrevTargetSurface = NULL;
}

//	デストラクタ
CMglLayers2::~CMglLayers2()
{
	Release();

	SAFE_DELETE( p_layerInfos );
	SAFE_DELETE( p_indexs );
}

//	開放
void CMglLayers2::Release()
{
	CMglImageManager::Release();
	DeleteAll();
}

//	全てのレイヤーを削除（現時点ではRelease()と同じ）
void CMglLayers2::DeleteAll()
{
	p_layerInfos->clear();
	p_indexs->clear();

	CMglImageManager::DeleteAll();
}

//	初期化
void CMglLayers2::Init( CMglGraphicManager *in_m_myudg, const char* in_szDummyFile, D3DCOLOR colorKey )
{
	//	内部変数へコピー
	strcpy( m_szDummyFile, in_szDummyFile );
	m_colorKey = colorKey;

	//	CMglImageManagerのInit()を呼び出す
	CMglImageManager::Init( in_m_myudg );

	//	レンダリング用サーフェスの初期化
	m_renderingSurface.Init( in_m_myudg );
	m_renderingSurface.Create();
}

//	レイヤーの追加
void CMglLayers2::Add( const char *szBufferName )
{
	CMglImage *pSurface = AddEntry( szBufferName );

	//	CreateFromFile()は良くエラーを起こすのでExceptionを書き換える
	try
	{
		pSurface->Create( m_szDummyFile, TRUE, m_colorKey );
		//pSurface->CreateFromFile( m_szDummyFile, TRUE, m_colorKey );
		//pSurface->CreateFromFile( m_szDummyFile, FALSE, m_colorKey );	//	重いイイイ_|￣|○

		//	ダミーサーフェスのサイズチェック
		if ( pSurface->GetBmpWidth() != m_myudg->GetDispX() ||
			 pSurface->GetBmpHeight() != m_myudg->GetDispY() )
		{
			MyuThrow( 0, "ダミーサーフェスは画面のサイズと一致していなければいけません。" );
		}

		pSurface->Clear();
	}
	catch( MyuCommonException except )
	{
		static MyuCommonException except2;
		sprintf( except2.szErrMsg, "CMglLayers2::Add(\"%s\")\r\n"
			"0x%08x %s", szBufferName, except.nErrCode, except.szErrMsg );
		throw except2;
	}
	catch( ... )
	{
		MyuThrow( 0, "CMglLayers2::Add()  Unknown Exception Error." );
	}
}

//	レイヤーの追加（Pre）
CMglImage* CMglLayers2::AddEntry( const char *szBufferName )
{
	//	indexs
	INDEXS_MAP &indexs = *p_indexs;
	LAYERINFOS_MAP &layerInfos = *p_layerInfos;
	indexs[layerInfos.size()] = szBufferName;

	//	layerInfos
	LAYERINFO layerInfo;
	ZeroMemory( &layerInfo, sizeof(LAYERINFO) );
	layerInfo.bShow = TRUE;
	layerInfo.color = 0xffffffff;
	layerInfos[szBufferName] = layerInfo;

	return CMglImageManager::Add( szBufferName );
}

//	レイヤーを取得
CMglImage* CMglLayers2::GetRenderingSurface( const char *szLayerName )
{
	InitCheck();

	//	前回のレンダリングを反映
	AdaptRenderingSurface();

	//	ターゲットサーフェスを取得し、コピーしてくる
	CMglImageManager::Get( szLayerName )->CopyRectToOther(&m_renderingSurface);

	//	ターゲットサーフェスを保持
	m_pPrevTargetSurface = CMglImageManager::Get( szLayerName );
	if ( m_pPrevTargetSurface == NULL )
		MyuThrow( 0, "CMglLayers2::GetRenderingSurface()  なんかNULL㌧で来ました（何" );

	//	偽のレンダリング用サーフェスを復帰
	return &m_renderingSurface;
}

//	前回のレンダリングを反映
void CMglLayers2::AdaptRenderingSurface()
{
	//	m_pPrevTargetSurfaceがNULL→初回なので前回のレンダリングは無い
	if ( m_pPrevTargetSurface != NULL )
	{
		m_renderingSurface.CopyRectToOther(m_pPrevTargetSurface);

		//	初期化
		m_pPrevTargetSurface = NULL;
	}
}

//	exを設定するです
void CMglLayers2::SetLayerOption( const char *szLayerName, RECT *rect, D3DCOLOR color )
{
	SetLayerOption( szLayerName, rect );
	SetLayerOption( szLayerName, color );
}

//	exを設定するです
void CMglLayers2::SetLayerOption( const char *szLayerName, RECT *rect )
{
	InitCheck();

	//	てかあんの…？
	if ( p_layerInfos->find( szLayerName ) == p_layerInfos->end() )
	{
		MyuThrow( 0, "CMglLayers2::SetLayerOption()  レイヤー %s は存在しません。", szLayerName );
	}

	LAYERINFOS_MAP &layerInfos = *p_layerInfos;

	if ( rect == NULL )
		ZeroMemory( &layerInfos[szLayerName].rect, sizeof(RECT) );	//	NULLなら0,0,0,0
	else
		layerInfos[szLayerName].rect = *rect;						//	構造体まるこぴー
}

//	exを設定するです
void CMglLayers2::SetLayerOption( const char *szLayerName, D3DCOLOR color )
{
	InitCheck();

	//	てかあんの…？
	if ( p_layerInfos->find( szLayerName ) == p_layerInfos->end() )
	{
		MyuThrow( 0, "CMglLayers2::SetLayerOption()  レイヤー %s は存在しません。", szLayerName );
	}

	LAYERINFOS_MAP &layerInfos = *p_layerInfos;

	layerInfos[szLayerName].color = color;
}


//	画面への反映
void CMglLayers2::OnDraw( D3DCOLOR baseColor )
{
	InitCheck();

	//if ( p_buffers->size() == 0 )
	//	MyuThrow( 0, "CMglLayers2::OnDraw() レイヤーが空です。" );

	//	前回のレンダリングを反映
	AdaptRenderingSurface();

	//	バックバッファにレンダリング。ついでに画面をクリア
	m_myudg->SetRenderBackBuffer();
	m_myudg->Clear( baseColor );

	//	レイヤー結合ループ
	for ( int i=0; i<m_buffers.Size(); i++ )
	{
		LAYERINFO *pInfo = &iLayerInfos(i);
		CMglImage *pSfc = iBuffers(i);

		if ( pInfo->bShow == TRUE )
		{
			//pSfc->XDraw();
			//pSfc->Draw( pInfo->rect.left, pInfo->rect.top, NULL, pInfo->color );

			if ( pInfo->rect.left == pInfo->rect.right || pInfo->rect.top == pInfo->rect.bottom )
				pSfc->Draw( pInfo->rect.left, pInfo->rect.top, NULL, pInfo->color );
			else
				pSfc->Draw( pInfo->rect.left, pInfo->rect.top, &pInfo->rect, pInfo->color );
		}
	}

	m_myudg->UpdateScreen();
}

