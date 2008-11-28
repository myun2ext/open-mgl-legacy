#include "stdafx.h"
#include "MglKeyboardInputBase.h"

#define PRESSKEY(DIK_CODE)	(DIK_CODE & 0x80)

//	������
void CMglKeyboardInputBase::Init( HWND hWnd, DWORD dwCooperativeFlag )
{
	CMglDirectInputDeviceBase::Init(
		GUID_SysKeyboard, &c_dfDIKeyboard, KB_STATEBUF_SIZE,
		hWnd, dwCooperativeFlag );
}

//	������Ă�[�H
BOOL CMglKeyboardInputBase::IsPressKey( BYTE keyCode )
{
	//if( PRESSKEY(m_stateBuf[keyCode]) ) 
	if( PRESSKEY(m_pStateBuf[keyCode]) ) 
		return TRUE;
	else
		return FALSE;
}
