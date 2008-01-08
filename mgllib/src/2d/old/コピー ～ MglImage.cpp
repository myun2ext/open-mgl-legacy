//////////////////////////////////////////////////////////
//
//	MglImage
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglImage.h"

//	コンストラクタ
CMglImage::CMglImage()
{
	m_nSfcID = g_nSfcCount;
	g_nSfcCount++;
	//_MGL_DEBUGLOG( "+ CMglImage::CMglImage( ID : %d )", g_nSfcCount );

	m_myudg = NULL;
	m_pTexture = NULL;
	m_pSurface = NULL;
	m_pSprite = NULL;
	d3d = NULL;

	//	フラグを初期化
	initFlg = FALSE;
	createFlg = FALSE;
	m_bCenterDraw = FALSE;
}

//	デストラクタ
CMglImage::~CMglImage()
{
	//_MGL_DEBUGLOG( "+ CMglImage::~CMglImage( ID : %d )", m_nSfcID );
//	_MGL_DEBUGLOG( "+ CMglImage::デストラクタ" );
	Release();
//	_MGL_DEBUGLOG( "- CMglImage::デストラクタ" );
}


//	初期化
void CMglImage::Init( CMglGraphicManager* in_myudg, const char* szName )
{
	//_MGL_DEBUGLOG( "+ CMglImage::Init()" );

	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();
	m_colorKey = D3DCOLOR_BLACK;
	if ( szName != NULL )
		m_sfcName = szName;

	//	自動開放用にリファレンスを追加
	m_myudg->AddRefOfAutoRelease( this );

	initFlg = TRUE;
	//_MGL_DEBUGLOG( "- CMglImage::Init()" );
}

//	明示的開放
void CMglImage::Release()
{
//	_MGL_DEBUGLOG( "+ CMglImage::Release()" );

	//	自動開放用のリファレンスを削除
	DELREF();

	SAFE_RELEASE( m_pSurface );
	SAFE_RELEASE( m_pTexture );
//	SAFE_RELEASE( m_pSprite );
//	_MGL_DEBUGLOG( "- CMglImage::Release()" );
}

