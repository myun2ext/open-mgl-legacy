//////////////////////////////////////////////////////////
//
//	AugustImage
//
//////////////////////////////////////////////////////////

#ifndef __AugustImage_H__
#define __AugustImage_H__

#include "agh.h"
#include "AugustCommon.h"
#include "MglGraphicManager.h"
#include "MglImageCacher.h"

template class DLL_EXP agh::CImageBaseT< CAugustVisualControlBase >;
//class DLL_EXP agh::CImageBase;

//	クラス宣言  /////////////////////////////////////////////////////////
//class DLL_EXP CAugustImage : public agh::CImageBase
class DLL_EXP CAugustImage : public agh::CImageBaseT< CAugustVisualControlBase >
{
	friend class CMglguiScreen;	//	CMguigui用にまだ必要・・・
	friend class CAugustScreen;	//	CMguigui用にまだ必要・・・
private:
	CMglGraphicManager *m_pGrp;
	CMglImageCacher *m_pCacher;
	CMglImage* m_pImg;

	//	friend Access	//	CMguigui用にまだ必要・・・
	void _Setup(CMglGraphicManager *pGrp, CMglImageCacher *pCacher){
		m_pGrp = pGrp;
		m_pCacher = pCacher;
	}
	
	///////////////////////////////////////////

	CMglImage* _Img(){
		return (*m_pCacher)[m_strFilePath.c_str()];
	}
protected:
	//virtual void OnRegist(CAugustGlobalCommon *pGlobal);
	virtual void OnDraw();

protected:
	std::string m_strAlias;
	std::string m_strFilePath;
public:
	//	コンストラクタ
	CAugustImage(){
		m_pGrp = NULL;
		m_pCacher = NULL;
	}

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath){ Load(szImageFilePath,szImageFilePath); }
	virtual bool Load(const char* szImageFilePath, const char* szAlias);
};

typedef CAugustImage CAugustImageCtrl;
typedef CAugustImage CAugustImage;

#endif//__AugustImage_H__
