//////////////////////////////////////////////////////////
//
//	MglAghImage
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglAghImage.h"

using namespace agh;

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

void CMglAghImage::OnRegist(CAugustGlobalCommon *pGlobal)
{
	CImageBaseT< CAugustVisualControlBase >::OnRegist(pGlobal);

	const char* szFilePath = m_strFilePath.c_str();
	const char* szAlias = m_strLayerName.c_str();

	//	せっとあっぷ
	m_pGrp = &(pGlobal->grp);
	m_pCacher = &(pGlobal->imgCache);
	
	//	きゃっしゅ
	m_pCacher->Cache(szFilePath);

	SetRect(0,0, m_pCacher->Get(szFilePath)->GetBmpWidth(),
		m_pCacher->Get(szFilePath)->GetBmpHeight());
}

bool CMglAghImage::SetImageFilePath(const char* szImageFilePath)
{
	m_strLayerName = szImageFilePath;
	m_strFilePath = szImageFilePath;

	return true;
}

void CMglAghImage::OnDraw()
{
	_Img()->Draw( GetRect().left, GetRect().top,
		NULL, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_fAngle);
}

