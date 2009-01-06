#include "stdafx.h"
#include "AugustWindow.h"

using namespace agh;

//	�R���X�g���N�^
CAugustWindow::CAugustWindow()	//	�f�t�H���g�X�N���[���Ƃ����ڂ��Ă݂邩�E�E�E�B
{
	m_pActiveScreen = NULL;
	//m_pActiveScreen = &m_defaultScreen;	//	�f�t�H���g�X�N���[���Ƃ����ڂ��Ă݂邩�E�E�E�B

	m_hInstance = NULL;
	m_hPrevInstance = NULL;
	m_lpCmdLine = NULL;
	m_nCmdShow = -1;
}

//	��ʂ��X�V
void CAugustWindow::ScreenUpdate()
{
	//if ( m_grp.GetD3dDevPtr() != NULL ) {
	//grp.Clear(m_rgbBackground);
	//grp.Clear(D3DCOLOR_WHITE);	//	<- �Ƃ肠�����[

	//m_layer.Draw();
	m_pActiveScreen->OnDraw();

	//m_grp.UpdateScreen(); -> DoFpsWait()�񒆂ł���Ă��ł���B
}

//	�t���[������
bool CAugustWindow::DoFrame()
{
	try{
		if ( m_pActiveScreen == NULL)
			MyuThrow(25598, "SetActiveScreenControl() �ɂăX�N���[����ݒ肵�Ă��������B");

		//	2008/11/29 Screen����DoFrame()���Ăяo���d�l��
		if ( m_pActiveScreen != (void*)this )
			if ( m_pActiveScreen->DoFrame() == false )
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


//	�X���b�h�֐�
bool CAugustWindow::ThreadFunc()
{
	try{
		//	2008/11/29 �f�t�H���g�X�N���[���Ƃ����ڂ��Ă݂邩�E�E�E�B
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
			"���̃G���[�������������߃A�v���P�[�V�������I�����܂��B\r\n\r\n"
			"%s", e.szErrMsg);
	}
	catch( agh::CAghException e )
	{
		//EzErrBox(g_->hWnd, e.GetMessage());
		MyuMessageBox(g_->hWnd, "Application Error", MB_ICONSTOP,
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

	//m_hWnd = hWnd;

	if ( m_pActiveScreen == NULL)
		MyuThrow(25598, "SetActiveScreenControl() �ɂăX�N���[����ݒ肵�Ă��������B");

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
