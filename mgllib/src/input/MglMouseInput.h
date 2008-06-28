//////////////////////////////////////////////////////////
//
//	MglMouseInput - マウス入力クラス
//
//////////////////////////////////////////////////////////

#ifndef __MglMouseInput_H__
#define __MglMouseInput_H__

#include "MglMouseInputBase.h"

//	クラス宣言
class DLL_EXP CMglMouseInput : public CMglMouseInputBase
{
protected:

public:
	//	コンストラクタ・デストラクタ
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
			MyuThrow(77, "CMglMouseInput::IsPressButton() 指定可能なボタンインデックスは0から7の範囲です。" );

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