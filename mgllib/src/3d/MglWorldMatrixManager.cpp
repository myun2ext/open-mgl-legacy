//////////////////////////////////////////////////////////
//
//	MglWorldMatrixManager
//		- DirectX Graphics 管理クラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglWorldMatrixManager.h"

//	コンストラクタ
CMglWorldMatrixManager::CMglWorldMatrixManager()
{
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

	m_fRotateX = 0;
	m_fRotateY = 0;
	m_fRotateZ = 0;
	m_fMoveX = 0;
	m_fMoveY = 0;
	m_fMoveZ = 0;
}

//	デストラクタ
CMglWorldMatrixManager::~CMglWorldMatrixManager()
{
}

//	開放
void CMglWorldMatrixManager::Release()
{
}

//	初期化
void CMglWorldMatrixManager::Init( CMglGraphicManager* in_myudg )
{
	CMglDgBase::Init(in_myudg);
	/*m_myudg = in_myudg;
	m_pD3dDev = m_myudg->GetD3dDevPtr();
	if ( m_pD3dDev == NULL )
		MyuThrow(36129115, "CMglWorldMatrixManager::Init()  Direct3DDevice が初期化されていません。");*/

	//	Projectionの設定
	SetupProjection( (m_myudg->GetWidth()*1.0f) / m_myudg->GetHeight());

	//	とりあえずデフォルトなカメラを設定
	SetCamera(0,0,-5.0f, 0,0,0);

	/*
	//	ワールド設定
    D3DXMATRIX mRotX, mRotY, mTrans;
	D3DXMatrixRotationY(&mRotY, 0.0f);
	D3DXMatrixRotationX(&mRotX, 0.0f);
	D3DXMatrixTranslation(&mTrans, 0,0,0.0f);
	m_matWorld = mRotX * mRotY * mTrans;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &m_matWorld), D3D_OK,
		"CMglWorldMatrixManager::Init()  SetTransform(D3DTS_WORLD)に失敗" );
	*/
	D3DXMatrixIdentity(&m_matWorld);
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &m_matWorld), D3D_OK,
		"CMglWorldMatrixManager::Init()  SetTransform(D3DTS_WORLD)に失敗" );
}

//	Projectionの設定
void CMglWorldMatrixManager::SetupProjection( float fAspectRatio, float fViewingAngle, float fClipNear, float fClipFar )
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
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMglWorldMatrixManager::SetupProjection()  SetTransform()に失敗" );

	m_fAspectRatio = fAspectRatio;
	m_fViewingAngle = fViewingAngle;
	m_fClipNear = fClipNear;
	m_fClipFar = fClipFar;

//D3D_COORDINATE	g_WorldFrame(D3DXVECTOR3(1,1,1), D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
}

////////////////////////////////////////////////////////////

void CMglWorldMatrixManager::SetCamera(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ)
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
//void CMglWorldMatrixManager::SetCameraPos(float x, float y, float z)
void CMglWorldMatrixManager::CameraLockAt(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ)
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
		"CMglWorldMatrixManager::SetCamera()  SetTransform()に失敗" );
}

//	カメラの位置を変更
void CMglWorldMatrixManager::SetCameraPos(float x, float y, float z)
{
	SetCamera(x, y, z, m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
}
//	カメラの注目点を変更
void CMglWorldMatrixManager::SetCameraViewTarget(float x, float y, float z)
{
	SetCamera(m_fCameraPosX, m_fCameraPosY, m_fCameraPosZ, x, y, z);
}
//	カメラを移動（シフト）
void CMglWorldMatrixManager::MoveCamera(float x, float y, float z)
{
	SetCamera(
		m_fCameraPosX+x, m_fCameraPosY+y, m_fCameraPosZ+z,
		m_fCameraTargetX+x, m_fCameraTargetY+y, m_fCameraTargetZ+z);
}

//	カメラをX軸方向に回転
void CMglWorldMatrixManager::CameraRotation(int direction, float fAngle)
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
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
		break;

	//	縦軸
	case MGL3D_Y:
		m_fRotateY += fAngle;
		rad = D3DXToRadian(m_fRotateY);
		CameraLockAt(
				m_fCameraPosX,
				m_fCameraPosY+(sin(rad)*(-m_fCameraPosZ)),
				m_fCameraPosZ+(1.0f-cos(rad))*(-m_fCameraPosZ),
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
		break;

	//	Z軸
	case MGL3D_Z:
		m_fRotateY += fAngle;
		rad = D3DXToRadian(m_fRotateY);
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
		"CMglWorldMatrixManager::SetCamera()  SetTransform()に失敗" );
	*/
}

