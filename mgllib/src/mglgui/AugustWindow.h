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
#include "MglEzGameFrame.h"

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
class DLL_EXP CMyuThreadBase;

//class DLL_EXP CAugustWindow : public CAugustScreen
//class DLL_EXP CAugustWindow : public CMyuThreadBase, public agh::CWindowBase
class DLL_EXP CAugustWindow : public CMyuThreadBase, public agh::CWindowBase, public CMglEzGameFrame
{
	friend class CAugustScreen;
private:
protected:
	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;
	LPSTR m_lpCmdLine;
	int m_nCmdShow;

	//	DirectX（MGL）系
	CMglGraphicManager m_grp;
	CMyuFPS m_fps;
	CMglInput m_input;
	CMglAudio m_audio;

	//	FPSで待つ
	BOOL DoFpsWait();
	BOOL DoEvent(){ return DoFpsWait(); }	//	VB風
	BOOL DoFrameEnd(){ return DoFpsWait(); }
	void SetBreak(){ m_bBreak = TRUE; }

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

	//	各種設定
	/*void SetWindowTitle( const char *szCaption );	//	ウインドウのタイトル*/
	void SetFPS( int nFps ){ fps.SetFPS(nFps); }	//	FPSの設定
	void SetFps( int nFps ){ fps.SetFPS(nFps); }	//	FPSの設定
	void SetFpsShow( BOOL bFpsShow ){ m_bFpsShow = bFpsShow; }
	void EnableEscEnd(){ m_bEscEnd = TRUE; }
	void DisableEscEnd(){ m_bEscEnd = FALSE; }

private:
	void Init( HWND hWnd, int nDispX, int nDispY );
	bool DoFrame();
	void ScreenUpdate();

protected:
	bool ThreadFunc();
};




#endif//__AugustWindow_H__
