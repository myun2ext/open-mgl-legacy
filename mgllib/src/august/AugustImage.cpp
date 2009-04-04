//////////////////////////////////////////////////////////
//
//	AugustImage
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustImage.h"

using namespace agh;

#define _P m_pBaseControl

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

void CAugustImage::OnRegist(CAugustGlobalCommon *pGlobal)
{
	_BASE::OnRegist(pGlobal);

	m_pCacher = &(pGlobal->imgCache);
}

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


////////////////////////////////////////////////////////////////

void CAugustImageCore::OnRegist(CAugustGlobalCommon *pGlobal)
{
	_BASE::OnRegist(pGlobal);

	m_pCacher = &(pGlobal->imgCache);
}

bool CAugustImageCore::Load(const char* szImageFilePath)
{
	m_strFilePath = szImageFilePath;
	
	if ( m_pCacher == NULL ){
		MyuThrow(993243, "CAugustImage::Load()  親コントロールがありません。(CAugustScreen::RegistControl() による登録が行われていません。)");
	}

	//	読み込み
	m_pCacher->Cache(szImageFilePath);
	m_pImg = m_pCacher->Get(szImageFilePath);

	m_pBaseControl->SetRect(0,0, m_pImg->GetBmpWidth(), m_pImg->GetBmpHeight());

	return true;
}

void CAugustImageCore::OnDraw()
{
	//_Img()->Draw( GetRect().left, GetRect().top,
	int x = _P->GetRect().left;
	int y = _P->GetRect().top;

	if ( _P->IsCentering() )	//	オーバーロードでやろうかとも思ったが・・・まぁこっちの方が安心か...
		m_pImg->EnableCenterDraw();
	else
		m_pImg->DisableCenterDraw();

	m_pImg->Draw( x, y,
		(RECT*)&(m_pBaseControl->GetRect()),
		_P->GetColor(), _P->GetScaleX(), _P->GetScaleY(), 0.5f, 0.5f, _P->GetAngle()); // 2009/03/31 対応
	//	NULL, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_fAngle);
}

