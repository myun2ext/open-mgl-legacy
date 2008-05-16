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

	//m_list[it] = t;
	//m_list.push_back(t);
	LIST_ITR newIt = m_list.insert(it,t);

	//SetParam(it,x,y,bShow,color,fScaleX,fScaleY,fAngle);	//	2008/05/16  ←これは間違い
	SetParam(newIt,x,y,bShow,color,fScaleX,fScaleY,fAngle);
}

//	パラメータ設定
void CMglLayers4::SetParam( LIST_ITR it, float x, float y, 
	BOOL bShow, D3DCOLOR color, float fScaleX, float fScaleY, float fAngle )
{
	ExistChk(it);

	it->bShow = bShow;
	it->color = color;
	it->x = x;
	it->y = y;
	it->fScaleX = fScaleX;
	it->fScaleY = fScaleY;
	it->fAngle = fAngle;

	it->fRotationCenterX = 0.5f;
	it->fRotationCenterY = 0.5f;
}

//	移動
void CMglLayers4::Move( LIST_ITR it, float x, float y )
{
	ExistChk(it);
	it->x += x;
	it->y += y;
}

//	パラメータ設定（位置）
void CMglLayers4::SetPos( LIST_ITR it, float x, float y )
{
	ExistChk(it);
	it->x = x;
	it->y = y;
}

//	パラメータ設定（色）
void CMglLayers4::SetColor( LIST_ITR it, D3DCOLOR color )
{
	ExistChk(it);
	it->color = color;
}

//	パラメータ設定（縮尺率）
void CMglLayers4::SetScale( LIST_ITR it, float fScaleX, float fScaleY )
{
	ExistChk(it);
	it->fScaleX = fScaleX;
	it->fScaleY = fScaleY;
}

//	パラメータ設定（角度）
void CMglLayers4::SetAngle( LIST_ITR it, float fAngle )
{
	ExistChk(it);
	it->fAngle = fAngle;
}

//	パラメータ設定（矩形）
void CMglLayers4::SetRect( LIST_ITR it, RECT rect )
{
	ExistChk(it);
	it->rect = rect;
}

//	パラメータ設定（回転の中心）
void CMglLayers4::SetRotationCenter( LIST_ITR it, float fRotationCenterX, float fRotationCenterY )
{
	ExistChk(it);
	it->fRotationCenterX = fRotationCenterX;
	it->fRotationCenterY = fRotationCenterY;
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

		//LAYERINFO& t = m_list.get(it.base());
		LAYERINFO& t = *(it.base());
		layer_t* pLayer = t.pLayer;

		if ( t.bShow == TRUE )
		{
			//pSfc->XDraw();
			//pSfc->Draw( pInfo->rect.left, pInfo->rect.top, NULL, pInfo->color );

			RECT* pRect = &t.rect;
			if ( pRect->left == 0 && pRect->right == 0 && pRect->top == 0 && pRect->bottom == 0 )
				pRect = NULL;

	MessageBox(NULL,"aa",NULL,NULL);

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

//	削除する
void CMglLayers4::Delete(LIST_ITR it)
{
	//LAYERINFO& t = m_list.get(it);
	LAYERINFO& t = *it;
	layer_t* pLayer = t.pLayer;

	//	ポインタを開放すべきであれば開放する
	if ( pLayer->IsShouldReleasePtr() )
		delete pLayer;

	//	リストから除去
	m_list.erase(it);
}

//	全てを削除
void CMglLayers4::Clear()
{
	InitCheck();

	//	リストをループして一つづつ開放
	//for( LIST_ITR it=m_list.begin(); it!=m_list.end(); it++ )
	for(;;){
		LIST_ITR it = m_list.begin();
		if ( it == m_list.end() )
			break;
		Delete(it);
	}

	//	一応実行しておこうか？
	m_list.clear();
}

