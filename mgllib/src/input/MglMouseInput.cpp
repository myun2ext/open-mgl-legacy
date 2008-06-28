#include "stdafx.h"
#include "MglMouseInput.h"

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
