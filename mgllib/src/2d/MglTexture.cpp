//////////////////////////////////////////////////////////
//
//	MglTexture
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglTexture.h"

////////////////////////////////////////////////////////////////////

//	コンストラクタ
CMglTexture::CMglTexture()
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
void CMglTexture::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();
}

//	開放
void CMglTexture::Release()
{
	SAFE_DELETE( m_pBitmapData );
	SAFE_RELEASE( m_pTexture );
	SAFE_RELEASE( m_pSurface );
}


//	ファイルから読み込み
//	bRenderTargetをTRUEにした場合はPOOLも D3DPOOL_MANAGED として読み込まれる。
//void CMglTexture::CreateTextureFromFile( LPCSTR szFileName, BOOL bRenderTarget, D3DCOLOR colorKey )
void CMglTexture::CreateTextureFromFileEx( LPCSTR szFileName, int nForceBmpWidth, int nForceBmpHeight,
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
void CMglTexture::Create( int x, int y, BOOL bRenderTarget )
{
	_MGL_DEBUGLOG( "+ CMglTexture::Create()" );

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
			"CMglTexture::Create()  D3DXCreateTexture(VRAM)に失敗" );
	}
	else {
		MyuAssert( D3DXCreateTexture( d3d, x, y, D3DX_DEFAULT, 0, m_myudg->GetFormat(), D3DPOOL_MANAGED, &m_pTexture ), D3D_OK,
			"CMglTexture::Create()  D3DXCreateTexture(SYSMEM)に失敗" );
	}

	//	記憶しておく
	m_bRenderTarget = bRenderTarget;

	/*
	//SetGradation();

	//	テクスチャのサーフェスを取得する
	MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
		"CMglTexture::Create()  GetSurfaceLevel()に失敗" );

	//	スプライト作成
	MyuAssert( D3DXCreateSprite( d3d, &this->m_pSprite ), D3D_OK,
		"CMglTexture::Init  D3DXCreateSprite()に失敗" );

	//	クリアする
	//Clear();

	createFlg = TRUE;
	*/

	//	SetRenderとかで必要なのでサーフェス取得しておく
	_GetSurface();

	_MGL_DEBUGLOG( "- CMglTexture::Create()" );
}

//////////////////////////////////////////////////////////////////////////////////////

//	新・描画方式
void CMglTexture::Draw(float x, float y, D3DCOLOR color )
{
	//	頂点初期情報取得
	MGL_SQUARE_VERTEXS vertexs;
	this->GetBmpVertexs( &vertexs );

	//	x, yに移動
	MglMoveVertexs( &vertexs, x, y );

	//	頂点の色
	vertexs.lt.color = color;
	vertexs.rt.color = color;
	vertexs.lb.color = color;
	vertexs.rb.color = color;

	//	描画
	Draw( &vertexs );
}

//	描画（二次元固定）
void CMglTexture::Draw( MGL_SQUARE_VERTEXS *pMglSqVertexs, BOOL bVertexRevise )
{
	Draw( (MYU_VERTEX*)pMglSqVertexs, 2, bVertexRevise );
}

//	描画（頂点数不定）
void CMglTexture::Draw( MYU_VERTEX *pMyuVertex, UINT nPrimitiveCount, BOOL bVertexRevise )
{
	CreateCheck();	//	Createチェック
	LockedCheck();

	//	頂点補正
	if ( bVertexRevise )
		MglMoveVertexs( pMyuVertex, TEXTURE_FLOAT_ADJ, TEXTURE_FLOAT_ADJ, 2+nPrimitiveCount );

	//	テクスチャの設定
	MyuAssert( d3d->SetTexture(0, m_pTexture), D3D_OK,
		"CMglImage::TextureDrawPrimitive()  SetTexture()に失敗" );

	DrawPrimitiveUP( D3DPT_TRIANGLEFAN, nPrimitiveCount, pMyuVertex, sizeof(MYU_VERTEX) );
	//	絵画
	/*MyuAssert( d3d->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, nPrimitiveCount, pMyuVertex, sizeof(MYU_VERTEX) ), D3D_OK,
		"CMglImage::TextureDrawPrimitive()  DrawPrimitiveUP()に失敗" );*/
}