//	ファイルから読み込み
//	カラーキーはアルファ未使用のときのみ有効
//	カラーキーを使用したくない場合はcolorKeyを0に
//	カラーキーを有効にしたい場合は0xff******にする
void CMglImage::CreateFromFile( LPCSTR szFileName, BOOL bRenderTarget, D3DCOLOR colorKey )
{
	_MGL_DEBUGLOG( "+ CMglImage::CreateFromFile( \"%s\", %d, 0x%08X )", szFileName, bRenderTarget, colorKey );

	InitCheck();	//	初期化チェック

	//	二回目以降の呼び出しを考慮し一端Release
	Release();

	//////////////////////////////////////////////////////////////////////////////
	//
	//	D3DXGetImageInfoFromFile()が無いので無理矢理サイズ取得です。あほくせぇ(´Д`)
	//

	IDirect3DTexture8* m_pTexture2;	//	テクスチャ
	D3DXIMAGE_INFO imgInfo;

	MyuAssert( D3DXCreateTextureFromFileEx( d3d, szFileName, 256, 256, D3DX_DEFAULT,
		0, /* m_myudg->backBufferDesc.Format */ m_myudg->GetFormat(), D3DPOOL_SYSTEMMEM,
		D3DX_FILTER_POINT, D3DX_FILTER_POINT, colorKey, &imgInfo, NULL, &m_pTexture2 ),
		D3D_OK, "CMglImage::CreateFromFile()  %s のイメージ情報取得に失敗。", szFileName );

	int x = imgInfo.Width;
	int y = imgInfo.Height;

	SAFE_RELEASE( m_pTexture2 );

	///////////////////////////////////////////////////////////////////
	//
	//	テクスチャを作成する
	//
	//	D3DXCreateTextureFromFileEx()にて作成を行うが、
	//	これはあくまでカラーキーを設定するためだけ。
	//	なお、画像は引き伸ばされて飲まれるので、後々再読み込みする
	//

	if ( bRenderTarget == TRUE ) {
		DWORD r = D3DXCreateTextureFromFileEx( d3d, szFileName, x, y, D3DX_DEFAULT,
			D3DUSAGE_RENDERTARGET, /* m_myudg->backBufferDesc.Format */ m_myudg->GetFormat(), D3DPOOL_DEFAULT,
			D3DX_FILTER_POINT, D3DX_FILTER_POINT, colorKey, &imgInfo, NULL, &m_pTexture );

		if ( r == E_OUTOFMEMORY )
			MyuThrow2( r, 0x0201, "%s の読み込みに失敗。VRAMまたはメモリが不足しています。", szFileName );
		else if ( r == D3DERR_OUTOFVIDEOMEMORY )
			MyuThrow2( r, 0x0202, "%s の読み込みに失敗。VRAMが不足しています。", szFileName );
		else if ( r != S_OK ) 
			MyuThrow2( r, 0x0203, "CMglImage::CreateFromFile()  D3DXCreateTextureFromFileEx(VRAM,%s)に失敗", szFileName );
	}
	else {
		DWORD r = D3DXCreateTextureFromFileEx( d3d, szFileName, x, y, D3DX_DEFAULT,
			0, /* m_myudg->backBufferDesc.Format */ m_myudg->GetFormat(), D3DPOOL_MANAGED,
			D3DX_FILTER_POINT, D3DX_FILTER_POINT, colorKey, &imgInfo, NULL, &m_pTexture );

		if ( r == E_OUTOFMEMORY )
			MyuThrow( r, "%s の読み込みに失敗。メモリが足りません。", szFileName );
		else if ( r != S_OK ) 
			MyuThrow( r, "CMglImage::CreateFromFile()  D3DXCreateTextureFromFileEx(MANAGED,%s)に失敗", szFileName );
	}

	m_nBmpSizeX = x;
	m_nBmpSizeY = y;

	int i;
	ZeroMemory( m_vertices, sizeof(MYU_VERTEX)*4 );

	//	実サイズを算出(GetRealTexSizeを使う方法もあるが、一応テクスチャから取ってくる)
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	nRealSizeX = texDesc.Width;
	nRealSizeY = texDesc.Height;

	//	比率設定
	fRealTexTu = (float)x / (float)nRealSizeX;
	fRealTexTv = (float)y / (float)nRealSizeY;

	//	消そうとも思ったが一応デフォルト値として入れておくか…
	//	X,Yをまずは
	m_vertices[VERTEXNO_LT].x = m_vertices[VERTEXNO_LB].x = 0+X_ADJ;
	m_vertices[VERTEXNO_LT].y = m_vertices[VERTEXNO_RT].y = 0+Y_ADJ;
	m_vertices[VERTEXNO_RB].x = m_vertices[VERTEXNO_RT].x = x+X_ADJ;
	m_vertices[VERTEXNO_RB].y = m_vertices[VERTEXNO_LB].y = y+Y_ADJ;

	//	U,Vを
	m_vertices[VERTEXNO_LT].tu = m_vertices[VERTEXNO_LB].tu = 0.0f;
	m_vertices[VERTEXNO_LT].tv = m_vertices[VERTEXNO_RT].tv = 0.0f;
	//m_vertices[VERTEXNO_RB].tu = m_vertices[VERTEXNO_RT].tu = 1.0f;
	//m_vertices[VERTEXNO_RB].tv = m_vertices[VERTEXNO_LB].tv = 1.0f;
	m_vertices[VERTEXNO_RT].tu = m_vertices[VERTEXNO_RB].tu = fRealTexTu;
	m_vertices[VERTEXNO_LB].tv = m_vertices[VERTEXNO_RB].tv = fRealTexTv;


	//	その他共通
	for ( i=0; i<4; i++ )
	{
		m_vertices[i].z = 0.0f;
		m_vertices[i].rhw = 1.0f;
		m_vertices[i].color = 0xffffffff;
	}
	//SetGradation();

	//	テクスチャのサーフェスを取得する
	MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
		"CMglImage::Create()  GetSurfaceLevel()に失敗" );

	m_colorKey = colorKey;
	if ( m_colorKey != 0 )	//	カラーキーを使用する場合は0xffを念のためつけておく
		m_colorKey |= 0xff000000;

	//	スプライト作成
	MyuAssert( D3DXCreateSprite( d3d, &this->m_pSprite ), D3D_OK,
		"CMglImage::Init  D3DXCreateSprite()に失敗" );

	/////////////////////////////////////////////////////////////////////////
	//
	//	イメージを再読み込みする
	//

	IDirect3DSurface8* m_pTempSurface;	//	一時サーフェス
	MyuAssert( d3d->CreateImageSurface( x, y, m_myudg->GetFormat(), &m_pTempSurface ),
		D3D_OK, "CMglImage::CreateFromFile()  CreateImageSurface()に失敗" );

	MyuAssert( D3DXLoadSurfaceFromFile( m_pTempSurface, NULL, NULL, szFileName, NULL, D3DX_FILTER_POINT, 0xffff00ff, NULL ),
		D3D_OK, "CMglImage::CreateFromFile()  D3DXLoadSurfaceFromFile()に失敗" );

	//MyuAssert( d3d->CopyRects(m_pTempSurface, NULL, 0, m_pSurface, NULL),
	MyuAssert( d3d->CopyRects(m_pTempSurface, NULL, 0, m_pSurface, NULL),
		D3D_OK, "CMglImage::CreateFromFile()  CopyRects()に失敗" );

	SAFE_RELEASE( m_pTempSurface );

	m_bRenderTarget = bRenderTarget;
	createFlg = TRUE;

	_MGL_DEBUGLOG( "- CMglImage::CreateFromFile( \"%s\" )", szFileName );
}

