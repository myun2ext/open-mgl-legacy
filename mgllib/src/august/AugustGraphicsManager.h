//////////////////////////////////////////////////////////
//
//	AugustGraphicsManager
//
//////////////////////////////////////////////////////////

#ifndef __AugustGraphicsManager_H__
#define __AugustGraphicsManager_H__

#include "AugustCommon2.h"

class CMglGraphicManager;

//	クラス宣言  /////////////////////////////////////////////////////////
class _AGST_DLL_EXP CAugustGraphicsManager : public agh::CControlBase
{
protected:
	CMglGraphicManager *m_pGrp;

	/////////////////////////////////////////////////////////

	//HWND m_hWnd;
	//CMglLayers4 m_layer;
	//CMglImageCacher m_imgCache;
	//CMglImageCacher &m_imgCache;
	agh::AGH_COLOR m_rgbBackground;

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

	///// コントロールの登録 /////////////////////////////////////////////////

	//////////////////////////////////////////////////////

	//BOOL IsExistPool(const char* szAlias); <- ?

	void SetBackgroundColor(agh::AGHCOLOR color){ m_rgbBackground = color; }

public:
	//bool OnFrameMouseInput(); <- なんかpublicなのに理由あんのかな・・・？
};

typedef CAugustGraphicsManager CAugustGraphicManager;

#endif//__AugustGraphicsManager_H__
