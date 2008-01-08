//////////////////////////////////////////////////////////
//
//	MglImageFader
//		- MglGraphicManager �T�[�t�F�X�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglImageFader.h"

//	�R���X�g���N�^
CMglImageFader::CMglImageFader()
{
	//m_pImgMgr = NULL;
	m_pImage = NULL;
	m_nFadeSpeed = 0;
	m_x = m_y = 0;
	m_color = 0;
	m_nFrameCounter = -1;
	//m_nFadeInStart = -1;
	m_nFadeOutStart = -1;
	ZeroMemory( &m_rect, sizeof(m_rect) );
}

//	�f�X�g���N�^
CMglImageFader::~CMglImageFader()
{

}

/*
//	�Z�b�g�A�b�v
void CMglImageFader::Setup( CMglImageManager* pImageManager, const char* szName, int nFadeSpeed,
						    int x, int y, CONST RECT *srcRect, D3DCOLOR color )
{
	m_pImgMgr = pImageManager;
	m_strName = szName;
	m_nFadeSpeed =nFadeSpeed;
	m_x =x;
	m_y = y;
	m_color = color;
	if ( srcRect != NULL )
		m_rect = *srcRect;
}
*/
void CMglImageFader::Setup( CMglImage* pImage, int nFadeSpeed, int x, int y, CONST RECT *srcRect, D3DCOLOR color )
{
	m_pImage = pImage;
	m_nFadeSpeed =nFadeSpeed;
	m_x = x;
	m_y = y;
	m_color = color;
	if ( srcRect != NULL )
		m_rect = *srcRect;
}

/*
//	�t�F�[�h�C��
void CMglImageFader::FadeIn( int nFadeSpeed )
{
	InitCheck();
	if ( nFadeSpeed == 0 )
		nFadeSpeed = m_nFadeSpeed;
}

//	�t�F�[�h�A�E�g
void CMglImageFader::FadeOut( int nFadeSpeed )
{
	InitCheck();
	if ( nFadeSpeed == 0 )
		nFadeSpeed = m_nFadeSpeed;
}
*/

void CMglImageFader::DoDraw()
{
	InitCheck();

	int nPlusAlpha = 0;

	//	�t�F�[�h�A�E�g
	if ( m_nFadeOutStart >= 0 )
	{
		int a = m_nFrameCounter - m_nFadeOutStart;
		nPlusAlpha = 256 - a*m_nFadeSpeed;
		if ( nPlusAlpha > 255 )
			nPlusAlpha = 255;
		if ( a > 255 || nPlusAlpha < 0 ){
			nPlusAlpha = 0;

			//	�����I��肷 -> ������
			m_nFrameCounter = -2;	//	���Ƃ�++���邩��
			m_nFadeOutStart = -1;
		}
	}
	//	�t�F�[�h�C��
	else if ( m_nFrameCounter >= 0 )
	{
		nPlusAlpha = m_nFrameCounter*m_nFadeSpeed;
		if ( m_nFrameCounter > 255 || nPlusAlpha > 255 )
			nPlusAlpha = 255;
	}
	else
	{
		return;
	}

	//	�`��
	D3DCOLOR drawColor = D3DCOLOR_ZEROALPHA_FILTER(m_color);
	drawColor |= D3DCOLOR_A(nPlusAlpha);
	if ( m_rect.top==0 && m_rect.left==0 && m_rect.bottom==0 && m_rect.right==0 )
		m_pImage->Draw(m_x,m_y,NULL,drawColor);
//		m_pImgMgr->Get(m_strName.c_str())->Draw(m_x,m_y,NULL,drawColor);
	else
		m_pImage->Draw(m_x,m_y,&m_rect,drawColor);
//		m_pImgMgr->Get(m_strName.c_str())->Draw(m_x,m_y,&m_rect,drawColor);

	//	�J�E���g�A�b�v
	m_nFrameCounter++;
}

