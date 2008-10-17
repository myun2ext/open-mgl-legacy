//////////////////////////////////////////////////////////
//
//	MglguiScreen
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglguiScreen.h"

using namespace agh;

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
	if ( nMoveX != 0 || nMoveY != 0 ){
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
		_AGL_RECT& rect = p->GetRect();

		if ( IsRectInternal((_MSL_RECT*)&rect, x, y) ){
			OnControlLButtonDown(p,x,y);
			return;
		}
	}

	//	�ǂ̃R���g���[���ɂ���v���Ȃ��ꍇ�̓o�b�N�O���E���h
	OnBackgroundLButtonDown(x,y);
}
