//////////////////////////////////////////////////////////
//
//	MglMatrixManager
//		- DirectX Graphics 管理クラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglMatrixManager.h"

//	コンストラクタ
CMglMatrixManager::CMglMatrixManager()
{
	m_pWorldMgr = NULL;
}

//	デストラクタ
CMglMatrixManager::~CMglMatrixManager()
{
}

//	開放
void CMglMatrixManager::Release()
{
}

//	初期化
void CMglMatrixManager::Init( CMglGraphicManager* in_myudg )
{
	//CMglDgBase::Init(in_myudg);
	CMglCameraMatrixManager::Init(in_myudg);

	//	デフォルトワールドマトリックスを設定しておく
	SetWorldMatrix(m_initWorld);
}

void CMglMatrixManager::ReTransform()
{
	InitCheck();
	//WorldCheck();

	//	ワールドのReTransform
	m_pWorldMgr->ReTransform();

	//	ProjectionのReTransform
	m_matMgrProjection.ReTransform();

	//	カメラのReTransform
	CMglCameraMatrixManager::ReTransform();
}

//////////////////////////////////////////////////////////////////////////////////////////////

void CMglMatrixManager::ConvertToScreenVector(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pInVector)
{
	InitCheck();

	_D3DVIEWPORTx vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = m_myudg->GetWidth();
	vp.Height = m_myudg->GetHeight();
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	
	D3DXVec3Project(pOut, pInVector, &vp,
		&(GetProjectionMatrix()),
		&(GetViewMatrix()),
		+&(m_pWorldMgr->GetMatrix()));
}

