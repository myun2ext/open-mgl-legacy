//////////////////////////////////////////////////////////
//
//	MglSprite
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglSprite.h"

//	�R���X�g���N�^
CMglSprite::CMglSprite()
{
	m_pTex = new CMglD3dTexture();
}

//	�f�X�g���N�^
CMglSprite::~CMglSprite()
{
	SAFE_DELETE( m_pTex );
}

//	�`��
void CMglSprite::Draw()
{
	
}

