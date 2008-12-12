//////////////////////////////////////////////////////////
//
//	AugustText
//
//////////////////////////////////////////////////////////

#ifndef __AugustText_H__
#define __AugustText_H__

#include "agh.h"
#include "MglGraphicManager.h"
#include "MglText.h"

class DLL_EXP agh::CTextBase;

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CAugustText : public agh::CTextBase
{
	friend class CMglguiScreen;
	friend class CAugustScreen;
private:
	CMglGraphicManager *m_pGrp;

	//	friend Access
	void _Setup(CMglGraphicManager *pGrp, CMglImageCacher *pCacher){
		m_pGrp = pGrp;
		m_pCacher = pCacher;
	}
	
	///////////////////////////////////////////

	CMglImage* _Img(){
		return (*m_pCacher)[m_strFilePath.c_str()];
	}
protected:
	CMglText m_text;

	// ---- Event Handlers ----
	void OnDraw();

public:
	//	コンストラクタ
	CAugustText(){
		m_pGrp = NULL;
		m_pCacher = NULL;
	}

};

typedef CAugustText CMglguiText;

#endif//__AugustText_H__
