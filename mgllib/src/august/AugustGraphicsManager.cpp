//////////////////////////////////////////////////////////
//
//	AugustGraphicsManager
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustGraphicsManager.h"
#include "MglGraphicManager.h"
#include "MglImage.h"
#include "AugustWindow2.h"

/*
//class _AGST_DLL_EXP CAugustImageLoader : public agh::util::CLoaderBase<CAugustImage2_2>
class _AGST_DLL_EXP CAugustImageLoader : public agh::util::CLoaderBase<CMglImage>
{
private:
	//typedef CAugustImage2_2 _IMG;
	typedef CMglImage _IMG;
	typedef agh::util::CLoaderBase<_IMG> _BASE;

protected:
	CMglGraphicManager *m_pGrp;

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CAugustImageLoader(){
		m_pGrp = NULL;
	}
	virtual ~CAugustImageLoader(){}

	/*virtual _IMG* Load(const char* szName){

	}*//*

//	�C�x���g�n���h���̎���
_AGH_EVENT_ACCESS_MODIFIER:

	virtual void OnRegist(){
		m_pGrp = (CMglGraphicManager*)MyuAssertNull(GetValPtr(AUGUST_VALKEY_GRP),
			"CAugustImageLoader: GetValPtr(AUGUST_VALKEY_GRP) �̎擾�Ɏ��s�B");
	}

	virtual bool OnNewLoaderAppend(const char* szName, _IMG* pItem){
		pItem->Init(m_pGrp);
		pItem->Create(szName);
		return true;
	}
};*/

bool CAugustImageLoader::OnNewLoaderAppend(const char* szName, _IMG* pItem){
	pItem->Init(m_pGrp);
	pItem->Create(szName);
	return true;
}


////////////////////////////////////////////////

using namespace agh;
using namespace std;

//	�R���X�g���N�^
CAugustGraphicsManager::CAugustGraphicsManager()
{
	m_pGrp = new CMglGraphicManager();
	m_pImageLoader = new CAugustImageLoader();	//	�ǂ����ł��s����悤��new�̂܂܂ɂ��Ă�̂��ȁE�E�E�H

	//m_rgbBackground = AGHCOLOR_WHITE;

	//	2009/05/13
	SetValPtr(AUGUST_VALKEY_GRP, m_pGrp);
	SetValPtr(AUGUST_VALKEY_IMAGE_LOADER, m_pImageLoader);

	//	2009/05/13
	RegistSubControl(m_pImageLoader);
	//RegistSubControl(m_imageLoader);
}

//	�f�X�g���N�^
CAugustGraphicsManager::~CAugustGraphicsManager()
{
	SAFE_DELETE(m_pImageLoader);
	SAFE_DELETE(m_pGrp);
}

//////////////////////////////////////////////////

#define grp		(*m_pGrp)
#define m_grp	(*m_pGrp)

//	������
void CAugustGraphicsManager::Init(bool bIsFullscreen)
{
	_MGL_DEBUGLOG("grp.Init()..." );

	//CAugustWindow2* pWindow = (CAugustWindow2*)_BASE::GetParentControl();
	//CAugustWindow2* pWindow = (CAugustWindow2*)MyuAssertNull(_BASE::GetParentControl(),
	m_pWindow = (CAugustWindow2*)MyuAssertNull(_BASE::GetParentControl(),
		"CAugustGraphicsManager: �e�R���g���[����������܂���B�e�R���g���[���ւ̒ǉ�������Ă��邩�m�F���Ă��������B");

	//HWND hWnd = (HWND)GetValPtr(MWLAGH_VALKEY_HWND);
	//HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_HWND),
	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_ROOT_WINDOW_HWND),
		"CAugustGraphicsManager::Init()  �E�C���h�E�n���h���̎擾�Ɏ��s");

	m_pGrp->Init( hWnd, m_pWindow->GetWidth(), m_pWindow->GetHeight(), bIsFullscreen );

	Clear();
}

//	�J��
void CAugustGraphicsManager::Release()
{
	m_grp.Release();
}

//	�N���A
void CAugustGraphicsManager::Clear(){
	//m_grp.Clear(m_rgbBackground);	//	2008/11/29 CAugustGraphicsManager�Ή�
	m_grp.Clear(m_pWindow->GetColor());
}
void CAugustGraphicsManager::Clear(agh::AGHCOLOR color){
	m_grp.Clear(color);	//	2008/11/29 CAugustGraphicsManager�Ή�
}

//	�`��
void CAugustGraphicsManager::OnDraw()
{
	Clear();

	/*
	for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	{
		GetVCtrlPtr(i)->Draw();
	}
	*/
	for(int i=0; i<m_ctrlPtrAry.size(); i++)
	{
		agh::CControlBase *pCtrl = m_ctrlPtrAry[i];
		if ( pCtrl->IsVisual() )
			((agh::CVisualControlBase*)pCtrl)->Draw();
	}
}

//	�t���[������
bool CAugustGraphicsManager::DoFrame()
{
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

//	�t���[���̊J�n
void CAugustGraphicsManager::FrameStart()
{
	//	�X�v���C�g�J�n
	m_pGrp->SpriteBegin();
}

//	�t���[���̏I��
void CAugustGraphicsManager::FrameEnd()
{
	//	�X�v���C�g�I��
	m_pGrp->SpriteEnd();

	//	�X�N���[���̃A�b�v�f�[�g
	m_pGrp->UpdateScreen();
}
