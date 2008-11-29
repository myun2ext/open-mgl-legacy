//////////////////////////////////////////////////////////
//
//	AugustScreen
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustScreen.h"

using namespace agh;

class DLL_EXP agh::CScreenBase;

/*
//	�R���X�g���N�^
CAugustScreen::CAugustScreen()
{
}

//	�f�X�g���N�^
CAugustScreen::~CAugustScreen()
{
}
*/


//////////////////////////////////////////////////

void CAugustScreen::OnDraw()
{
	m_grp.Clear(m_rgbBackground);	//	2008/11/29 CAugustScreen�Ή�

	//for(int i=0; i<m_ctrlPtrAry.size(); i++)
	for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	{
		//m_ctrlPtrAry[i]->Draw();
		GetVCtrlPtr(i)->Draw();
	}
}


//	�t���[������
bool CAugustScreen::DoFrame()
{
	OnFrameMouseInput();	//	�Ȃ񂩏E��Ȃ���false��Ԃ��d�l�ɂȂ��Ă���ۂ��E�E�E
	/*if ( OnFrameMouseInput() != true )
		return false;*/

	if ( OnFrameKeyboardInput() != true )
		return false;

	//	2008/11/02 ���[�U�C�x���g����
	if ( OnFrameDoUser() != true )
		return false;
}


/////////////////////////////////////////////////////////////

//	Events�ցB

/////////////////////////////////////////////////////////////

void CAugustScreen::RegistControl(CMglAghImage* pImage)
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
void CAugustScreen::_RegistControl(agh::CControlBase* pCtrl)
{
	m_ctrlPtrAry.push_back(pCtrl);
}
