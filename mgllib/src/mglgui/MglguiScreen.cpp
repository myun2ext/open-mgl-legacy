//////////////////////////////////////////////////////////
//
//	MglguiScreen
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglguiScreen.h"

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
	m_grp.Init(hWnd, nDispX, nDispY, FALSE );

	//	�����̃C���X�^���X���쐬���鎖�ɂȂ�̂�Init()���K�v
	m_imgPool.Init(&m_grp);
	m_layer.Init(&m_grp);

	m_hWnd = hWnd;
	ScreenUpdate();
}

//////////////////////////////////////////////////

//	��ʂ��X�V
void CMglguiScreen::ScreenUpdate()
{
	//if ( m_grp.GetD3dDevPtr() != NULL ) {
	m_grp.Clear(m_rgbBackground);

	m_layer.Draw();

	m_grp.UpdateScreen();
}

//	�t���[������
bool CMglguiScreen::DoFrame()
{
	try{
		//	�C�x���g����
		OnFrameMouseInput();

		//	�t���[������ (CMglEzGameFrame)
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
	int y = m_mouse.GetCursorPosX();
	int nMoveX = m_mouse.GetXMoveCount();
	int nMoveY = m_mouse.GetYMoveCount();

	//	�}�E�X�ړ�
	if ( nMoveX > 0 || nMoveY > 0)
		CScreenBase::OnMouseMove(x, y, nMoveX, nMoveY);

	//	�^���{�^����������
	if ( m_mouse.IsOnDownCenterButton() )
		CScreenBase::OnCButtonDown(x,y);

	//	���{�^����������
	if ( m_mouse.IsOnDownLeftButton() )
		CScreenBase::OnLButtonDown(x,y);

	//	�E�{�^����������
	if ( m_mouse.IsOnDownRightButton() )
		CScreenBase::OnRButtonDown(x,y);

	return true;
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

