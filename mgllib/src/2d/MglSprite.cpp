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
	ZeroMemory(&m_rect, sizeof(m_rect));

	m_bShow = TRUE;
	m_color = D3DCOLOR_WHITE;
	m_x = 0;
	m_y = 0;
	m_fScaleX = 1.0f;
	m_fScaleY = 1.0f;
	m_fAngle = 0.0f;

	m_fRotationCenterX = 0.5f;
	m_fRotationCenterY = 0.5f;
}

//	�f�X�g���N�^
CMglSprite::~CMglSprite()
{

}

//	�`��
void CMglSprite::Draw()
{
	RECT* pRect = &m_rect;
	if ( m_rect.left == 0 && m_rect.right == 0 && m_rect.top == 0 && m_rect.bottom == 0 )
		pRect = NULL;

	//	�`��
	CMglImage::Draw(m_x, m_y, pRect, m_color,
		m_fScaleX, m_fScaleY, m_fRotationCenterX, m_fRotationCenterY, m_fAngle );
}

