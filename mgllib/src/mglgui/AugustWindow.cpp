#include "stdafx.h"
#include "AugustWindow.h"

using namespace agh;





//	��ʂ��X�V
void CAugustWindow::ScreenUpdate()
{
	//if ( m_grp.GetD3dDevPtr() != NULL ) {
	grp.Clear(m_rgbBackground);
	//grp.Clear(D3DCOLOR_BLUE);

	//m_layer.Draw();
	OnDraw();

	//m_grp.UpdateScreen(); -> DoFpsWait()�񒆂ł���Ă��ł���B
}

//	�t���[������
bool CAugustWindow::DoFrame()
{
	try{
		//	�C�x���g����
		OnFrameMouseInput();	//	�Ȃ񂩏E��Ȃ���false��Ԃ��d�l�ɂȂ��Ă���ۂ��E�E�E
		/*if ( OnFrameMouseInput() != true )
			return false;*/

		if ( OnFrameKeyboardInput() != true )
			return false;

		//	2008/11/02 ���[�U�C�x���g����
		if ( OnFrameDoUser() != true )
			return false;

		//	�`�揈��
		ScreenUpdate();

		//	�t���[�����[�g����{������ (CMglEzGameFrame)
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


//	�L�����ǂ������A���܂��iFALSE�ɂȂ�����I�����邱�ƁI�j
BOOL CAugustWindow::DoFpsWait()
{
	//	�E�C���h�E�������Ă邩�̃`�F�b�N
	if ( m_window.IsAlive() != TRUE )
		return FALSE;

	//	������H
	if ( m_bBreak )
		return FALSE;

	//	FPS/�f�o�b�O������o��
	if ( m_bFpsShow == TRUE )
	{
		char szFps[64];
		sprintf( szFps, "FPS : %.01f", fps.GetAveFps() );
		m_txtFps.Draw( szFps, 6, 6, D3DCOLORW_XRGB(0,0,0) );
		m_txtFps.Draw( szFps, 5, 5, D3DCOLORW_XRGB(255,255,255) );
	}
	m_txtDebug.Draw( m_strDebugText.c_str(), 6, 21, D3DCOLORW_XRGB(0,0,0) );
	m_txtDebug.Draw( m_strDebugText.c_str(), 5, 20, D3DCOLORW_XRGB(255,255,255) );

	//	�X�v���C�g�I��
	grp.SpriteEnd();

	//	�X�N���[���̃A�b�v�f�[�g
	grp.UpdateScreen();

	//	�҂��
	fps.Sleep();

	//	�L�[�{�[�h���͂̍X�V
	input.Update();

	if ( m_bEscEnd ){
		if ( input.GetOnKey(ASCII_ESC) )
			return FALSE;
	}

	//	�X�v���C�g�J�n
	grp.SpriteBegin();

	return TRUE;
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
	winInfo.nWinXPos = 0;	//	���݂����ĂȂ����E�E�E
	winInfo.nWinYPos = 0;	//	���݂����ĂȂ����E�E�E
	winInfo.pExtendStructure = &extendInfo;
	winInfo.strWindowClass = "";	//	���݂����ĂȂ����E�E�E
	winInfo.strWindowTitle = "Application";

	extendInfo.bFullScreen = FALSE;

	//	�I�[�o�[���[�h�Ăяo��
	OnCreateWindow(&winInfo);

	/*return*/ StartWindowEx(
		winInfo.nWinWidthSize,
		winInfo.nWinHeightSize, (LPTHREAD_START_ROUTINE)CAugustWindow_ThreadFunc,
		this, winInfo.strWindowTitle.c_str(), extendInfo.bFullScreen);
}


//////////////////////////////////////////////////

//	�X���b�h�J�n
void CAugustWindow::AutoLoopThreadStart()
{
	if ( CMyuThreadBase::Execute() != true )
		MyuThrow(64929, "CAugustScreen: CMyuThreadBase::Execute() failed.");
}

//	�X���b�h�֐�
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
			"���̃G���[�������������߃A�v���P�[�V�������I�����܂��B\r\n\r\n"
			"%s", e.szErrMsg);
	}
	catch( agh::CAghException e )
	{
		//EzErrBox(this->m_hWnd, e.GetMessage());
		MyuMessageBox(this->m_hWnd, "Application Error", MB_ICONSTOP,
			"���̃G���[�������������߃A�v���P�[�V�������I�����܂��B\r\n\r\n"
			"AGH : %s", e.GetMessage());
	}

	return true;
}

//	������
void CAugustWindow::Init( HWND hWnd, int nDispX, int nDispY )
{
	//m_grp.Init(hWnd, nDispX, nDispY, FALSE );

	//	�����̃C���X�^���X���쐬���鎖�ɂȂ�̂�Init()���K�v
	m_imgCache.Init(&grp);
	//m_layer.Init(&grp);

	m_hWnd = hWnd;

	//	virtual��
	//OnInit();
	CAugustScreen::OnInit();
	//ScreenUpdate();
}