//////////////////////////////////////////////////////////
//
//	MglguiText
//
//////////////////////////////////////////////////////////

#ifndef __MglguiText_H__
#define __MglguiText_H__

#include "agh.h"
#include "AugustCommon.h"
#include "MglGraphicManager.h"
#include "MglText.h"

//class DLL_EXP agh::CTextBase;
//class DLL_EXP agh::CTextBase< CAugustVisualControlBase >;
template class DLL_EXP agh::CTextBaseT< CAugustVisualControlBase >;

//	クラス宣言  /////////////////////////////////////////////////////////
//class DLL_EXP CMglguiText : public agh::CTextBase, public CAugustControlBase
class DLL_EXP CMglguiText : public agh::CTextBaseT< CAugustVisualControlBase >
{
	friend class CMglguiScreen;
private:
	CMglGraphicManager *m_pGrp;
	CMglImageCacher *m_pCacher;

	//	friend Access
	void _Setup(CMglGraphicManager *pGrp, CMglImageCacher *pCacher){
		m_pGrp = pGrp;
		m_pCacher = pCacher;
	}
private:
	//BOOL bBold, bItalic, bUnderLine, bStrikeOut;
	void ReCreateFont();
	DWORD GetDrawInternalOption();

protected:
	CMglText m_text;

	// ---- Event Handlers ----
	void OnRegist(CAugustGlobalCommon *pGlobal);
	void OnDraw();

public:
	// ---- Public Event Handlers ----
	virtual void SetOption(agh::AGHDWORD dwOption);
	virtual void SetFontName(const char* szFontName);
	virtual void SetFontPoint(int point);
	//virtual void SetStr(const char* szStr){ m_textData = szStr; }
	//virtual const char* GetStr(){ return m_textData.c_str(); }
	virtual void SetColor(agh::AGHCOLOR color);
	//virtual void SetOption(AGHDWORD dwOption);
	//virtual AGHCOLOR GetColor(){ return m_color; }
	//virtual AGHDWORD GetOption(){ return m_dwOption; }
	//virtual void Align(int align){ m_nAlign = align; }

public:
	//	コンストラクタ
	CMglguiText(){
		m_pGrp = NULL;

		/*bBold = FALSE;
		bItalic = FALSE;
		bUnderLine = FALSE;
		bStrikeOut = FALSE;*/
	}
};

typedef CMglguiText CMglguiText;

#endif//__MglguiText_H__
