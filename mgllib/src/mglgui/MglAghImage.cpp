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


bool CMglAghImage::Load(const char* szImageFilePath)
{
	m_strLayerName = szImageFilePath;
	m_strFilePath = szImageFilePath;

	return true;
}

void CMglAghImage::OnDraw()
{
	_Img()->Draw();
}

