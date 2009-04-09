//////////////////////////////////////////////////////////
//
//	AugustImage
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustImage.h"
#include "AugustImageImpl.h"

using namespace agh;

#define _P m_pBaseControl

////////////////////////////////////////////////////////////////

/*
void CAugustImageImpl::OnRegist(CAugustGlobalCommon *pGlobal)
{
	_BASE::OnRegist(pGlobal);

	m_pCacher = &(pGlobal->imgCache);
}
*/

bool CAugustImageImpl::Load(const char* szImageFilePath)
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

void CAugustImageImpl::OnDraw()
{
	if ( m_pImg == NULL ){
		MyuThrow(993243, "CAugustImage::OnDraw()  親コントロールがありません。(CAugustScreen::RegistControl() による登録が行われていません。)");
	}

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

////////////////////////////////////////////////////////////

#define _IMPL  ((CAugustImageImpl*)m_pImpl)

//	コンストラクタ
CAugustImage2::CAugustImage2(){
	m_pImpl = new CAugustImageImpl(this);
}

//	デストラクタ
CAugustImage2::~CAugustImage2(){
	//SAFE_DELETE_TMPL<CAugustImageImpl*>((CAugustImageImpl**)&m_pImpl);
	SAFE_DELETE_TMPL(CAugustImageImpl,m_pImpl);
}

/*void CAugustImage2::OnDraw(){ _IMPL->OnDraw(); }
bool CAugustImage2::Load(const char* szImageFilePath){ return _IMPL->Load(szImageFilePath); }*/
