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

	//	���[���h�ݒ�
    D3DXMATRIX mWorld, mRotX, mRotY, mTrans;
	D3DXMatrixRotationY(&mRotY, 0.0f);
	D3DXMatrixRotationX(&mRotX, 0.0f);
	D3DXMatrixTranslation(&mTrans, 0,0,0.0f);
	mWorld = mRotX * mRotY * mTrans;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &mWorld), D3D_OK,
		"CMgl3DManager::Init()  SetTransform(D3DTS_WORLD)�Ɏ��s" );
}

//	Projection�̐ݒ�
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
					D3DXToRadian(fViewingAngle),		// ����p
					fAspectRatio,		// �A�X�y�N�g��i�c�A���䗦�j
					fClipNear,				// Near �N���b�v
					fClipFar);				// Far  �N���b�v
	/*				D3DXToRadian(45.0),		// ����p
					640.0f / 480.0f,		// �A�X�y�N�g��i�c�A���䗦�j
					clip_near,				// Near �N���b�v
					clip_far);				// Far  �N���b�v*/
	/*MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMgl3DManager::SetupProjection()  SetTransform()�Ɏ��s" );*/

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

//	�J�����ʒu�̐ݒ�
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
					,&D3DXVECTOR3(fPosX, fPosY, fPosZ)	// �J�����ʒu
					,&D3DXVECTOR3(fTargetX, fTargetY, fTargetZ)		// �J�����̒��ړ_
					,&D3DXVECTOR3(0,1,0)		// ��̌���
					);

	/*MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMgl3DManager::SetCamera()  SetTransform()�Ɏ��s" );*/
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
//	�J�������ړ��i�V�t�g�j
void CMgl3DManager::MoveCamera(float x, float y, float z)
{
	SetCamera(
		m_fCameraPosX+x, m_fCameraPosY+y, m_fCameraPosZ+z,
		m_fCameraTargetX+x, m_fCameraTargetY+y, m_fCameraTargetZ+z);
}

//	�J������X�������ɉ�]
void CMgl3DManager::CameraRotation(int direction, float fAngle)
{
	InitCheck();

	float rad;

	switch(direction){
	//	����
	case MGL3D_X:
		m_fCameraRotationMemX += fAngle;
		rad = D3DXToRadian(m_fCameraRotationMemX);
		CameraLockAt(
				m_fCameraPosX+(sin(rad)*(-m_fCameraPosZ)),
				m_fCameraPosY,
				m_fCameraPosZ+(1.0f-cos(rad))*(-m_fCameraPosZ),
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
		break;

	//	�c��
	case MGL3D_Y:
		m_fCameraRotationMemY += fAngle;
		rad = D3DXToRadian(m_fCameraRotationMemY);
		CameraLockAt(
				m_fCameraPosX,
				m_fCameraPosY+(sin(rad)*(-m_fCameraPosZ)),
				m_fCameraPosZ+(1.0f-cos(rad))*(-m_fCameraPosZ),
				m_fCameraTargetX, m_fCameraTargetY, m_fCameraTargetZ);
		break;

	//	Z��
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
		"CMgl3DManager::SetCamera()  SetTransform()�Ɏ��s" );
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

	//	���[���h�ݒ�
    D3DXMATRIX mWorld, mRotX, mRotY, mTrans;
	D3DXMatrixRotationY(&mRotY, 0.0f);
	D3DXMatrixRotationX(&mRotX, 0.0f);
	D3DXMatrixTranslation(&mTrans, 0,0,0.0f);
	mWorld = mRotX * mRotY * mTrans;

	MyuAssert( m_pD3dDev->SetTransform(D3DTS_WORLD, &mWorld), D3D_OK,
		"CMgl3DManager::ReTransform()  SetTransform(D3DTS_WORLD)�Ɏ��s" );

	//	View�i�J�����j
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMgl3DManager::ReTransform()  SetTransform(D3DTS_VIEW)�Ɏ��s" );

	//	�v���W�F�N�V����
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMgl3DManager::SetupProjection()  SetTransform()�Ɏ��s" );
}


///////////////////////////////////////////////////////////////////////////////////

/*	���ړ����邾���őS�R�ʖځE�E�E
//	�J������X�������ɉ�]
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
		"CMgl3DManager::SetCamera()  SetTransform()�Ɏ��s" );
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

