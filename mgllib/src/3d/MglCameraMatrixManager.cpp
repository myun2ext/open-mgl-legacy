//////////////////////////////////////////////////////////
//
//	MglCameraMatrixManager
//		- DirectX Graphics �Ǘ��N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglCameraMatrixManager.h"

//	�R���X�g���N�^
CMglCameraMatrixManager::CMglCameraMatrixManager()
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

//	�f�X�g���N�^
CMglCameraMatrixManager::~CMglCameraMatrixManager()
{
}

//	�J��
void CMglCameraMatrixManager::Release()
{
}

//	������
void CMglCameraMatrixManager::Init( CMglGraphicManager* in_myudg )
{
	CMglDgBase::Init(in_myudg);

	//	Projection�̐ݒ�
	SetupProjection( (m_myudg->GetWidth()*1.0f) / m_myudg->GetHeight());

	//	�Ƃ肠�����f�t�H���g�ȃJ������ݒ�
	SetCamera(0,0,-5.0f, 0,0,0);
}

//	Projection�̐ݒ�
void CMglCameraMatrixManager::SetupProjection( float fAspectRatio, float fViewingAngle, float fClipNear, float fClipFar )
{
	InitCheck();

	//D3DXMATRIX matPrj;
#if _MGL3D_COORDINATE_USE == _MGL3D_COORDINATE_LEFT_HAND
	D3DXMatrixPerspectiveFovLH(
#else
	D3DXMatrixPerspectiveFovRH(
#endif	
					&m_projection,
					D3DXToRadian(fViewingAngle),		// ����p
					fAspectRatio,		// �A�X�y�N�g��i�c�A���䗦�j
					fClipNear,				// Near �N���b�v
					fClipFar);				// Far  �N���b�v
	/*				D3DXToRadian(45.0),		// ����p
					640.0f / 480.0f,		// �A�X�y�N�g��i�c�A���䗦�j
					clip_near,				// Near �N���b�v
					clip_far);				// Far  �N���b�v*/
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMglCameraMatrixManager::SetupProjection()  SetTransform()�Ɏ��s" );

	m_fAspectRatio = fAspectRatio;
	m_fViewingAngle = fViewingAngle;
	m_fClipNear = fClipNear;
	m_fClipFar = fClipFar;

//D3D_COORDINATE	g_WorldFrame(D3DXVECTOR3(1,1,1), D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
}

////////////////////////////////////////////////////////////

void CMglCameraMatrixManager::SetCamera(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ)
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

//	�J�����ʒu�̐ݒ�
//void CMglCameraMatrixManager::SetCameraPos(float x, float y, float z)
void CMglCameraMatrixManager::CameraLockAt(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ)
{
	InitCheck();
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
		"CMglCameraMatrixManager::SetCamera()  SetTransform()�Ɏ��s" );
}

//	�J�����̈ʒu��ύX
void CMglCameraMatrixManager::SetCameraPos(float x, float y, float z)
{
	SetCamera(x, y, z, m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
}
//	�J�����̒��ړ_��ύX
void CMglCameraMatrixManager::SetCameraViewTarget(float x, float y, float z)
{
	SetCamera(m_fCameraPosX, m_fCameraPosY, m_fCameraPosZ, x, y, z);
}
//	�J�������ړ��i�V�t�g�j
void CMglCameraMatrixManager::MoveCamera(float x, float y, float z)
{
	SetCamera(
		m_fCameraPosX+x, m_fCameraPosY+y, m_fCameraPosZ+z,
		m_fCameraTargetX+x, m_fCameraTargetY+y, m_fCameraTargetZ+z);
}

//	�J������X�������ɉ�]
void CMglCameraMatrixManager::CameraRotation(int direction, float fAngle)
{
	InitCheck();

	float rad;

	switch(direction){
	//	����
	case MGL3D_X:
		m_fRotateX += fAngle;
		rad = D3DXToRadian(m_fRotateX);
		CameraLockAt(
				m_fCameraPosX+(sin(rad)*(-m_fCameraPosZ)),
				m_fCameraPosY,
				m_fCameraPosZ+(1.0f-cos(rad))*(-m_fCameraPosZ),
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
		break;

	//	�c��
	case MGL3D_Y:
		m_fRotateY += fAngle;
		rad = D3DXToRadian(m_fRotateY);
		CameraLockAt(
				m_fCameraPosX,
				m_fCameraPosY+(sin(rad)*(-m_fCameraPosZ)),
				m_fCameraPosZ+(1.0f-cos(rad))*(-m_fCameraPosZ),
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
		break;

	//	Z��
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
		"CMglCameraMatrixManager::SetCamera()  SetTransform()�Ɏ��s" );
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
		m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
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

	//	View�i�J�����j
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglCameraMatrixManager::ReTransform()  SetTransform(D3DTS_VIEW)�Ɏ��s" );

	//	�v���W�F�N�V����
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMglCameraMatrixManager::SetupProjection()  SetTransform()�Ɏ��s" );
}

//	View�ݒ�
void CMglCameraMatrixManager::SetViewMatrix(D3DXMATRIX &matView)
{
	InitCheck();
	m_matView = matView;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglCameraMatrixManager::ReTransform()  SetTransform(D3DTS_VIEW)�Ɏ��s" );
}

//	Projection�ݒ�
void CMglCameraMatrixManager::SetProjectionMatrix(D3DXMATRIX &matProjection)
{
	InitCheck();
	m_projection = matProjection;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMglCameraMatrixManager::SetupProjection()  SetTransform()�Ɏ��s" );
}

///////////////////////////////////////////////////////////////////////////////////

/*	���ړ����邾���őS�R�ʖځE�E�E
//	�J������X�������ɉ�]
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
		"CMglCameraMatrixManager::SetCamera()  SetTransform()�Ɏ��s" );
}
*/
