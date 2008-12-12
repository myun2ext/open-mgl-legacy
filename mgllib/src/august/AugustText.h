//////////////////////////////////////////////////////////
//
//	AugustText
//
//////////////////////////////////////////////////////////

#ifndef __AugustText_H__
#define __AugustText_H__

#include "agh.h"
#include "MglGraphicManager.h"
#include "MglImageCacher.h"

class DLL_EXP agh::CImageBase;

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CAugustText : public agh::CImageBase
{
	friend class CMglguiScreen;
	friend class CAugustScreen;
private:
	CMglGraphicManager *m_pGrp;
	CMglImageCacher *m_pCacher;

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
	void OnDraw();

protected:
	std::string m_strLayerName;
	std::string m_strFilePath;
public:
	//	コンストラクタ
	CAugustText(){
		m_pGrp = NULL;
		m_pCacher = NULL;
	}

	bool SetImageFilePath(const char* szImageFilePath);
	bool Load(const char* szImageFilePath){ return SetImageFilePath(szImageFilePath); }
};

typedef CAugustText CAugustTextCtrl;
typedef CAugustText CAugustImage;

#endif//__AugustText_H__
