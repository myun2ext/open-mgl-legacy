#include "stdafx.h"
#include "MglMouseInput.h"

const int CMglMouseInput::RGB_BUTTON_OFFSET = 12;

//	�R���X�g���N�^
CMglMouseInput::CMglMouseInput()
{

}

//	�f�X�g���N�^
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