//	DrawPrimitiveUP
void CMglTexture::DrawPrimitiveUP( D3DPRIMITIVETYPE primitiveType, UINT nPrimitiveCount,
								  const void *pVertexStreamZeroData, UINT nVertexStreamZeroStride )
{
	CreateCheck();	//	Createチェック
	LockedCheck();

	//	絵画
	MyuAssert( d3d->DrawPrimitiveUP( primitiveType, nPrimitiveCount, pVertexStreamZeroData, nVertexStreamZeroStride ), D3D_OK,
		"CMglImage::TextureDrawPrimitive()  DrawPrimitiveUP()に失敗" );
}

   
///////////////////////////////////////////////////////////////////////////

//	BMPの頂点情報取得
void CMglTexture::GetBmpVertexs( MGL_SQUARE_VERTEXS *pMglSqVertexs )
{
	int nBmpSrcX = m_imgInfo.Width;
	int nBmpSrcY = m_imgInfo.Height;

	//	2007/01/10  スケール取得
	//	# テクスチャ領域は2の倍数になる。その内の0.?fがBMPの領域かを算出する
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	const float fBmpScaleX = (float)nBmpSrcX / (float)texDesc.Width;
	const float fBmpScaleY = (float)nBmpSrcY / (float)texDesc.Height;

	//	頂点情報生成
	MglVertexGen( &pMglSqVertexs->lt, 0, 0,					0.0f, 0.0f );
	MglVertexGen( &pMglSqVertexs->rt, nBmpSrcX,				0,	fBmpScaleX, 0.0f );
	MglVertexGen( &pMglSqVertexs->lb, 0, nBmpSrcY,			0.0f, fBmpScaleY );
	MglVertexGen( &pMglSqVertexs->rb, nBmpSrcX, nBmpSrcY,	fBmpScaleX, fBmpScaleY );

	//	頂点のズラし
	//MglMoveVertexs( pMglSqVertexs, TEXTURE_FLOAT_ADJ, TEXTURE_FLOAT_ADJ );
}




/////////////////////////////////////////////////////////////////////////////////////////////

//	↓↓↓　古い描画方式　↓↓↓


