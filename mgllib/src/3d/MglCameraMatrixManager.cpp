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
	//m_fRotate = 0.0f;
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
	//SetCamera(0,0,-5.0f, 0,0,0);
	SetCamera(0,0,0, 0,0,-5.0f);
}

/////////////////////////////////////////////////////////////
void CMglCameraMatrixManager::ZoomIn(float fDistance){}
void CMglCameraMatrixManager::ZoomOut(float fDistance){}


//	ReTransform
void CMglCameraMatrixManager::ReTransform()
{
	InitCheck();

	//	2009/03/16 なんでReTransformの時にやんないんだろ。なんか意味あんのかな・・・？
	ReCreateViewMatrix(); //<- そっか・・・直接SetCamera()呼ばれた時のためか・・・ <- 嘘つけｗｗｗｗちげーよｗｗｗｗ

	//	View（カメラ）
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglCameraMatrixManager::ReTransform()  SetTransform(D3DTS_VIEW)に失敗" );
}

void CMglCameraMatrixManager::ReCreateViewMatrix()
{

	ReCreateMatrixLookAt(m_vecCamera, m_vecTarget, D3DXVECTOR3(0,1,0));
	//SetCamera();
	//CameraLockAt();
}

//	カメラ位置の設定
void CMglCameraMatrixManager::ReCreateMatrixLookAt(D3DXVECTOR3 &vecPos, D3DXVECTOR3 &vecTarget, D3DXVECTOR3 &vecUp)
{
	InitCheck();

#if _MGL3D_COORDINATE_USE == _MGL3D_COORDINATE_LEFT_HAND
	D3DXMatrixLookAtLH(
#else
	D3DXMatrixLookAtRH(
#endif
					&m_matView, &vecPos, &vecTarget, &vecUp
//					,&D3DXVECTOR3(fPosX, fPosY, fPosZ)	// カメラ位置
//					,&D3DXVECTOR3(fTargetX, fTargetY, fTargetZ)		// カメラの注目点
//					,&D3DXVECTOR3(0,1,0)		// 上の向き
					);

/*	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglCameraMatrixManager::ReCreateViewMatrix()  SetTransform()に失敗" );*/
}

/////////////////////////////////////////////////////////////////////

//	View設定
void CMglCameraMatrixManager::SetViewMatrix(D3DXMATRIX &matView)
{
	InitCheck();
	m_matView = matView;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglCameraMatrixManager::ReTransform()  SetTransform(D3DTS_VIEW)に失敗" );
}
