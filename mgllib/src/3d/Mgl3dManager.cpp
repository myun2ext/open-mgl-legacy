//////////////////////////////////////////////////////////
//
//	Mgl3DManager
//		- DirectX Graphics 管理クラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mgl3DManager.h"

//	コンストラクタ
CMgl3DManager::CMgl3DManager()
{
	m_myudg = NULL;
	d3d = NULL;
}

//	デストラクタ
CMgl3DManager::~CMgl3DManager()
{
}

//	開放
void CMgl3DManager::Release()
{
}

//	初期化
void CMgl3DManager::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();
}

