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

////////////////////////////////////////////////////////////

//	カメラ位置の設定
//void CMgl3DManager::SetCameraPos(float x, float y, float z)
void CMgl3DManager::SetCamera(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ)
{
	D3DXMATRIX mView;
	D3DXMatrixLookAtLH(&mView
					,&D3DXVECTOR3(fPosX, fPosY, fPosZ)	// カメラ位置
					,&D3DXVECTOR3(fTargetX, fTargetY, fTargetZ)		// カメラの注目点
					,&D3DXVECTOR3(0,1,0)		// 上の向き
					);
	d3d->SetTransform(D3DTS_VIEW, &mView);
}
/*
//	カメラの注目点設定
void CMgl3DManager::SetCameraViewTarget(float x, float y, float z)
{

}
*/