//	サーフェイスの生成
void CMglImage::Create( int x, int y, BOOL bRenderTarget )
{
	_MGL_DEBUGLOG( "+ CMglImage::Create()" );

	InitCheck();	//	初期化チェック

	if ( x == 0 )	x = m_myudg->GetDispX();
	if ( y == 0 )	y = m_myudg->GetDispY();
	m_nBmpSizeX = x;
	m_nBmpSizeY = y;

	int i;
	ZeroMemory( m_vertices, sizeof(MYU_VERTEX)*4 );

	//	m_myudg->backBufferDesc.Format
	if ( bRenderTarget == TRUE ) {
		MyuAssert( D3DXCreateTexture( d3d, x, y, D3DX_DEFAULT, D3DUSAGE_RENDERTARGET, m_myudg->GetFormat(), D3DPOOL_DEFAULT, &m_pTexture ), D3D_OK,
			"CMglImage::Create()  D3DXCreateTexture(VRAM)に失敗" );
	}
	else {
		MyuAssert( D3DXCreateTexture( d3d, x, y, D3DX_DEFAULT, 0, m_myudg->GetFormat(), D3DPOOL_MANAGED, &m_pTexture ), D3D_OK,
			"CMglImage::Create()  D3DXCreateTexture(SYSMEM)に失敗" );
	}

	//	実サイズを算出(GetRealTexSizeを使う方法もあるが、一応テクスチャから取ってくる)
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	nRealSizeX = texDesc.Width;
	nRealSizeY = texDesc.Height;

	//	比率設定
	fRealTexTu = (float)x / (float)nRealSizeX;
	fRealTexTv = (float)y / (float)nRealSizeY;

	//	消そうとも思ったが一応デフォルト値として入れておくか…
	//	X,Yをまずは
	m_vertices[VERTEXNO_LT].x = m_vertices[VERTEXNO_LB].x = 0+X_ADJ;
	m_vertices[VERTEXNO_LT].y = m_vertices[VERTEXNO_RT].y = 0+Y_ADJ;
	m_vertices[VERTEXNO_RB].x = m_vertices[VERTEXNO_RT].x = x+X_ADJ;
	m_vertices[VERTEXNO_RB].y = m_vertices[VERTEXNO_LB].y = y+Y_ADJ;

	//	U,Vを
	m_vertices[VERTEXNO_LT].tu = m_vertices[VERTEXNO_LB].tu = 0.0f;
	m_vertices[VERTEXNO_LT].tv = m_vertices[VERTEXNO_RT].tv = 0.0f;
	//m_vertices[VERTEXNO_RB].tu = m_vertices[VERTEXNO_RT].tu = 1.0f;
	//m_vertices[VERTEXNO_RB].tv = m_vertices[VERTEXNO_LB].tv = 1.0f;
	m_vertices[VERTEXNO_RT].tu = m_vertices[VERTEXNO_RB].tu = fRealTexTu;
	m_vertices[VERTEXNO_LB].tv = m_vertices[VERTEXNO_RB].tv = fRealTexTv;

	//	その他共通
	for ( i=0; i<4; i++ )
	{
		m_vertices[i].z = 0.0f;
		m_vertices[i].rhw = 1.0f;
		m_vertices[i].color = 0xffffffff;
	}
	//SetGradation();

	//	テクスチャのサーフェスを取得する
	MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
		"CMglImage::Create()  GetSurfaceLevel()に失敗" );

	//	スプライト作成
	MyuAssert( D3DXCreateSprite( d3d, &this->m_pSprite ), D3D_OK,
		"CMglImage::Init  D3DXCreateSprite()に失敗" );

	//	クリアする
	//Clear();

	m_bRenderTarget = bRenderTarget;

	createFlg = TRUE;

	_MGL_DEBUGLOG( "- CMglImage::Create()" );
}


