//////////////////////////////////////////////////////////
//
//	MyuEzWindow
//		- Window�������ȒP�ɍs��
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyuEzWindow.h"
#include "MyuFunctions.h"
#include "MglManager.h"		//	�f�o�b�O���O

LRESULT WINAPI MyuEzWindowMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

//	�R���X�g���N�^
CMyuEzWindow::CMyuEzWindow()
{
	m_nThreadExitTimeout = DEFAULT_THREAD_EXIT_TIMEOUT;
	m_bAlive = FALSE;
	m_hWnd = NULL;
}

//	�f�X�g���N�^
CMyuEzWindow::~CMyuEzWindow()
{

}

//	�E�C���h�E����
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

	// �E�B���h�E �N���X��o�^����B
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

	//	�E�C���h�E�X�^�C��
	DWORD dwWinStyle = dwExtendWinStyle | WS_CAPTION | WS_SYSMENU;

	//	�E�C���h�E�̘g���܂߂��c���̃T�C�Y���擾����
    RECT rc = { 0, 0, nWinWidthSize, nWinHeightSize } ;
    if ( AdjustWindowRect( &rc, dwWinStyle, FALSE ) == 0 )
		MessageBox( NULL, "AdjustWindowRect() �̎��s�Ɏ��s���܂����B", NULL, MB_ICONERROR );

	// �A�v���P�[�V�����̃E�B���h�E���쐬����B

	hWnd = CreateWindow( szWinClassName, szAppCaption, dwWinStyle,
						 nWinXPos, nWinYPos, rc.right - rc.left, rc.bottom - rc.top,
						 GetDesktopWindow(), NULL, wc.hInstance, NULL );

	//	�f�t�H���gHWND
	MglDefaultInitialize( hWnd );

	/*
	// �A�v���P�[�V�����̃E�B���h�E���쐬����B
	hWnd = CreateWindow( szWinClass, APPANME, 
						 WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
						 100, 100, GetDGWindowX(WIDTH), GetDGWindowY(HEIGHT),
						 GetDesktopWindow(), NULL, wc.hInstance, NULL );
	*/

	// Show the window
	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow( hWnd );

	//	�J�[�\����\��
	ShowCursor(FALSE);

	//////////////////////////////////////////
	//
	//		�X���b�h�쐬�̎��Ԃ̎��Ԃł�
	//

	DWORD id;
	m_hWnd = hWnd;
	m_bAlive = TRUE;
	//hMainThread = CreateThread( NULL, 0, threadFunc, &threadFuncParam, 0, &id );
	_MGL_DEBUGLOG("CreateThread()..." );
	hMainThread = CreateThread( NULL, 0, threadFunc, threadFuncParam, 0, &id );
	
	//////////////////////////////////////////
	//
	//			���b�Z�[�W���[�v
	//

	//	���񂳂�͏���ɉ���ĂĂ��炳���R(�L�[�M)�
	MSG msg;
	do {
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			//	�X���b�h�I������
			static DWORD exitCode; 
			if ( GetExitCodeThread( hMainThread, &exitCode ) == 0 )
			{
				MessageBox( hWnd, "CMyuEzWindow::StartWindow()  GetExitCodeThread()�Ɏ��s�B", szAppCaption, MB_ICONERROR );
				break;
			}
			if ( exitCode != STILL_ACTIVE ){
				_MGL_DEBUGLOG("exitCode is not STILL_ACTIVE." );
				break;
			}

			//	�Ȃ�ɂ����邱�ƂȂ���[��B(߁��)�`��
			Sleep(1);	//	Zzzz..
		}
	} while( msg.message!=WM_QUIT );

	//	�e�v���Z�X�̃X�e�[�^�X���I����Ԃ�
	m_bAlive = FALSE;

	//	�X���b�h���I���̂�҂ł�
	//	�w��ms�o���Ă����������������ꍇ���b�Z�[�W�{�b�N�X���o�͂���
	//	�����I�ɃX���b�h���I�������܂��B
	for( int i=0; i<m_nThreadExitTimeout; i++ )
	{
		static DWORD exitCode; 
		if ( GetExitCodeThread( hMainThread, &exitCode ) == 0 )
		{
			MessageBox( NULL, "CMyuEzWindow::StartWindow()  GetExitCodeThread()�Ɏ��s�B", szAppCaption, MB_ICONERROR );
			break;
		}
		if ( exitCode != STILL_ACTIVE )
			break;

		Sleep(1);	//	Zzzz..
	}
	if ( i >= m_nThreadExitTimeout )
	{
		MessageBox( NULL, "CMyuEzWindow::StartWindow()  �X���b�h����̉���������܂���B�����I�ɃX���b�h���I�������܂��B\r\n"
			"\r\n"
			"�v���O���}����ցF\r\n"
			"�@CMyuEzWindow::IsAcrive() �ɂāA�E�C���h�E�̊�����Ԃ��`�F�b�N���AFALSE�������ꍇ�A\r\n"
			"�@�X���b�h���I��������悤�ȏ�����ǉ����Ă��������B�i�ڍׂ̓w���v�Q�Ɓj",
			szAppCaption, MB_ICONERROR );

		//	������x�`�F�b�N�̏���

		TerminateThread( hMainThread, -1 );
	}

	//	�A��܂��您�܂���
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

