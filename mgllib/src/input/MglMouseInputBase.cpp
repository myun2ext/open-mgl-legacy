#include "stdafx.h"
#include "MglMouseInputBase.h"

//	�R���X�g���N�^
CMglMouseInputBase::CMglMouseInputBase()
{

}

//	�f�X�g���N�^
CMglMouseInputBase::~CMglMouseInputBase()
{

}

//	������
void CMglMouseInputBase::Init( HWND hWnd, DWORD dwCooperativeFlag )
{
	CMglDirectInputDeviceBase::Init(
		GUID_SysMouse, &c_dfDIMouse2, sizeof(DIMOUSESTATE2),
		hWnd, dwCooperativeFlag );
}