void CMglWorldMatrixManager::SetCameraAngle(float fAngleX, float fAngleY, float fAngleZ)
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

//	ワールドを設定
void CMglWorldMatrixManager::SetWorld(
		float fRotateX, float fRotateY, float fRotateZ,
		float fMoveX, float fMoveY, float fMoveZ )
{
	D3DXMATRIX mRotX, mRotY, mRotZ, mTrans;
	D3DXMatrixRotationX(&mRotX, D3DXToRadian(fRotateX));
	D3DXMatrixRotationY(&mRotY, D3DXToRadian(fRotateY));
	D3DXMatrixRotationZ(&mRotZ, D3DXToRadian(fRotateZ));
	D3DXMatrixTranslation(&mTrans, fMoveX, fMoveY, fMoveZ);

	SetWorldMatrix(mRotX * mRotY * mRotZ * mTrans);
	/*m_matWorld = mRotX * mRotY * mRotZ * mTrans;

	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &m_matWorld), D3D_OK,
		"CMglWorldMatrixManager::Init()  SetTransform(D3DTS_WORLD)に失敗" );*/

	m_fRotateX = fRotateX;
	m_fRotateY = fRotateY;
	m_fRotateZ = fRotateZ;
	m_fMoveX = fMoveX;
	m_fMoveY = fMoveY;
	m_fMoveZ = fMoveZ;
}

void CMglWorldMatrixManager::Rotate(float fAngleX, float fAngleY, float fAngleZ)
{
	m_fRotateX += fAngleX;
	m_fRotateY += fAngleY;
	m_fRotateZ += fAngleZ;

	SetWorld(m_fRotateX, m_fRotateY, m_fRotateZ, m_fMoveX, m_fMoveY, m_fMoveZ);
}

void CMglWorldMatrixManager::ReTransform()
{
	InitCheck();

	//	ワールド設定
    /*D3DXMATRIX mWorld, mRotX, mRotY, mTrans;
	D3DXMatrixRotationY(&mRotY, 0.0f);
	D3DXMatrixRotationX(&mRotX, 0.0f);
	D3DXMatrixTranslation(&mTrans, 0,0,0.0f);
	mWorld = mRotX * mRotY * mTrans;
*/
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &m_matWorld), D3D_OK,
		"CMglWorldMatrixManager::ReTransform()  SetTransform(D3DTS_WORLD)に失敗" );

	//	View（カメラ）
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglWorldMatrixManager::ReTransform()  SetTransform(D3DTS_VIEW)に失敗" );

	//	プロジェクション
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMglWorldMatrixManager::SetupProjection()  SetTransform()に失敗" );
}

//	ワールド設定
void CMglWorldMatrixManager::SetWorldMatrix(D3DXMATRIX &matWorld)
{
	InitCheck();
	m_matWorld = matWorld;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &m_matWorld), D3D_OK,
		"CMglWorldMatrixManager::ReTransform()  SetTransform(D3DTS_WORLD)に失敗" );
}

//	View設定
void CMglWorldMatrixManager::SetViewMatrix(D3DXMATRIX &matView)
{
	InitCheck();
	m_matView = matView;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglWorldMatrixManager::ReTransform()  SetTransform(D3DTS_VIEW)に失敗" );
}

//	Projection設定
void CMglWorldMatrixManager::SetProjectionMatrix(D3DXMATRIX &matProjection)
{
	InitCheck();
	m_projection = matProjection;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMglWorldMatrixManager::SetupProjection()  SetTransform()に失敗" );
}

///////////////////////////////////////////////////////////////////////////////////

/*	↓移動するだけで全然駄目・・・
//	カメラをX軸方向に回転
void CMglWorldMatrixManager::SetCameraAngle2(float fAngleX, float fAngleY, float fAngleZ)
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
		"CMglWorldMatrixManager::SetCamera()  SetTransform()に失敗" );
}
*/

void CMglWorldMatrixManager::ConvertToScreenVector(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pInVector)
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

