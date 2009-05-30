//////////////////////////////////////////////////////////
//
//	AugustKeyboardInput
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustKeyboardInput.h"

using namespace agh;
using namespace std;

class DLL_EXP agh::CControlBase;

/*
//	コンストラクタ
CAugustKeyboardInput::CAugustKeyboardInput()
{
}

//	デストラクタ
CAugustKeyboardInput::~CAugustKeyboardInput()
{
}
*/


//////////////////////////////////////////////////

bool CAugustKeyboardInput::OnFrame()
{
	t_AUGUST_KB_EVT_HANDLERS::iterator it=m_kbEventHandlers.begin();
	for(; it!=m_kbEventHandlers.end(); it++)
	{
		AUGUST_KB_EVT_HANDLER &r = *it;

		switch(r.evtType)
		{
		case AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_PRESS:
			if ( g_->pInput->IsPressKey(r.keyCode) )
				if ( (this->*r.pCallbackFunc)() != true )
					return false;
			break;

		case AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN:
			if ( g_->pInput->IsOnDownKey(r.keyCode) )
				if ( (this->*r.pCallbackFunc)() != true )
					return false;
			break;

		case AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP:
			if ( g_->pInput->IsOnUpKey(r.keyCode) )
				if ( (this->*r.pCallbackFunc)() != true )
					return false;
			break;
		}
	}

	return true;
}

