#include "stdafx.h"
#include "MglMouseInput.h"

const int CMglMouseInput::RGB_BUTTON_OFFSET = 12;

//	コンストラクタ
CMglMouseInput::CMglMouseInput()
{

}

//	デストラクタ
CMglMouseInput::~CMglMouseInput()
{

}

POINT CMglMouseInput::GetCursorPos()
{
	POINT point;
	::GetCursorPos( &point );
	ScreenToClient( this->m_hWnd, &point);
	return point;
}
