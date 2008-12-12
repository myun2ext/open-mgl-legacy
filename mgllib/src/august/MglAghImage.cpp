//////////////////////////////////////////////////////////
//
//	MglAghImage
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglAghImage.h"

/*
//	コンストラクタ
CMglAghImage::CMglAghImage()
{
}

//	デストラクタ
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

