//////////////////////////////////////////////////////////
//
//	AugustKeyboardInput
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustKeyboardInput.h"

using namespace agh;
using namespace std;

class DLL_EXP agh::CControlBase;


//	�R�A�̊��N���X
class CAugustKeyboardCore : public agh::CKeyboardCoreBase
{
public:
	virtual bool IsOnKeyEvt(agh::KB_EVTTYPE_t evtType, agh::KEYCODE_t keyCode)
	{
		switch(evtType)
		{
		//	������Ă����
		case AGH_KB_EVT_HANDLER_EVTTYPE_ON_PRESS:
			break;

		//	�L�[�{�[�h�������ꂽ�u��
		case AGH_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN:
			break;

		//	�L�[�{�[�h���b���ꂽ�u��
		case AGH_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP:
			break;
		}

		return false;
	}
};

///////////////////////////////////////////////////////////////////////////

//	�R���X�g���N�^
CAugustKeyboardInput::CAugustKeyboardInput()
{
	m_pCore = new CAugustKeyboardCore();
}

//	�f�X�g���N�^
CAugustKeyboardInput::~CAugustKeyboardInput()
{
	delete m_pCore;
}




