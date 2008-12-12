//////////////////////////////////////////////////////////
//
//	AugustText
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustText.h"

//	登録されたとき。色々する
void CAugustText::OnRegist(CAugustGlobalCommon *pGlobal)
{
	CAugustControlBase::OnRegist(pGlobal);

	m_pGrp = &(pGlobal->grp);
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

	m_text.Create(m_pGrp, m_nPoint, m_strFontName.c_str(),
		bItalic, bBold, bUnderLine, bStrikeOut);
	/* CMglGraphicManager* in_myudg, int nHeight, const char* szFontName,
			BOOL bItalic, BOOL bBold, BOOL bUnderLine, BOOL bStrikeOut, float fAngle )*/
}

//	描画イベント
void CAugustText::OnDraw()
{
	m_text.Draw(GetStr(), m_rect.left, m_rect.top, m_color );
}

//	オプション設定
void CAugustText::SetOption(agh::AGHDWORD dwOption)
{
	CTextBase::SetOption(dwOption);
	//if ( dwOption & 
	ReCreateFont();
}
