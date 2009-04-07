#ifndef __AugustCommon_H__
#define __AugustCommon_H__

#include "agh.h"
#include "MglImageCacher.h"
#include "MglImageLayer.h"
#include "MglInput.h"
#include "MglAudio.h"
#include "AugustCtrlBase.h"

//#define AUGUST_GLOBAL_COMMON_PTR
class CAugustGlobalCommon
{
public:

#ifdef AUGUST_GLOBAL_COMMON_PTR
	CMglGraphicManager *grp;
	CMglInput *input;
	//CMglMouseInput mouse;
	CMglMouseInput *mouse;
	CMglAudio *audio;

	CMglImageCacher *imgCache;
#else
	CMglGraphicManager grp;
	CMglInput input;
	//CMglMouseInput mouse;
	CMglMouseInput *mouse;
	CMglAudio audio;

	CMglImageCacher imgCache;


	CMglGraphicManager *pGrp;
	CMglInput *pInput;
	//CMglMouseInput *pMouse;
	CMglAudio *pAudio;

	CMglImageCacher *pImgCache;
#endif

	HWND hWnd;
	int nWindowWidth;
	int nWindowHeight;

public:
	CAugustGlobalCommon() {
		hWnd = NULL;
		nWindowWidth = -1;
		nWindowHeight = -1;
		/*grp = NULL;
		input = NULL;
		mouse = NULL;
		audio = NULL;
		imgCache = NULL;*/

		mouse = &input.mouse;
		pGrp = &grp;
		pInput = &input;
		pAudio = &audio;
		pImgCache = &imgCache;
	}
	virtual ~CAugustGlobalCommon(){}
	void Setup(){}
};
typedef CAugustGlobalCommon CAugustGlobal;
typedef CAugustGlobalCommon CAugustGlobalParam;
typedef CAugustGlobalCommon CAugustCommon;
typedef CAugustGlobalCommon AUGUST_GLOBAL_PARAM;


//	�N���X�錾  /////////////////////////////////////////////////////////
/*class DLL_EXP CAugustControlBase
{
protected:
	CAugustGlobalCommon *m_pGlobal;

public:
	//	�R���X�g���N�^
	CAugustControlBase(){
		m_pGlobal = NULL;
	}

	//	���J�C�x���g�n���h��
	void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
	}
	//agh::CControlBase* _GetThisControl(){ return 
};
*/

class DLL_EXP agh::CControlBase;
class DLL_EXP agh::CVisualControlBase;
class DLL_EXP agh::C3dVisualControlBase;



//	�N���X�錾
//template <typename T> DLL_EXP CAugustVisualControlBase : public T <- ����ł��悩�����Ȃ��E�E�E
class DLL_EXP CAugustBaseCore
{
protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B

public:
	//	�R���X�g���N�^
	CAugustBaseCore(){
		m_pGlobal = NULL;
	}
	virtual ~CAugustBaseCore(){}

	//	���J�C�x���g�n���h��
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B
	}
};

//	�N���X�錾
//template <typename T> DLL_EXP CAugustVisualControlBase : public T <- ����ł��悩�����Ȃ��E�E�E
class DLL_EXP CAugustVisualControlBase : public agh::CVisualControlBase
{
protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B

public:
	//	�R���X�g���N�^
	CAugustVisualControlBase(){
		m_pGlobal = NULL;
	}
	virtual ~CAugustVisualControlBase(){}

	//	���J�C�x���g�n���h��
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B
	}
	//agh::CControlBase* _GetThisControl(){ return 
};

//	�N���X�錾
//template <typename T> DLL_EXP CAugustVisualControlBase : public T <- ����ł��悩�����Ȃ��E�E�E
class DLL_EXP CAugustVisualControlBase2
{
protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B

public:
	//	�R���X�g���N�^
	CAugustVisualControlBase2(){
		m_pGlobal = NULL;
	}
	virtual ~CAugustVisualControlBase2(){}

	//	���J�C�x���g�n���h��
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B
	}
	virtual agh::CControlBase* _GetAghControl()=0;
};

//	�N���X�錾
//template <typename T> DLL_EXP CAugustVisualControlBase : public T <- ����ł��悩�����Ȃ��E�E�E
class DLL_EXP CAugustVisualControlBase3
{
protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B

public:
	//	�R���X�g���N�^
	CAugustVisualControlBase3(){
		m_pGlobal = NULL;
	}
	virtual ~CAugustVisualControlBase3(){}

	//	���J�C�x���g�n���h��
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B
	}
};
//	�N���X�錾
template <typename T>
class DLL_EXP CAugustVisualControlBaseT : public T
{
protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B

public:
	//	�R���X�g���N�^
	CAugustVisualControlBaseT(){
		m_pGlobal = NULL;
	}
	virtual ~CAugustVisualControlBaseT(){}

	//	���J�C�x���g�n���h��
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B
	}
};


/////////////////////////////////////////////////////////////////////////

//	�N���X�錾
//template <typename T> DLL_EXP CAugustVisualControlBase : public T <- ����ł��悩�����Ȃ��E�E�E
class DLL_EXP CAugustSemiVisualControlBase : public agh::CControlBase
{
protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B

public:
	//	�R���X�g���N�^
	CAugustSemiVisualControlBase(){
		m_pGlobal = NULL;
	}
	virtual ~CAugustSemiVisualControlBase(){}

	//	���J�C�x���g�n���h��
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B
	}
	//agh::CControlBase* _GetThisControl(){ return 
};

//	�N���X�錾
//template <typename T> DLL_EXP CAugustVisualControlBase : public T <- ����ł��悩�����Ȃ��E�E�E
class DLL_EXP CAugust3dVisualControlBase : public agh::C3dVisualControlBase, CAugustBaseCore
{
/*protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B

public:
	//	�R���X�g���N�^
	CAugust3dVisualControlBase(){
		m_pGlobal = NULL;
	}

	//	���J�C�x���g�n���h��
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	�ǂ����݂�Ȏg����ł���B�������Ă�񂾂���B
	}
	//agh::CControlBase* _GetThisControl(){ return */
};

/*
#include "MglMouseInput.h"

class DLL_EXP agh::CControlBase;

class DLL_EXP CMglguiControl : public agh::CControlBase
{
public:

protected:
	CMglMouseInput m_mouse;

	HWND m_hWnd;

public:
	//	�R���X�g���N�^
	CMglguiControl(){
	}

	//////////////////////////////////////////////////////


};
*/

#endif//__AugustCommon_H__
