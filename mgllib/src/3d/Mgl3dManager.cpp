//////////////////////////////////////////////////////////
//
//	Mgl3dManager
//		- DirectX Graphics �Ǘ��N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mgl3dManager.h"

//	�R���X�g���N�^
CMgl3dManager::CMgl3dManager()
{
}
//	�f�X�g���N�^
CMgl3dManager::~CMgl3dManager()
{
}

//	�J��
void CMgl3dManager::Release()
{
}

//	������
void CMgl3dManager::Init( CMglGraphicManager* in_myudg )
{
	//CMglDgBase::Init();
	CMglMatrixManager::Init(in_myudg);

	//	����񂮁A�炢�Ƃɂ�
	m_pD3dDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3dDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	//	Z�o�b�t�@�ݒ�
	m_pD3dDev->SetRenderState( D3DRS_ZENABLE,	D3DZB_TRUE );		// Z�o�b�t�@��L���ɂ���B
	m_pD3dDev->SetRenderState( D3DRS_ZWRITEENABLE,		TRUE );			// Z�o�b�t�@�ւ̏������݋���
}
