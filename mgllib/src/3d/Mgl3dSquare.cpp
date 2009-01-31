//////////////////////////////////////////////////////////
//
//	Mgl3dSquare
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mgl3dSquare.h"

//	コンストラクタ
CMgl3dSquare::CMgl3dSquare()
{
	m_myudg = NULL;
	m_d3d = NULL;
}

//	初期化
void CMgl3dSquare::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	m_d3d = m_myudg->GetD3dDevPtr();
}

//	作成
void CMgl3dSquare::SimpleCreate(float fWidth, float fHeight, D3DCOLOR color)
{
	MYUX_VERTEX v;
	v.color = color;
	v.x = 0;
	//v.SetTuTv(

	v.x = 0; v.y = 0; 
	AddVertex(v);
	v.x = fWidth; v.y = 0; 
	AddVertex(v);
	v.x = 0; v.y = fHeight; 
	AddVertex(v);
	v.x = fWidth; v.y = fHeight; 
	AddVertex(v);
}
