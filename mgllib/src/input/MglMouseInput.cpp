#include "stdafx.h"
#include "MglMouseInput.h"

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
