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
	d3d = NULL;
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
	d3d = m_myudg->GetD3dDevPtr();
}

