//////////////////////////////////////////////////////////
//
//	AugustScreen2
//
//////////////////////////////////////////////////////////

#ifndef __AugustScreen2_H__
#define __AugustScreen2_H__

#include "AugustWindow2.h"
#include "AugustGraphicsManager.h"

//////////////////////////////////////////////////////////////////////////////////////

class CMyuFPS;

class DLL_EXP CAugustFpsManager : public agh::CControlBase
{
protected:
	CMyuFPS* m_pInternal;
public:
	CAugustFpsManager();
	virtual ~CAugustFpsManager();

	void DoWait();
	void SetFps(int nFps);
	float GetAveFps();
	float GetFps();
};

//////////////////////////////////////////////////////////////////////////////////////

//	�L�[�{�[�h�C�x���g�n���h���n

#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_PRESS		(1)	//	������Ă����
#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN	(2)	//	�L�[�{�[�h�������ꂽ�u��
#define AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP		(3)	//	�L�[�{�[�h�������ꂽ�u��
/*#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_DOWNUP	(8)	//	��������b�����i�N���b�N�I�ȁj
#define MGL_KB_EVT_HANDLER_EVTTYPE_ON_PUSH		(MGL_KB_EVT_HANDLER_EVTTYPE_ON_DOWNUP)*/

//	�L�[�{�[�h�C�x���g�n���h���\����
class CAugustScreen2;
typedef bool (CAugustScreen2::*AUGUST_KB_EVT_HANDLER_CALLBACK)();
typedef struct {
	AUGUST_KB_EVT_HANDLER_CALLBACK pCallbackFunc;
	BYTE keyCode;
	short evtType;
} AUGUST_KB_EVT_HANDLER;
typedef list<AUGUST_KB_EVT_HANDLER> t_AUGUST_KB_EVT_HANDLERS;

/////////////////////////////////////////////////////////////////////////

class _AGST_DLL_EXP CMwlAghWindow;
class _AGST_DLL_EXP CMyuThreadBase;
class _AGST_DLL_EXP agh::CScreenBase;

//	�N���X�錾  /////////////////////////////////////////////////////////
//class DLL_EXP CAugustScreen2 : public CAugustWindow2, public CMyuThreadBase
class DLL_EXP CAugustScreen2 : public CMwlAghWindow, public CMyuThreadBase
{
private:
	//typedef CAugustWindow2 _BASE;
	typedef CMwlAghWindow _BASE;
	typedef CMyuThreadBase _THREAD_BASE;
protected:
	CAugustGraphicsManager m_grp;
	CAugustFpsManager m_fps;
	/*CMglInput *m_input;			//	Alias
	CMglMouseInput *m_mouse;	//	Alias
	CMglAudio *m_audio;			//	Alias*/

	//	2008/11/26 Add. �f�t�H���g�̃C���[�W�z��
	//list<bool (*)()> m_kbEventHandlers;	//	�{����vector_list�g���l�E�E�E
	//list<MGL_KB_EVT_HANDLER_CALLBACK> m_kbEventHandlers;	//	�{����vector_list�g���l�E�E�E
	list<AUGUST_KB_EVT_HANDLER> m_kbEventHandlers;	//	�{����vector_list�g���l�E�E�E

	/////////////////////////////////////////////////////////

	//HWND m_hWnd;
	POINT m_nCachedCurPos;
	int m_nCachedCurPosX;
	int m_nCachedCurPosY;
	bool m_bUseMouseHandle;
	bool m_bEndFlg;

	agh::_AGH_POINT GetCurPos(){
		return *((agh::_AGH_POINT*)&m_nCachedCurPos);
	}

_AGH_EVENT_ACCESS_MODIFIER:
	///// �I�[�o�[���C�h�\�ȃC�x���g /////////////////////////////////////////////////

	/**
	  �����ɂ����� OnControl, OnBackground �͉��Ɉړ����Ƃ�����B
	**/

	virtual void OnDraw();
	virtual bool DoFrame();
	virtual bool OnClose();

	//	���̃N���X����
	virtual bool OnFrameDoUser(){return true;}
	//virtual bool OnFrameKeyboardInput();
	//virtual bool OnFrameMouseInput();

	virtual bool OnInitFirst(){ return true; }	//	false��Ԃ��ƃv���O�����I��
	virtual bool OnGraphicInitEnded(){ return true; }	//	false��Ԃ��ƃv���O�����I��
	virtual void MainLoop();

protected:
	BOOL DoFpsWait();

private:
	//	�Ȃ��Public�H�iPrivate�ł͂Ȃ��̂��E�E�E�H�j
	//void OnLButtonDown(int x, int y);

