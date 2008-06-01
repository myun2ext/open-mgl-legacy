// mgl_test.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"

CMglEzGameFrame g_frame;
BOOL MainThread(CMglEzGameFrame *pFrame);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	g_frame.EnableEscEnd();
	g_frame.StartWindow( 640, 480, (LPTHREAD_START_ROUTINE)MainThread,
			"hgoe", FALSE );

	return 0;
}

//	メインスレッド
BOOL MainThread( CMglEzGameFrame *pFrame )
{
	for(;;){


		if ( !pFrame->DoFpsWait() )
			return TRUE;
	}
	return TRUE;
}