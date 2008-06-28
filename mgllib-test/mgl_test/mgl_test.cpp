// mgl_test.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"

CMglEzGameFrame g_frame;
BOOL WINAPI MainThread(CMglEzGameFrame *pFrame);
//BOOL MainThread(void *pFrame);
//DWORD WINAPI MainThread( LPVOID lpThreadParameter );

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
BOOL WINAPI MainThread( CMglEzGameFrame *pFrame )
//DWORD WINAPI MainThread( LPVOID vpFrame )
{
	//CMglEzGameFrame *pFrame = (CMglEzGameFrame*)vpFrame;

	//CMglImage img;
	//img.Create();
	for(;;){
		//img.Draw();

		/*if ( !pFrame->DoFpsWait() )
			return TRUE;*/
	}
	return TRUE;
}
