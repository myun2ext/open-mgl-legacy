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
void CMglguiScreen::DoFrame()
{
	try{
		/*
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
		*/
	}
	catch( MyuCommonException e )
	{
		EzErrBox(e.szErrMsg);
	}
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
		
	}
	catch( MyuCommonException e )
	{
		EzErrBox(e.szErrMsg);
	}

	return true;
}