//	Texture(DrawPrimitiveUP)で絵画
void CMglTexture::TextureDraw(
	float x, float y, RECT* srcRect, float fScaleX, float fScaleY,
	float fRotationCenterX, float fRotationCenterY, float fAngle,
	VERTEX_COLORS* vertexColors, DWORD dwAlphaOption )
{
	CreateCheck();	//	Createチェック
	LockedCheck();

	//	srcRectを考慮したBMPサイズ
	//int nBmpSrcX = m_nBmpSizeX;
	//int nBmpSrcY = m_nBmpSizeY;
	int nBmpSrcX = m_imgInfo.Width;
	int nBmpSrcY = m_imgInfo.Height;

	//	2007/01/10  スケール取得
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	const float fRealTexTu = (float)nBmpSrcX / (float)texDesc.Width;
	const float fRealTexTv = (float)nBmpSrcY / (float)texDesc.Height;

	MYU_VERTEX vertices[4];		//	頂点
	ZeroMemory( vertices, sizeof(vertices) );

	//	転送元もどきの設定
	if ( srcRect == NULL )
	{
		vertices[VERTEXNO_LT].tu = vertices[VERTEXNO_LB].tu = 0.0f;
		vertices[VERTEXNO_LT].tv = vertices[VERTEXNO_RT].tv = 0.0f;
		//vertices[VERTEXNO_RB].tu = vertices[VERTEXNO_RT].tu = 1.0f; - 2007/01/10 1.0f化やっぱ廃止
		//vertices[VERTEXNO_RB].tv = vertices[VERTEXNO_LB].tv = 1.0f;
		vertices[VERTEXNO_RT].tu = vertices[VERTEXNO_RB].tu = fRealTexTu;
		vertices[VERTEXNO_LB].tv = vertices[VERTEXNO_RB].tv = fRealTexTv;
	}
	else
	{
		float fLeftTu = ((float)srcRect->left / nBmpSrcX) * fRealTexTu;
		float fRightTu = ((float)srcRect->right / nBmpSrcX) * fRealTexTu;
		float fTopTv = ((float)srcRect->top / nBmpSrcY) * fRealTexTv;
		float fBottomTv = ((float)srcRect->bottom / nBmpSrcY) * fRealTexTv;
		/*float fLeftTu = ((float)srcRect->left / nBmpSrcX);
		float fRightTu = ((float)srcRect->right / nBmpSrcX); - 2007/01/10 1.0f化やっぱ廃止
		float fTopTv = ((float)srcRect->top / nBmpSrcY);
		float fBottomTv = ((float)srcRect->bottom / nBmpSrcY);*/

		/*	2007/01/10  nBmpSrc*化
		float fLeftTu = ((float)srcRect->left / m_nBmpSizeX) * fRealTexTu;
		float fRightTu = ((float)srcRect->right / m_nBmpSizeX) * fRealTexTu;
		float fTopTv = ((float)srcRect->top / m_nBmpSizeY) * fRealTexTv;
		float fBottomTv = ((float)srcRect->bottom / m_nBmpSizeY) * fRealTexTv;
		*/

		/*
		vertices[VERTEXNO_LT].tu = vertices[VERTEXNO_LB].tu = fLeftTu;
		vertices[VERTEXNO_RT].tu = vertices[VERTEXNO_RB].tu = fRightTu;
		vertices[VERTEXNO_LT].tv = vertices[VERTEXNO_RT].tv = fTopTv;
		vertices[VERTEXNO_LB].tv = vertices[VERTEXNO_RB].tv = fBottomTv;
		*/
		vertices[VERTEXNO_LT].tu = vertices[VERTEXNO_LB].tu = fLeftTu;
		vertices[VERTEXNO_RT].tu = vertices[VERTEXNO_RB].tu = fRightTu;
		vertices[VERTEXNO_LT].tv = vertices[VERTEXNO_RT].tv = fTopTv;
		vertices[VERTEXNO_LB].tv = vertices[VERTEXNO_RB].tv = fBottomTv;

		nBmpSrcX = srcRect->right - srcRect->left;
		nBmpSrcY = srcRect->bottom - srcRect->top;
	}
	/*
	//	中心基点絵画機能
	if ( m_bCenterDraw == TRUE )
	{
		int nSizeX = srcRect->right - srcRect->left;
		int nSizeY = srcRect->bottom - srcRect->top;
		x -= (nSizeX/2) * fScaleX;
		y -= (nSizeY/2) * fScaleY;
	}
	*/

	//	絵画先位置、及び伸縮率の設定
	vertices[VERTEXNO_LT].x = vertices[VERTEXNO_LB].x = x + TEXTURE_FLOAT_ADJ;	//	絵画先位置X
	vertices[VERTEXNO_LT].y = vertices[VERTEXNO_RT].y = y + TEXTURE_FLOAT_ADJ;	//	絵画先位置Y
	vertices[VERTEXNO_RB].x = vertices[VERTEXNO_RT].x = x + TEXTURE_FLOAT_ADJ + nBmpSrcX * fScaleX;	//	伸縮率X
	vertices[VERTEXNO_RB].y = vertices[VERTEXNO_LB].y = y + TEXTURE_FLOAT_ADJ + nBmpSrcY * fScaleY;	//	伸縮率Y
	/*vertices[VERTEXNO_LT].x = vertices[VERTEXNO_LB].x = x + X_ADJ;//	絵画先位置X
	vertices[VERTEXNO_LT].y = vertices[VERTEXNO_RT].y = y + Y_ADJ;	//	絵画先位置Y
	vertices[VERTEXNO_RB].x = vertices[VERTEXNO_RT].x = x + X_ADJ + nBmpSrcX * fScaleX;	//	伸縮率X
	vertices[VERTEXNO_RB].y = vertices[VERTEXNO_LB].y = y + Y_ADJ + nBmpSrcY * fScaleY;	//	伸縮率Y*/

	//	色
	vertices[VERTEXNO_LT].color = vertexColors->leftTop;
	vertices[VERTEXNO_RT].color = vertexColors->rightTop;
	vertices[VERTEXNO_LB].color = vertexColors->leftBottom;
	vertices[VERTEXNO_RB].color = vertexColors->rightBottom;

	//	アルファオプション
	m_myudg->SetAlphaMode( dwAlphaOption );

	//	描画
	Draw( vertices );
}

//	イテレータ ////////////////////////////////////////////////

CMglBitmapData* CMglTexture::GetIternalBitmapData()
{
	if ( m_pBitmapData == NULL )
		m_pBitmapData = new CMglBitmapData(this);
	return m_pBitmapData;
}

/*
CMglTexture::iterator CMglTexture::begin()
{

}

CMglTexture::iterator CMglTexture::end()
{


}
*/

