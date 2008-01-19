#include "stdafx.h"
#include "MglMouseInputBase.h"

//	コンストラクタ
CMglMouseInputBase::CMglMouseInputBase()
{

}

//	デストラクタ
CMglMouseInputBase::~CMglMouseInputBase()
{

}

//	初期化
void CMglMouseInputBase::Init( HWND hWnd, DWORD dwCooperativeFlag )
{
	CMglDirectInputDeviceBase::Init(
		GUID_SysMouse, &c_dfDIMouse2, sizeof(DIMOUSESTATE2),
		hWnd, dwCooperativeFlag );
}
