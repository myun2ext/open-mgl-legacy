//////////////////////////////////////////////////////////
//
//	AugustKeyboardInput
//
//////////////////////////////////////////////////////////

#ifndef __AugustKeyboardInput_H__
#define __AugustKeyboardInput_H__

#include "agh.h"

//////////////////////////////////////////////////////////////////////////////////////

//	�L�[�{�[�h�C�x���g�n���h���n

#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_PRESS		(1)	//	������Ă����
#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN	(2)	//	�L�[�{�[�h�������ꂽ�u��
#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP		(3)	//	�L�[�{�[�h�������ꂽ�u��
/*#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_DOWNUP	(8)	//	��������b�����i�N���b�N�I�ȁj
#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_PUSH		(MGL_KB_EVT_HANDLER_EVTTYPE_ON_DOWNUP)*/

//	�L�[�{�[�h�C�x���g�n���h���\����
class CAugustKeyboardInput;
typedef bool (CAugustKeyboardInput::*AUGUST_KB_EVT_HANDLER_CALLBACK)();
typedef struct {
	AUGUST_KB_EVT_HANDLER_CALLBACK pCallbackFunc;
	BYTE keyCode;
	short evtType;
} AUGUST_KB_EVT_HANDLER;
typedef list<AUGUST_KB_EVT_HANDLER> t_AUGUST_KB_EVT_HANDLERS;

class CMglKeyboardInput;

/////////////////////////////////////////////////////////////////////////

//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CAugustKeyboardInput : public agh::CControlBase
{
protected:
	CMglInput *m_pInput;			//	Alias

	//list<bool (*)()> m_kbEventHandlers;	//	�{����vector_list�g���l�E�E�E
	//list<MGL_KB_EVT_HANDLER_CALLBACK> m_kbEventHandlers;	//	�{����vector_list�g���l�E�E�E
	list<AUGUST_KB_EVT_HANDLER> m_kbEventHandlers;	//	�{����vector_list�g���l�E�E�E

	/////////////////////////////////////////////////////////

_AGH_EVENT_ACCESS_MODIFIER:
	///// �I�[�o�[���C�h�\�ȃC�x���g /////////////////////////////////////////////////

	/**
	  �����ɂ����� OnControl, OnBackground �͉��Ɉړ����Ƃ�����B
	**/
	virtual bool DoFrame();

public:
	//	�R���X�g���N�^
	//	�R���X�g���N�^
	CAugustKeyboardInput(){}
	virtual ~CAugustKeyboardInput(){}

	//////////////////////////////////////////////////////

	//	�L�[�{�[�h�n���h���̓o�^
	void RegistKbHandler(AUGUST_KB_EVT_HANDLER &evt){
		m_kbEventHandlers.push_back(evt);
	}
	void RegistKbHandler(
		short evtType,
		BYTE keyCode,		
		AUGUST_KB_EVT_HANDLER_CALLBACK pCallbackFunc)
	{
		AUGUST_KB_EVT_HANDLER evt;
		evt.pCallbackFunc = pCallbackFunc;
		evt.keyCode = keyCode;
		evt.evtType = evtType;
		m_kbEventHandlers.push_back(evt);
	}
};


#endif//__AugustKeyboardInput_H__
