//////////////////////////////////////////////////////////
//
//	MglProjectionMatrixManager
//		- DirectX Graphics 管理クラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglProjectionMatrixManager.h"

//	コンストラクタ
CMglProjectionMatrixManager::CMglProjectionMatrixManager()
{
	m_fAspectRatio = 640.0f/480.0f;
	m_fViewingAngle = 45.0f;
	m_fClipNear = 0.01f;
	m_fClipFar = 100.0f;
}

//	デストラクタ
CMglProjectionMatrixManager::~CMglProjectionMatrixManager()
{
}

//	開放
void CMglProjectionMatrixManager::Release()
{
}

//	初期化
void CMglProjectionMatrixManager::Init( CMglGraphicManager* in_myudg )
{
	CMglDgBase::Init(in_myudg);

	//	Projectionの設定
	SetupProjection( (m_myudg->GetWidth()*1.0f) / m_myudg->GetHeight());
}

//	Projectionの設定
void CMglProjectionMatrixManager::SetupProjection( float fAspectRatio, float fViewingAngle, float fClipNear, float fClipFar )
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
					fAspectRatio,			// アスペクト比（縦、横比率）
					fClipNear,				// Near クリップ
					fClipFar);				// Far  クリップ
	/*				D3DXToRadian(45.0),		// 視野角
					640.0f / 480.0f,		// アスペクト比（縦、横比率）
					clip_near,				// Near クリップ
					clip_far);				// Far  クリップ*/
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMglProjectionMatrixManager::SetupProjection()  SetTransform()に失敗" );

	m_fAspectRatio = fAspectRatio;
	m_fViewingAngle = fViewingAngle;
	m_fClipNear = fClipNear;
	m_fClipFar = fClipFar;

//D3D_COORDINATE	g_WorldFrame(D3DXVECTOR3(1,1,1), D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
}

//	Projection設定
void CMglProjectionMatrixManager::SetProjectionMatrix(D3DXMATRIX &matProjection)
{
	InitCheck();
	m_projection = matProjection;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMglProjectionMatrixManager::SetupProjection()  SetTransform()に失敗" );
}
