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
	m_pD3dDev = NULL;
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
	m_pD3dDev = m_myudg->GetD3dDevPtr();

	//	Projectionの設定
	SetupProjection( (m_myudg->GetWidth()*1.0f) / m_myudg->GetHeight());
}

//	Projectionの設定
void CMgl3DManager::SetupProjection( float fAspectRatio, float fViewingAngle, float fClipNear, float fClipFar )
{
	D3DXMATRIX matPrj;
	D3DXMatrixPerspectiveFovLH(&matPrj,		// 作成プロジェクションマトリックスへのポインタ
					D3DXToRadian(fViewingAngle),		// 視野角
					fAspectRatio,		// アスペクト比（縦、横比率）
					fClipNear,				// Near クリップ
					fClipFar);				// Far  クリップ
	/*				D3DXToRadian(45.0),		// 視野角
					640.0f / 480.0f,		// アスペクト比（縦、横比率）
					clip_near,				// Near クリップ
					clip_far);				// Far  クリップ*/

	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &matPrj), D3D_OK,
		"CMgl3DManager::SetupProjection()  SetTransform()に失敗" );
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
	m_pD3dDev->SetTransform(D3DTS_VIEW, &mView);
}
/*
//	カメラの注目点設定
void CMgl3DManager::SetCameraViewTarget(float x, float y, float z)
{

}
*/