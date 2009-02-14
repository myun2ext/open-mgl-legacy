//////////////////////////////////////////////////////////
//
//	MglWorldMatrixManager
//		- DirectX Graphics �Ǘ��N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglWorldMatrixManager.h"

//	�R���X�g���N�^
CMglWorldMatrixManager::CMglWorldMatrixManager()
{
	m_fRotateX = 0;
	m_fRotateY = 0;
	m_fRotateZ = 0;
	m_fMoveX = 0;
	m_fMoveY = 0;
	m_fMoveZ = 0;
}

//	�f�X�g���N�^
CMglWorldMatrixManager::~CMglWorldMatrixManager()
{
}

//	�J��
void CMglWorldMatrixManager::Release()
{
}

//	������
void CMglWorldMatrixManager::Init( CMglGraphicManager* in_myudg )
{
	CMglDgBase::Init(in_myudg);

	/*
	//	���[���h�ݒ�
    D3DXMATRIX mRotX, mRotY, mTrans;
	D3DXMatrixRotationY(&mRotY, 0.0f);
	D3DXMatrixRotationX(&mRotX, 0.0f);
	D3DXMatrixTranslation(&mTrans, 0,0,0.0f);
	m_matWorld = mRotX * mRotY * mTrans;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &m_matWorld), D3D_OK,
		"CMglWorldMatrixManager::Init()  SetTransform(D3DTS_WORLD)�Ɏ��s" );
	*/
	D3DXMatrixIdentity(&m_matWorld);
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &m_matWorld), D3D_OK,
		"CMglWorldMatrixManager::Init()  SetTransform(D3DTS_WORLD)�Ɏ��s" );
}

//	���[���h��ݒ�
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
		"CMglWorldMatrixManager::Init()  SetTransform(D3DTS_WORLD)�Ɏ��s" );*/

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

	//	���[���h�ݒ�
    /*D3DXMATRIX mWorld, mRotX, mRotY, mTrans;
	D3DXMatrixRotationY(&mRotY, 0.0f);
	D3DXMatrixRotationX(&mRotX, 0.0f);
	D3DXMatrixTranslation(&mTrans, 0,0,0.0f);
	mWorld = mRotX * mRotY * mTrans;
*/
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &m_matWorld), D3D_OK,
		"CMglWorldMatrixManager::ReTransform()  SetTransform(D3DTS_WORLD)�Ɏ��s" );
}

//	���[���h�ݒ�
void CMglWorldMatrixManager::SetWorldMatrix(D3DXMATRIX &matWorld)
{
	InitCheck();
	m_matWorld = matWorld;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &m_matWorld), D3D_OK,
		"CMglWorldMatrixManager::ReTransform()  SetTransform(D3DTS_WORLD)�Ɏ��s" );
}
