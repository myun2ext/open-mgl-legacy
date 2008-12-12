//////////////////////////////////////////////////////////
//
//	AugustText
//
//////////////////////////////////////////////////////////

#ifndef __AugustText_H__
#define __AugustText_H__

#include "agh.h"
#include "AugustCommon.h"
#include "MglGraphicManager.h"
#include "MglText.h"

//class DLL_EXP agh::CTextBase;
//class DLL_EXP agh::CTextBase< CAugustVisualControlBase >;
template class DLL_EXP agh::CTextBaseT< CAugustVisualControlBase >;

//	クラス宣言  /////////////////////////////////////////////////////////
//class DLL_EXP CAugustText : public agh::CTextBase, public CAugustControlBase
class DLL_EXP CAugustText : public agh::CTextBaseT< CAugustVisualControlBase >
{
private:
	//BOOL bBold, bItalic, bUnderLine, bStrikeOut;
	void ReCreateFont();
	DWORD GetDrawInternalOption();

protected:
	CMglGraphicManager *m_pGrp;
	CMglText m_text;

	// ---- Event Handlers ----
	void OnRegist(CAugustGlobalCommon *pGlobal);
	void OnDraw();

public:
	//	コンストラクタ
	CAugustText(){
		m_pGrp = NULL;

		/*bBold = FALSE;
		bItalic = FALSE;
		bUnderLine = FALSE;
		bStrikeOut = FALSE;*/
	}

public:
	//	オーバーライド系
	virtual void SetOption(agh::AGHDWORD dwOption);

};

typedef CAugustText CMglguiText;

#endif//__AugustText_H__
