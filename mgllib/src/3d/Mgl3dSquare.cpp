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
