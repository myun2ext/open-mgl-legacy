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
	//img.Create("C:\\Documents and Settings\\智章\\My Documents\\shana_36-1.jpg");
	img.Create("font_big.tga");
	//img.Create();
	//CMglBitmapData *pBitmap = img.GetIternalBitmapData();
	CMglBitmapData inBitmap(&img);
	//inBitmap.Get(20,29);
	//inBitmap.Fill(D3DCOLOR_WHITE);
	//inBitmap.Release();

	int i=0;
	for(;;){
		i++;
		//inBitmap.Set(i,i,D3DCOLOR_WHITE);
		//inBitmap.Fill(D3DCOLOR_WHITE, Rect(i*4,i*4,i*4+4,i*4*4));
		img.Draw();

		if ( pFrame->input.mouse.IsPressLeftButton() )
		{
			POINT point = pFrame->input.mouse.GetCursorPos();
			//inBitmap.Set(point.x, point.y, D3DCOLOR_WHITE);
			//inBitmap.Set(point.x, point.y, D3DCOLOR_RED);
			try {
				if ( D3DCOLOR_GETA(inBitmap.Get(point.x, point.y)) != 0 )
					inBitmap.Fill(D3DCOLOR_RED,Rect(point.x, point.y, point.x+3, point.y+3));
			}
			catch(MyuCommonException e){
				if ( e.nErrCode != MSGMSLNO_BITMAP_DATA_INVALID_POS )
					throw e;
			}
		}

		if ( !pFrame->DoFpsWait() )
			return TRUE;
	}
	return TRUE;
}