	//void ScreenUpdate();

public:
	//	�R���X�g���N�^
	/*CAugustScreen2(CAugustGlobalCommon &g_in) : g_(g_in),
		m_mouse(g_in.input.mouse), m_grp(g_in.grp), m_input(g_in.input), m_audio(g_in.audio),
		m_imgCache(g_in.imgCache)
	{
		//m_hWnd = NULL;
		m_rgbBackground = D3DCOLOR_WHITE;
	}*/
	//	�R���X�g���N�^
	CAugustScreen2()
	{
		m_bEndFlg = false;

		//m_hWnd = NULL;
		ZeroMemory(&m_nCachedCurPos, sizeof(m_nCachedCurPos));
		m_nCachedCurPosX = -1;
		m_nCachedCurPosY = -1;
		m_bUseMouseHandle = false;
	}
	virtual ~CAugustScreen2(){}

	/////////////////////////////////////////////////////////////////////////

	virtual void OnCreatedWindow(){
		_THREAD_BASE::StartThread();
	}
	bool ThreadFunc();

	///// �R���g���[���̓o�^ /////////////////////////////////////////////////

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



	/*virtual void OnBackgroundLButtonDown(int x, int y){}
	virtual void OnBackgroundRButtonDown(int x, int y){}
	virtual void OnBackgroundCButtonDown(int x, int y){}
	virtual void OnControlLButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnControlRButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnControlCButtonDown(agh::CControlBase *pControl, int x, int y){}

	//	���N���b�N�n : Left Click Events
	virtual void OnLButtonClick(agh::CControlBase *pControl, int x, int y){}
	virtual void OnLButtonDblClk(agh::CControlBase *pControl, int x, int y){}
	virtual void OnLButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnLButtonUp(agh::CControlBase *pControl, int x, int y){}

	//	�E�N���b�N�n : Right Click Events
	virtual void OnRButtonClick(agh::CControlBase *pControl, int x, int y){}
	virtual void OnRButtonDblClk(agh::CControlBase *pControl, int x, int y){}
	virtual void OnRButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnRButtonUp(agh::CControlBase *pControl, int x, int y){}

	//	�}�E�X�ړ� : Move Mouse Events
	virtual void OnMouseMove(agh::CControlBase *pControl, int nPosX, int nPosY, int nMoveX, int nMoveY){}

	//	�z�C�[�� : Wheel Events
	virtual void OnWheelUp(agh::CControlBase *pControl, int count){}
	virtual void OnWheelDown(agh::CControlBase *pControl, int count){}
	virtual void OnCButtonClick(agh::CControlBase *pControl, int x, int y){}
	virtual void OnCButtonDblClk(agh::CControlBase *pControl, int x, int y){}
	virtual void OnCButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnCButtonUp(agh::CControlBase *pControl, int x, int y){}
	virtual void OnMButtonClick(agh::CControlBase *pControl, int x, int y){}
	virtual void OnMButtonDblClk(agh::CControlBase *pControl, int x, int y){}
	virtual void OnMButtonDown(agh::CControlBase *pControl, int x, int y){}
	virtual void OnMButtonUp(agh::CControlBase *pControl, int x, int y){}*/

	/*
	//	���N���b�N�n : Left Click Events
	virtual void OnBackgroundLButtonClick(int x, int y){}
	virtual void OnBackgroundLButtonDblClk(int x, int y){}
	virtual void OnBackgroundLButtonDown(int x, int y){}
	virtual void OnBackgroundLButtonUp(int x, int y){}

	//	�E�N���b�N�n : Right Click Events
	virtual void OnBackgroundRButtonClick(int x, int y){}
	virtual void OnBackgroundRButtonDblClk(int x, int y){}
	virtual void OnBackgroundRButtonDown(int x, int y){}
	virtual void OnBackgroundRButtonUp(int x, int y){}

	//	�}�E�X�ړ� : Move Mouse Events
	virtual void OnBackgroundMouseMove(int nPosX, int nPosY, int nMoveX, int nMoveY){}

	//	�z�C�[�� : Wheel Events
	virtual void OnBackgroundWheelUp(int count){}
	virtual void OnBackgroundWheelDown(int count){}
	virtual void OnBackgroundCButtonClick(int x, int y){}
	virtual void OnBackgroundCButtonDblClk(int x, int y){}
	virtual void OnBackgroundCButtonDown(int x, int y){}
	virtual void OnBackgroundCButtonUp(int x, int y){}
	virtual void OnBackgroundMButtonClick(int x, int y){}
	virtual void OnBackgroundMButtonDblClk(int x, int y){}
	virtual void OnBackgroundMButtonDown(int x, int y){}
	virtual void OnBackgroundMButtonUp(int x, int y){}
	*/

#endif//__AugustScreen2_H__
