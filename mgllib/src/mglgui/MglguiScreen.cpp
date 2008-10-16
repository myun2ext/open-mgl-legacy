//////////////////////////////////////////////////////////
//
//	MglguiScreen
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglguiScreen.h"

using namespace agh;

/*
//	�R���X�g���N�^
CMglguiScreen::CMglguiScreen()
{
}

//	�f�X�g���N�^
CMglguiScreen::~CMglguiScreen()
{
}
*/

//	������
void CMglguiScreen::Init( HWND hWnd, int nDispX, int nDispY )
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
void CMglguiScreen::ScreenUpdate()
{
	//if ( m_grp.GetD3dDevPtr() != NULL ) {
	grp.Clear(m_rgbBackground);
	//grp.Clear(D3DCOLOR_BLUE);

	//m_layer.Draw();
	OnDraw();

	//m_grp.UpdateScreen(); -> DoFpsWait()�񒆂ł���Ă��ł���B
}
void CMglguiScreen::OnDraw()
{
	for(int i=0; i<m_ctrlPtrAry.size(); i++)
	{
		m_ctrlPtrAry[i]->OnDraw();
	}
}

//	�t���[������
bool CMglguiScreen::DoFrame()
{
	try{
		//	�C�x���g����
		OnFrameMouseInput();

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

bool CMglguiScreen::OnFrameMouseInput()
{
	int x = m_mouse.GetCursorPosX();
	int y = m_mouse.GetCursorPosY();
	int nMoveX = m_mouse.GetXMoveCount();
	int nMoveY = m_mouse.GetYMoveCount();

	/*	�Ⴆ�΃h���b�O�ŉ�ʊO�̎��ɑΉ��o���Ȃ��̂ł����ł̓`�F�b�N���Ȃ����Ƃ���
	//	�E�C���h�E�͈̔͊O�Ȃ�C�x���g�͈͊O�Ƃ���
	if ( x < 0 || y < 0 ||
		 x > )
		return false;
	*/

	bool ret = false;

	//	�}�E�X�ړ�
	if ( nMoveX > 0 || nMoveY > 0 ){
		//CScreenBase::OnMouseMove(x, y, nMoveX, nMoveY); <- ���ꂶ�Ⴀ�p�����������Ă΂�Ȃ�����Ȃ��E�E�E
		OnMouseMove(x, y, nMoveX, nMoveY);
		ret = true;
	}

	//	�^���{�^����������
	if ( m_mouse.IsOnDownCenterButton() ){
		//CScreenBase::OnCButtonDown(x,y);
		OnCButtonDown(x,y);
		ret = true;
	}

	//	���{�^����������
	if ( m_mouse.IsOnDownLeftButton() ){

		//	�E�C���h�E�͈̔͊O�Ȃ�C�x���g�͈͊O�Ƃ���
		if ( x < 0 || y < 0 ||
			 x >= CMglEzGameFrame::m_nWidth || y >= CMglEzGameFrame::m_nHeight )
		{
		}
		else
		{
			//CScreenBase::OnLButtonDown(x,y);
			OnLButtonDown(x,y);
			ret = true;
		}
	}

	//	�E�{�^����������
	if ( m_mouse.IsOnDownRightButton() ){
		//CScreenBase::OnRButtonDown(x,y);
		OnRButtonDown(x,y);
		ret = true;
	}

	return ret;
}

//	���{�^���������ꂽ
void CMglguiScreen::OnLButtonDown(int x, int y)
{
	//	�R���g���[���ŊY��������̂����邩�H
	for(int i=0; i<m_controlPtrAry.size(); i++)
	{
		CControlBase *p = m_controlPtrAry[i];
		_AGL_RECT& rect = p->m_rect;

		if ( IsRectInternal((_MSL_RECT*)&rect, x, y) ){
			OnControlLButtonDown(p,x,y);
			return;
		}
	}

	//	�ǂ̃R���g���[���ɂ���v���Ȃ��ꍇ�̓o�b�N�O���E���h
	OnBackgroundLButtonDown(x,y);
}

//////////////////////////////////////////////////

//	�X���b�h�J�n
void CMglguiScreen::AutoLoopThreadStart()
{
	if ( CMyuThreadBase::Execute() != true )
		MyuThrow(64929, "CMglguiScreen: CMyuThreadBase::Execute() failed.");
}

//	�X���b�h�֐�
bool CMglguiScreen::ThreadFunc()
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
		EzErrBox(e.szErrMsg);
	}

	return true;
}

/////////////////////////////////////////////////////////////

void CMglguiScreen::RegistControl(CMglAghImage* pImage)
{
	const char* szFilePath = pImage->m_strFilePath.c_str();
	const char* szAlias = pImage->m_strLayerName.c_str();

	//	�����Ƃ�����
	pImage->_Setup(&m_grp, &m_imgCache);
	
	//	���������
	m_imgCache.Cache(szFilePath);

	//	�����ēo�^
	_RegistControl(pImage);
	//m_layer.RegistBegin( new CMglImageLayer(m_imgCache[szFilePath]), true );
}
void CMglguiScreen::_RegistControl(agh::CControlBase* pCtrl)
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
