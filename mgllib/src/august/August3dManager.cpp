//////////////////////////////////////////////////////////
//
//	August3dManager
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "August3dManager.h"

using namespace agh;
using namespace std;

class DLL_EXP agh::CScreenBase;

/*
//	�R���X�g���N�^
CAugust3dManager::CAugust3dManager()
{
}

//	�f�X�g���N�^
CAugust3dManager::~CAugust3dManager()
{
}
*/


//////////////////////////////////////////////////

void CAugust3dManager::OnDraw()
{
	g_->pGrp->Clear(m_rgbBackground);	//	2008/11/29 CAugust3dManager�Ή�

	//for(int i=0; i<m_ctrlPtrAry.size(); i++)
	for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	{
		//m_ctrlPtrAry[i]->Draw();
		GetVCtrlPtr(i)->Draw();
	}
}


//	�t���[������
bool CAugust3dManager::DoFrame()
{
	//	2009/01/23 �}�E�X�̃n���h���͖����ɏo����悤�ɁB
	//	�i���\�����������A��������N���b�N�Ƃ��ŗ]�v�ȏ�������Ƃ܂������E�E�E�j
	if ( m_bUseMouseHandle == true )
	{
		OnFrameMouseInput();	//	�Ȃ񂩏E��Ȃ���false��Ԃ��d�l�ɂȂ��Ă���ۂ��E�E�E
		/*if ( OnFrameMouseInput() != true )
			return false;*/
	}

	//	�L�[�{�[�h�̃n���h������
	if ( OnFrameKeyboardInput() != true )
		return false;

	//	2008/11/02 ���[�U�C�x���g����
	if ( OnFrameDoUser() != true )
		return false;

	//	�e�R���g���[���̃t���[������
	//for(int i=0; i<m_ctrlPtrAry.size(); i++)
	//for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	for(citr it=cbegin(); it != cend(); it++)
	//for(vector<CControlBase*>::iterator it=cbegin(); it != cend(); it++)
	{
		it->OnFrame();
		//(*it)->OnFrame();
		//((CControlBase*)it)->OnFrame();
		//m_ctrlPtrAry[i]->OnFrame();
		//GetVCtrlPtr(i)->Draw();
	}

	return true;
}


/////////////////////////////////////////////////////////////

//	Events�ցB

/////////////////////////////////////////////////////////////

/*
void CAugust3dManager::RegistControl(CMglAghImage* pImage)
{
	const char* szFilePath = pImage->m_strFilePath.c_str();
	const char* szAlias = pImage->m_strLayerName.c_str();

	//	�����Ƃ�����
	pImage->_Setup(g_->pGrp, g_->pImgCache);
	
	//	���������
	g_->pImgCache->Cache(szFilePath);

	pImage->SetRect(0,0,g_->pImgCache->Get(szFilePath)->GetBmpWidth(),
		g_->pImgCache->Get(szFilePath)->GetBmpHeight());

	//	�����ēo�^
	_RegistControl(pImage);
	//m_layer.RegistBegin( new CMglImageLayer(m_imgCache[szFilePath]), true );
}
*/
void CAugust3dManager::RegistControl(CAugustVisualControlBase* pControl)
{
	pControl->OnRegist(g_);

	_RegistControlInternal(pControl);
}

void CAugust3dManager::_RegistControlInternal(agh::CControlBase* pCtrl)
{
	m_ctrlPtrAry.push_back(pCtrl);
}