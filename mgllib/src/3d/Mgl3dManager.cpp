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

	m_fCameraPosX = 0;
	m_fCameraPosY = 0;
	m_fCameraPosZ = 0;
	m_fCameraTargetX = 0;
	m_fCameraTargetY = 0;
	m_fCameraTargetZ = 0;

	m_fCameraRotationMemX = 0;
	m_fCameraRotationMemY = 0;
	m_fCameraRotationMemZ = 0;
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
	if ( m_pD3dDev == NULL )
		MyuThrow(36129115, "CMgl3DManager::Init()  Direct3DDevice が初期化されていません。");

	//	かりんぐ、らいとにんぐ
	m_pD3dDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3dDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	//	Projectionの設定
	SetupProjection( (m_myudg->GetWidth()*1.0f) / m_myudg->GetHeight());

	//	とりあえずデフォルトなカメラを設定
	SetCamera(0,0,-5.0f, 0,0,0);
}

//	Projectionの設定
void CMgl3DManager::SetupProjection( float fAspectRatio, float fViewingAngle, float fClipNear, float fClipFar )
{
	D3DXMATRIX matPrj;
#if _MGL3D_COORDINATE_USE == _MGL3D_COORDINATE_LEFT_HAND
	D3DXMatrixPerspectiveFovLH(
#else
	D3DXMatrixPerspectiveFovRH(
#endif	
					&matPrj,
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

//D3D_COORDINATE	g_WorldFrame(D3DXVECTOR3(1,1,1), D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
}

////////////////////////////////////////////////////////////

//	カメラ位置の設定
//void CMgl3DManager::SetCameraPos(float x, float y, float z)
void CMgl3DManager::SetCamera(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ)
{
#if _MGL3D_COORDINATE_USE == _MGL3D_COORDINATE_LEFT_HAND
	D3DXMatrixLookAtLH(
#else
	D3DXMatrixLookAtRH(
#endif
					&m_matView
					,&D3DXVECTOR3(fPosX, fPosY, fPosZ)	// カメラ位置
					,&D3DXVECTOR3(fTargetX, fTargetY, fTargetZ)		// カメラの注目点
					,&D3DXVECTOR3(0,1,0)		// 上の向き
					);

	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMgl3DManager::SetCamera()  SetTransform()に失敗" );

	m_fCameraPosX = fPosX;
	m_fCameraPosY = fPosY;
	m_fCameraPosZ = fPosZ;
	m_fCameraTargetX = fTargetX;
	m_fCameraTargetY = fTargetY;
	m_fCameraTargetZ = fTargetZ;
}

//	カメラの位置を変更
void CMgl3DManager::SetCameraPos(float x, float y, float z)
{
	SetCamera(x, y, z, m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
}
//	カメラの注目点を変更
void CMgl3DManager::SetCameraViewTarget(float x, float y, float z)
{
	SetCamera(m_fCameraPosX, m_fCameraPosY, m_fCameraPosZ, x, y, z);
}

//	カメラをX軸方向に回転
void CMgl3DManager::CameraRotation(int direction, float fAngle)
{
	/*
	float rad = D3DXToRadian(fAngle);

	switch(direction){
	case MGL3D_X:
		SetCamera(m_fCameraPosX+(sin(rad)*3), m_fCameraPosY, m_fCameraPosZ,
				  m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
	case MGL3D_Y:
		D3DXMatrixRotationY(&matView, D3DXToRadian(fAngle)); break;
	case MGL3D_Z:
		D3DXMatrixRotationZ(&matView, D3DXToRadian(fAngle)); break;
	}
	*/
	switch(direction){
	case MGL3D_X:
		m_fCameraRotationMemX += fAngle;
		D3DXMatrixRotationX(&m_matView, D3DXToRadian(m_fCameraRotationMemX));
		break;
	case MGL3D_Y:
		m_fCameraRotationMemY += fAngle;
		D3DXMatrixRotationY(&m_matView, D3DXToRadian(m_fCameraRotationMemY));
		break;
	case MGL3D_Z:
		m_fCameraRotationMemZ += fAngle;
		D3DXMatrixRotationZ(&m_matView, D3DXToRadian(m_fCameraRotationMemZ));
		break;
	}
/*
	switch(direction){
	case MGL3D_X:
		m_fCameraRotationMemX += fAngle;
		D3DXMatrixRotationX(&m_matView, D3DXToRadian(fAngle));
		break;
	case MGL3D_Y:
		m_fCameraRotationMemY += fAngle;
		D3DXMatrixRotationY(&m_matView, D3DXToRadian(fAngle));
		break;
	case MGL3D_Z:
		m_fCameraRotationMemZ += fAngle;
		D3DXMatrixRotationZ(&m_matView, D3DXToRadian(fAngle));
		break;
	}
	*/
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMgl3DManager::SetCamera()  SetTransform()に失敗" );
}

