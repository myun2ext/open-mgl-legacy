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
class DLL_EXP CMglguiScreen : public agh::CScreenBase, public CMyuThreadBase, public CMglEzGameFrame
{
public:
	//CMglGraphicManager m_grp;
	CMglImageCacher m_imgPool;

protected:
	HWND m_hWnd;
	CMglLayers4 m_layer;
	CMglMouseInput &m_mouse;
	D3DCOLOR m_rgbBackground;

public:
	//	コンストラクタ
	CMglguiScreen() : m_mouse(input.mouse) {
		m_hWnd = NULL;
		m_rgbBackground = D3DCOLOR_WHITE;
	}
	void Init( HWND hWnd, int nDispX, int nDispY );

	//////////////////////////////////////////////////////

	void RegistControl(CMglAghImage* pImage);

	//////////////////////////////////////////////////////

	void ScreenUpdate();
	bool DoFrame();
	void AutoLoopThreadStart();

	void OnLButtonDown(int x, int y);
	virtual void OnBackgroundLButtonDown(int x, int y){}
	virtual void OnBackgroundRButtonDown(int x, int y){}
	virtual void OnBackgroundCButtonDown(int x, int y){}
	virtual void OnControlLButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnControlRButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnControlCButtonDown(agh::CControlBase *pControl, int x, int y){}

	BOOL IsExistPool(const char* szAlias);

	//////////////////////////////////////////////////////

	/*BOOL InsertImage(IMGLIST_ITR it);
	BOOL InsertImage(){ return InsertImage(GetScene()->m_images.begin()); }*/

	void SetBackgroundColor(D3DCOLOR color){ m_rgbBackground = color; }

protected:
	bool ThreadFunc();
public:
	bool OnFrameMouseInput();
};


//	asfsdasfasfda
class DLL_EXP CMglguiWindow : public CMglguiScreen
{
private:
public:
	bool __ThreadFunc();

public:
	int StartWindow( int nWinWidthSize, int nWinHeightSize,
		const char *szWindowTitle="MGL Application", BOOL bFullscreen=FALSE );
};

#endif//__MglguiScreen_H__
