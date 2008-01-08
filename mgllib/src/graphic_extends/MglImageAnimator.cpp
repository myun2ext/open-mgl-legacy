//////////////////////////////////////////////////////////
//
//	MglImageAnimator
//		- MglGraphicManager �T�[�t�F�X�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglImageAnimator.h"

#define M_IMAGE		g_mglGlobalImageCacher[
//	�R���X�g���N�^
CMglImageAnimator::CMglImageAnimator()
{
	m_nTipWidth = 0;
	m_nTipHeight = 0;
	m_nCounter = 0;
	m_nTipCountX = 0;
	m_nTipCountY = 0;
	m_nTipCount = 0;
	EnableAutoCountUp();

	m_pImage = NULL;
}

//	�f�X�g���N�^
CMglImageAnimator::~CMglImageAnimator()
{

}

//	�ǂݍ���
void CMglImageAnimator::Load( LPCSTR szImageFileName, int nTipWidth, int nTipHeight, D3DCOLOR colorKey )
{
	//	�L��
	m_nTipWidth = nTipWidth;
	m_nTipHeight = nTipHeight;

	//	�摜�t�@�C���̓ǂݍ���
	//m_image.Create( szImageFileName, FALSE, colorKey );
	g_mglGlobalImageCacher.Cache( szImageFileName );	//	2007/04/14 �L���b�V���g�p��
	m_pImage = g_mglGlobalImageCacher[szImageFileName];

	m_nCounter = 0;

	//	�\�ߌv�Z���Ă���
	/*int nBmpWidth = m_image.GetBmpWidth();
	int nBmpHeight = m_image.GetBmpHeight();*/
	int nBmpWidth = m_pImage->GetBmpWidth();
	int nBmpHeight = m_pImage->GetBmpHeight();
	m_nTipCountX = nBmpWidth / m_nTipWidth;
	m_nTipCountY = nBmpHeight / m_nTipHeight;
	m_nTipCount = m_nTipCountX * m_nTipCountY;
}

//	�`��
void CMglImageAnimator::Draw( float x, float y, D3DCOLOR color,
	float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle )
{
	/*
	int nBmpWidth = m_image.GetBmpWidth();
	int nBmpHeight = m_image.GetBmpHeight();

	RECT rect;
	rect.left = (m_nCounter % m_nTipCountX) * nBmpWidth;
	rect.right = rect.left + nBmpWidth;
	rect.top = (m_nCounter / m_nTipCountY);
	rect.bottom = rect.top + nBmpHeight;

	//	�`��
	m_image.Draw( x, y, &rect, color, fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle );
	*/
	DrawEx( m_nCounter, x, y, color, fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle );

	//	�����J�E���g�A�b�v�Ȃ�J�E���g�A�b�v
	if ( m_bAutoCountUp )
		CountUp();
}

//	�`��
void CMglImageAnimator::DrawEx( int nCount, float x, float y, D3DCOLOR color,
	float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle )
{
	/*int nBmpWidth = m_image.GetBmpWidth();
	int nBmpHeight = m_image.GetBmpHeight();*/
	int nBmpWidth = m_pImage->GetBmpWidth();
	int nBmpHeight = m_pImage->GetBmpHeight();

	RECT rect;
	rect.left = (nCount % m_nTipCountX) * nBmpWidth;
	rect.right = rect.left + nBmpWidth;
	rect.top = (nCount / m_nTipCountY);
	rect.bottom = rect.top + nBmpHeight;

	//	�`��
	//m_image.Draw( x, y, &rect, color, fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle );
	m_pImage->Draw( x, y, &rect, color, fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle );
}

void CMglImageAnimator::CountUp()
{
	m_nCounter++;
	m_nCounter %= m_nTipCount;
}

