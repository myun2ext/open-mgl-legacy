//////////////////////////////////////////////////////////
//
//	AugustImage1
//
//////////////////////////////////////////////////////////

#ifndef __AugustImage1_H__
#define __AugustImage1_H__

#include "agh.h"
#include "AugustCommon.h"
#include "MglGraphicManager.h"
#include "MglImageCacher.h"

#pragma warning( disable : 4660 ) 
class DLL_EXP agh::CImageBase;

DLL_TMPL_EXP CAugustVisualControlBaseT<agh::CImageBase>;


//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CAugustImage1 : public agh::CImageBase, public CAugustVisualControlBase2
//class DLL_EXP CAugustImage1 : public CAugustVisualControlBaseT<agh::CImageBase>
{
private:
	//typedef CAugustVisualControlBaseT<agh::CImageBase> _BASE;
	typedef CAugustVisualControlBase2 _BASE;

protected:
	CMglImageCacher *m_pCacher;
	CMglImage* m_pImg;
	std::string m_strFilePath;

protected:	//	_AGH_EVENT_ACCESS_MODIFIER�łȂ��̂ɂ͉����Ӗ��ł�����񂾂낤��
	virtual void OnRegist(CAugustGlobalCommon *pGlobal);
	virtual void OnDraw();

public:
	//	�R���X�g���N�^
	CAugustImage1(){
		m_pCacher = NULL;
		m_pImg = NULL;
	}
	virtual ~CAugustImage1(){} // ����Ă����Ȃ��Ƌ��炭CImageBase����̃f�X�g���N�^����肭�����Ȃ��C������E�E�E

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);

	virtual agh::CControlBase* _GetAghControl(){ return this; }
};

////////////////////////////////////////////////////////////////////

/*
template class DLL_EXP agh::CImageBaseT< CAugustVisualControlBase >;
//class DLL_EXP agh::CImageBase;

//	�N���X�錾  /////////////////////////////////////////////////////////
//class DLL_EXP CAugustImage1 : public agh::CImageBase
class DLL_EXP CAugustImage1 : public agh::CImageBaseT< CAugustVisualControlBase >
{
private:
	CMglGraphicManager *m_pGrp;
	CMglImageCacher *m_pCacher;
protected:
	CMglImage* m_pImg;
	std::string m_strFilePath;

protected:	//	_AGH_EVENT_ACCESS_MODIFIER�łȂ��̂ɂ͉����Ӗ��ł�����񂾂낤��
	virtual void OnRegist(CAugustGlobalCommon *pGlobal);
	virtual void OnDraw();


public:
	//	�R���X�g���N�^
	CAugustImage1(){
		m_pGrp = NULL;
		m_pCacher = NULL;
	}

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);
};
*/

/*

typedef CAugustImage1 CAugustImage1Ctrl;
typedef CAugustImage1 CAugustImage1;
*/
#endif//__AugustImage_old_H__
