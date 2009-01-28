//////////////////////////////////////////////////////////
//
//	MglD3dTexture
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglD3dTexture.h"

////////////////////////////////////////////////////////////////////

//	コンストラクタ
CMglD3dTexture::CMglD3dTexture()
{
	m_myudg = NULL;
	m_pTexture = NULL;
	m_pSurface = NULL;
	d3d = NULL;
	//m_bCenterDraw = FALSE;
	m_colorKey = D3DCOLOR_PINK;
	m_bRenderTarget = FALSE;
	m_bLocked = FALSE;
	m_pBitmapData = NULL;
	ZeroMemory(&m_imgInfo,sizeof(m_imgInfo));
}


//	初期化
void CMglD3dTexture::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();
}

//	開放
void CMglD3dTexture::Release()
{
	SAFE_DELETE( m_pBitmapData );
	SAFE_RELEASE( m_pTexture );
	SAFE_RELEASE( m_pSurface );
}


//	ファイルから読み込み
//	bRenderTargetをTRUEにした場合はPOOLも D3DPOOL_MANAGED として読み込まれる。
//void CMglD3dTexture::CreateTextureFromFile( LPCSTR szFileName, BOOL bRenderTarget, D3DCOLOR colorKey )
void CMglD3dTexture::CreateTextureFromFileEx( LPCSTR szFileName, int nForceBmpWidth, int nForceBmpHeight,
	BOOL bRenderTarget, D3DCOLOR colorKey, DWORD dwFilter, DWORD dwMapFilter )
{
	InitCheck();	//	初期化チェック

	//	二回目以降の呼び出しを考慮し一端Release
	Release();

	//	bRenderTargetの反映
	DWORD usage;
	D3DPOOL pool;
	if ( bRenderTarget ){
		usage = D3DUSAGE_RENDERTARGET;
		pool = D3DPOOL_DEFAULT; // D3DPOOL_MANAGED; <= 逆…？
	}
	else{
		usage = 0;
		pool = D3DPOOL_MANAGED; // D3DPOOL_DEFAULT; <= 逆…？
	}

	//	記憶しておく
	m_colorKey = colorKey;
	m_bRenderTarget = bRenderTarget;

	/*	2007/01/10  D3DX_FILTER_NONE にしたら要らなくなる系じゃない系みたいな系？
	m_imgInfo.Width = nForceBmpWidth;
	m_imgInfo.Height = nForceBmpHeight;*/

	//	作成
	//DWORD r = D3DXCreateTextureFromFileEx( d3d, szFileName, x, y, D3DX_DEFAULT,
	DWORD r = D3DXCreateTextureFromFileEx(
		d3d, szFileName,
/*		D3DX_DEFAULT,	//	Width -  この値が 0 または D3DX_DEFAULT の場合、ディメンジョンはファイルから取得される。
		D3DX_DEFAULT,	//	Height - この値が 0 または D3DX_DEFAULT の場合、ディメンジョンはファイルから取得される。*/
		nForceBmpWidth,	//	Width -  この値が 0 または D3DX_DEFAULT の場合、ディメンジョンはファイルから取得される。
		nForceBmpHeight,//	Height - この値が 0 または D3DX_DEFAULT の場合、ディメンジョンはファイルから取得される。
		D3DX_DEFAULT,	//	MipLevels
		usage,			//	Usage - 0 または D3DUSAGE_RENDERTARGET。このフラグに D3DUSAGE_RENDERTARGET を設定すると、そのサーフェスはレンダリング ターゲットとして使用されることを示す。
		m_myudg->GetFormat(),//	Format - テクスチャに対して要求されたピクセル フォーマットを記述する、D3DFORMAT 列挙型のメンバ。
		pool,			//	Pool - テクスチャの配置先となるメモリ クラスを記述する、D3DPOOL 列挙型のメンバ。
		dwFilter, dwMapFilter, colorKey, &m_imgInfo, NULL, &m_pTexture );
//		D3DX_FILTER_NONE, D3DX_FILTER_NONE, colorKey, &m_imgInfo, NULL, &m_pTexture );
//		D3DX_FILTER_POINT, D3DX_FILTER_POINT, colorKey, &m_imgInfo, NULL, &m_pTexture );

	//	エラーコードによってメッセージを変更する
	if ( r == E_OUTOFMEMORY )
		MyuThrow2( r, 0x0201, "%s の読み込みに失敗。VRAMまたはメモリが不足しています。", szFileName );
	else if ( r == D3DERR_OUTOFVIDEOMEMORY )
		MyuThrow2( r, 0x0202, "%s の読み込みに失敗。VRAMが不足しています。", szFileName );
	else if ( r == D3DERR_NOTAVAILABLE ) 
		MyuThrow2( r, 0x0202, "%s の読み込みに失敗。(DxErr=D3DERR_NOTAVAILABLE)", szFileName );
	else if ( r == D3DERR_INVALIDCALL ) 
		MyuThrow2( r, 0x0202, "%s の読み込みに失敗。(DxErr=D3DERR_INVALIDCALL)", szFileName );
	else if ( r == D3DXERR_INVALIDDATA ) 
		MyuThrow2( r, 0x0202, "%s の読み込みに失敗。(DxErr=D3DXERR_INVALIDDATA)", szFileName );
	else if ( r != S_OK ) 
		MyuThrow2( r, 0x0203, "CMglImage::CreateFromFile()  D3DXCreateTextureFromFileEx(%s)に失敗", szFileName );

	//	SetRenderとかで必要なのでサーフェス取得しておく
	_GetSurface();
}


