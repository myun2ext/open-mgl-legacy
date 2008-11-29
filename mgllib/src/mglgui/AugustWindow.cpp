#include "stdafx.h"
#include "AugustWindow.h"

using namespace agh;





//	画面を更新
void CAugustWindow::ScreenUpdate()
{
	//if ( m_grp.GetD3dDevPtr() != NULL ) {
	grp.Clear(m_rgbBackground);
	//grp.Clear(D3DCOLOR_BLUE);

	//m_layer.Draw();
	OnDraw();

	//m_grp.UpdateScreen(); -> DoFpsWait()ん中でやってるんですわ。
}

//	フレーム処理
bool CAugustWindow::DoFrame()
{
	try{
		//	イベント処理
		OnFrameMouseInput();	//	なんか拾わないとfalseを返す仕様になってるっぽい・・・
		/*if ( OnFrameMouseInput() != true )
			return false;*/

		if ( OnFrameKeyboardInput() != true )
			return false;

		//	2008/11/02 ユーザイベント処理
		if ( OnFrameDoUser() != true )
			return false;

		//	描画処理
		ScreenUpdate();

		//	フレームレート制御＋α処理 (CMglEzGameFrame)
		if ( CMglEzGameFrame::DoFpsWait() == FALSE )
			return false;
	}
	catch( MyuCommonException e )
	{
		EzErrBox(e.szErrMsg);
		return false;
	}

	return true;
}


/////////////////////////////////////////////////////////////

DWORD WINAPI CAugustWindow_ThreadFunc(CAugustWindow *pWindow){ return (bool)pWindow->__ThreadFunc(); }

bool CAugustWindow::__ThreadFunc()
{
	//Init(GetWindowHandle(), 640, 480);
	return ThreadFunc();
}

/*int CAugustWindow::StartWindow( int nWinWidthSize, int nWinHeightSize,
	const char *szWindowTitle, BOOL bFullscreen )
{
	return StartWindowEx(nWinWidthSize, nWinHeightSize, (LPTHREAD_START_ROUTINE)CAugustWindow_ThreadFunc,
		this, szWindowTitle, bFullscreen);
}*/
void CAugustWindow::Start()
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
		winInfo.nWinHeightSize, (LPTHREAD_START_ROUTINE)CAugustWindow_ThreadFunc,
		this, winInfo.strWindowTitle.c_str(), extendInfo.bFullScreen);
}


//////////////////////////////////////////////////

//	スレッド開始
void CAugustWindow::AutoLoopThreadStart()
{
	if ( CMyuThreadBase::Execute() != true )
		MyuThrow(64929, "CAugustScreen: CMyuThreadBase::Execute() failed.");
}

//	スレッド関数
bool CAugustWindow::ThreadFunc()
{
	try{
		Init(GetWindowHandle(), CMglEzGameFrame::m_nWidth, CMglEzGameFrame::m_nHeight);

		for(;;){
			if ( DoFrame() == false )
				return true;
		}
	}
	catch( MyuCommonException e )
	{
		//EzErrBox(this->m_hWnd, );
		MyuMessageBox(this->m_hWnd, "Application Error", MB_ICONSTOP,
			"次のエラーが発生したためアプリケーションを終了します。\r\n\r\n"
			"%s", e.szErrMsg);
	}
	catch( agh::CAghException e )
	{
		//EzErrBox(this->m_hWnd, e.GetMessage());
		MyuMessageBox(this->m_hWnd, "Application Error", MB_ICONSTOP,
			"次のエラーが発生したためアプリケーションを終了します。\r\n\r\n"
			"AGH : %s", e.GetMessage());
	}

	return true;
}

//	初期化
void CAugustWindow::Init( HWND hWnd, int nDispX, int nDispY )
{
	//m_grp.Init(hWnd, nDispX, nDispY, FALSE );

	//	複数のインスタンスを作成する事になるのでInit()が必要
	m_imgCache.Init(&grp);
	//m_layer.Init(&grp);

	m_hWnd = hWnd;

	//	virtualな
	//OnInit();
	CAugustScreen::OnInit();
	//ScreenUpdate();
}