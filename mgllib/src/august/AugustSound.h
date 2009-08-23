//////////////////////////////////////////////////////////
//
//	AugustSound
//
//////////////////////////////////////////////////////////

#ifndef __AugustSound_H__
#define __AugustSound_H__

#include "agh.h"

//////////////////////////////////////////////////////////////////////////////////////

//	キーボードイベントハンドラ系

#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_PRESS		(1)	//	押されている間
#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN	(2)	//	キーボードが押された瞬間
#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP		(3)	//	キーボードが離された瞬間
/*#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_DOWNUP	(8)	//	押した後話した（クリック的な）
#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_PUSH		(MGL_KB_EVT_HANDLER_EVTTYPE_ON_DOWNUP)*/

//	キーボードイベントハンドラ構造体
class CAugustSound;
typedef bool (CAugustSound::*AUGUST_KB_EVT_HANDLER_CALLBACK)();
typedef struct {
	AUGUST_KB_EVT_HANDLER_CALLBACK pCallbackFunc;
	BYTE keyCode;
	short evtType;
} AUGUST_KB_EVT_HANDLER;
typedef list<AUGUST_KB_EVT_HANDLER> t_AUGUST_KB_EVT_HANDLERS;

class CMglMouseInput;

/////////////////////////////////////////////////////////////////////////

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CAugustSound : public agh::CControlBase
{
protected:
	CMglMouseInput *m_pMouse;

	//list<bool (*)()> m_kbEventHandlers;	//	本当はvector_list使うネ・・・
	//list<MGL_KB_EVT_HANDLER_CALLBACK> m_kbEventHandlers;	//	本当はvector_list使うネ・・・
	list<AUGUST_KB_EVT_HANDLER> m_kbEventHandlers;	//	本当はvector_list使うネ・・・

	/////////////////////////////////////////////////////////

	POINT m_nCachedCurPos;
	int m_nCachedCurPosX;
	int m_nCachedCurPosY;
	bool m_bUseMouseHandle;

	agh::_AGH_POINT GetCurPos(){
		return *((agh::_AGH_POINT*)&m_nCachedCurPos);
	}

_AGH_EVENT_ACCESS_MODIFIER:
	///// オーバーライド可能なイベント /////////////////////////////////////////////////

	/**
	  ここにあった OnControl, OnBackground は下に移動しといたよ。
	**/
	virtual bool DoFrame();

protected:

private:
	//	なんでPublic？（Privateではないのか・・・？）
	//void OnLButtonDown(int x, int y);

	//void ScreenUpdate();

public:
	//	コンストラクタ
	/*CAugustSound(CAugustGlobalCommon &g_in) : g_(g_in),
		m_mouse(g_in.input.mouse), m_grp(g_in.grp), m_input(g_in.input), m_audio(g_in.audio),
		m_imgCache(g_in.imgCache)
	{
		//m_hWnd = NULL;
		m_rgbBackground = D3DCOLOR_WHITE;
	}*/
	//	コンストラクタ
	CAugustSound()
	{
		//m_hWnd = NULL;
		ZeroMemory(&m_nCachedCurPos, sizeof(m_nCachedCurPos));
		m_nCachedCurPosX = -1;
		m_nCachedCurPosY = -1;
		m_bUseMouseHandle = false;
	}
	virtual ~CAugustSound(){}

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

	void EnableMouseHandle(){ m_bUseMouseHandle = true; }
	void DisableMouseHandle(){ m_bUseMouseHandle = false; }

public:
	//bool OnFrameMouseInput(); <- なんかpublicなのに理由あんのかな・・・？
};


#endif//__AugustSound_H__
