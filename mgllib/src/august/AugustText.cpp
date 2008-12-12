//////////////////////////////////////////////////////////
//
//	AugustText
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustText.h"

//	2008/12/13	�uagh::CTextBase< CAugustVisualControlBase >::SetOption(dwOption);�v
//				���������Ȃ��ƃR���p�C���G���[�ɂȂ��Ă��܂��E�E�E�i�ǂ���VC++6.0�̃o�O���Ƃ����\���E�E�E
using namespace agh;


//	�o�^���ꂽ�Ƃ��B�F�X����
void CAugustText::OnRegist(CAugustGlobalCommon *pGlobal)
{
	CAugustVisualControlBase::OnRegist(pGlobal);

	m_pGrp = &(pGlobal->grp);
	ReCreateFont();	//	�f�t�H���g�t�H���g�̍쐬
}

//	�t�H���g�̍č\�z
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

//	�`��C�x���g
void CAugustText::OnDraw()
{
	DWORD dwOption = 0;
	
	m_text.Draw(GetStr(), m_rect.left, m_rect.top, m_color, GetDrawInternalOption());
}

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

//	�I�v�V�����ݒ�
void CAugustText::SetOption(agh::AGHDWORD dwOption)
{
	CTextBaseT< CAugustVisualControlBase >::SetOption(dwOption);
	//if ( dwOption & 
	ReCreateFont();
}
