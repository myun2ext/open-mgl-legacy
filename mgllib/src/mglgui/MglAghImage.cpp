//////////////////////////////////////////////////////////
//
//	MglAghImage
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglAghImage.h"

/*
//	�R���X�g���N�^
CMglAghImage::CMglAghImage()
{
}

//	�f�X�g���N�^
CMglAghImage::~CMglAghImage()
{
}
*/


bool CMglAghImage::SetImageFilePath(const char* szImageFilePath)
{
	m_strLayerName = szImageFilePath;
	m_strFilePath = szImageFilePath;

	return true;
}

void CMglAghImage::OnDraw()
{
	_Img()->Draw( GetRect().left, GetRect().top,
		NULL, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_nAngle);
}

