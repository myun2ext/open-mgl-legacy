#include "stdafx.h"
#include "MglguiWindow.h"

using namespace agh;

/////////////////////////////////////////////////////////////

DWORD WINAPI CMglguiWindow_ThreadFunc(CMglguiWindow *pWindow){ return (bool)pWindow->__ThreadFunc(); }

bool CMglguiWindow::__ThreadFunc()
{
	//Init(GetWindowHandle(), 640, 480);
	return ThreadFunc();
}

/*int CMglguiWindow::StartWindow( int nWinWidthSize, int nWinHeightSize,
	const char *szWindowTitle, BOOL bFullscreen )
{
	return StartWindowEx(nWinWidthSize, nWinHeightSize, (LPTHREAD_START_ROUTINE)CMglguiWindow_ThreadFunc,
		this, szWindowTitle, bFullscreen);
}*/
void CMglguiWindow::Start()
{
	CREATE_WINDOW_INFO winInfo;
	MGLGUI_WINDOW_ON_CREATE_EXTEND extendInfo;

	winInfo.nWinWidthSize = 640;
	winInfo.nWinHeightSize = 480;
	winInfo.nWinXPos = 0;	//	現在つかってないお・・・
	winInfo.nWinYPos = 0;	//	現在つかってないお・・・
	winInfo.pExtendStructure = &extendInfo;
	winInfo.strWindowClass = "";	//	現在つかってないお・・・
	winInfo.strWindowTitle = "Application";

	extendInfo.bFullScreen = FALSE;

	//	オーバーロード呼び出し
	OnCreateWindow(&winInfo);

	/*return*/ StartWindowEx(
		winInfo.nWinWidthSize,
		winInfo.nWinHeightSize, (LPTHREAD_START_ROUTINE)CMglguiWindow_ThreadFunc,
		this, winInfo.strWindowTitle.c_str(), extendInfo.bFullScreen);
}
