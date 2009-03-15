//////////////////////////////////////////////////////////
//
//	MglProjectionMatrixManager
//		- DirectX Graphics �Ǘ��N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglProjectionMatrixManager.h"

//	�R���X�g���N�^
CMglProjectionMatrixManager::CMglProjectionMatrixManager()
{
	m_fAspectRatio = 640.0f/480.0f;
	m_fViewingAngle = 45.0f;
	m_fClipNear = 0.01f;
	m_fClipFar = 100.0f;
}

//	�f�X�g���N�^
CMglProjectionMatrixManager::~CMglProjectionMatrixManager()
{
}

//	�J��
void CMglProjectionMatrixManager::Release()
{
}

//	������
void CMglProjectionMatrixManager::Init( CMglGraphicManager* in_myudg )
{
	CMglDgBase::Init(in_myudg);

	//	Projection�̐ݒ�
	SetupProjection( (m_myudg->GetWidth()*1.0f) / m_myudg->GetHeight());
}

//	Projection�̐ݒ�
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
					D3DXToRadian(fViewingAngle),		// ����p
					fAspectRatio,			// �A�X�y�N�g��i�c�A���䗦�j
					fClipNear,				// Near �N���b�v
					fClipFar);				// Far  �N���b�v
	/*				D3DXToRadian(45.0),		// ����p
					640.0f / 480.0f,		// �A�X�y�N�g��i�c�A���䗦�j
					clip_near,				// Near �N���b�v
					clip_far);				// Far  �N���b�v*/
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMglProjectionMatrixManager::SetupProjection()  SetTransform()�Ɏ��s" );

	m_fAspectRatio = fAspectRatio;
	m_fViewingAngle = fViewingAngle;
	m_fClipNear = fClipNear;
	m_fClipFar = fClipFar;

//D3D_COORDINATE	g_WorldFrame(D3DXVECTOR3(1,1,1), D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));
}

//	Projection�ݒ�
void CMglProjectionMatrixManager::SetProjectionMatrix(D3DXMATRIX &matProjection)
{
	InitCheck();
	m_projection = matProjection;
	MyuAssert( m_pD3dDev->SetTransform(D3DTS_PROJECTION, &m_projection), D3D_OK,
		"CMglProjectionMatrixManager::SetupProjection()  SetTransform()�Ɏ��s" );
}
