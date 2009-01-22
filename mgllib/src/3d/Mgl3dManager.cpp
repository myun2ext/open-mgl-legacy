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

	m_fAspectRatio = 640.0f/480;
	m_fViewingAngle = 45.0f;
	m_fClipNear = 0.01f;
	m_fClipFar = 100.0f;

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

	//	ワールド設定
    D3DXMATRIX mWorld, mRotX, mRotY, mTrans;
	D3DXMatrixRotationY(&mRotY, 0.0f);
	D3DXMatrixRotationX(&mRotX, 0.0f);
	D3DXMatrixTranslation(&mTrans, 0,0,0.0f);
	mWorld = mRotX * mRotY * mTrans;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &mWorld), D3D_OK,
		"CMgl3DManager::Init()  SetTransform(D3DTS_WORLD)に失敗" );
}

//	Projectionの設定
void CMgl3DManager::SetupProjection( float fAspectRatio, float fViewingAngle, float fClipNear, float fClipFar )
{
	InitCheck();

	//D3DXMATRIX matPrj;
#if _MGL3D_COORDINATE_USE == _MGL3D_COORDINATE_LEFT_HAND
	D3DXMatrixPerspectiveFovLH(
#else
	D3DXMatrixPerspectiveFovRH(
#endif	
					&m_projection,
					D3DXToRadian(fViewingAngle),		// 視野角
					fAspectRatio,		// アスペクト比（縦、横比率）
					fClipNear,				// Near クリップ
					fClipFar);				// Far  クリップ
	/*				D3DXToRadian(45.0),		// 視野角
					640.0f / 480.0f,		// アスペクト比（縦、横比率）
					clip_near,				// Near クリップ
					clip_far);				// Far  クリップ*/
	/*MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMgl3DManager::SetupProjection()  SetTransform()に失敗" );*/

	m_fAspectRatio = fAspectRatio;
	m_fViewingAngle = fViewingAngle;
	m_fClipNear = fClipNear;
	m_fClipFar = fClipFar;

//D3D_COORDINATE	g_WorldFrame(D3DXVECTOR3(1,1,1), D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
}

////////////////////////////////////////////////////////////

void CMgl3DManager::SetCamera(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ)
{
	InitCheck();
	CameraLockAt(fPosX, fPosY, fPosZ, fTargetX, fTargetY, fTargetZ);

	m_fCameraPosX = fPosX;
	m_fCameraPosY = fPosY;
	m_fCameraPosZ = fPosZ;
	m_fCameraTargetX = fTargetX;
	m_fCameraTargetY = fTargetY;
	m_fCameraTargetZ = fTargetZ;
}

//	カメラ位置の設定
//void CMgl3DManager::SetCameraPos(float x, float y, float z)
void CMgl3DManager::CameraLockAt(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ)
{
	InitCheck();
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

	/*MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMgl3DManager::SetCamera()  SetTransform()に失敗" );*/
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
//	カメラを移動（シフト）
void CMgl3DManager::MoveCamera(float x, float y, float z)
{
	SetCamera(
		m_fCameraPosX+x, m_fCameraPosY+y, m_fCameraPosZ+z,
		m_fCameraTargetX+x, m_fCameraTargetY+y, m_fCameraTargetZ+z);
}

//	カメラをX軸方向に回転
void CMgl3DManager::CameraRotation(int direction, float fAngle)
{
	InitCheck();

	float rad;

	switch(direction){
	//	横軸
	case MGL3D_X:
		m_fCameraRotationMemX += fAngle;
		rad = D3DXToRadian(m_fCameraRotationMemX);
		CameraLockAt(
				m_fCameraPosX+(sin(rad)*(-m_fCameraPosZ)),
				m_fCameraPosY,
				m_fCameraPosZ+(1.0f-cos(rad))*(-m_fCameraPosZ),
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
		break;

	//	縦軸
	case MGL3D_Y:
		m_fCameraRotationMemY += fAngle;
		rad = D3DXToRadian(m_fCameraRotationMemY);
		CameraLockAt(
				m_fCameraPosX,
				m_fCameraPosY+(sin(rad)*(-m_fCameraPosZ)),
				m_fCameraPosZ+(1.0f-cos(rad))*(-m_fCameraPosZ),
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
		break;

	//	Z軸
	case MGL3D_Z:
		m_fCameraRotationMemY += fAngle;
		rad = D3DXToRadian(m_fCameraRotationMemY);
		CameraLockAt(
				m_fCameraPosX+(1.0f-cos(rad))*(-m_fCameraPosZ),
				m_fCameraPosY+(sin(rad)*(-m_fCameraPosZ)),
				m_fCameraPosZ,
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
		break;
	}
	/*
	D3DXMATRIX matRotation;
	switch(direction){
	case MGL3D_X:
		m_fCameraRotationMemX += fAngle;
		D3DXMatrixRotationX(&matRotation, D3DXToRadian(m_fCameraRotationMemX));
		break;
	case MGL3D_Y:
		m_fCameraRotationMemY += fAngle;
		D3DXMatrixRotationY(&matRotation, D3DXToRadian(m_fCameraRotationMemY));
		break;
	case MGL3D_Z:
		m_fCameraRotationMemZ += fAngle;
		D3DXMatrixRotationZ(&matRotation, D3DXToRadian(m_fCameraRotationMemZ));
		break;
	}

	//matRotation *= m_matView;
	D3DXMATRIX mat;
	D3DXMatrixMultiply(&mat, &m_matView, &matRotation);

	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &mat), D3D_OK,
		"CMgl3DManager::SetCamera()  SetTransform()に失敗" );
	*/
}

void CMgl3DManager::SetCameraAngle(float fAngleX, float fAngleY, float fAngleZ)
{
	InitCheck();
	float radX = D3DXToRadian(fAngleX);
	float radY = D3DXToRadian(fAngleY);
	float radZ = D3DXToRadian(fAngleZ);

	CameraLockAt(
		m_fCameraPosX+(sin(radX)*(-m_fCameraPosZ)),
		m_fCameraPosY+(sin(radY)*(-m_fCameraPosZ)),
		m_fCameraPosZ+(1.0f-cos(radX))*(-m_fCameraPosZ),
		m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
}

void CMgl3DManager::ReTransform()
{
	InitCheck();

	//	ワールド設定
    D3DXMATRIX mWorld, mRotX, mRotY, mTrans;
	D3DXMatrixRotationY(&mRotY, 0.0f);
	D3DXMatrixRotationX(&mRotX, 0.0f);
	D3DXMatrixTranslation(&mTrans, 0,0,0.0f);
	mWorld = mRotX * mRotY * mTrans;

	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &mWorld), D3D_OK,
		"CMgl3DManager::ReTransform()  SetTransform(D3DTS_WORLD)に失敗" );

	//	View（カメラ）
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMgl3DManager::ReTransform()  SetTransform(D3DTS_VIEW)に失敗" );

	//	プロジェクション
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMgl3DManager::SetupProjection()  SetTransform()に失敗" );
}


///////////////////////////////////////////////////////////////////////////////////

/*	↓移動するだけで全然駄目・・・
//	カメラをX軸方向に回転
void CMgl3DManager::SetCameraAngle2(float fAngleX, float fAngleY, float fAngleZ)
{
	D3DXMATRIX matX;
	D3DXMATRIX matY;
	D3DXMATRIX matZ;
	D3DXMatrixRotationX(&matX, D3DXToRadian(fAngleX));
	D3DXMatrixRotationY(&matY, D3DXToRadian(fAngleY));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(fAngleZ));

	D3DXMATRIX mat = m_matView * matX * matY * matZ;
	/*D3DXMatrixMultiply(&mat, &m_matView, &matRotation);
	D3DXMatrixMultiply(&mat, &m_matView, &matRotation);
	D3DXMatrixMultiply(&mat, &m_matView, &matRotation);*

	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &mat), D3D_OK,
		"CMgl3DManager::SetCamera()  SetTransform()に失敗" );
}
*/

void CMgl3DManager::ConvertToScreenVector(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pInVector)
{
	InitCheck();

	_D3DVIEWPORTx vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = m_myudg->GetWidth();
	vp.Height = m_myudg->GetHeight();
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	
	D3DXVec3Project(pOut, pInVector, &vp, &m_projection, &m_matView, &m_matWorld);
}

