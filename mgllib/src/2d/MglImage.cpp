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
	//m_pSurface = NULL;
	m_bCenterDraw = FALSE;
}

//	デストラクタ
CMglImage::~CMglImage()
{

}

////////////////////////////////////////////////////////////////////////////////


//	描画
void CMglImage::Draw(
	float x, float y, CONST RECT *srcRect, D3DCOLOR color,
	float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle )
{
	if ( m_bCenterDraw ){
		x -= CMglTexture::GetBmpWidth()/2;
		y -= CMglTexture::GetBmpHeight()/2;
	}
	m_myudg->SpriteDraw( this, x, y, srcRect, color, fScaleX, fScaleY,
		fRotationCenterX, fRotationCenterY, fAngle );
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

/*
	######## D3DXCreateRenderToSurface でやるようにしよう… ########
*/
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
		//workSurface.Create();	//	レンダリング先はTRUEにしないと無限再帰してしまう
		workSurface.Create(TRUE);	//	レンダリング先はTRUEにしないと無限再帰してしまう
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
		//workSurface.Create();
		workSurface.Create(TRUE);	//	レンダリング先はTRUEにしないと無限再帰してしまう
		workSurface.Paint( rect, color );
		workSurface.Paint( rect, color );
		CopyRectToThis( &workSurface );
	}
}
