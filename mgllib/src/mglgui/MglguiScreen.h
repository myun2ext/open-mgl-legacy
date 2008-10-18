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

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglguiScreen : public agh::CScreenBase, public CMyuThreadBase, protected CMglEzGameFrame
{
public:
	CMglGraphicManager m_grp;
	CMglImageCacher m_imgCache;

protected:
	HWND m_hWnd;
	//CMglLayers4 m_layer;
	CMglMouseInput &m_mouse;
	D3DCOLOR m_rgbBackground;

	///// オーバーライド可能なイベント /////////////////////////////////////////////////

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

	virtual void OnDraw();

private:
	//	なんでPublic？（Privateではないのか・・・？）
	//void OnLButtonDown(int x, int y);

	void ScreenUpdate();
	bool DoFrame();

	void Init( HWND hWnd, int nDispX, int nDispY );

	void _RegistControl(agh::CControlBase* pCtrl);

public:
	//	コンストラクタ
	CMglguiScreen() : m_mouse(input.mouse), m_grp(grp) {
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

protected:
	bool ThreadFunc();
public:
	bool OnFrameMouseInput();
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

class DLL_EXP CMglguiWindow : public CMglguiScreen
{
private:
public:
	bool __ThreadFunc();

public:
	void Start();
	/*int StartWindow( int nWinWidthSize, int nWinHeightSize,
		const char *szWindowTitle="MGL Application", BOOL bFullscreen=FALSE );*/
};

#endif//__MglguiScreen_H__
