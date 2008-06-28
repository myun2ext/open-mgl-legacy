// mgl_test.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"

CMglEzGameFrame g_frame;
BOOL WINAPI MainThread(CMglEzGameFrame *pFrame);

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
{
	CMglImage img;
	img.Create();
	//CMglBitmapData *pBitmap = img.GetIternalBitmapData();
	CMglBitmapData inBitmap(&img);
	inBitmap.Set(20,29,D3DCOLOR_WHITE);
	//inBitmap.Get(20,29);
	//inBitmap.Fill(D3DCOLOR_WHITE);
	inBitmap.Release();

	for(;;){
		img.Draw();

		if ( !pFrame->DoFpsWait() )
			return TRUE;
	}
	return TRUE;
}
