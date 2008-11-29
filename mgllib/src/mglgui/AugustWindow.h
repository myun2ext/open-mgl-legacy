//////////////////////////////////////////////////////////
//
//	AugustWindow
//
//////////////////////////////////////////////////////////

#ifndef __AugustWindow_H__
#define __AugustWindow_H__

#include "AugustScreen.h"
#include "MglGraphicManager.h"
#include "MglText.h"
#include "MyuFPS.h"
#include "MglInput.h"
#include "MglAudio.h"

/*class CAugustWindowOnCreateExtend : public CCreateWindowInfoExtendBase
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

//class DLL_EXP CAugustWindow : public CAugustScreen
class DLL_EXP CAugustWindow : public CAugustScreen, public CMyuThreadBase, public agh::CWindowBase
{
	friend CAugustScreen;
private:
protected:
	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;
	LPSTR m_lpCmdLine;
	int m_nCmdShow;

	//	DirectX（MGL）系
	CMglGraphicManager m__grp;
	CMyuFPS m__fps;
	CMglInput m__input;
	CMglAudio m__audio;
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
	void AutoLoopThreadStart();
private:
	void Init( HWND hWnd, int nDispX, int nDispY );
	bool DoFrame();
	void ScreenUpdate();

protected:
	bool ThreadFunc();
};




#endif//__AugustWindow_H__
