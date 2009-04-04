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

#pragma warning( disable : 4660 ) 
class DLL_EXP agh::CImageBase;

DLL_TMPL_EXP CAugustVisualControlBaseT<agh::CImageBase>;


//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CAugustImage : public agh::CImageBase, public CAugustVisualControlBase2
//class DLL_EXP CAugustImage : public CAugustVisualControlBaseT<agh::CImageBase>
{
private:
	//typedef CAugustVisualControlBaseT<agh::CImageBase> _BASE;
	typedef CAugustVisualControlBase2 _BASE;

protected:
	CMglImageCacher *m_pCacher;
	CMglImage* m_pImg;
	std::string m_strFilePath;

protected:	//	_AGH_EVENT_ACCESS_MODIFIERでないのには何か意味でもあるんだろうか
	virtual void OnRegist(CAugustGlobalCommon *pGlobal);
	virtual void OnDraw();

public:
	//	コンストラクタ
	CAugustImage(){
		m_pCacher = NULL;
		m_pImg = NULL;
	}
	virtual ~CAugustImage(){} // 作っておかないと恐らくCImageBaseからのデストラクタが上手く動かない気がする・・・

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);

	virtual agh::CControlBase* _GetAghControl(){ return this; }
};

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CAugustImageCore : public CAugustVisualControlBase2
{
private:
	//typedef CAugustVisualControlBaseT<agh::CImageBase> _BASE;
	typedef CAugustVisualControlBase2 _BASE;

protected:
	CMglImageCacher *m_pCacher;
	CMglImage* m_pImg;
	agh::CImageBase *m_pBaseControl;
	std::string m_strFilePath; //別に親でもいいか？（いやだめか？

protected:	//	_AGH_EVENT_ACCESS_MODIFIERでないのには何か意味でもあるんだろうか
	virtual void OnRegist(CAugustGlobalCommon *pGlobal);
	virtual void OnDraw();

public:
	//	コンストラクタ
	CAugustImageCore(){
		m_pCacher = NULL;
		m_pImg = NULL;
		m_pBaseControl = NULL;
	}
	virtual ~CAugustImageCore(){}

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);
	void SetAghControlPtr(agh::CImageBase *pControl){
		m_pBaseControl = pControl;
	}
};
typedef CAugustImageCore CAugustImageImpl;

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



typedef CAugustImage CAugustImageCtrl;
typedef CAugustImage CAugustImage;

#endif//__AugustImage_H__