//void DrawEx( float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
//	float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE );

//	Texture(DrawPrimitiveUP)で絵画
void CMglImage::TextureDraw(
	float x, float y, RECT* srcRect, float fScaleX, float fScaleY,
	float fRotationCenterX, float fRotationCenterY, float fAngle,
	VERTEX_COLORS* vertexColors, DWORD dwAlphaOption )
{
	CreateCheck();	//	Createチェック

	//	srcRectを考慮したBMPサイズ
	int nBmpSrcX = m_nBmpSizeX;
	int nBmpSrcY = m_nBmpSizeY;

	//	転送元もどきの設定
	if ( srcRect == NULL )
	{
		m_vertices[VERTEXNO_LT].tu = m_vertices[VERTEXNO_LB].tu = 0.0f;
		m_vertices[VERTEXNO_LT].tv = m_vertices[VERTEXNO_RT].tv = 0.0f;
		//m_vertices[VERTEXNO_RB].tu = m_vertices[VERTEXNO_RT].tu = 1.0f;
		//m_vertices[VERTEXNO_RB].tv = m_vertices[VERTEXNO_LB].tv = 1.0f;
		m_vertices[VERTEXNO_RT].tu = m_vertices[VERTEXNO_RB].tu = fRealTexTu;
		m_vertices[VERTEXNO_LB].tv = m_vertices[VERTEXNO_RB].tv = fRealTexTv;
	}
	else
	{
		float fLeftTu = ((float)srcRect->left / m_nBmpSizeX) * fRealTexTu;
		float fRightTu = ((float)srcRect->right / m_nBmpSizeX) * fRealTexTu;
		float fTopTv = ((float)srcRect->top / m_nBmpSizeY) * fRealTexTv;
		float fBottomTv = ((float)srcRect->bottom / m_nBmpSizeY) * fRealTexTv;

		/*
		m_vertices[VERTEXNO_LT].tu = m_vertices[VERTEXNO_LB].tu = fLeftTu;
		m_vertices[VERTEXNO_RT].tu = m_vertices[VERTEXNO_RB].tu = fRightTu;
		m_vertices[VERTEXNO_LT].tv = m_vertices[VERTEXNO_RT].tv = fTopTv;
		m_vertices[VERTEXNO_LB].tv = m_vertices[VERTEXNO_RB].tv = fBottomTv;
		*/
		m_vertices[VERTEXNO_LT].tu = m_vertices[VERTEXNO_LB].tu = fLeftTu;
		m_vertices[VERTEXNO_RT].tu = m_vertices[VERTEXNO_RB].tu = fRightTu;
		m_vertices[VERTEXNO_LT].tv = m_vertices[VERTEXNO_RT].tv = fTopTv;
		m_vertices[VERTEXNO_LB].tv = m_vertices[VERTEXNO_RB].tv = fBottomTv;

		nBmpSrcX = srcRect->right - srcRect->left;
		nBmpSrcY = srcRect->bottom - srcRect->top;
	}
	//	中心基点絵画機能
	if ( m_bCenterDraw == TRUE )
	{
		int nSizeX = srcRect->right - srcRect->left;
		int nSizeY = srcRect->bottom - srcRect->top;
		x -= (nSizeX/2) * fScaleX;
		y -= (nSizeY/2) * fScaleY;
	}

	//	絵画先位置、及び伸縮率の設定
	m_vertices[VERTEXNO_LT].x = m_vertices[VERTEXNO_LB].x = x + X_ADJ;	//	絵画先位置X
	m_vertices[VERTEXNO_LT].y = m_vertices[VERTEXNO_RT].y = y + Y_ADJ;	//	絵画先位置Y
	m_vertices[VERTEXNO_RB].x = m_vertices[VERTEXNO_RT].x = x + X_ADJ + nBmpSrcX * fScaleX;	//	伸縮率X
	m_vertices[VERTEXNO_RB].y = m_vertices[VERTEXNO_LB].y = y + Y_ADJ + nBmpSrcY * fScaleY;	//	伸縮率Y

	//	色
	m_vertices[VERTEXNO_LT].color = vertexColors->leftTop;
	m_vertices[VERTEXNO_RT].color = vertexColors->rightTop;
	m_vertices[VERTEXNO_LB].color = vertexColors->leftBottom;
	m_vertices[VERTEXNO_RB].color = vertexColors->rightBottom;

	//	アルファオプション
	m_myudg->SetAlphaMode( dwAlphaOption );

	//	絵画
	TextureDrawPrimitive();
}


