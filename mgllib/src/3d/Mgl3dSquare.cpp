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
	//m_tex = NULL;
	ZeroMemory(m_texList, sizeof(CMglD3dTexture*)*MGL_TEXTURE_STAGE_MAX);
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
	//v.tu = 1.0f; v.tv = 0.0f; 
	AddVertex(v);
	v.x = 0.0f; v.y = fHeight; 
	//v.tu = 0.0f; v.tv = 1.0f; 
	AddVertex(v);
	v.x = fWidth; v.y = fHeight; 
	//v.tu = 1.0f; v.tv = 1.0f; 
	AddVertex(v);

	Compile();
}

//	テクスチャからの生成
void CMgl3dSquare::CreateFromTexture(CMglD3dTexture &tex, float fWidth, float fHeight, D3DCOLOR color)
{
	InitCheck();
	CreatedCheck();

	SimpleCreate(fWidth, fHeight, color);

	SetTexture(tex);
	/*
	m_tex = &tex;

	//MGLTUTV tutv = m_tex->GetTuTv();
	SetTuTv(m_tex->GetTuTv());
	*/
}

void CMgl3dSquare::SetTexture(int no, CMglD3dTexture &tex)
{
	InitCheck();
	CreateCheck();

	m_texList[no] = &tex;

	//MGLTUTV tutv = m_tex->GetTuTv();
	SetTuTv(no, tex.GetTuTv());
}

void CMgl3dSquare::AddTexture(CMglD3dTexture &tex)
{
	for(int i=0; i<MGL_TEXTURE_STAGE_MAX; i++ ){
		if ( m_texList[i] == NULL ){
			SetTexture(i, tex);
			return;
		}
	}

	MyuThrow( MGLMSGNO_3DSQUARE(20),
		"CMgl3dSquare::AddTexture()  これ以上テクスチャを追加する事はできません。");
}

#ifdef _MGLVERTEX_USE_MULTITEX
void CMgl3dSquare::SetTuTv(int no, MGLTUTV &tutv)
{
	_VERTEX &v1 = Get(1);
	v1.tPosAry[no].x = tutv.tu;
	_VERTEX &v2 = Get(2);
	v2.tPosAry[no].y = tutv.tv;
	_VERTEX &v3 = Get(3);
	v3.tPosAry[no].x = tutv.tu;
	v3.tPosAry[no].y = tutv.tv;

	Compile();
}
#else
void CMgl3dSquare::SetTuTv(MGLTUTV &tutv)
{
	/*
	_VERTEX *pv = NULL;
	pv = GetPtr(1);
	pv->tu = tutv.tu;
	pv = GetPtr(2);
	pv->tv = tutv.tv;
	pv = GetPtr(3);
	pv->tu = tutv.tu;
	pv->tv = tutv.tv;
	*/

	_VERTEX &v1 = Get(1);
	v1.tu = tutv.tu;
	_VERTEX &v2 = Get(2);
	v2.tv = tutv.tv;
	_VERTEX &v3 = Get(3);
	v3.tu = tutv.tu;
	v3.tv = tutv.tv;

	Compile();
}
#endif


//	描画
void CMgl3dSquare::Draw()
{
	InitCheck();
	CreateCheck();

	/*if ( m_tex != NULL )
		m_tex->SetD3dStageTexture();*/
	for(int i=0; i<MGL_TEXTURE_STAGE_MAX; i++ ){
		if ( m_texList[i] != NULL )
			m_texList[i]->SetD3dStageTexture(i);
	}

	CMglVertexManagerX::Draw(D3DPT_TRIANGLESTRIP);
}

