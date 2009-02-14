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

void CMglWorldMatrixManager::SetsTransform()
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
}

//	ワールド設定
void CMglWorldMatrixManager::SetWorldMatrix(D3DXMATRIX &matWorld)
{
	InitCheck();
	m_matWorld = matWorld;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &m_matWorld), D3D_OK,
		"CMglWorldMatrixManager::ReTransform()  SetTransform(D3DTS_WORLD)に失敗" );
}
