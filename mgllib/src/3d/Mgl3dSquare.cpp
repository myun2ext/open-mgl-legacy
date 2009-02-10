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
	m_tex = NULL;
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
	InitCheck();
	CreatedCheck();

	_VERTEX v;
	v.color = color;
	v.x = 0.0f;
	v.specular = D3DCOLOR_WHITE;
	//v.SetTuTv(

	v.x = 0.0f; v.y = 0.0f; 
	AddVertex(v);
	v.x = fWidth; v.y = 0.0f; 
	AddVertex(v);
	v.x = 0.0f; v.y = fHeight; 
	AddVertex(v);
	v.x = fWidth; v.y = fHeight; 
	AddVertex(v);

	Compile();
}

//	テクスチャからの生成
void CMgl3dSquare::CreateFromTexture(CMglD3dTexture &tex, float fWidth, float fHeight, D3DCOLOR color)
{
	InitCheck();
	CreatedCheck();

	SimpleCreate(fWidth, fHeight, color);
	m_tex = &tex;

	//MGLTUTV tutv = m_tex->GetTuTv();
	SetTuTv(m_tex->GetTuTv());
}

//	描画
void CMgl3dSquare::Draw()
{
	InitCheck();

	if ( m_vertexes.size() == 0 )
			MyuThrow( 4678, "CMgl3dSquare::Draw()  未作成です。" );

	if ( m_tex != NULL )
		m_tex->SetD3dStageTexture();

	CMglVertexManagerX::Draw(D3DPT_TRIANGLESTRIP);
}

void CMgl3dSquare::SetTuTv(MGLTUTV &tutv)
{
	_VERTEX &v1 = Get(1);
	v1.tu = tutv.tu;
	_VERTEX &v2 = Get(2);
	v2.tv = tutv.tv;
	_VERTEX &v3 = Get(3);
	v3.tu = tutv.tu;
	v3.tv = tutv.tv;
}


