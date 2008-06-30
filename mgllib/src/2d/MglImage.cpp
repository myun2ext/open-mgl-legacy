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
	CreateCheck();
	LockedCheck();

	if ( m_bCenterDraw ){
		/*x -= CMglTexture::GetBmpWidth()/2;
		y -= CMglTexture::GetBmpHeight()/2;*/

		//	2008/01/19 拡大縮小の際に中心にならないがわざとなのかなんなのか・・・？
		//x -= (CMglTexture::GetBmpWidth() - ((1.0f-fScaleX)*CMglTexture::GetBmpWidth())/2);
		x -= fScaleX * CMglTexture::GetBmpWidth() / 2;
		y -= fScaleY * CMglTexture::GetBmpHeight() / 2;
	}
	m_myudg->SpriteDraw( this, x, y, srcRect, color, fScaleX, fScaleY,
		fRotationCenterX, fRotationCenterY, fAngle );
}


//	絵画（CopyRectを使用）
void CMglImage::CopyRectToOther( CMglImage* destSurface, RECT *srcRect, int x, int y )
{
	CreateCheck();	//	Createチェック
	LockedCheck();

	//if ( m_pSurface == NULL )
	//	MyuThrow( 0, "CMglImage::CopyRectToOther()  m_pSurfaceが取得されていません。");
	//	srcRectにNULLを指定された場合はフルで絵画

	D3DXLoadSurfaceFromSurface(
		destSurface->GetSurfacePtr(), NULL, srcRect,
		m_pSurface, NULL, srcRect,
		D3DX_FILTER_POINT, 0 );

	/*
	RECT srcRect2;
	_Rect(0,0, this->GetBmpWidth(), this->GetBmpHeight(), &srcRect2);
	D3DXLoadSurfaceFromSurface(
		destSurface->GetSurfacePtr(), NULL, &srcRect2,
		this->m_pSurface, NULL, &srcRect2,
		D3DX_FILTER_POINT, 0 );
	*/

	/*	これは全然駄目
	d3d->UpdateTexture(this->m_pTexture, destSurface->GetDirect3dTexturePtr());
	*/

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
