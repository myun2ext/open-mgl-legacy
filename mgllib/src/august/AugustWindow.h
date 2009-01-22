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
//#include "MglEzGameFrame.h"
#include "AugustEzGameFrame.h"

/*class CAugustWindowOnCreateExtend : public CCreateWindowInfoExtendBase
{

};*/
typedef struct : agh::CREATE_WINDOW_EXTEND_BASE
{
	BOOL bFullScreen;
	BOOL bEscKeyExit;
	int nNotMoveHideCursolTimeMs;	//	非移動でカーソルを消すまでの時間
	std::string strWindowClassName;
} AUGUST_WINDOW_ON_CREATE_EXTEND;

////////////////////////////////////////////////////////////////////////////////////

//	2008/11/13  CWindowBaseのDLLエクスポート
class DLL_EXP agh::CWindowBase;
class DLL_EXP CMyuThreadBase;

//class DLL_EXP CAugustWindow : public CAugustScreen
//class DLL_EXP CAugustWindow : public CMyuThreadBase, public agh::CWindowBase
//class DLL_EXP CAugustWindow : public agh::CWindowBase, public CMyuThreadBase, public CMglEzGameFrame
class DLL_EXP CAugustWindow : /*public CAugustScreen,*/ public agh::CWindowBase, public CMyuThreadBase, public CAugustEzGameFrame
{
private:
	CAugustScreen *m_pActiveScreen;

	//CAugustGlobalCommon g_;
//protected:
	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;
	LPSTR m_lpCmdLine;
	int m_nCmdShow;

	//	DirectX（MGL）系
	/*CMglGraphicManager m_grp;
	CMyuFPS m_fps;
	CMglInput m_input;
	CMglAudio m_audio;*/
	CMglImageCacher m_imgCache;

	//HWND m_hWnd;

public:
	bool __ThreadFunc();

_AGH_EVENT_ACCESS_MODIFIER:
	bool DoFrame();

public:
	//	コンストラクタ・デストラクタ
	CAugustWindow();
	virtual ~CAugustWindow(){}

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

	void SetActiveScreenControl(CAugustScreen *pScreen){
		m_pActiveScreen = pScreen;
	}
	void SetScreenControl(CAugustScreen *pScreen){
		m_pActiveScreen = pScreen;
	}

private:
	void Init( HWND hWnd, int nDispX, int nDispY );
	void ScreenUpdate();

protected:
	bool ThreadFunc();
};




#endif//__AugustWindow_H__
