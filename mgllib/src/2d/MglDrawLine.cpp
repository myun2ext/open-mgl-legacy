//////////////////////////////////////////////////////////
//
//	MglDrawLine
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglDrawLine.h"

CMglTexture* CMglDrawLine::m_pLineTex;

//	コンストラクタ
CMglDrawLine::CMglDrawLine(){
	//	初回一回だけ
	if ( m_pLineTex == NULL ){
		m_pLineTex = new CMglTexture();

		//m_pLineTex->Create(1,1,FALSE);
		m_pLineTex->Create(2,2,FALSE);
	}
}

//	描画
void CMglDrawLine::Draw(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR startColor, D3DCOLOR endColor, float width)
{
	m_pLineTex->CreateCheck();	//	Createチェック

	MYU_VERTEX vertices[4];		//	頂点
	ZeroMemory( vertices, sizeof(vertices) );

	//	転送元設定
	vertices[VERTEXNO_LT].tu = vertices[VERTEXNO_LB].tu = 0.0f;
	vertices[VERTEXNO_LT].tv = vertices[VERTEXNO_RT].tv = 0.0f;
	vertices[VERTEXNO_RB].tu = vertices[VERTEXNO_RT].tu = 1.0f;
	vertices[VERTEXNO_RB].tv = vertices[VERTEXNO_LB].tv = 1.0f;

	//	始点
	vertices[VERTEXNO_LT].x = fStartX;
	vertices[VERTEXNO_LT].y = fStartY;
	vertices[VERTEXNO_RT].y = fStartX;
	vertices[VERTEXNO_RT].x = fStartY;
	vertices[VERTEXNO_LT].color = startColor;
	vertices[VERTEXNO_RT].color = startColor;
	
	//	終点
	vertices[VERTEXNO_LB].x = fEndX;
	vertices[VERTEXNO_LB].y = fEndY;
	vertices[VERTEXNO_RB].x = fEndX;
	vertices[VERTEXNO_RB].y = fEndY;
	vertices[VERTEXNO_LB].color = endColor;
	vertices[VERTEXNO_RB].color = endColor;

	//	アルファオプション
	m_myudg->SetAlphaMode( MGL_ALPHA_OPT_DEFAULT );

	//	描画
	Draw( vertices );
}

