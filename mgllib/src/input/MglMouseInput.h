//////////////////////////////////////////////////////////
//
//	MglMouseInput - �}�E�X���̓N���X
//
//////////////////////////////////////////////////////////

#ifndef __MglMouseInput_H__
#define __MglMouseInput_H__

#include "MglMouseInputBase.h"

//	�N���X�錾
class DLL_EXP CMglMouseInput : public CMglMouseInputBase
{
public:
	static const int RGB_BUTTON_OFFSET;
protected:

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglMouseInput();
	virtual ~CMglMouseInput();

	//	�ړ��J�E���g
	LONG GetXMoveCount(){ return CMglMouseInputBase::GetStateBuf()->lX; }
	LONG GetYMoveCount(){ return CMglMouseInputBase::GetStateBuf()->lY; }
	LONG GetZMoveCount(){ return CMglMouseInputBase::GetStateBuf()->lZ; }
	LONG GetWheelMoveCount(){ return CMglMouseInputBase::GetStateBuf()->lZ; }
	//LONG GetWheelCount(){ return CMglMouseInputBase::GetStateBuf()->lZ; }

	////////////////////////////////////////////////////////////////////////////

	//	�{�^����������Ă��邩
	BOOL IsPressLeftButton(){ return IsPressButton(0); }
	BOOL IsPressRightButton(){ return IsPressButton(1); }
	BOOL IsPressCenterButton(){ return IsPressButton(2); }

	BOOL IsPressButton(int nButtonIndex){
		if ( nButtonIndex > 7 )
			MyuThrow(MGLMSGNO_INPUT_MOUSE(80),
			"CMglMouseInput::IsPressButton() �w��\�ȃ{�^���C���f�b�N�X��0����7�͈̔͂ł��B" );

		if( CMglMouseInputBase::GetStateBuf()->rgbButtons[nButtonIndex] ) 
			return TRUE;
		else
			return FALSE;
	}

	/////////////////////////////////////////////////////////////////////

	//	�{�^���������ꂽ���i�C�x���g�j
	BOOL IsOnDownLeftButton(){ return IsOnDownButton(0); }
	BOOL IsOnDownRightButton(){ return IsOnDownButton(1); }
	BOOL IsOnDownCenterButton(){ return IsOnDownButton(2); }

	BOOL IsOnDownButton(int nButtonIndex){
		if ( nButtonIndex > 7 )
			MyuThrow(MGLMSGNO_INPUT_MOUSE(81),
			"CMglMouseInput::IsOnDownButton() �w��\�ȃ{�^���C���f�b�N�X��0����7�͈̔͂ł��B" );

		/*if( CMglMouseInputBase::GetStateBuf()->rgbButtons[nButtonIndex] -
			CMglMouseInputBase::GetOldStateBuf()->rgbButtons[nButtonIndex] )*/
		if( CMglMouseInputBase::GetStateChanged(RGB_BUTTON_OFFSET+nButtonIndex) > 0 ) 
			return TRUE;
		else
			return FALSE;
	}

	/////////////////////////////////////////////////////////////////////

	//	�{�^���������ꂽ���i�C�x���g�j
	BOOL IsOnUpLeftButton(){ return IsOnUpButton(0); }
	BOOL IsOnUpRightButton(){ return IsOnUpButton(1); }
	BOOL IsOnUpCenterButton(){ return IsOnUpButton(2); }

	BOOL IsOnUpButton(int nButtonIndex){
		if ( nButtonIndex > 7 )
			MyuThrow(MGLMSGNO_INPUT_MOUSE(82),
			"CMglMouseInput::IsOnUpButton() �w��\�ȃ{�^���C���f�b�N�X��0����7�͈̔͂ł��B" );

		/*if( CMglMouseInputBase::GetStateBuf()->rgbButtons[nButtonIndex] -
			CMglMouseInputBase::GetOldStateBuf()->rgbButtons[nButtonIndex] )*/
		if( CMglMouseInputBase::GetStateChanged(RGB_BUTTON_OFFSET+nButtonIndex) < 0 ) 
			return TRUE;
		else
			return FALSE;
	}

	//////////////////////////////////////////////

	POINT GetCursorPos();
	LONG GetCursorPosX(){ return GetCursorPos().x; }
	LONG GetCursorPosY(){ return GetCursorPos().y; }
};


#endif//__MglMouseInput_H__