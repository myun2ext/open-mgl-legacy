//////////////////////////////////////////////////////////
//
//	MglAghImage
//
//////////////////////////////////////////////////////////

#ifndef __MglAghImage_H__
#define __MglAghImage_H__

#include "agh.h"
#include "AugustCommon.h"
#include "MglGraphicManager.h"
#include "MglImageCacher.h"

class DLL_EXP agh::CImageBase;

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglAghImage : public agh::CImageBase, public CAugustControlBase
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
	CMglAghImage(){
		m_pGrp = NULL;
		m_pCacher = NULL;
	}

	bool SetImageFilePath(const char* szImageFilePath);
	bool Load(const char* szImageFilePath){ return SetImageFilePath(szImageFilePath); }
};

typedef CMglAghImage CMglAghImageCtrl;
typedef CMglAghImage CAugustImage;

#endif//__MglAghImage_H__
