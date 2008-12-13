//////////////////////////////////////////////////////////
//
//	AugustImage
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustImage.h"

using namespace agh;

/*
//	コンストラクタ
CAugustImage::CAugustImage()
{
}

//	デストラクタ
CAugustImage::~CAugustImage()
{
}
*/

/*void CAugustImage::OnRegist(CAugustGlobalCommon *pGlobal)
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
}*/

bool CAugustImage::Load(const char* szImageFilePath)
{
	m_strFilePath = szImageFilePath;
	
	if ( m_pCacher == NULL ){
		MyuThrow(993243, "CAugustImage::Load()  親コントロールがありません。(CAugustScreen::RegistControl() による登録が行われていません。)");
	}

	//	読み込み
	m_pCacher->Cache(szImageFilePath);
	m_pImg = m_pCacher->Get(szImageFilePath);

	SetRect(0,0, m_pImg->GetBmpWidth(), m_pImg->GetBmpHeight());

	return true;
}

void CAugustImage::OnDraw()
{
	//_Img()->Draw( GetRect().left, GetRect().top,
	m_pImg->Draw( GetRect().left, GetRect().top,
		NULL, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_nAngle);
}

