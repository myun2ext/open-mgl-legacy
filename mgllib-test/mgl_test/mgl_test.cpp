// mgl_test.cpp : �A�v���P�[�V�����p�̃G���g�� �|�C���g�̒�`
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

//	���C���X���b�h
BOOL WINAPI MainThread( CMglEzGameFrame *pFrame )
{
	CMglImage img;
	//img.Create("C:\\Documents and Settings\\�q��\\My Documents\\shana_36-1.jpg");
	//img.Create("font_level.tga");
	img.Create();
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

		POINT point = pFrame->input.mouse.GetCursorPos();
		inBitmap.Set(point.x, point.y, D3DCOLOR_WHITE);

		if ( !pFrame->DoFpsWait() )
			return TRUE;
	}
	return TRUE;
}