//	生成
void CMglD3dTexture::Create( int x, int y, BOOL bRenderTarget )
{
	_MGL_DEBUGLOG( "+ CMglD3dTexture::Create()" );

	InitCheck();	//	初期化チェック

	//	二回目以降の呼び出しを考慮し一端Release
	Release();

	if ( x <= 0 )	x = m_myudg->GetDispX();
	if ( y <= 0 )	y = m_myudg->GetDispY();
	/*m_nBmpSizeX = x;
	m_nBmpSizeY = y;*/

	//	2008/06/28  m_imgInfoも設定してあ・げ・る。
	m_imgInfo.Width = x;
	m_imgInfo.Height = y;

	/*int i;
	ZeroMemory( m_vertices, sizeof(MYU_VERTEX)*4 );*/

	//	m_myudg->backBufferDesc.Format
	if ( bRenderTarget == TRUE ) {
		MyuAssert( D3DXCreateTexture( d3d, x, y, D3DX_DEFAULT, D3DUSAGE_RENDERTARGET, m_myudg->GetFormat(), D3DPOOL_DEFAULT, &m_pTexture ), D3D_OK,
			"CMglD3dTexture::Create()  D3DXCreateTexture(VRAM)に失敗" );
	}
	else {
		MyuAssert( D3DXCreateTexture( d3d, x, y, D3DX_DEFAULT, 0, m_myudg->GetFormat(), D3DPOOL_MANAGED, &m_pTexture ), D3D_OK,
			"CMglD3dTexture::Create()  D3DXCreateTexture(SYSMEM)に失敗" );
	}

	//	記憶しておく
	m_bRenderTarget = bRenderTarget;

	/*
	//SetGradation();

	//	テクスチャのサーフェスを取得する
	MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
		"CMglD3dTexture::Create()  GetSurfaceLevel()に失敗" );

	//	スプライト作成
	MyuAssert( D3DXCreateSprite( d3d, &this->m_pSprite ), D3D_OK,
		"CMglD3dTexture::Init  D3DXCreateSprite()に失敗" );

	//	クリアする
	//Clear();

	createFlg = TRUE;
	*/

	//	SetRenderとかで必要なのでサーフェス取得しておく
	_GetSurface();

	//	2008/06/30 なんでクリアしないんだろうかー？
	//Clear();
	Clear(0);	//	0にしないとカラーキー＋白に勝手にされてしまう・・・

	_MGL_DEBUGLOG( "- CMglD3dTexture::Create()" );
}

//////////////////////////////////////////////////////////////////////////////////////

void CMglD3dTexture::SetD3dStageTexture(DWORD nStage)
{
	//	テクスチャの設定
	MyuAssert( d3d->SetTexture(nStage, m_pTexture), D3D_OK,
		"CMglD3dTexture::SetD3dTexture()  d3d->SetTexture()に失敗" );
}

