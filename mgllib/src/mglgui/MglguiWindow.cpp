//////////////////////////////////////////////////////////
//
//	MglguiWindow
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglguiWindow.h"

using namespace agh;

class DLL_EXP agh::CScreenBase;

/*
//	�R���X�g���N�^
CMglguiWindow::CMglguiWindow()
{
}

//	�f�X�g���N�^
CMglguiWindow::~CMglguiWindow()
{
}
*/

//	������
void CMglguiWindow::Init( HWND hWnd, int nDispX, int nDispY )
{
	//m_grp.Init(hWnd, nDispX, nDispY, FALSE );

	//	�����̃C���X�^���X���쐬���鎖�ɂȂ�̂�Init()���K�v
	m_imgCache.Init(&grp);
	//m_layer.Init(&grp);

	m_hWnd = hWnd;

	//	virtual��
	OnInit();
	//ScreenUpdate();
}

//////////////////////////////////////////////////

//	��ʂ��X�V
void CMglguiWindow::ScreenUpdate()
{
	//if ( m_grp.GetD3dDevPtr() != NULL ) {
	grp.Clear(m_rgbBackground);
	//grp.Clear(D3DCOLOR_BLUE);

	//m_layer.Draw();
	OnDraw();

	//m_grp.UpdateScreen(); -> DoFpsWait()�񒆂ł���Ă��ł���B
}
void CMglguiWindow::OnDraw()
{
	//for(int i=0; i<m_ctrlPtrAry.size(); i++)
	for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	{
		//m_ctrlPtrAry[i]->Draw();
		GetVCtrlPtr(i)->Draw();
	}
}

//	�t���[������
bool CMglguiWindow::DoFrame()
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
		if ( CMglEzGameFrame::DoFpsWait() == FALSE )
			return false;
	}
	catch( MyuCommonException e )
	{
		EzErrBox(e.szErrMsg);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////

//	�X���b�h�J�n
void CMglguiWindow::AutoLoopThreadStart()
{
	if ( CMyuThreadBase::Execute() != true )
		MyuThrow(64929, "CMglguiWindow: CMyuThreadBase::Execute() failed.");
}

//	�X���b�h�֐�
bool CMglguiWindow::ThreadFunc()
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

/////////////////////////////////////////////////////////////

//	Events�ցB

/////////////////////////////////////////////////////////////

void CMglguiWindow::RegistControl(CMglAghImage* pImage)
{
	const char* szFilePath = pImage->m_strFilePath.c_str();
	const char* szAlias = pImage->m_strLayerName.c_str();

	//	�����Ƃ�����
	pImage->_Setup(&m_grp, &m_imgCache);
	
	//	���������
	m_imgCache.Cache(szFilePath);

	pImage->SetRect(0,0,m_imgCache.Get(szFilePath)->GetBmpWidth(),
		m_imgCache.Get(szFilePath)->GetBmpHeight());

	//	�����ēo�^
	_RegistControl(pImage);
	//m_layer.RegistBegin( new CMglImageLayer(m_imgCache[szFilePath]), true );
}
void CMglguiWindow::_RegistControl(agh::CControlBase* pCtrl)
{
	m_ctrlPtrAry.push_back(pCtrl);
}

/////////////////////////////////////////////////////////////

DWORD WINAPI CMglguiWindow_ThreadFunc(CMglguiWindow *pWindow){ return (bool)pWindow->__ThreadFunc(); }

bool CMglguiWindow::__ThreadFunc()
{
	//Init(GetWindowHandle(), 640, 480);
	return ThreadFunc();
}

/*int CMglguiWindow::StartWindow( int nWinWidthSize, int nWinHeightSize,
	const char *szWindowTitle, BOOL bFullscreen )
{
	return StartWindowEx(nWinWidthSize, nWinHeightSize, (LPTHREAD_START_ROUTINE)CMglguiWindow_ThreadFunc,
		this, szWindowTitle, bFullscreen);
}*/
void CMglguiWindow::Start()
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
		winInfo.nWinHeightSize, (LPTHREAD_START_ROUTINE)CMglguiWindow_ThreadFunc,
		this, winInfo.strWindowTitle.c_str(), extendInfo.bFullScreen);
}
