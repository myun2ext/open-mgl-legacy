//////////////////////////////////////////////////////////
//
//	AugustKeyboardInput
//
//////////////////////////////////////////////////////////

#ifndef __AugustKeyboardInput_H__
#define __AugustKeyboardInput_H__

#include "agh.h"

//////////////////////////////////////////////////////////////////////////////////////

//	キーボードイベントハンドラ系

#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_PRESS		(1)	//	押されている間
#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN	(2)	//	キーボードが押された瞬間
#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP		(3)	//	キーボードが離された瞬間
/*#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_DOWNUP	(8)	//	押した後話した（クリック的な）
#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_PUSH		(MGL_KB_EVT_HANDLER_EVTTYPE_ON_DOWNUP)*/

//	キーボードイベントハンドラ構造体
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

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CAugustKeyboardInput : public agh::CControlBase
{
protected:
	CMglInput *m_pInput;			//	Alias

	//list<bool (*)()> m_kbEventHandlers;	//	本当はvector_list使うネ・・・
	//list<MGL_KB_EVT_HANDLER_CALLBACK> m_kbEventHandlers;	//	本当はvector_list使うネ・・・
	list<AUGUST_KB_EVT_HANDLER> m_kbEventHandlers;	//	本当はvector_list使うネ・・・

	/////////////////////////////////////////////////////////

_AGH_EVENT_ACCESS_MODIFIER:
	///// オーバーライド可能なイベント /////////////////////////////////////////////////

	/**
	  ここにあった OnControl, OnBackground は下に移動しといたよ。
	**/
	virtual bool DoFrame();

public:
	//	コンストラクタ
	//	コンストラクタ
	CAugustKeyboardInput(){}
	virtual ~CAugustKeyboardInput(){}

	//////////////////////////////////////////////////////

	//	キーボードハンドラの登録
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
