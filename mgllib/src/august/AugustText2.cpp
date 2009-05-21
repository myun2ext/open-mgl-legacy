//////////////////////////////////////////////////////////
//
//	AugustText2
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustText2.h"
#include "MglImage.h"

using namespace agh;

#define _P m_pBaseControl

//	コンストラクタ
/*CAugustText2::CAugustText2()
{
}

//	デストラクタ
CAugustText2::~CAugustText2()
{
}*/


bool CAugustText2::Load(const char* szImageFilePath)
{
	m_strFilePath = szImageFilePath;
	
	//CAugustImageLoader* pImgLoader = (CAugustImageLoader*)MyuAssertNull(_BASE::GetValPtr(AUGUST_VALKEY_IMAGE_LOADER),
	//	"CAugustText2:  AUGUST_VALKEY_IMAGE_LOADER の取得に失敗。");
	//m_pImg = pImgLoader->Load(szImageFilePath);	//	基本的に例外で飛ぶはずー
	CAugustGraphicsManager* pAGrpMgr = (CAugustGraphicsManager*)MyuAssertNull(_BASE::GetValPtr(AUGUST_VALKEY_AGRPM),
		"CAugustText2:  AUGUST_VALKEY_IMAGE_LOADER の取得に失敗。");

	//	読み込み
	m_pImg = pAGrpMgr->LoadImageA(szImageFilePath);	//	基本的に例外で飛ぶはずー

	SetRect(0,0, m_pImg->GetBmpWidth(), m_pImg->GetBmpHeight());

	return true;
}

void CAugustText2::OnDraw()
{
	//_Img()->Draw( GetRect().left, GetRect().top,
	int x = GetRect().left;
	int y = GetRect().top;

	if ( m_bCentering == true )	//	オーバーロードでやろうかとも思ったが・・・まぁこっちの方が安心か...
		m_pImg->EnableCenterDraw();
	else
		m_pImg->DisableCenterDraw();

	m_pImg->Draw( x, y,
		(RECT*)&m_srcRect, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_fAngle); // 2009/03/31 対応
	//	NULL, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_fAngle);
}
