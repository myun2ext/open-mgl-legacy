// mgl_test.cpp : �A�v���P�[�V�����p�̃G���g�� �|�C���g�̒�`
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

//	���C���X���b�h
BOOL MainThread( CMglEzGameFrame *pFrame )
{
	for(;;){


		if ( !pFrame->DoFpsWait() )
			return TRUE;
	}
	return TRUE;
}