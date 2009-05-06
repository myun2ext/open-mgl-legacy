//////////////////////////////////////////////////////////
//
//	AugustGraphicsManager
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustGraphicsManager.h"
#include "MglGraphicManager.h"
#include "AugustWindow2.h"

using namespace agh;
using namespace std;

//	�R���X�g���N�^
CAugustGraphicsManager::CAugustGraphicsManager()
{
	m_pGrp = new CMglGraphicManager();

	m_rgbBackground = AGHCOLOR_WHITE;
}

//	�f�X�g���N�^
CAugustGraphicsManager::~CAugustGraphicsManager()
{
	SAFE_DELETE(m_pGrp);
}



//////////////////////////////////////////////////

#define grp		(*m_pGrp)
#define m_grp	(*m_pGrp)

void CAugustGraphicsManager::Init(bool bIsFullscreen)
{
	_MGL_DEBUGLOG("grp.Init()..." );

	//CAugustWindow2* pWindow = (CAugustWindow2*)_BASE::GetParentControl();
	CAugustWindow2* pWindow = (CAugustWindow2*)MyuAssertNull(_BASE::GetParentControl(),
		"CAugustGraphicsManager: �e�R���g���[����������܂���B�e�R���g���[���ւ̒ǉ�������Ă��邩�m�F���Ă��������B");

	//HWND hWnd = (HWND)GetValPtr(MWLAGH_VALKEY_HWND);
	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_HWND),
		"CAugustGraphicsManager::Init()  �E�C���h�E�n���h���̎擾�Ɏ��s");

	m_pGrp->Init( hWnd, pWindow->GetWidth(), pWindow->GetHeight(), bIsFullscreen );

	Clear();
}

void CAugustGraphicsManager::Release()
{
	m_grp.Release();
}

void CAugustGraphicsManager::Clear()
{
	m_grp.Clear(m_rgbBackground);	//	2008/11/29 CAugustGraphicsManager�Ή�
}

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
