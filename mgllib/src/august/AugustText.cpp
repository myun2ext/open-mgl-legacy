//////////////////////////////////////////////////////////
//
//	AugustText
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustText.h"

//	2008/12/13	「agh::CTextBase< CAugustVisualControlBase >::SetOption(dwOption);」
//				がこうしないとコンパイルエラーになってしまう・・・（どうもVC++6.0のバグだという噂が・・・
using namespace agh;


//	登録されたとき。色々する
void CAugustText::OnRegist(CAugustGlobalCommon *pGlobal)
{
	CAugustVisualControlBase::OnRegist(pGlobal);

	//m_pGrp = &(pGlobal->grp);
	ReCreateFont();	//	デフォルトフォントの作成
}

//	フォントの再構築
void CAugustText::ReCreateFont()
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
	m_text.Init(m_pGrp);
	m_text.Create(m_nPoint, m_strFontName.c_str(), bItalic, bBold);
#endif
}

//	描画イベント
void CAugustText::OnDraw()
{
	DWORD dwOption = 0;
	
	m_text.Draw(GetStr(), m_rect.left, m_rect.top, m_color, GetDrawInternalOption());
}

//	オプションのDWORD取得
DWORD CAugustText::GetDrawInternalOption()
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
void CAugustText::SetOption(agh::AGHDWORD dwOption)
{
	CTextBaseT< CAugustVisualControlBase >::SetOption(dwOption);
	ReCreateFont();
}
void CAugustText::SetFontName(const char* szFontName){
	CTextBaseT< CAugustVisualControlBase >::SetFontName(szFontName);
	ReCreateFont();
}
void CAugustText::SetFontPoint(int point){
	CTextBaseT< CAugustVisualControlBase >::SetFontPoint(point);
	ReCreateFont();
}
void CAugustText::SetColor(AGHCOLOR color){
	CTextBaseT< CAugustVisualControlBase >::SetColor(color);
	ReCreateFont();
}
