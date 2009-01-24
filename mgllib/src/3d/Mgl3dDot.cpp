//////////////////////////////////////////////////////////
//
//	Mgl3dDot
//		- MglGraphicManager �T�[�t�F�X�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mgl3dDot.h"

//	�R���X�g���N�^
CMgl3dDot::CMgl3dDot()
{
	m_myudg = NULL;
	m_d3d = NULL;
}

//	������
void CMgl3dDot::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	m_d3d = m_myudg->GetD3dDevPtr();
}
