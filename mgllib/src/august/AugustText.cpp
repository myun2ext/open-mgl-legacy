//////////////////////////////////////////////////////////
//
//	AugustText
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustText.h"

/*
//	�R���X�g���N�^
CAugustText::CAugustText()
{
}

//	�f�X�g���N�^
CAugustText::~CAugustText()
{
}
*/


bool CAugustText::SetImageFilePath(const char* szImageFilePath)
{
	m_strLayerName = szImageFilePath;
	m_strFilePath = szImageFilePath;

	return true;
}

void CAugustText::OnDraw()
{
	_Img()->Draw( GetRect().left, GetRect().top,
		NULL, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_nAngle);
}

