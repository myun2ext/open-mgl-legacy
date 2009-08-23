//////////////////////////////////////////////////////////
//
//	AugustSound
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustSound.h"

using namespace agh;
using namespace std;

class DLL_EXP agh::CScreenBase;

/*
//	�R���X�g���N�^
CAugustSound::CAugustSound()
{
}

//	�f�X�g���N�^
CAugustSound::~CAugustSound()
{
}
*/


//////////////////////////////////////////////////

//	�}�E�X����
bool CAugustSound::OnFrameMouseInput()
{
	/*int x = g_->mouse->GetCursorPosX();
	int y = g_->mouse->GetCursorPosY();*/
	//POINT point = g_->mouse->GetCursorPos();
	m_nCachedCurPos = g_->mouse->GetCursorPos();
	int x = m_nCachedCurPos.x;
	int y = m_nCachedCurPos.y;
	m_nCachedCurPosX = x;
	m_nCachedCurPosY = y;
	int nMoveX = g_->mouse->GetXMoveCount();
	int nMoveY = g_->mouse->GetYMoveCount();

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
	if ( g_->mouse->IsOnDownCenterButton() ){
		//	�E�C���h�E�͈̔͊O�Ȃ�C�x���g�͈͊O�Ƃ���
		if ( x < 0 || y < 0 ||
			 x >= g_->nWindowWidth || y >= g_->nWindowHeight )
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
	if ( g_->mouse->IsOnDownLeftButton() ){

		//	�E�C���h�E�͈̔͊O�Ȃ�C�x���g�͈͊O�Ƃ���
		if ( x < 0 || y < 0 ||
			 x >= g_->nWindowWidth || y >= g_->nWindowHeight )
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
	if ( g_->mouse->IsOnDownRightButton() ){

		//	�E�C���h�E�͈̔͊O�Ȃ�C�x���g�͈͊O�Ƃ���
		if ( x < 0 || y < 0 ||
			 x >= g_->nWindowWidth || y >= g_->nWindowHeight )
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
	if ( g_->mouse->IsOnUpCenterButton() ){
		//CScreenBase::OnCButtonUp(x,y);
		_P->OnCButtonUp(x,y);
		ret = true;
	}

	//	���{�^���𗣂���
	if ( g_->mouse->IsOnUpLeftButton() ){
		//CScreenBase::OnLButtonUp(x,y);
		_P->OnLButtonUp(x,y);
		ret = true;
	}

	//	�E�{�^���𗣂���
	if ( g_->mouse->IsOnUpRightButton() ){
		//CScreenBase::OnRButtonUp(x,y);
		_P->OnRButtonUp(x,y);
		ret = true;
	}

	return ret;
}