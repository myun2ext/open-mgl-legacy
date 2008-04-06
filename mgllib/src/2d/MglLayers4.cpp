//////////////////////////////////////////////////////////
//
//	MglLayers4
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglLayers4.h"

//	コンストラクタ
CMglLayers4::CMglLayers4()
{
	m_myudg = NULL;
	m_d3d = NULL;
}

//	デストラクタ
CMglLayers4::~CMglLayers4()
{

}

///////////////////////////////////////////////////////

//	登録
void CMglLayers4::Regist( layer_t *pLayer, LIST_ITR it, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	if ( m_list.find(it) != m_list.end() )
		MyuThrow( 66126, "CMglLayers4::Regist() it=%d は既にあります。", it );

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
	t.pLayer = pLayer;

	m_list[it] = t;

	SetParam(it,x,y,bShow,color,fScaleX,fScaleY,fAngle);
}

//	パラメータ設定
void CMglLayers4::SetParam( LIST_ITR it, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	ExistChk(it);

	m_list[it].bShow = bShow;
	m_list[it].color = color;
	m_list[it].x = x;
	m_list[it].y = y;
	m_list[it].fScaleX = fScaleX;
	m_list[it].fScaleY = fScaleY;
	m_list[it].fAngle = fAngle;

	m_list[it].fRotationCenterX = 0.5f;
	m_list[it].fRotationCenterY = 0.5f;
}

//	移動
void CMglLayers4::Move( LIST_ITR it, float x, float y )
{
	ExistChk(it);
	m_list[it].x += x;
	m_list[it].y += y;
}

//	パラメータ設定（位置）
void CMglLayers4::SetPos( LIST_ITR it, float x, float y )
{
	ExistChk(it);
	m_list[it].x = x;
	m_list[it].y = y;
}

//	パラメータ設定（色）
void CMglLayers4::SetColor( LIST_ITR it, D3DCOLOR color )
{
	ExistChk(it);
	m_list[it].color = color;
}

//	パラメータ設定（縮尺率）
void CMglLayers4::SetScale( LIST_ITR it, float fScaleX, float fScaleY )
{
	ExistChk(it);
	m_list[it].fScaleX = fScaleX;
	m_list[it].fScaleY = fScaleY;
}

//	パラメータ設定（角度）
void CMglLayers4::SetAngle( LIST_ITR it, float fAngle )
{
	ExistChk(it);
	m_list[it].fAngle = fAngle;
}

//	パラメータ設定（矩形）
void CMglLayers4::SetRect( LIST_ITR it, RECT rect )
{
	ExistChk(it);
	m_list[it].rect = rect;
}

//	パラメータ設定（回転の中心）
void CMglLayers4::SetRotationCenter( LIST_ITR it, float fRotationCenterX, float fRotationCenterY )
{
	ExistChk(it);
	m_list[it].fRotationCenterX = fRotationCenterX;
	m_list[it].fRotationCenterY = fRotationCenterY;
}

////////////////////////////////////////////////////////////////

//	描画
void CMglLayers4::Rendering()
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

		LAYERINFO& t = m_list.get(it.base());
		layer_t* pLayer = t.pLayer;

		if ( t.bShow == TRUE )
		{
			//pSfc->XDraw();
			//pSfc->Draw( pInfo->rect.left, pInfo->rect.top, NULL, pInfo->color );

			RECT* pRect = &t.rect;
			if ( pRect->left == 0 && pRect->right == 0 && pRect->top == 0 && pRect->bottom == 0 )
				pRect = NULL;

			//	描画
			pLayer->Draw(t.x, t.y, pRect, t.color,
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

