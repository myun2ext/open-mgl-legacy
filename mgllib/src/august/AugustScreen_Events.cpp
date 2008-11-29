//////////////////////////////////////////////////////////
//
//	AugustScreen
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustScreen.h"

using namespace agh;

//	�}�E�X����
bool CAugustScreen::OnFrameMouseInput()
{
	/*int x = m_mouse.GetCursorPosX();
	int y = m_mouse.GetCursorPosY();*/
	//POINT point = m_mouse.GetCursorPos();
	m_nCachedCurPos = m_mouse.GetCursorPos();
	int x = m_nCachedCurPos.x;
	int y = m_nCachedCurPos.y;
	m_nCachedCurPosX = x;
	m_nCachedCurPosY = y;
	int nMoveX = m_mouse.GetXMoveCount();
	int nMoveY = m_mouse.GetYMoveCount();

//#define _P this
#define _P pControl
	agh::CVisualControlBase *pControl = GetPosControl(x,y);
	if ( pControl == NULL )
		pControl = this;

	/*	�Ⴆ�΃h���b�O�ŉ�ʊO�̎��ɑΉ��o���Ȃ��̂ł����ł̓`�F�b�N���Ȃ����Ƃ���
	//	�E�C���h�E�͈̔͊O�Ȃ�C�x���g�͈͊O�Ƃ���
	if ( x < 0 || y < 0 ||
		 x > )
		return false;
	*/

	//	���荞�ݏ���
	OnMouseEventInterrupt(pControl, x, y, nMoveX, nMoveY);

	bool ret = false;

	//	�}�E�X�ړ�
	if ( nMoveX != 0 || nMoveY != 0 ){
		//CScreenBase::OnMouseMove(x, y, nMoveX, nMoveY); <- ���ꂶ�Ⴀ�p�����������Ă΂�Ȃ�����Ȃ��E�E�E
		_P->OnMouseMove(x, y, nMoveX, nMoveY);
		ret = true;
	}

	//	�^���{�^����������
	if ( m_mouse.IsOnDownCenterButton() ){
		//	�E�C���h�E�͈̔͊O�Ȃ�C�x���g�͈͊O�Ƃ���
		if ( x < 0 || y < 0 ||
			 x >= g_.m_nWindowWidth || y >= g_.m_nWindowHeight )
		{
			//	�������Ȃ��B�iif���������]�ɂ��ׂ���������...�j
		}
		else
		{
			//CScreenBase::OnCButtonDown(x,y);
			_P->OnCButtonDown(x,y);
			ret = true;
		}
	}

	//	���{�^����������
	if ( m_mouse.IsOnDownLeftButton() ){

		//	�E�C���h�E�͈̔͊O�Ȃ�C�x���g�͈͊O�Ƃ���
		if ( x < 0 || y < 0 ||
			 x >= g_.m_nWindowWidth || y >= g_.m_nWindowHeight )
		{
			//	�������Ȃ��B�iif���������]�ɂ��ׂ���������...�j
		}
		else
		{
			//CScreenBase::OnLButtonDown(x,y);
			_P->OnLButtonDown(x,y);
			ret = true;
		}
	}

	//	�E�{�^����������
	if ( m_mouse.IsOnDownRightButton() ){

		//	�E�C���h�E�͈̔͊O�Ȃ�C�x���g�͈͊O�Ƃ���
		if ( x < 0 || y < 0 ||
			 x >= g_.m_nWindowWidth || y >= g_.m_nWindowHeight )
		{
			//	�������Ȃ��B�iif���������]�ɂ��ׂ���������...�j
		}
		else
		{
			//CScreenBase::OnRButtonDown(x,y);
			_P->OnRButtonDown(x,y);
			ret = true;
		}
	}

	//// ������ ////////////////////////////

	//	�^���{�^���𗣂���
	if ( m_mouse.IsOnUpCenterButton() ){
		//CScreenBase::OnCButtonUp(x,y);
		_P->OnCButtonUp(x,y);
		ret = true;
	}

	//	���{�^���𗣂���
	if ( m_mouse.IsOnUpLeftButton() ){
		//CScreenBase::OnLButtonUp(x,y);
		_P->OnLButtonUp(x,y);
		ret = true;
	}

	//	�E�{�^���𗣂���
	if ( m_mouse.IsOnUpRightButton() ){
		//CScreenBase::OnRButtonUp(x,y);
		_P->OnRButtonUp(x,y);
		ret = true;
	}

	return ret;
}

////////////////////////////////////////////////////////////

bool CAugustScreen::OnFrameKeyboardInput()
{
	t_MGL_KB_EVT_HANDLERS::iterator it=m_kbEventHandlers.begin();
	for(; it!=m_kbEventHandlers.end(); it++)
	{
		MGL_KB_EVT_HANDLER &r = *it;

		switch(r.evtType)
		{
		case MGL_KB_EVT_HANDLER_EVTTYPE_ON_PRESS:
			if ( m_input.IsPressKey(r.keyCode) )
				if ( (this->*r.pCallbackFunc)() != true )
					return false;
			break;

		case MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN:
			if ( m_input.IsOnDownKey(r.keyCode) )
				if ( (this->*r.pCallbackFunc)() != true )
					return false;
			break;

		case MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP:
			if ( m_input.IsOnUpKey(r.keyCode) )
				if ( (this->*r.pCallbackFunc)() != true )
					return false;
			break;
		}
	}

	return true;
}


/*
//	���{�^���������ꂽ
void CAugustScreen::OnLButtonDown(int x, int y)
{
	agh::CControlBase *pControl = GetPosControl(x,y);
	if ( pControl == NULL )
		pControl->OnLButtonDown(x,y);
	else
		OnBackgroundLButtonDown(x,y);
}
*/

/*
//	���{�^���������ꂽ
void CAugustScreen::OnLButtonDown(int x, int y)
{
	//	�R���g���[���ŊY��������̂����邩�H
	for(int i=0; i<m_controlPtrAry.size(); i++)
	{
		CControlBase *p = m_controlPtrAry[i];
		_AGH_RECT& rect = p->GetRect();

		if ( IsRectInternal((_MSL_RECT*)&rect, x, y) ){
			OnControlLButtonDown(p,x,y);
			return;
		}
	}

	//	�ǂ̃R���g���[���ɂ���v���Ȃ��ꍇ�̓o�b�N�O���E���h
	OnBackgroundLButtonDown(x,y);
}
*/
