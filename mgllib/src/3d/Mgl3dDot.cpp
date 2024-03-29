//////////////////////////////////////////////////////////
//
//	Mgl3dDot
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mgl3dDot.h"

//	コンストラクタ
CMgl3dDots::CMgl3dDots()
{
	m_myudg = NULL;
	m_d3d = NULL;
}

//	初期化
void CMgl3dDots::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	m_d3d = m_myudg->GetD3dDevPtr();
}
