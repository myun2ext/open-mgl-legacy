//////////////////////////////////////////////////////////
//
//	MglCameraMatrixManager
//		- DirectX Graphics 管理クラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglCameraMatrixManager.h"

//	コンストラクタ
CMglCameraMatrixManager::CMglCameraMatrixManager()
{
	m_fCameraPosX = 0;
	m_fCameraPosY = 0;
	m_fCameraPosZ = 0;
	m_fCameraTargetX = 0;
	m_fCameraTargetY = 0;
	m_fCameraTargetZ = 0;

	m_fRotateX = 0;
	m_fRotateY = 0;
	m_fRotateZ = 0;
	m_fMoveX = 0;
	m_fMoveY = 0;
	m_fMoveZ = 0;
}

//	デストラクタ
CMglCameraMatrixManager::~CMglCameraMatrixManager()
{
}

//	開放
void CMglCameraMatrixManager::Release()
{
}

//	初期化
void CMglCameraMatrixManager::Init( CMglGraphicManager* in_myudg )
{
	CMglDgBase::Init(in_myudg);

	//	とりあえずデフォルトなカメラを設定
	SetCamera(0,0,-5.0f, 0,0,0);
}

////////////////////////////////////////////////////////////

void CMglCameraMatrixManager::SetCamera(D3DXMATRIX &matTarget, D3DXMATRIX& matPos, float fRotate)
{
	m_matTarget = matTarget;
	m_matPos = matPos;
	SetCamera(
		D3DXMatrixToVector3(&matTarget),
		D3DXMatrixToVector3(&matPos), fRotate);
}

void CMglCameraMatrixManager::SetCamera(D3DXVECTOR3 &vecTarget, D3DXVECTOR3 &vecPos, float fRotate)
{
	m_vecTarget = vecTarget;
	m_vecPos = vecPos;
	SetCamera(
		vecPos.x, vecPos.y, vecPos.z,
		vecTarget.x, vecTarget.y, vecTarget.z,
		fRotate);
}

void CMglCameraMatrixManager::SetCamera(
	float fPosX, float fPosY, float fPosZ,
	float fTargetX, float fTargetY, float fTargetZ,
	float fRotate)
{
	InitCheck();
	CameraLockAt(fPosX, fPosY, fPosZ, fTargetX, fTargetY, fTargetZ, fRotate);

	m_fCameraPosX = fPosX;
	m_fCameraPosY = fPosY;
	m_fCameraPosZ = fPosZ;
	m_fCameraTargetX = fTargetX;
	m_fCameraTargetY = fTargetY;
	m_fCameraTargetZ = fTargetZ;
}

//	カメラ位置の設定
//void CMglCameraMatrixManager::SetCameraPos(float x, float y, float z)
void CMglCameraMatrixManager::CameraLockAt(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ, float fRotate)
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

	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglCameraMatrixManager::SetCamera()  SetTransform()に失敗" );
}

//	カメラの位置を変更
void CMglCameraMatrixManager::SetCameraPos(float x, float y, float z)
{
	SetCamera(x, y, z, m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
}
//	カメラの注目点を変更
void CMglCameraMatrixManager::SetCameraViewTarget(float x, float y, float z)
{
	SetCamera(m_fCameraPosX, m_fCameraPosY, m_fCameraPosZ, x, y, z);
}
//	カメラを移動（シフト）
void CMglCameraMatrixManager::MoveCamera(float x, float y, float z)
{
	SetCamera(
		m_fCameraPosX+x, m_fCameraPosY+y, m_fCameraPosZ+z,
		m_fCameraTargetX+x, m_fCameraTargetY+y, m_fCameraTargetZ+z);
}

//	カメラをX軸方向に回転
void CMglCameraMatrixManager::CameraRotation(int direction, float fAngle)
{
	InitCheck();

	float rad;

	switch(direction){
	//	横軸
	case MGL3D_X:
		m_fRotateX += fAngle;
		rad = D3DXToRadian(m_fRotateX);
		CameraLockAt(
				m_fCameraPosX+(sin(rad)*(-m_fCameraPosZ)),
				m_fCameraPosY,
				m_fCameraPosZ+(1.0f-cos(rad))*(-m_fCameraPosZ),
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ, 0.0f);
		break;

	//	縦軸
	case MGL3D_Y:
		m_fRotateY += fAngle;
		rad = D3DXToRadian(m_fRotateY);
		CameraLockAt(
				m_fCameraPosX,
				m_fCameraPosY+(sin(rad)*(-m_fCameraPosZ)),
				m_fCameraPosZ+(1.0f-cos(rad))*(-m_fCameraPosZ),
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ, 0.0f);
		break;

	//	Z軸
	case MGL3D_Z:
		m_fRotateY += fAngle;
		rad = D3DXToRadian(m_fRotateY);
		CameraLockAt(
				m_fCameraPosX+(1.0f-cos(rad))*(-m_fCameraPosZ),
				m_fCameraPosY+(sin(rad)*(-m_fCameraPosZ)),
				m_fCameraPosZ,
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ, 0.0f);
		break;
	}
	/*
	D3DXMATRIX matRotation;
	switch(direction){
	case MGL3D_X:
		m_fRotateX += fAngle;
		D3DXMatrixRotationX(&matRotation, D3DXToRadian(m_fRotateX));
		break;
	case MGL3D_Y:
		m_fRotateY += fAngle;
		D3DXMatrixRotationY(&matRotation, D3DXToRadian(m_fRotateY));
		break;
	case MGL3D_Z:
		m_fRotateZ += fAngle;
		D3DXMatrixRotationZ(&matRotation, D3DXToRadian(m_fRotateZ));
		break;
	}

	//matRotation *= m_matView;
	D3DXMATRIX mat;
	D3DXMatrixMultiply(&mat, &m_matView, &matRotation);

	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &mat), D3D_OK,
		"CMglCameraMatrixManager::SetCamera()  SetTransform()に失敗" );
	*/
}

void CMglCameraMatrixManager::SetCameraAngle(float fAngleX, float fAngleY, float fAngleZ)
{
	InitCheck();
	float radX = D3DXToRadian(fAngleX);
	float radY = D3DXToRadian(fAngleY);
	float radZ = D3DXToRadian(fAngleZ);

	CameraLockAt(
		m_fCameraPosX+(sin(radX)*(-m_fCameraPosZ)),
		m_fCameraPosY+(sin(radY)*(-m_fCameraPosZ)),
		m_fCameraPosZ+(1.0f-cos(radX))*(-m_fCameraPosZ),
		m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ, 0.0f);
}

void CMglCameraMatrixManager::Rotate(float fAngleX, float fAngleY, float fAngleZ)
{
	m_fRotateX += fAngleX;
	m_fRotateY += fAngleY;
	m_fRotateZ += fAngleZ;
}

void CMglCameraMatrixManager::ReTransform()
{
	InitCheck();

	//	View（カメラ）
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglCameraMatrixManager::ReTransform()  SetTransform(D3DTS_VIEW)に失敗" );
}

//	View設定
void CMglCameraMatrixManager::SetViewMatrix(D3DXMATRIX &matView)
{
	InitCheck();
	m_matView = matView;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglCameraMatrixManager::ReTransform()  SetTransform(D3DTS_VIEW)に失敗" );
}

///////////////////////////////////////////////////////////////////////////////////

/*	↓移動するだけで全然駄目・・・
//	カメラをX軸方向に回転
void CMglCameraMatrixManager::SetCameraAngle2(float fAngleX, float fAngleY, float fAngleZ)
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
		"CMglCameraMatrixManager::SetCamera()  SetTransform()に失敗" );
}
*/
