//////////////////////////////////////////////////////////
//
//	MglTexture2
//		- MglGraphicManager �T�[�t�F�X�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglTexture2.h"

////////////////////////////////////////////////////////////////////

//	�R���X�g���N�^
CMglTexture2::CMglTexture2()
{
	m_myudg = NULL;
	d3d = NULL;
}


//	������
void CMglTexture2::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();
}

//	�J��
void CMglTexture2::Release()
{
}