void CMglImage::TextureDrawPrimitive()
{
	CreateCheck();	//	Createチェック

	//	テクスチャの設定
	MyuAssert( d3d->SetTexture(0, m_pTexture), D3D_OK,
		"CMglImage::TextureDrawPrimitive()  SetTexture()に失敗" );

	//	絵画
	MyuAssert( d3d->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(MYU_VERTEX) ), D3D_OK,
		"CMglImage::TextureDrawPrimitive()  DrawPrimitiveUP()に失敗" );
}


//	回転・スケーリング・アルファオプション付き絵画（スプライトを使用）
void CMglImage::DrawEx(
	float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
	float x, float y, RECT *srcRect, D3DCOLOR color )
//	float x, float y, RECT *srcRect, D3DCOLOR color, DWORD dwAlphaOption )
{
	CreateCheck();	//	Createチェック

	//	srcRectにNULLを指定された場合はフルで絵画
	RECT _srcRect;
	if ( srcRect == NULL )
	{
		srcRect = &_srcRect;
		_Rect( 0, 0, m_nBmpSizeX, m_nBmpSizeY, srcRect );
	}

	//	中心基点絵画機能
	if ( m_bCenterDraw == TRUE )
	{
		int nSizeX = srcRect->right - srcRect->left;
		int nSizeY = srcRect->bottom - srcRect->top;
		x -= (nSizeX/2) * fScaleX;
		y -= (nSizeY/2) * fScaleY;
	}

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
	vctRtCenter.x = (srcRect->right - srcRect->left) * fRotationCenterX * fScaleX;
	vctRtCenter.y = (srcRect->bottom - srcRect->top) * fRotationCenterY * fScaleY;

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

	//	絵画
	MyuAssert( m_pSprite->Draw( m_pTexture, srcRect, &vctScale, &vctRtCenter, fRad, &vctPos, color ), D3D_OK,
		"CMglImage::Draw()  m_pSprite->Draw()に失敗" );

	/*	スプライトはアルファオプション効かないっぽい
	//	アルファオプションを元に戻す
	if ( dwAlphaOption != MGL_ALPHA_OPT_NOCHANGE )
	{
		m_myudg->SetAlphaMode( dwAlphaOptionBkup );
	}*/
}


//	絵画（CopyRectを使用）
void CMglImage::CopyRectToOther( CMglImage* destSurface, RECT *srcRect, int x, int y )
{
	CreateCheck();	//	Createチェック

	//if ( m_pSurface == NULL )
	//	MyuThrow( 0, "CMglImage::CopyRectToOther()  m_pSurfaceが取得されていません。");
	//	srcRectにNULLを指定された場合はフルで絵画

	D3DXLoadSurfaceFromSurface(
		destSurface->GetSurfacePtr(), NULL, NULL,
		m_pSurface, NULL, NULL,
		D3DX_FILTER_POINT, 0 );

	/*
	RECT _srcRect;
	if ( srcRect == NULL )
	{
		srcRect = &_srcRect;
		_Rect( m_nBmpSizeX, m_nBmpSizeY, srcRect );
	}
	POINT destPoint;
	destPoint.x = x;
	destPoint.y = y;

	//	そのうちクリッピングさぽーとさせるぅ

	if ( m_pSurface == destSurface->GetSurfacePtr() )
		MyuThrow(0,"CMglImage::CopyRectToOther()  destSurfaceに自分自身のサーフェスを指定することは出来ません。");

	//if (FAILED(d3d->CopyRects(m_pSurface, srcRect, 1, destSurface, &destPoint))) {
	//MyuAssert( d3d->CopyRects(m_pSurface, NULL, 1, destSurface, NULL), D3D_OK,
	MyuAssert( d3d->CopyRects(m_pSurface, srcRect, 1, destSurface->GetSurfacePtr(), &destPoint), D3D_OK,
		"CMglImage::CopyRectToOther()  CopyRect()に失敗" );
	*/
}

//	このサーフェスにCopyRect
void CMglImage::CopyRectToThis( CMglImage* srcSurface, RECT *srcRect, int x, int y )
{
	srcSurface->CopyRectToOther( this, srcRect, x, y );
}

