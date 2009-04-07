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


//	クラス宣言  /////////////////////////////////////////////////////////
/*class DLL_EXP CAugustControlBase
{
protected:
	CAugustGlobalCommon *m_pGlobal;

public:
	//	コンストラクタ
	CAugustControlBase(){
		m_pGlobal = NULL;
	}

	//	公開イベントハンドラ
	void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
	}
	//agh::CControlBase* _GetThisControl(){ return 
};
*/

class DLL_EXP agh::CControlBase;
class DLL_EXP agh::CVisualControlBase;
class DLL_EXP agh::C3dVisualControlBase;



//	クラス宣言
//template <typename T> DLL_EXP CAugustVisualControlBase : public T <- これでもよかったなぁ・・・
class DLL_EXP CAugustBaseCore
{
protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	どうせみんな使うんでしょ。分かってるんだから。

public:
	//	コンストラクタ
	CAugustBaseCore(){
		m_pGlobal = NULL;
	}
	virtual ~CAugustBaseCore(){}

	//	公開イベントハンドラ
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	どうせみんな使うんでしょ。分かってるんだから。
	}
};

//	クラス宣言
//template <typename T> DLL_EXP CAugustVisualControlBase : public T <- これでもよかったなぁ・・・
class DLL_EXP CAugustVisualControlBase : public agh::CVisualControlBase
{
protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	どうせみんな使うんでしょ。分かってるんだから。

public:
	//	コンストラクタ
	CAugustVisualControlBase(){
		m_pGlobal = NULL;
	}
	virtual ~CAugustVisualControlBase(){}

	//	公開イベントハンドラ
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	どうせみんな使うんでしょ。分かってるんだから。
	}
	//agh::CControlBase* _GetThisControl(){ return 
};

//	クラス宣言
//template <typename T> DLL_EXP CAugustVisualControlBase : public T <- これでもよかったなぁ・・・
class DLL_EXP CAugustVisualControlBase2
{
protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	どうせみんな使うんでしょ。分かってるんだから。

public:
	//	コンストラクタ
	CAugustVisualControlBase2(){
		m_pGlobal = NULL;
	}
	virtual ~CAugustVisualControlBase2(){}

	//	公開イベントハンドラ
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	どうせみんな使うんでしょ。分かってるんだから。
	}
	virtual agh::CControlBase* _GetAghControl()=0;
};

//	クラス宣言
//template <typename T> DLL_EXP CAugustVisualControlBase : public T <- これでもよかったなぁ・・・
class DLL_EXP CAugustVisualControlBase3
{
protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	どうせみんな使うんでしょ。分かってるんだから。

public:
	//	コンストラクタ
	CAugustVisualControlBase3(){
		m_pGlobal = NULL;
	}
	virtual ~CAugustVisualControlBase3(){}

	//	公開イベントハンドラ
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	どうせみんな使うんでしょ。分かってるんだから。
	}
};
//	クラス宣言
template <typename T>
class DLL_EXP CAugustVisualControlBaseT : public T
{
protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	どうせみんな使うんでしょ。分かってるんだから。

public:
	//	コンストラクタ
	CAugustVisualControlBaseT(){
		m_pGlobal = NULL;
	}
	virtual ~CAugustVisualControlBaseT(){}

	//	公開イベントハンドラ
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	どうせみんな使うんでしょ。分かってるんだから。
	}
};


/////////////////////////////////////////////////////////////////////////

//	クラス宣言
//template <typename T> DLL_EXP CAugustVisualControlBase : public T <- これでもよかったなぁ・・・
class DLL_EXP CAugustSemiVisualControlBase : public agh::CControlBase
{
protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	どうせみんな使うんでしょ。分かってるんだから。

public:
	//	コンストラクタ
	CAugustSemiVisualControlBase(){
		m_pGlobal = NULL;
	}
	virtual ~CAugustSemiVisualControlBase(){}

	//	公開イベントハンドラ
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	どうせみんな使うんでしょ。分かってるんだから。
	}
	//agh::CControlBase* _GetThisControl(){ return 
};

//	クラス宣言
//template <typename T> DLL_EXP CAugustVisualControlBase : public T <- これでもよかったなぁ・・・
class DLL_EXP CAugust3dVisualControlBase : public agh::C3dVisualControlBase, CAugustBaseCore
{
/*protected:
	CAugustGlobalCommon *m_pGlobal;
	CMglGraphicManager *m_pGrp;		//	どうせみんな使うんでしょ。分かってるんだから。

public:
	//	コンストラクタ
	CAugust3dVisualControlBase(){
		m_pGlobal = NULL;
	}

	//	公開イベントハンドラ
	virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	どうせみんな使うんでしょ。分かってるんだから。
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
	//	コンストラクタ
	CMglguiControl(){
	}

	//////////////////////////////////////////////////////


};
*/

#endif//__AugustCommon_H__
