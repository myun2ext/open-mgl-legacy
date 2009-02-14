//////////////////////////////////////////////////////////
//
//	Mgl3dManager
//		- DirectX Graphics 管理クラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mgl3dManager.h"

//	コンストラクタ
CMgl3dManager::CMgl3dManager()
{
}
//	デストラクタ
CMgl3dManager::~CMgl3dManager()
{
}

//	開放
void CMgl3dManager::Release()
{
}

//	初期化
void CMgl3dManager::Init( CMglGraphicManager* in_myudg )
{
	//CMglDgBase::Init();
	CMglMatrixManager::Init(in_myudg);

	//	かりんぐ、らいとにんぐ
	m_pD3dDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3dDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	//	Zバッファ設定
	m_pD3dDev->SetRenderState( D3DRS_ZENABLE,	D3DZB_TRUE );		// Zバッファを有効にする。
	m_pD3dDev->SetRenderState( D3DRS_ZWRITEENABLE,		TRUE );			// Zバッファへの書き込み許可
}
