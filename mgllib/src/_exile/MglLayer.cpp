//////////////////////////////////////////////////////////
//
//	MglLayer
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglLayer.h"

//	コンストラクタ
CMglLayer::CMglLayer()
{
	m_myudg = NULL;
	m_d3d = NULL;
}

//	デストラクタ
CMglLayer::~CMglLayer()
{

}

///////////////////////////////////////////////////////

//	登録
void CMglLayer::Regist( CMglImage *pImage, int depth, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	if ( m_list.find(depth) != m_list.end() )
		MyuThrow( 66126, "CMglLayer::Regist() depth=%d は既にあります。", depth );

	LAYERINFO t;
	ZeroMemory(&t,sizeof(t));

	/*
	t.bShow = bShow;
	t.color = color;
	t.x = x;
	t.y = y;
	t.fScaleX = fScaleX;
	t.fScaleY = fScaleY;
	t.fAngle = fAngle;
	*/
	t.pImage = pImage;

	m_list[depth] = t;

	SetParam(depth,x,y,bShow,color,fScaleX,fScaleY,fAngle);
}

//	パラメータ設定
void CMglLayer::SetParam( int depth, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	ExistChk(depth);

	m_list[depth].bShow = bShow;
	m_list[depth].color = color;
	m_list[depth].x = x;
	m_list[depth].y = y;
	m_list[depth].fScaleX = fScaleX;
	m_list[depth].fScaleY = fScaleY;
	m_list[depth].fAngle = fAngle;

	m_list[depth].fRotationCenterX = 0.5f;
	m_list[depth].fRotationCenterY = 0.5f;
}

//	移動
void CMglLayer::Move( int depth, float x, float y )
{
	ExistChk(depth);
	m_list[depth].x += x;
	m_list[depth].y += y;
}

//	パラメータ設定（位置）
void CMglLayer::SetPos( int depth, float x, float y )
{
	ExistChk(depth);
	m_list[depth].x = x;
	m_list[depth].y = y;
}

//	パラメータ設定（色）
void CMglLayer::SetColor( int depth, D3DCOLOR color )
{
	ExistChk(depth);
	m_list[depth].color = color;
}

//	パラメータ設定（縮尺率）
void CMglLayer::SetScale( int depth, float fScaleX, float fScaleY )
{
	ExistChk(depth);
	m_list[depth].fScaleX = fScaleX;
	m_list[depth].fScaleY = fScaleY;
}

//	パラメータ設定（角度）
void CMglLayer::SetAngle( int depth, float fAngle )
{
	ExistChk(depth);
	m_list[depth].fAngle = fAngle;
}

//	パラメータ設定（矩形）
void CMglLayer::SetRect( int depth, RECT rect )
{
	ExistChk(depth);
	m_list[depth].rect = rect;
}

//	パラメータ設定（回転の中心）
void CMglLayer::SetRotationCenter( int depth, float fRotationCenterX, float fRotationCenterY )
{
	ExistChk(depth);
	m_list[depth].fRotationCenterX = fRotationCenterX;
	m_list[depth].fRotationCenterY = fRotationCenterY;
}

////////////////////////////////////////////////////////////////

//	描画
void CMglLayer::Rendering()
{
	InitCheck();

	//	2008/02/17  表示の順番逆だと思う・・・（後ろ＝一番深いものから描画していくべき）
	//	ループ
	//for ( LIST_ITR it = m_list.begin(); it != m_list.end(); it++ )
	/*LIST_ITR it = m_list.end();
	for(;;)*/
	for( LIST_RITR it = m_list.rbegin(); it != m_list.rend(); it++ )
	{
		//it--;

		LAYERINFO& t = it->second;
		CMglImage* pImage = t.pImage;

		if ( t.bShow == TRUE )
		{
			//pSfc->XDraw();
			//pSfc->Draw( pInfo->rect.left, pInfo->rect.top, NULL, pInfo->color );

			RECT* pRect = &t.rect;
			if ( pRect->left == 0 && pRect->right == 0 && pRect->top == 0 && pRect->bottom == 0 )
				pRect = NULL;

			//	描画
			pImage->Draw(t.x, t.y, pRect, t.color,
				t.fScaleX, t.fScaleY, t.fRotationCenterX, t.fRotationCenterY, t.fAngle );

			/*
			if ( pInfo->rect.left == pInfo->rect.right || pInfo->rect.top == pInfo->rect.bottom )
				pSfc->Draw( pInfo->rect.left, pInfo->rect.top, NULL, pInfo->color );
			else
				pSfc->Draw( pInfo->rect.left, pInfo->rect.top, &pInfo->rect, pInfo->color );
			*/
		}

		/*if ( it == m_list.begin() )
			break;*/
	}

	m_myudg->UpdateScreen();
}

