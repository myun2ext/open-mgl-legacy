//////////////////////////////////////////////////////////
//
//	MglguiScreen
//
//////////////////////////////////////////////////////////

#ifndef __MglguiScreen_H__
#define __MglguiScreen_H__

#include "agh.h"
#include "MglLayers4.h"
#include "MglImageCacher.h"
#include "MglImageLayer.h"
#include "MglEzGameFrame.h"
#include "MglAghImage.h"
//#include "MglMouseInput.h"

class DLL_EXP agh::CScreenBase;
class DLL_EXP CMyuThreadBase;

#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN	(1)
#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP		(2)
#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_PRESS		(3)
#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_DOWNUP	(8)
#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_PUSH		(MGL_KB_EVT_HANDLER_EVTTYPE_ON_DOWNUP)

class CMglguiScreen;

typedef bool (CMglguiScreen::*MGL_KB_EVT_HANDLER_CALLBACK)();
typedef struct {
	MGL_KB_EVT_HANDLER_CALLBACK pCallbackFunc;
	BYTE keyCode;
	short evtType;
} MGL_KB_EVT_HANDLER;
typedef list<MGL_KB_EVT_HANDLER> t_MGL_KB_EVT_HANDLERS;

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglguiScreen : public agh::CScreenBase, public CMyuThreadBase, protected CMglEzGameFrame
{
protected:
	//CMglGraphicManager m_grp; <- 間違いでは・・・？
	CMglGraphicManager &m_grp;	//	Alias
	CMglInput &m_input;			//	Alias
	CMglMouseInput &m_mouse;	//	Alias

	//	2008/11/26 Add. デフォルトのイメージ配列
	map<std::string,CMglAghImage> m_imgAry;

	//	2008/11/26 Add. デフォルトのイメージ配列
	//list<bool (*)()> m_kbEventHandlers;	//	本当はvector_list使うネ・・・
	//list<MGL_KB_EVT_HANDLER_CALLBACK> m_kbEventHandlers;	//	本当はvector_list使うネ・・・
	list<MGL_KB_EVT_HANDLER> m_kbEventHandlers;	//	本当はvector_list使うネ・・・

	/////////////////////////////////////////////////////////

	HWND m_hWnd;
	//CMglLayers4 m_layer;
	CMglImageCacher m_imgCache;
	D3DCOLOR m_rgbBackground;
	POINT m_nCachedCurPos;
	int m_nCachedCurPosX;
	int m_nCachedCurPosY;

	agh::_AGH_POINT GetCurPos(){
		return *((agh::_AGH_POINT*)&m_nCachedCurPos);
	}

_AGH_EVENT_ACCESS_MODIFIER:
	///// オーバーライド可能なイベント /////////////////////////////////////////////////

	/**
	  ここにあった OnControl, OnBackground は下に移動しといたよ。
	**/

	virtual void OnDraw();

	//	このクラスから
	virtual bool OnFrameDoUser(){return true;}
	virtual bool OnFrameKeyboardInput();
	virtual bool OnFrameMouseInput();

protected:

private:
	//	なんでPublic？（Privateではないのか・・・？）
	//void OnLButtonDown(int x, int y);

	void ScreenUpdate();
	bool DoFrame();

	void Init( HWND hWnd, int nDispX, int nDispY );

	void _RegistControl(agh::CControlBase* pCtrl);

public:
	//	コンストラクタ
	CMglguiScreen() : m_mouse(input.mouse), m_grp(grp), m_input(input) {
		m_hWnd = NULL;
		m_rgbBackground = D3DCOLOR_WHITE;
	}
	void AutoLoopThreadStart();

	///// コントロールの登録 /////////////////////////////////////////////////

	void RegistControl(CMglAghImage* pImage);

	//////////////////////////////////////////////////////

	//BOOL IsExistPool(const char* szAlias); <- ?

	/*BOOL InsertImage(IMGLIST_ITR it);
	BOOL InsertImage(){ return InsertImage(GetScene()->m_images.begin()); }*/

	void SetBackgroundColor(D3DCOLOR color){ m_rgbBackground = color; }

	//	キーボードハンドラの登録
	void RegistKbHandler(MGL_KB_EVT_HANDLER &evt){
		m_kbEventHandlers.push_back(evt);
	}
	void RegistKbHandler(
		short evtType,
		BYTE keyCode,		
		MGL_KB_EVT_HANDLER_CALLBACK pCallbackFunc)
	{
		MGL_KB_EVT_HANDLER evt;
		evt.pCallbackFunc = pCallbackFunc;
		evt.keyCode = keyCode;
		evt.evtType = evtType;
		m_kbEventHandlers.push_back(evt);
	}

protected:
	bool ThreadFunc();
public:
	//bool OnFrameMouseInput(); <- なんかpublicなのに理由あんのかな・・・？
};

