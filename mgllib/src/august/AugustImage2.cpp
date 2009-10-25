//////////////////////////////////////////////////////////
//
//	AugustImage2
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustImage2.h"
#include "MglImage.h"

using namespace agh;

#define _P m_pBaseControl

//	コンストラクタ
/*CAugustImage2::CAugustImage2()
{
}

//	デストラクタ
CAugustImage2::~CAugustImage2()
{
}*/


bool CAugustImage2::LoadEx(const char* szImageFilePath, agh::COLOR transparentColor)
{
	RegistedCheck();
	////////////////////////////////////////

	m_strFilePath = szImageFilePath;
	
	//CAugustImageLoader* pImgLoader = (CAugustImageLoader*)MyuAssertNull(_BASE::GetValPtr(AUGUST_VALKEY_IMAGE_LOADER),
	//	"CAugustImage2:  AUGUST_VALKEY_IMAGE_LOADER の取得に失敗。");
	//m_pImg = pImgLoader->Load(szImageFilePath);	//	基本的に例外で飛ぶはずー
	CAugustGraphicsManager* pAGrpMgr = (CAugustGraphicsManager*)MyuAssertNull(_BASE::GetValPtr(AUGUST_VALKEY_AGRPM),
		"CAugustImage2:  AUGUST_VALKEY_IMAGE_LOADER の取得に失敗。");

	//	読み込み
	//m_pImg = pAGrpMgr->LoadImageA(szImageFilePath);	//	基本的に例外で飛ぶはずー
	m_pImg = pAGrpMgr->LoadImage(szImageFilePath, transparentColor);	//	基本的に例外で飛ぶはずー

	SetRect(0,0, m_pImg->GetBmpWidth(), m_pImg->GetBmpHeight());

	return true;
}

void CAugustImage2::OnDraw()
{
	RegistedCheck();
	if ( m_pImg == NULL )	//	2009/10/25
		return;

	////////////////////////////////////////

	//_Img()->Draw( GetRect().left, GetRect().top,
	int x = GetRect().left;
	int y = GetRect().top;

	if ( m_bCentering == true )	//	オーバーロードでやろうかとも思ったが・・・まぁこっちの方が安心か...
		m_pImg->EnableCenterDraw();
	else
		m_pImg->DisableCenterDraw();

/*	char work[1024];
	sprintf(work, "%d, %d, (%d, %d, %d, %d), color=%08X, %f, %f, %f", x, y,
		m_srcRect.left, m_srcRect.top, m_srcRect.right, m_srcRect.bottom,
		m_color, m_fScaleX, m_fScaleY, m_fAngle);*/

	m_pImg->Draw( x, y,
		(::RECT*)&m_srcRect, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_fAngle); // 2009/03/31 対応
	//	NULL, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_fAngle);

//	MessageBox(NULL,work,NULL,NULL);
}
