//////////////////////////////////////////////////////////
//
//	MglguiScreen
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglguiScreen.h"

using namespace agh;

class DLL_EXP agh::CScreenBase;

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
	//for(int i=0; i<m_ctrlPtrAry.size(); i++)
	for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	{
		//m_ctrlPtrAry[i]->Draw();
		GetVCtrlPtr(i)->Draw();
	}
}

//	�t���[������
bool CMglguiScreen::DoFrame()
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

void CMglguiScreen::RegistControl(CMglAghImage* pImage)
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

void CMglguiScreen::RegistControl(CMglAghText* pText)
{
	//	�����Ƃ�����
	pText->_Setup(&m_grp);

	//	�����ēo�^
	_RegistControl(pText);
}

void CMglguiScreen::_RegistControl(agh::CControlBase* pCtrl)
{
	m_ctrlPtrAry.push_back(pCtrl);
}
