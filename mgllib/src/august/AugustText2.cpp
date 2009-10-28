//////////////////////////////////////////////////////////
//
//	AugustText2
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustText2.h"
#include "MglText.h"

const char* CAugustText2::CLASS_NAME = "sf/jp/open-mgl/CAugustText2";

using namespace agh;

#define _P m_pBaseControl

//	コンストラクタ
CAugustText2::CAugustText2()
: _BASE(CLASS_NAME)
{
	m_pText = new CMglText();

	m_bChanged = true;
}

//	コンストラクタ
CAugustText2::CAugustText2(const char* szClassName)
: _BASE(szClassName)
{
	m_pText = new CMglText();

	m_bChanged = true;
}

//	デストラクタ
CAugustText2::~CAugustText2()
{
	SAFE_DELETE( m_pText );
}

//	コピーコンストラクタ
CAugustText2::CAugustText2(const CAugustText2 &from)
: _BASE(from.m_strClassName.c_str())
{
	//*this = from;

	m_pText = new CMglText();	//	新たにnewし直さないとデストラクタで二重解放どかーん！

	m_bChanged = true;
}

////////////////////////////////////

//	フォントの再構築
void CAugustText2::ReCreateFont()
{
	m_pGrp = (CMglGraphicManager*)MyuAssertNull(GetValPtr(AUGUST_VALKEY_GRP),
		"CAugustText2: GetValPtr(AUGUST_VALKEY_GRP) の取得に失敗。");

	BOOL bBold, bItalic, bUnderLine, bStrikeOut;

	bBold =		m_dwOption & AGH_FONT_OPTION_BOLD;
	bItalic =	m_dwOption & AGH_FONT_OPTION_ITALIC;
	bUnderLine=	m_dwOption & AGH_FONT_OPTION_UNDERLINE;
	bStrikeOut=	m_dwOption & AGH_FONT_OPTION_STRIKEOUT;

#if _MGL_DXVER == 8
	m_text.Create(m_pGrp, m_nPoint, m_strFontName.c_str(),
		bItalic, bBold, bUnderLine, bStrikeOut);
	/* CMglGraphicManager* in_myudg, int nHeight, const char* szFontName,
			BOOL bItalic, BOOL bBold, BOOL bUnderLine, BOOL bStrikeOut, float fAngle )*/
#else
	m_pText->Init(m_pGrp);
	m_pText->Create(m_nPoint, m_strFontName.c_str(), bItalic, bBold);
#endif

	m_bChanged = false;
}

//	オプションのDWORD取得
DWORD CAugustText2::GetDrawInternalOption()
{
	DWORD dwOption = 0;
	switch(_AGH_TEXT_ALIGN_HFILTER(m_nAlign))
	{
		case AGH_TEXT_ALIGN_LEFT:	dwOption |= DT_LEFT; break;
		case AGH_TEXT_ALIGN_RIGHT:	dwOption |= DT_RIGHT; break;
		case AGH_TEXT_ALIGN_CENTER:	dwOption |= DT_CENTER; break;
	}
	switch(_AGH_TEXT_ALIGN_VFILTER(m_nAlign))
	{
		case AGH_TEXT_ALIGN_TOP:	dwOption |= DT_TOP; break;
		case AGH_TEXT_ALIGN_BOTTOM:	dwOption |= DT_BOTTOM; break;
		case AGH_TEXT_ALIGN_VCENTER:	dwOption |= DT_VCENTER; break;
	}
	return dwOption;
}

//	オプション設定
void CAugustText2::SetOption(agh::AGHDWORD dwOption)
{
	_BASE::SetOption(dwOption);
	OnChanged();
}
void CAugustText2::SetFontName(const char* szFontName){
	_BASE::SetFontName(szFontName);
	OnChanged();
}
void CAugustText2::SetFontPoint(int point){
	_BASE::SetFontPoint(point);
	OnChanged();
}
void CAugustText2::SetColor(agh::COLOR color){
	_BASE::SetColor(color);
	OnChanged();
}

//	描画
void CAugustText2::OnDraw()
{
	if ( m_bChanged )
		ReCreateFont();

	DWORD dwOption = 0;

	//::MessageBox(0,0,0,0);
	agh::CRect absRect = GetAbsoluteRect();

	char work[256];
	sprintf(work,"%d, %d", absRect.left, absRect.top );
	//::MessageBox(0,work,0,0);

	AGHCOLOR bgColor = agh::CRectControl::GetBackgroundColor();

	if ( absRect.top < -10 || absRect.top > 600 )
		return;

	CMglImage tx;
	tx.Create(1,1,TRUE);
	tx.Clear(bgColor);
	tx.Draw( absRect.left, absRect.top, NULL, D3DCOLOR_WHITE, absRect.right - absRect.left, absRect.bottom - absRect.top );

/*	if ( bgColor != 0 )
		//m_pGrp->Paint((::RECT*)&absRect, bgColor);
		m_pGrp->Paint((::RECT*)&(agh::CRect(GetRect())+5), bgColor);
		//m_pGrp->Paint((::RECT*)&(agh::CRect(0,0,100,200)), bgColor);
		//m_pGrp->Clear(bgColor);
	else 
		m_pGrp->Paint((::RECT*)&(agh::CRect(GetRect())+12), D3DCOLOR_ARGB(50,0,0,0));*/

	static int sdfdsf = 0;
	//if ( (sdfdsf % 2000) == 0 )
		m_pText->Draw(GetStr(), absRect.left, absRect.top, m_color, GetDrawInternalOption());

	sdfdsf++;
	//m_pText->Draw(GetStr(), m_rect.left, m_rect.top, m_color, GetDrawInternalOption());
}
