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
protected:

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglMouseInput();
	virtual ~CMglMouseInput();

	LONG GetXMoveCount(){ return CMglMouseInputBase::GetStateBuf()->lX; }
	LONG GetYMoveCount(){ return CMglMouseInputBase::GetStateBuf()->lY; }
	LONG GetZMoveCount(){ return CMglMouseInputBase::GetStateBuf()->lZ; }
	LONG GetWheelMoveCount(){ return CMglMouseInputBase::GetStateBuf()->lZ; }
	//LONG GetWheelCount(){ return CMglMouseInputBase::GetStateBuf()->lZ; }

	BOOL IsPressLeftButton(){ return IsPressButton(0); }
	BOOL IsPressRightButton(){ return IsPressButton(1); }
	BOOL IsPressCenterButton(){ return IsPressButton(2); }

	BOOL IsPressButton(int nButtonIndex){
		if ( nButtonIndex > 7 )
			MyuThrow(77, "CMglMouseInput::IsPressButton() �w��\�ȃ{�^���C���f�b�N�X��0����7�͈̔͂ł��B" );

		if( CMglMouseInputBase::GetStateBuf()->rgbButtons[nButtonIndex] ) 
			return TRUE;
		else
			return FALSE;
	}

	POINT GetCursorPos();
	LONG GetCursorPosX(){ return GetCursorPos().x; }
	LONG GetCursorPosY(){ return GetCursorPos().y; }
};


#endif//__MglMouseInput_H__