//	絵画先をこのサーフェスに設定する
void CMglD3dTexture::SetRender()
{
	CreateCheck();	//	Createチェック
	LockedCheck();

#if _MGL_DXVER == 9
	MyuAssert( d3d->SetRenderTarget( 0, m_pSurface ), D3D_OK,
#else
	MyuAssert( d3d->SetRenderTarget( m_pSurface, NULL ), D3D_OK, //m_myudg->lpZbuffer
#endif
		"CMglD3dTexture::SetRender()  SetRenderTarget()に失敗" );
}

//	クリアする
/*void CMglImage::Clear()
{
	//	m_colorKeyが関連するのでデフォルト引数には出来ないのでれす
	Clear( m_colorKey & 0x00ffffff );
}*/

/*
	######## D3DXCreateRenderToSurface でやるようにしよう… ########
*/

//	クリアする
void CMglD3dTexture::Clear( D3DCOLOR color )
{
	Paint(NULL,color);
}

void CMglD3dTexture::Clear__( D3DCOLOR color )
{
	CreateCheck();	//	Createチェック
	LockedCheck();

	if ( m_bRenderTarget == TRUE )
	{
		//	現在のレンダーを保持（勝手に書き換えちゃマズいからなｗ）
		_MGL_IDirect3DSurface* bkupRender;
#if _MGL_DXVER == 9
		d3d->GetRenderTarget( 0, &bkupRender );
#else
		d3d->GetRenderTarget( &bkupRender );
#endif
		SetRender();
		//d3d->Clear( 0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0 );	//	|D3DCLEAR_ZBUFFER
		m_myudg->Clear( color );	//	|D3DCLEAR_ZBUFFER
		//	D3DCOLOR_FULLALPHA

		//	レンダーを元に戻す
#if _MGL_DXVER == 9
		MyuAssert( d3d->SetRenderTarget( 0, bkupRender ), D3D_OK,
#else
		MyuAssert( d3d->SetRenderTarget( bkupRender, NULL ), D3D_OK, //m_myudg->lpZbuffer
#endif
			"CMglD3dTexture::Clear()  レンダーを戻すのに失敗" );
	}
	else
	{
		/*
		//	別にクリアされたサーフェスを作成してそこからコピー、と言う面倒な処理(´Д`)
		CMglD3dTexture workSurface;
		workSurface.Init( m_myudg );
		//workSurface.Create();	//	レンダリング先はTRUEにしないと無限再帰してしまう
		workSurface.Create(TRUE);	//	レンダリング先はTRUEにしないと無限再帰してしまう
		workSurface.Clear( color );
		CopyRectToThis( &workSurface );
		*/

		//	2008/06/29  CMglBitmapData::Fill()実装したんだからFill()使えばよくネ？
		this->GetIternalBitmapData()->Fill(color);
	}
}

//	指定された矩形領域を塗りつぶす
void CMglD3dTexture::Paint( RECT* pRect, D3DCOLOR color )
{
	CreateCheck();	//	Createチェック
	LockedCheck();

	if ( m_bRenderTarget == TRUE )
	{
		//	現在のレンダーを保持（勝手に書き換えちゃマズいからなｗ）
		_MGL_IDirect3DSurface* bkupRender;
#if _MGL_DXVER == 9
		d3d->GetRenderTarget( 0, &bkupRender );
#else
		d3d->GetRenderTarget( &bkupRender );
#endif
		SetRender();
		//d3d->Clear( 0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0 );	//	|D3DCLEAR_ZBUFFER
		m_myudg->Paint( pRect, color );	//	|D3DCLEAR_ZBUFFER

		//	レンダーを元に戻す
#if _MGL_DXVER == 9
		MyuAssert( d3d->SetRenderTarget( 0, bkupRender ), D3D_OK,
#else
		MyuAssert( d3d->SetRenderTarget( bkupRender, NULL ), D3D_OK, //m_myudg->lpZbuffer
#endif
			"CMglD3dTexture::Clear()  レンダーを戻すのに失敗" );
	}
	else
	{
		/*
		//	別にクリアされたサーフェスを作成してそこからコピー、と言う面倒な処理(´Д`)
		CMglImage workSurface;
		workSurface.Init( m_myudg );
		//workSurface.Create();
		workSurface.Create(TRUE);	//	レンダリング先はTRUEにしないと無限再帰してしまう
		workSurface.Paint( rect, color );
		workSurface.Paint( rect, color );
		CopyRectToThis( &workSurface );
		*/

		//	2008/06/29  CMglBitmapData::Fill()実装したんだからFill()使えばよくネ？
		if ( pRect != NULL )
			this->GetIternalBitmapData()->Fill(color,*pRect);
		else
			this->GetIternalBitmapData()->Fill(color);
	}
}


//	イテレータ ////////////////////////////////////////////////

CMglBitmapData* CMglD3dTexture::GetIternalBitmapData()
{
	/*if ( m_pBitmapData == NULL )
		m_pBitmapData = new CMglBitmapData(this);*/
	return m_pBitmapData;
}

/*
CMglD3dTexture::iterator CMglD3dTexture::begin()
{

}

CMglD3dTexture::iterator CMglD3dTexture::end()
{


}
*/


//	2007/01/10  スケール取得
//	# テクスチャ領域は2の倍数になる。その内の0.?fがBMPの領域かを算出する
MGLTUTV CMglD3dTexture::GetTuTv()
{
	MGLTUTV t;
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	t.tu = m_imgInfo.Width / (float)texDesc.Width;
	t.tv = m_imgInfo.Height / (float)texDesc.Height;
	return t;
}
