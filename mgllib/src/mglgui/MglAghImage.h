//////////////////////////////////////////////////////////
//
//	MglAghImage
//
//////////////////////////////////////////////////////////

#ifndef __MglAghImage_H__
#define __MglAghImage_H__

#include "agh.h"
#include "MglGraphicManager.h"
#include "MglImageCacher.h"

class DLL_EXP agh::CImageBase;

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglAghImage : public agh::CImageBase
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
	
	///////////////////////////////////////////

	CMglImage* _Img(){
		return (*m_pCacher)[m_strFilePath.c_str()];
	}

protected:
	std::string m_strLayerName;
	std::string m_strFilePath;
public:
	//	コンストラクタ
	CMglAghImage(){
		m_pGrp = NULL;
		m_pCacher = NULL;
	}

	bool Load(const char* szImageFilePath);
	void OnDraw();
};

#endif//__MglAghImage_H__
