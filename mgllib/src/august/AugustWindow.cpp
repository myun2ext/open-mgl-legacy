#include "stdafx.h"
#include "AugustWindow.h"

using namespace agh;

//	コンストラクタ
CAugustWindow::CAugustWindow()	//	デフォルトスクリーンとか搭載してみるか・・・。
{
	m_pActiveScreen = NULL;
	//m_pActiveScreen = &m_defaultScreen;	//	デフォルトスクリーンとか搭載してみるか・・・。

	m_hInstance = NULL;
	m_hPrevInstance = NULL;
	m_lpCmdLine = NULL;
	m_nCmdShow = -1;
}

//	画面を更新
void CAugustWindow::ScreenUpdate()
{
	//if ( m_grp.GetD3dDevPtr() != NULL ) {
	//grp.Clear(m_rgbBackground);
	//grp.Clear(D3DCOLOR_WHITE);	//	<- とりあえずー

	//m_layer.Draw();
	m_pActiveScreen->OnDraw();

	//m_grp.UpdateScreen(); -> DoFpsWait()ん中でやってるんですわ。
}

//	フレーム処理
bool CAugustWindow::DoFrame()
{
	try{
		if ( m_pActiveScreen == NULL)
			MyuThrow(25598, "SetActiveScreenControl() にてスクリーンを設定してください。");

		//	2008/11/29 Screen側のDoFrame()を呼び出す仕様に
		if ( m_pActiveScreen != (void*)this )
			if ( m_pActiveScreen->DoFrame() == false )
				return false;

		//	描画処理
		ScreenUpdate();

		//	フレームレート制御＋α処理 (CMglEzGameFrame)
		if ( DoFpsWait() == FALSE )
			return false;
	}
	catch( MyuCommonException e )
	{
		EzErrBox(e.szErrMsg);
		return false;
	}

	return true;
}


//	スレッド関数
bool CAugustWindow::ThreadFunc()
{
	try{
		//	2008/11/29 デフォルトスクリーンとか搭載してみるか・・・。
		if ( m_pActiveScreen == NULL ){
			m_pActiveScreen = this;
			this->g_ = this;
		}

		Init(GetWindowHandle(), g_->nWindowWidth, g_->nWindowHeight);

		for(;;){
			if ( DoFrame() == false )
				return true;
		}
	}
	catch( MyuCommonException e )
	{
		//EzErrBox(g_->hWnd, );
		MyuMessageBox(g_->hWnd, "Application Error", MB_ICONSTOP,
			"次のエラーが発生したためアプリケーションを終了します。\r\n\r\n"
			"%s", e.szErrMsg);
	}
	catch( agh::CAghException e )
	{
		//EzErrBox(g_->hWnd, e.GetMessage());
		MyuMessageBox(g_->hWnd, "Application Error", MB_ICONSTOP,
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

	//m_hWnd = hWnd;

	if ( m_pActiveScreen == NULL)
		MyuThrow(25598, "SetActiveScreenControl() にてスクリーンを設定してください。");

	m_pActiveScreen->OnInit();
	//ScreenUpdate();
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
	AUGUST_WINDOW_ON_CREATE_EXTEND extendInfo;

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
