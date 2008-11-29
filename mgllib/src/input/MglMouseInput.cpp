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
	if ( this->m_hWnd == NULL )
		MyuThrow(0, "CMglMouseInput::GetCursorPos()  m_hWnd がNULLです。" );

	POINT point;
	if ( ::GetCursorPos( &point ) != TRUE )
		MyuThrow(0, "GetCursorPos() に失敗" );
	if ( ::ScreenToClient( this->m_hWnd, &point) != TRUE )
		MyuThrow(0, "ScreenToClient() に失敗" );
	return point;
}
