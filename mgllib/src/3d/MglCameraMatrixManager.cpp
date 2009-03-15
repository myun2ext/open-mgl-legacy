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
	//m_fRotate = 0.0f;
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

	//	�Ƃ肠�����f�t�H���g�ȃJ������ݒ�
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

	CameraLockAt(vecPos, vecTarget, D3DXVECTOR3(0,1,0));
	/*SetCamera(
		vecPos.x, vecPos.y, vecPos.z,
		vecTarget.x, vecTarget.y, vecTarget.z,
		fRotate);*/
}

/////////////////////////////////////////////////////////////

void CMglCameraMatrixManager::SetTargetPos(D3DXVECTOR3 &vec){}
void CMglCameraMatrixManager::SetCameraPos(D3DXVECTOR3 &vec){}
void CMglCameraMatrixManager::MoveTarget(D3DXVECTOR3 &vec){}
void CMglCameraMatrixManager::MoveCamera(D3DXVECTOR3 &vec){}

void CMglCameraMatrixManager::SetCameraAngle(D3DXVECTOR3 &vecAngles){}
void CMglCameraMatrixManager::Rotate(float fAngleX, float fAngleY, float fAngleZ){}

void CMglCameraMatrixManager::ReCreateViewMatrix()
{

	//SetCamera();
	//CameraLockAt();
}

////////////////////////////////////////////////////////////

//	ReTransform
void CMglCameraMatrixManager::ReTransform()
{
	InitCheck();

	//	2009/03/16 �Ȃ��ReTransform�̎��ɂ��Ȃ��񂾂�B�Ȃ񂩈Ӗ�����̂��ȁE�E�E�H
	//ReCreateViewMatrix(); <- �������E�E�E����SetCamera()�Ă΂ꂽ���̂��߂��E�E�E

	//	View�i�J�����j
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglCameraMatrixManager::ReTransform()  SetTransform(D3DTS_VIEW)�Ɏ��s" );
}

//	�J�����ʒu�̐ݒ�
void CMglCameraMatrixManager::ReCreateViewMatrix(D3DXVECTOR3 &vecEye, D3DXVECTOR3 &vecAt, D3DXVECTOR3 &vecUp)
{
	InitCheck();

#if _MGL3D_COORDINATE_USE == _MGL3D_COORDINATE_LEFT_HAND
	D3DXMatrixLookAtLH(
#else
	D3DXMatrixLookAtRH(
#endif
					&m_matView, &vecEye, &vecAt, &vecUp
//					,&D3DXVECTOR3(fPosX, fPosY, fPosZ)	// �J�����ʒu
//					,&D3DXVECTOR3(fTargetX, fTargetY, fTargetZ)		// �J�����̒��ړ_
//					,&D3DXVECTOR3(0,1,0)		// ��̌���
					);

	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglCameraMatrixManager::ReCreateViewMatrix()  SetTransform()�Ɏ��s" );
}

/////////////////////////////////////////////////////////////////////

//	View�ݒ�
void CMglCameraMatrixManager::SetViewMatrix(D3DXMATRIX &matView)
{
	InitCheck();
	m_matView = matView;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_VIEW, &m_matView), D3D_OK,
		"CMglCameraMatrixManager::ReTransform()  SetTransform(D3DTS_VIEW)�Ɏ��s" );
}
