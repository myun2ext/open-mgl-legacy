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


//	コアの基底クラス
class CAugustKeyboardCore : public agh::CKeyboardCoreBase
{
public:
	virtual bool IsOnKeyEvt(agh::KB_EVTTYPE_t evtType, agh::KEYCODE_t keyCode)
	{
		switch(evtType)
		{
		//	押されている間
		case AGH_KB_EVT_HANDLER_EVTTYPE_ON_PRESS:
			break;

		//	キーボードが押された瞬間
		case AGH_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN:
			break;

		//	キーボードが話された瞬間
		case AGH_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP:
			break;
		}

		return false;
	}
};

///////////////////////////////////////////////////////////////////////////

//	コンストラクタ
CAugustKeyboardInput::CAugustKeyboardInput()
{
	m_pCore = new CAugustKeyboardCore();
}

//	デストラクタ
CAugustKeyboardInput::~CAugustKeyboardInput()
{
	delete m_pCore;
}




