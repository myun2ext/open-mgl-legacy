//////////////////////////////////////////////////////////
//
//	AugustText2
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustText2.h"
#include "MglText.h"

using namespace agh;

#define _P m_pBaseControl

//	コンストラクタ
CAugustText2::CAugustText2()
{
	m_pText = new CMglText();
}

//	デストラクタ
CAugustText2::~CAugustText2()
{
	delete m_pText;
}

////////////////////////////////////

//	フォントの再構築
void CAugustText2::ReCreateFont()
{
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
	ReCreateFont();
}
void CAugustText2::SetFontName(const char* szFontName){
	_BASE::SetFontName(szFontName);
	ReCreateFont();
}
void CAugustText2::SetFontPoint(int point){
	_BASE::SetFontPoint(point);
	ReCreateFont();
}
void CAugustText2::SetColor(AGHCOLOR color){
	_BASE::SetColor(color);
	ReCreateFont();
}

//	描画
void CAugustText2::OnDraw()
{
	DWORD dwOption = 0;
	m_pText->Draw(GetStr(), m_rect.left, m_rect.top, m_color, GetDrawInternalOption());
}