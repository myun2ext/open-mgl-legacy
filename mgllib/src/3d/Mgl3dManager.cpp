//////////////////////////////////////////////////////////
//
//	Mgl3DManager
//		- DirectX Graphics �Ǘ��N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mgl3DManager.h"

//	�R���X�g���N�^
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

//	�f�X�g���N�^
CMgl3DManager::~CMgl3DManager()
{
}

//	�J��
void CMgl3DManager::Release()
{
}

//	������
void CMgl3DManager::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	m_pD3dDev = m_myudg->GetD3dDevPtr();
	if ( m_pD3dDev == NULL )
		MyuThrow(36129115, "CMgl3DManager::Init()  Direct3DDevice ������������Ă��܂���B");

	//	����񂮁A�炢�Ƃɂ�
	m_pD3dDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3dDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	//	Projection�̐ݒ�
	SetupProjection( (m_myudg->GetWidth()*1.0f) / m_myudg->GetHeight());

	//	�Ƃ肠�����f�t�H���g�ȃJ������ݒ�
	SetCamera(0,0,-5.0f, 0,0,0);
}

//	Projection�̐ݒ�
void CMgl3DManager::SetupProjection( float fAspectRatio, float fViewingAngle, float fClipNear, float fClipFar )
{
	D3DXMATRIX matPrj;
#if _MGL3D_COORDINATE_USE == _MGL3D_COORDINATE_LEFT_HAND
	D3DXMatrixPerspectiveFovLH(
#else
	D3DXMatrixPerspectiveFovRH(
#endif	
					&matPrj,
					D3DXToRadian(fViewingAngle),		// ����p
					fAspectRatio,		// �A�X�y�N�g��i�c�A���䗦�j
					fClipNear,				// Near �N���b�v
					fClipFar);				// Far  �N���b�v
	/*				D3DXToRadian(45.0),		// ����p
					640.0f / 480.0f,		// �A�X�y�N�g��i�c�A���䗦�j
					clip_near,				// Near �N���b�v
					clip_far);				// Far  �N���b�v*/
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &matPrj), D3D_OK,
		"CMgl3DManager::SetupProjection()  SetTransform()�Ɏ��s" );

//D3D_COORDINATE	g_WorldFrame(D3DXVECTOR3(1,1,1), D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
}

////////////////////////////////////////////////////////////

void CMgl3DManager::SetCamera(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ)
{
	SetCameraWorking(fPosX, fPosY, fPosZ, fTargetX, fTargetY, fTargetZ);

	m_fCameraPosX = fPosX;
	m_fCameraPosY = fPosY;
	m_fCameraPosZ = fPosZ;
	m_fCameraTargetX = fTargetX;
	m_fCameraTargetY = fTargetY;
	m_fCameraTargetZ = fTargetZ;
}

//	�J�����ʒu�̐ݒ�
//void CMgl3DManager::SetCameraPos(float x, float y, float z)
void CMgl3DManager::SetCameraWorking(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ)
{
#if _MGL3D_COORDINATE_USE == _MGL3D_COORDINATE_LEFT_HAND
	D3DXMatrixLookAtLH(
#else
	D3DXMatrixLookAtRH(
#endif
					&m_matView
					,&D3DXVECTOR3(fPosX, fPosY, fPosZ)	// �J�����ʒu
					,&D3DXVECTOR3(fTargetX, fTargetY, fTargetZ)		// �J�����̒��ړ_
					,&D3DXVECTOR3(0,1,0)		// ��̌���
					);

	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMgl3DManager::SetCamera()  SetTransform()�Ɏ��s" );
}

//	�J�����̈ʒu��ύX
void CMgl3DManager::SetCameraPos(float x, float y, float z)
{
	SetCamera(x, y, z, m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
}
//	�J�����̒��ړ_��ύX
void CMgl3DManager::SetCameraViewTarget(float x, float y, float z)
{
	SetCamera(m_fCameraPosX, m_fCameraPosY, m_fCameraPosZ, x, y, z);
}

//	�J������X�������ɉ�]
void CMgl3DManager::CameraRotation(int direction, float fAngle)
{
	float rad;
	D3DXMATRIX matView;

	switch(direction){
	case MGL3D_X:
		m_fCameraRotationMemX += fAngle;
		rad = D3DXToRadian(m_fCameraRotationMemX);
		SetCameraWorking(
				m_fCameraPosX+(sin(rad)*(-m_fCameraPosZ)),
				m_fCameraPosY,
				m_fCameraPosZ+(1.0f-cos(rad))*(-m_fCameraPosZ),
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
		break;
	case MGL3D_Y:
		D3DXMatrixRotationY(&matView, D3DXToRadian(fAngle)); break;
	case MGL3D_Z:
		D3DXMatrixRotationZ(&matView, D3DXToRadian(fAngle)); break;
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
		"CMgl3DManager::SetCamera()  SetTransform()�Ɏ��s" );
	*/
}

