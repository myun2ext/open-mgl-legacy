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
	if ( this->m_hWnd == NULL )
		MyuThrow(0, "CMglMouseInput::GetCursorPos()  m_hWnd ��NULL�ł��B" );

	POINT point;
	if ( ::GetCursorPos( &point ) != TRUE )
		MyuThrow(0, "GetCursorPos() �Ɏ��s" );
	if ( ::ScreenToClient( this->m_hWnd, &point) != TRUE )
		MyuThrow(0, "ScreenToClient() �Ɏ��s" );
	return point;
}
