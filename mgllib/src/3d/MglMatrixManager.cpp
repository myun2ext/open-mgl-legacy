//////////////////////////////////////////////////////////
//
//	MglMatrixManager
//		- DirectX Graphics �Ǘ��N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglMatrixManager.h"

//	�R���X�g���N�^
CMglMatrixManager::CMglMatrixManager()
{
	m_pWorldMgr = NULL;
}

//	�f�X�g���N�^
CMglMatrixManager::~CMglMatrixManager()
{
}

//	�J��
void CMglMatrixManager::Release()
{
}

//	������
void CMglMatrixManager::Init( CMglGraphicManager* in_myudg )
{
	//CMglDgBase::Init(in_myudg);
	CMglCameraMatrixManager::Init(in_myudg);

	//	�f�t�H���g���[���h�}�g���b�N�X��ݒ肵�Ă���
	SetWorldMatrix(m_initWorld);
}

void CMglMatrixManager::ReTransform()
{
	InitCheck();
	//WorldCheck();

	//	���[���h��ReTransform
	m_pWorldMgr->ReTransform();

	//	Projection��ReTransform
	m_matMgrProjection.ReTransform();

	//	�J������ReTransform
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

