//////////////////////////////////////////////////////////
//
//	AugustGraphicsManager
//
//////////////////////////////////////////////////////////

#ifndef __AugustGraphicsManager_H__
#define __AugustGraphicsManager_H__

#include "AugustCommon2.h"
//#include "AugustImage2.h"


//	クラス宣言  /////////////////////////////////////////////////////////

class CMglGraphicManager;
class CMglImage;
class CAugustWindow2;
class CAugustImageLoader;

class _AGST_DLL_EXP CAugustGraphicsManager : public agh::CControlBase
{
private:
	typedef agh::CControlBase _BASE;
protected:
	CMglGraphicManager *m_pGrp;
	CAugustImageLoader *m_pImageLoader;
	//CAugustImageLoader m_imageLoader;

	/////////////////////////////////////////////////////////

	//HWND m_hWnd;
	//CMglLayers4 m_layer;
	//CMglImageCacher m_imgCache;
	//CMglImageCacher &m_imgCache;
	//agh::AGH_COLOR m_rgbBackground;	2009/05/10  GetColor()から取ればよかろう？
	CAugustWindow2* m_pWindow;

_AGH_EVENT_ACCESS_MODIFIER:
	///// オーバーライド可能なイベント /////////////////////////////////////////////////

	/**
	  ここにあった OnControl, OnBackground は下に移動しといたよ。
	**/

	virtual void OnDraw();
	virtual bool DoFrame();

	//	このクラスから
	virtual bool OnFrameDoUser(){return true;}

protected:

private:
	//void ScreenUpdate();

public:
	//	コンストラクタ
	/*CAugustGraphicsManager(CAugustGlobalCommon &g_in) : g_(g_in),
		m_mouse(g_in.input.mouse), m_grp(g_in.grp), m_input(g_in.input), m_audio(g_in.audio),
		m_imgCache(g_in.imgCache)
	{
		//m_hWnd = NULL;
		m_rgbBackground = D3DCOLOR_WHITE;
	}*/
	//	コンストラクタ
	CAugustGraphicsManager();
	virtual ~CAugustGraphicsManager();

	//////////////////////////////////////////////////////

	virtual void Init(bool bIsFullscreen=false);
	virtual void Release();
	virtual void Clear();
	virtual void Clear(agh::COLOR color);

	void FrameEnd();
	void FrameStart();

	///// コントロールの登録 /////////////////////////////////////////////////

	//////////////////////////////////////////////////////

	//BOOL IsExistPool(const char* szAlias); <- ?

	//void SetBackgroundColor(agh::AGHCOLOR color){ m_rgbBackground = color; }

public:
	virtual void* GetInternalPtr(){ return m_pGrp; }
	virtual CMglGraphicManager* GetMglGrp(){ return m_pGrp; }
	//virtual CMglImage* LoadImage(const char* szImageFilepath){ return m_pImageLoader->Load(szImageFilepath); }
	virtual CMglImage* LoadImage(const char* szImageFilepath, agh::COLOR colorKey);
};

typedef CAugustGraphicsManager CAugustGraphicManager;

#endif//__AugustGraphicsManager_H__
