//////////////////////////////////////////////////////////
//
//	AugustSound
//
//////////////////////////////////////////////////////////

#ifndef __AugustSound_H__
#define __AugustSound_H__

#include "agh.h"

//////////////////////////////////////////////////////////////////////////////////////

//	�L�[�{�[�h�C�x���g�n���h���n

#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_PRESS		(1)	//	������Ă����
#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN	(2)	//	�L�[�{�[�h�������ꂽ�u��
#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP		(3)	//	�L�[�{�[�h�������ꂽ�u��
/*#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_DOWNUP	(8)	//	��������b�����i�N���b�N�I�ȁj
#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_PUSH		(MGL_KB_EVT_HANDLER_EVTTYPE_ON_DOWNUP)*/

//	�L�[�{�[�h�C�x���g�n���h���\����
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

//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CAugustSound : public agh::CControlBase
{
protected:
	CMglMouseInput *m_pMouse;

	//list<bool (*)()> m_kbEventHandlers;	//	�{����vector_list�g���l�E�E�E
	//list<MGL_KB_EVT_HANDLER_CALLBACK> m_kbEventHandlers;	//	�{����vector_list�g���l�E�E�E
	list<AUGUST_KB_EVT_HANDLER> m_kbEventHandlers;	//	�{����vector_list�g���l�E�E�E

	/////////////////////////////////////////////////////////

	POINT m_nCachedCurPos;
	int m_nCachedCurPosX;
	int m_nCachedCurPosY;
	bool m_bUseMouseHandle;

	agh::_AGH_POINT GetCurPos(){
		return *((agh::_AGH_POINT*)&m_nCachedCurPos);
	}

_AGH_EVENT_ACCESS_MODIFIER:
	///// �I�[�o�[���C�h�\�ȃC�x���g /////////////////////////////////////////////////

	/**
	  �����ɂ����� OnControl, OnBackground �͉��Ɉړ����Ƃ�����B
	**/
	virtual bool DoFrame();

protected:

private:
	//	�Ȃ��Public�H�iPrivate�ł͂Ȃ��̂��E�E�E�H�j
	//void OnLButtonDown(int x, int y);

	//void ScreenUpdate();

public:
	//	�R���X�g���N�^
	/*CAugustSound(CAugustGlobalCommon &g_in) : g_(g_in),
		m_mouse(g_in.input.mouse), m_grp(g_in.grp), m_input(g_in.input), m_audio(g_in.audio),
		m_imgCache(g_in.imgCache)
	{
		//m_hWnd = NULL;
		m_rgbBackground = D3DCOLOR_WHITE;
	}*/
	//	�R���X�g���N�^
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

	void EnableMouseHandle(){ m_bUseMouseHandle = true; }
	void DisableMouseHandle(){ m_bUseMouseHandle = false; }

public:
	//bool OnFrameMouseInput(); <- �Ȃ�public�Ȃ̂ɗ��R����̂��ȁE�E�E�H
};


#endif//__AugustSound_H__