/*
//	このサーフェスにCopyRect
void CMglImage::CopyRectToThis( CMglImage* srcSurface, RECT *srcRect, int x, int y )
{
	CreateCheck();	//	Createチェック

	//if ( m_pSurface == NULL )
	//	MyuThrow( 0, "CMglImage::CopyRectToThis()  m_pSurfaceが取得されていません。");
	//	srcRectにNULLを指定された場合はフルで絵画
	RECT _srcRect;
	if ( srcRect == NULL )
	{
		srcRect = &_srcRect;
		_Rect( m_nBmpSizeX, m_nBmpSizeY, srcRect );
	}
	POINT destPoint;
	destPoint.x = x;
	destPoint.y = y;

	if ( m_pSurface == srcSurface->GetSurfacePtr() )
		MyuThrow(0,"CMglImage::CopyRectToThis()  srcSurfaceに自分自身のサーフェスを指定することは出来ません。");

	//if (FAILED(d3d->CopyRects(srcSurface, srcRect, 1, m_pSurface, &destPoint))) {
	MyuAssert( d3d->CopyRects(srcSurface->GetSurfacePtr(), NULL, 0, m_pSurface, NULL), D3D_OK,
		"CMglImage::CopyRectToThis()  CopyRect()に失敗" );
}
*/

/*	どうせフォーマットエラー起こすので未サポート
//	絵画（CopyRectを使用）
void CMglImage::CopyRect( int x, int y, RECT *srcRect )
{
	CreateCheck();	//	Createチェック
	CopyRectToOther( x, y, srcRect, m_myudg->_GetBackBuffer() );
}
*/

//	絵画先をこのサーフェスに設定する
void CMglImage::SetRender()
{
	CreateCheck();	//	Createチェック

	MyuAssert( d3d->SetRenderTarget( m_pSurface, NULL ), D3D_OK, //m_myudg->lpZbuffer
		"CMglImage::SetRender()  SetRenderTarget()に失敗" );
}

//	クリアする
/*void CMglImage::Clear()
{
	//	m_colorKeyが関連するのでデフォルト引数には出来ないのでれす
	Clear( m_colorKey & 0x00ffffff );
}*/

//	クリアする
void CMglImage::Clear( D3DCOLOR color )
{
	CreateCheck();	//	Createチェック

	if ( m_bRenderTarget == TRUE )
	{
		//	現在のレンダーを保持（勝手に書き換えちゃマズいからなｗ）
		IDirect3DSurface8* bkupRender;
		d3d->GetRenderTarget( &bkupRender );

		SetRender();
		//d3d->Clear( 0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0 );	//	|D3DCLEAR_ZBUFFER
		m_myudg->Clear( color );	//	|D3DCLEAR_ZBUFFER
		//	D3DCOLOR_FULLALPHA

		//	レンダーを元に戻す
		MyuAssert( d3d->SetRenderTarget( bkupRender, NULL ), D3D_OK, //m_myudg->lpZbuffer
			"CMglImage::Clear()  レンダーを戻すのに失敗" );
	}
	else
	{
		//	別にクリアされたサーフェスを作成してそこからコピー、と言う面倒な処理(´Д`)
		CMglImage workSurface;
		workSurface.Init( m_myudg );
		workSurface.Create();	//	レンダリング先はTRUEにしないと無限再帰してしまう
		workSurface.Clear( color );
		CopyRectToThis( &workSurface );
	}
}

//	指定された矩形領域を塗りつぶす
void CMglImage::Paint( RECT* rect, D3DCOLOR color )
{
	CreateCheck();	//	Createチェック

	if ( m_bRenderTarget == TRUE )
	{
		//	現在のレンダーを保持（勝手に書き換えちゃマズいからなｗ）
		IDirect3DSurface8* bkupRender;
		d3d->GetRenderTarget( &bkupRender );

		SetRender();
		//d3d->Clear( 0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0 );	//	|D3DCLEAR_ZBUFFER
		m_myudg->Paint( rect, color );	//	|D3DCLEAR_ZBUFFER

		//	レンダーを元に戻す
		MyuAssert( d3d->SetRenderTarget( bkupRender, NULL ), D3D_OK, //m_myudg->lpZbuffer
			"CMglImage::Clear()  レンダーを戻すのに失敗" );
	}
	else
	{
		//	別にクリアされたサーフェスを作成してそこからコピー、と言う面倒な処理(´Д`)
		CMglImage workSurface;
		workSurface.Init( m_myudg );
		workSurface.Create();	//	レンダリング先はTRUEにしないと無限再帰してしまう
		workSurface.Paint( rect, color );
		CopyRectToThis( &workSurface );
	}
}