//////////// ウインドウ作成もやってくれるクラス ////////////////////

/*class CMglguiWindowOnCreateExtend : public CCreateWindowInfoExtendBase
{

};*/
typedef struct : agh::CREATE_WINDOW_EXTEND_BASE
{
	BOOL bFullScreen;
	BOOL bEscKeyExit;
	int nNotMoveHideCursolTimeMs;
} MGLGUI_WINDOW_ON_CREATE_EXTEND;

//	2008/11/13  CWindowBaseのDLLエクスポート
class DLL_EXP agh::CWindowBase;

//class DLL_EXP CMglguiWindow : public CMglguiScreen
class DLL_EXP CMglguiWindow : public CMglguiScreen, public agh::CWindowBase
{
private:
protected:
	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;
	LPSTR m_lpCmdLine;
	int m_nCmdShow;
public:
	bool __ThreadFunc();

public:
	void Start();
	void Start(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
		m_hInstance = hInstance;
		m_hPrevInstance = m_hPrevInstance;
		m_lpCmdLine = lpCmdLine;
		m_nCmdShow = nCmdShow;
		Start();
	}
	/*int StartWindow( int nWinWidthSize, int nWinHeightSize,
		const char *szWindowTitle="MGL Application", BOOL bFullscreen=FALSE );*/
};



	/*virtual void OnBackgroundLButtonDown(int x, int y){}
	virtual void OnBackgroundRButtonDown(int x, int y){}
	virtual void OnBackgroundCButtonDown(int x, int y){}
	virtual void OnControlLButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnControlRButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnControlCButtonDown(agh::CControlBase *pControl, int x, int y){}

	//	左クリック系 : Left Click Events
	virtual void OnLButtonClick(agh::CControlBase *pControl, int x, int y){}
	virtual void OnLButtonDblClk(agh::CControlBase *pControl, int x, int y){}
	virtual void OnLButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnLButtonUp(agh::CControlBase *pControl, int x, int y){}

	//	右クリック系 : Right Click Events
	virtual void OnRButtonClick(agh::CControlBase *pControl, int x, int y){}
	virtual void OnRButtonDblClk(agh::CControlBase *pControl, int x, int y){}
	virtual void OnRButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnRButtonUp(agh::CControlBase *pControl, int x, int y){}

	//	マウス移動 : Move Mouse Events
	virtual void OnMouseMove(agh::CControlBase *pControl, int nPosX, int nPosY, int nMoveX, int nMoveY){}

	//	ホイール : Wheel Events
	virtual void OnWheelUp(agh::CControlBase *pControl, int count){}
	virtual void OnWheelDown(agh::CControlBase *pControl, int count){}
	virtual void OnCButtonClick(agh::CControlBase *pControl, int x, int y){}
	virtual void OnCButtonDblClk(agh::CControlBase *pControl, int x, int y){}
	virtual void OnCButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnCButtonUp(agh::CControlBase *pControl, int x, int y){}
	virtual void OnMButtonClick(agh::CControlBase *pControl, int x, int y){}
	virtual void OnMButtonDblClk(agh::CControlBase *pControl, int x, int y){}
	virtual void OnMButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnMButtonUp(agh::CControlBase *pControl, int x, int y){}*/

	/*
	//	左クリック系 : Left Click Events
	virtual void OnBackgroundLButtonClick(int x, int y){}
	virtual void OnBackgroundLButtonDblClk(int x, int y){}
	virtual void OnBackgroundLButtonDown(int x, int y){}
	virtual void OnBackgroundLButtonUp(int x, int y){}

	//	右クリック系 : Right Click Events
	virtual void OnBackgroundRButtonClick(int x, int y){}
	virtual void OnBackgroundRButtonDblClk(int x, int y){}
	virtual void OnBackgroundRButtonDown(int x, int y){}
	virtual void OnBackgroundRButtonUp(int x, int y){}

	//	マウス移動 : Move Mouse Events
	virtual void OnBackgroundMouseMove(int nPosX, int nPosY, int nMoveX, int nMoveY){}

	//	ホイール : Wheel Events
	virtual void OnBackgroundWheelUp(int count){}
	virtual void OnBackgroundWheelDown(int count){}
	virtual void OnBackgroundCButtonClick(int x, int y){}
	virtual void OnBackgroundCButtonDblClk(int x, int y){}
	virtual void OnBackgroundCButtonDown(int x, int y){}
	virtual void OnBackgroundCButtonUp(int x, int y){}
	virtual void OnBackgroundMButtonClick(int x, int y){}
	virtual void OnBackgroundMButtonDblClk(int x, int y){}
	virtual void OnBackgroundMButtonDown(int x, int y){}
	virtual void OnBackgroundMButtonUp(int x, int y){}
	*/

#endif//__MglguiScreen_H__
