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

//	�N���X�錾  /////////////////////////////////////////////////////////
//class DLL_EXP CAugustImage : public agh::CImageBase
class DLL_EXP CAugustImage : public agh::CImageBaseT< CAugustVisualControlBase >
{
private:
	CMglGraphicManager *m_pGrp;
	CMglImageCacher *m_pCacher;
protected:
	CMglImage* m_pImg;
	std::string m_strFilePath;

protected:
	virtual void OnRegist(CAugustGlobalCommon *pGlobal);
	virtual void OnDraw();


public:
	//	�R���X�g���N�^
	CAugustImage(){
		m_pGrp = NULL;
		m_pCacher = NULL;
	}

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);
};

typedef CAugustImage CAugustImageCtrl;
typedef CAugustImage CAugustImage;

#endif//__AugustImage_H__
