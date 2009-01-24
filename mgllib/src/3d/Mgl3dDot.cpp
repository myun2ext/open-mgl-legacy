//////////////////////////////////////////////////////////
//
//	Mgl3dDot
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mgl3dDot.h"

//	コンストラクタ
CMgl3dDot::CMgl3dDot()
{
	m_myudg = NULL;
	m_d3d = NULL;
}

//	初期化
void CMgl3dDot::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	m_d3d = m_myudg->GetD3dDevPtr();
}
