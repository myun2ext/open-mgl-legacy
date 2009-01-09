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

	//	Projection�̐ݒ�
	SetupProjection( (m_myudg->GetWidth()*1.0f) / m_myudg->GetHeight());
}

//	Projection�̐ݒ�
void CMgl3DManager::SetupProjection( float fAspectRatio, float fViewingAngle, float fClipNear, float fClipFar )
{
	D3DXMATRIX matPrj;
	D3DXMatrixPerspectiveFovLH(&matPrj,		// �쐬�v���W�F�N�V�����}�g���b�N�X�ւ̃|�C���^
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
}

////////////////////////////////////////////////////////////

//	�J�����ʒu�̐ݒ�
//void CMgl3DManager::SetCameraPos(float x, float y, float z)
void CMgl3DManager::SetCamera(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ)
{
	D3DXMATRIX mView;
	D3DXMatrixLookAtLH(&mView
					,&D3DXVECTOR3(fPosX, fPosY, fPosZ)	// �J�����ʒu
					,&D3DXVECTOR3(fTargetX, fTargetY, fTargetZ)		// �J�����̒��ړ_
					,&D3DXVECTOR3(0,1,0)		// ��̌���
					);
	m_pD3dDev->SetTransform(D3DTS_VIEW, &mView);
}
/*
//	�J�����̒��ړ_�ݒ�
void CMgl3DManager::SetCameraViewTarget(float x, float y, float z)
{

}
*/