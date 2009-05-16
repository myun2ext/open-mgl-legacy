//////////////////////////////////////////////////////////
//
//	AugustScreen2
//
//////////////////////////////////////////////////////////

#ifndef __AugustScreen2_H__
#define __AugustScreen2_H__

#include "AugustWindow2.h"
#include "AugustGraphicsManager.h"
#include "MwlMxpThreadBase.h"

//////////////////////////////////////////////////////////////////////////////////////

class CMyuFPS;

class _AGST_DLL_EXP CAugustFpsManager : public agh::CControlBase
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

/////////////////////////////////////////////////////////////////////////

#define _CAugustScreen2_THREAD_BASE CMwlMxpThreadBase
//#define _CAugustScreen2_WINDOW_BASE CMwlAghWindow
#define _CAugustScreen2_WINDOW_BASE CAugustWindow2

class _CAugustScreen2_THREAD_BASE;
class _CAugustScreen2_WINDOW_BASE;
class agh::CScreenBase;

//	クラス宣言  /////////////////////////////////////////////////////////
//class DLL_EXP CAugustScreen2 : public CAugustWindow2, public CMyuThreadBase
class CAugustScreen2 : public _CAugustScreen2_WINDOW_BASE, public _CAugustScreen2_THREAD_BASE
{
private:
	//typedef CAugustWindow2 _BASE;
	typedef _CAugustScreen2_WINDOW_BASE _BASE, _WIN_BASE, _WINDOW_BASE;
	typedef _CAugustScreen2_THREAD_BASE _THREAD_BASE;

protected:
	CAugustGraphicsManager m_grp;	//	Control
	CAugustFpsManager m_fps;		//	Control
	void* m_vphWnd;

	/*CMglInput *m_input;			//	Alias
	CMglMouseInput *m_mouse;		//	Alias
	CMglAudio *m_audio;				//	Alias*/

	/////////////////////////////////////////////////////////

	//HWND m_hWnd;
	bool m_bUseMouseHandle;
	bool m_bEndFlg;

protected:
	bool _AGST_DLL_EXP DoFpsWait();
	bool _AGST_DLL_EXP ThreadFunc(int anyParam);	//	From mxp::CThreadBase overrided

_AGH_EVENT_ACCESS_MODIFIER:
	///// オーバーライド可能なイベント /////////////////////////////////////////////////

	/**
	  ここにあった OnControl, OnBackground は下に移動しといたよ。
	**/

	virtual _AGST_DLL_EXP void OnDraw();
	virtual _AGST_DLL_EXP bool DoFrame();
	virtual _AGST_DLL_EXP bool OnClose();

	//	このクラスから
	virtual bool OnFrameDoUser(){return true;}
	//virtual bool OnFrameKeyboardInput();
	//virtual bool OnFrameMouseInput();

	virtual bool OnInitFirst(){ return true; }	//	falseを返すとプログラム終了
	virtual bool OnGraphicInitEnded(){ return true; }	//	falseを返すとプログラム終了
	virtual _AGST_DLL_EXP void MainLoop();

private:
	//	なんでPublic？（Privateではないのか・・・？）
	//void OnLButtonDown(int x, int y);

	//void ScreenUpdate();

public:
	//	コンストラクタ
	/*CAugustScreen2(CAugustGlobalCommon &g_in) : g_(g_in),
		m_mouse(g_in.input.mouse), m_grp(g_in.grp), m_input(g_in.input), m_audio(g_in.audio),
		m_imgCache(g_in.imgCache)
	{
		//m_hWnd = NULL;
		m_rgbBackground = D3DCOLOR_WHITE;
	}*/
	//	コンストラクタ
	CAugustScreen2()
	{
		m_bEndFlg = false;

		m_vphWnd = NULL;
		m_bUseMouseHandle = false;
	}
	virtual ~CAugustScreen2(){}

	/////////////////////////////////////////////////////////////////////////

	virtual void OnCreatedWindow(){
		_BASE::OnCreatedWindow();

		//m_vphWnd = (void*)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_HWND),
		//	"CAugustScreen2::OnCreatedWindow()  ウインドウハンドルの取得に失敗");
		m_vphWnd = (void*)GetValPtr(MWLAGH_VALKEY_HWND);

		//	2009/05/03  追加してねぇじゃん・・・
		_BASE::RegistSubControl(&m_grp);
		_BASE::RegistSubControl(&m_fps);

		_THREAD_BASE::StartThread(0);
	}

	///// コントロールの登録 /////////////////////////////////////////////////

	void EnableMouseHandle(){ m_bUseMouseHandle = true; }
	void DisableMouseHandle(){ m_bUseMouseHandle = false; }

public:
	//bool OnFrameMouseInput(); <- なんかpublicなのに理由あんのかな・・・？
};

#endif//__AugustScreen2_H__
