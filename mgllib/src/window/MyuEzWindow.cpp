//////////////////////////////////////////////////////////
//
//	MyuEzWindow
//		- Window処理を簡単に行う
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyuEzWindow.h"
#include "MyuFunctions.h"
#include "MglManager.h"		//	デバッグログ

LRESULT WINAPI MyuEzWindowMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

//	コンストラクタ
CMyuEzWindow::CMyuEzWindow()
{
	m_nThreadExitTimeout = DEFAULT_THREAD_EXIT_TIMEOUT;
	m_bAlive = FALSE;
	m_hWnd = NULL;
}

//	デストラクタ
CMyuEzWindow::~CMyuEzWindow()
{

}

//	ウインドウ生成
int CMyuEzWindow::StartWindow( const char* szAppCaption, const char* szWinClassName,
							  int nWinXPos, int nWinYPos, int nWinWidthSize, int nWinHeightSize,
							  DWORD dwExtendWinStyle, LPTHREAD_START_ROUTINE threadFunc,
//							  DWORD dwThreadUserOption )
							  LPVOID threadFuncParam )
{
	_MGL_DEBUGLOG("+ CMyuEzWindow::StartWindow()" );
	CMglStackInstance("CMyuEzWindow::StartWindow");

	HANDLE hMainThread;
	HWND hWnd;

	// ウィンドウ クラスを登録する。
	/*WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MyuEzWindowMsgProc, 0L, 0L, 
					  GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
					  szWinClassName, NULL };*/
	/*
		UINT        cbSize;
		UINT        style;
		WNDPROC     lpfnWndProc;
		int         cbClsExtra;
		int         cbWndExtra;
		HINSTANCE   hInstance;
		HICON       hIcon;
		HCURSOR     hCursor;
		HBRUSH      hbrBackground;
		LPCSTR      lpszMenuName;
		LPCSTR      lpszClassName;
		HICON       hIconSm;
	*/
	WNDCLASSEX wc;
	ZeroMemory( &wc, sizeof(wc) );
	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= CS_CLASSDC;
	wc.lpfnWndProc		= MyuEzWindowMsgProc;
	wc.hInstance		= GetModuleHandle(NULL);
	//wc.hIcon			= LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName	= szWinClassName;

	RegisterClassEx( &wc );

	//	ウインドウスタイル
	DWORD dwWinStyle = dwExtendWinStyle | WS_CAPTION | WS_SYSMENU;

	//	ウインドウの枠を含めた縦横のサイズを取得する
    RECT rc = { 0, 0, nWinWidthSize, nWinHeightSize } ;
    if ( AdjustWindowRect( &rc, dwWinStyle, FALSE ) == 0 )
		MessageBox( NULL, "AdjustWindowRect() の実行に失敗しました。", NULL, MB_ICONERROR );

	// アプリケーションのウィンドウを作成する。

	hWnd = CreateWindow( szWinClassName, szAppCaption, dwWinStyle,
						 nWinXPos, nWinYPos, rc.right - rc.left, rc.bottom - rc.top,
						 GetDesktopWindow(), NULL, wc.hInstance, NULL );

	//	デフォルトHWND
	MglDefaultInitialize( hWnd );

	/*
	// アプリケーションのウィンドウを作成する。
	hWnd = CreateWindow( szWinClass, APPANME, 
						 WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
						 100, 100, GetDGWindowX(WIDTH), GetDGWindowY(HEIGHT),
						 GetDesktopWindow(), NULL, wc.hInstance, NULL );
	*/

	// Show the window
	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow( hWnd );

	//	カーソル非表示
	ShowCursor(FALSE);

	//////////////////////////////////////////
	//
	//		スレッド作成の時間の時間です
	//

	DWORD id;
	m_hWnd = hWnd;
	m_bAlive = TRUE;
	//hMainThread = CreateThread( NULL, 0, threadFunc, &threadFuncParam, 0, &id );
	_MGL_DEBUGLOG("CreateThread()..." );
	hMainThread = CreateThread( NULL, 0, threadFunc, threadFuncParam, 0, &id );
	
	//////////////////////////////////////////
	//
	//			メッセージループ
	//

	//	あんさんは勝手に回っててくらさいヽ(´ー｀)ﾉ
	MSG msg;
	do {
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			//	スレッド終了判定
			static DWORD exitCode; 
			if ( GetExitCodeThread( hMainThread, &exitCode ) == 0 )
			{
				MessageBox( hWnd, "CMyuEzWindow::StartWindow()  GetExitCodeThread()に失敗。", szAppCaption, MB_ICONERROR );
				break;
			}
			if ( exitCode != STILL_ACTIVE ){
				_MGL_DEBUGLOG("exitCode is not STILL_ACTIVE." );
				break;
			}

			//	なんにもすることないよーん。(ﾟ∋ﾟ)～♪
			Sleep(1);	//	Zzzz..
		}
	} while( msg.message!=WM_QUIT );

	//	親プロセスのステータスを終了状態に
	m_bAlive = FALSE;

	//	スレッドが終わるのを待つです
	//	指定ms経っても応答が無かった場合メッセージボックスを出力して
	//	強制的にスレッドを終了させます。
	for( int i=0; i<m_nThreadExitTimeout; i++ )
	{
		static DWORD exitCode; 
		if ( GetExitCodeThread( hMainThread, &exitCode ) == 0 )
		{
			MessageBox( NULL, "CMyuEzWindow::StartWindow()  GetExitCodeThread()に失敗。", szAppCaption, MB_ICONERROR );
			break;
		}
		if ( exitCode != STILL_ACTIVE )
			break;

		Sleep(1);	//	Zzzz..
	}
	if ( i >= m_nThreadExitTimeout )
	{
		MessageBox( NULL, "CMyuEzWindow::StartWindow()  スレッドからの応答がありません。強制的にスレッドを終了させます。\r\n"
			"\r\n"
			"プログラマさんへ：\r\n"
			"　CMyuEzWindow::IsAcrive() にて、ウインドウの活性状態をチェックし、FALSEだった場合、\r\n"
			"　スレッドを終了させるような処理を追加してください。（詳細はヘルプ参照）",
			szAppCaption, MB_ICONERROR );

		//	もう一度チェックの処理

		TerminateThread( hMainThread, -1 );
	}

	//	帰りますよおまいら
	CloseHandle( hMainThread );

	UnregisterClass( szWinClassName, wc.hInstance );

	return 0;
}

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MyuEzWindowMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static int nMoveMouseCounter = 0;
    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;

		case WM_CREATE:
			SetTimer( hWnd, 100, 100, NULL);
			return 0;

		case WM_MOUSEMOVE:
			for ( ; ShowCursor(TRUE) < 0; );
			nMoveMouseCounter = 1500;
			return 0;

		case WM_TIMER:
			if ( nMoveMouseCounter > 0 )
			{
				nMoveMouseCounter -= 100;
				if ( nMoveMouseCounter <= 0 )
					for ( ; ShowCursor(FALSE) >= 0; );
			}
			return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

