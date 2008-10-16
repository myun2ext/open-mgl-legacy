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

