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


//	�N���X�錾  /////////////////////////////////////////////////////////
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

protected:	//	_AGH_EVENT_ACCESS_MODIFIER�łȂ��̂ɂ͉����Ӗ��ł�����񂾂낤��
	virtual void OnRegist(CAugustGlobalCommon *pGlobal);
	virtual void OnDraw();

public:
	//	�R���X�g���N�^
	CAugustImage(){
		m_pCacher = NULL;
		m_pImg = NULL;
	}
	virtual ~CAugustImage(){} // ����Ă����Ȃ��Ƌ��炭CImageBase����̃f�X�g���N�^����肭�����Ȃ��C������E�E�E

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);

	virtual agh::CControlBase* _GetAghControl(){ return this; }
};

//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CAugustImageImpl : public agh::IImageImpl, public CAugustVisualControlBase3
{
private:
	//typedef CAugustVisualControlBaseT<agh::CImageBase> _BASE;
	typedef CAugustVisualControlBase3 _BASE;

protected:
	CMglImageCacher *m_pCacher;
	CMglImage* m_pImg;
	agh::CImageBase *m_pBaseControl;
	std::string m_strFilePath; //�ʂɐe�ł��������H�i���₾�߂��H

_AGH_EVENT_ACCESS_MODIFIER:	//	_AGH_EVENT_ACCESS_MODIFIER�łȂ��̂ɂ͉����Ӗ��ł�����񂾂낤��
	virtual void OnRegist(CAugustGlobalCommon *pGlobal);
	virtual void OnDraw();

public:
	//	�R���X�g���N�^
	CAugustImageImpl(agh::CImageBase *pControl){
		m_pCacher = NULL;
		m_pImg = NULL;
		m_pBaseControl = pControl;
	}
	/*CAugustImageCore(){
		m_pCacher = NULL;
		m_pImg = NULL;
		m_pBaseControl = NULL;
	}*/
	virtual ~CAugustImageImpl(){}

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);

	////////////////////////////////////////////

	/*void SetAghControlPtr(agh::CImageBase *pControl){
		m_pBaseControl = pControl;
	}*/
};
typedef CAugustImageImpl CAugustImageCore;




//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CAugustImage2 : public agh::CImageBase
{
protected:
	void *m_pImpl;
	//std::string m_strFilePath;

_AGH_EVENT_ACCESS_MODIFIER:	//	protected,,,_AGH_EVENT_ACCESS_MODIFIER�łȂ��̂ɂ͉����Ӗ��ł�����񂾂낤��
	//virtual void OnRegist(agh::CControlBase *pParentControl);	//	�e�R���g���[���ł�����Ă���
	virtual void OnDraw();

public:
	//	�R���X�g���N�^
	CAugustImage2();
	virtual ~CAugustImage2();

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);

	virtual agh::CControlBase* _GetAghControl(){ return this; }
};

////////////////////////////////////////////////////////////////////

/*
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

protected:	//	_AGH_EVENT_ACCESS_MODIFIER�łȂ��̂ɂ͉����Ӗ��ł�����񂾂낤��
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
*/



typedef CAugustImage CAugustImageCtrl;
typedef CAugustImage CAugustImage;

#endif//__AugustImage_H__
