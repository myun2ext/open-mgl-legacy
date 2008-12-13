//////////////////////////////////////////////////////////
//
//	MglguiControl
//
//////////////////////////////////////////////////////////

#ifndef __MglguiControl_H__
#define __MglguiControl_H__

#include "agh.h"
#include "MglImageCacher.h"
#include "MglImageLayer.h"
#include "MglInput.h"
#include "MglAudio.h"

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

class DLL_EXP agh::CVisualControlBase;

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

	//	公開イベントハンドラ
	void OnRegist(CAugustGlobalCommon *pGlobal){
		m_pGlobal = pGlobal;
		m_pGrp = &(pGlobal->grp);	//	どうせみんな使うんでしょ。分かってるんだから。
	}
	//agh::CControlBase* _GetThisControl(){ return 
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

#endif//__MglguiControl_H__
