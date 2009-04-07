//////////////////////////////////////////////////////////
//
//	AugustImage
//
//////////////////////////////////////////////////////////

#ifndef __AugustImage_H__
#define __AugustImage_H__

#include "agh.h"
#include "AugustCtrlBase.h"

#pragma warning( disable : 4660 ) 
//class DLL_EXP agh::CImageBase;
class DLL_EXP agh::CImageCore2;

//	クラス宣言  /////////////////////////////////////////////////////////
//class DLL_EXP CAugustImage2 : public agh::CImageBase, public agh::CImageCore
class DLL_EXP CAugustImage2 : public agh::CImageCore2, public CAugustCtrlBase
{
protected:
	//void *m_pImpl;
	//std::string m_strFilePath;

_AGH_EVENT_ACCESS_MODIFIER:	//	protected,,,_AGH_EVENT_ACCESS_MODIFIERでないのには何か意味でもあるんだろうか
	//virtual void OnRegist(agh::CControlBase *pParentControl);	//	親コントロールでもらってくる
//	virtual void OnDraw();

public:
	//	コンストラクタ
	CAugustImage2();
	virtual ~CAugustImage2();

	//bool SetImageFilePath(const char* szImageFilePath);
//	virtual bool Load(const char* szImageFilePath);

	virtual agh::CControlBase* _GetAghControl(){ return this; }
};

/*
//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CAugustImage2 : public agh::CImageBase
{
protected:
	void *m_pImpl;
	//std::string m_strFilePath;

_AGH_EVENT_ACCESS_MODIFIER:	//	protected,,,_AGH_EVENT_ACCESS_MODIFIERでないのには何か意味でもあるんだろうか
	//virtual void OnRegist(agh::CControlBase *pParentControl);	//	親コントロールでもらってくる
	virtual void OnDraw();

public:
	//	コンストラクタ
	CAugustImage2();
	virtual ~CAugustImage2();

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);

	virtual agh::CControlBase* _GetAghControl(){ return this; }
};
*/

////////////////////////////////////////////////////////////////////

/*
template class DLL_EXP agh::CImageBaseT< CAugustVisualControlBase >;
//class DLL_EXP agh::CImageBase;

//	クラス宣言  /////////////////////////////////////////////////////////
//class DLL_EXP CAugustImage : public agh::CImageBase
class DLL_EXP CAugustImage : public agh::CImageBaseT< CAugustVisualControlBase >
{
private:
	CMglGraphicManager *m_pGrp;
	CMglImageCacher *m_pCacher;
protected:
	CMglImage* m_pImg;
	std::string m_strFilePath;

protected:	//	_AGH_EVENT_ACCESS_MODIFIERでないのには何か意味でもあるんだろうか
	virtual void OnRegist(CAugustGlobalCommon *pGlobal);
	virtual void OnDraw();


public:
	//	コンストラクタ
	CAugustImage(){
		m_pGrp = NULL;
		m_pCacher = NULL;
	}

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);
};
*/

typedef CAugustImage2 CAugustImage;

#endif//__AugustImage_H__
