//////////////////////////////////////////////////////////
//
//	AugustMouseInput
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustMouseInput.h"
#include "MglInput.h"

using namespace agh;
using namespace std;

class DLL_EXP agh::CControlBase;

///////////////////////////////////////////////////////////////

#define AUGUST_KEYCODE_TABLE_SIZE	(256)

//#define PRESSKEY(DIK_CODE)	(DIK_CODE & 0x80)

//	�R�A�̊��N���X
class CAugustMouseCore : public agh::CMouseCoreBase
{
protected:
	CMglMouseInput m_mouse;

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CAugustMouseCore(){}
	virtual ~CAugustMouseCore(){}

	/* override */
	virtual _AGH_POINT IsOnMouseEvt(agh::MOUSE_EVTTYPE_t evtType, agh::MOUSECODE_t mouseCode)
	{
		BOOL isOnEvt = FALSE;
		switch(evtType)
		{
		//	������Ă����
		case AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_PRESS:
			isOnEvt = m_mouse.IsPressButton(mouseCode - 0x11);
			break;

		//	�����ꂽ�u��
		case AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_KEYDOWN:
			isOnEvt = m_mouse.IsOnDownButton(mouseCode - 0x11);
			break;

		//	�����ꂽ�u��
		case AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_KEYUP:
			isOnEvt = m_mouse.IsOnUpButton(mouseCode - 0x11);
			break;
		}

		if ( isOnEvt )
			return GetCursorPos();
		else
			return _AGH_POINT(INVALID_POINT, INVALID_POINT);
	}
	
	virtual _AGH_POINT GetCursorPos(){
		POINT point = m_mouse.GetCursorPos();
		return _AGH_POINT(point.x, point.y);
	}

	//	������
	void Init(HWND hWnd)
	{
		m_mouse.Init(hWnd);
	}
};

////////////////////////////////////////////////////////////////////////

//	�R���X�g���N�^
CAugustMouseInput::CAugustMouseInput()
{
	m_pCore = new CAugustMouseCore();
}

//	�f�X�g���N�^
CAugustMouseInput::~CAugustMouseInput()
{
	delete m_pCore;
}

void CAugustMouseInput::OnRegist()
{
	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_ROOT_WINDOW_HWND),
		"CAugustMouseInput::Init()  �E�C���h�E�n���h���̎擾�Ɏ��s");

	((CAugustMouseCore*)m_pCore)->Init(hWnd);
}


