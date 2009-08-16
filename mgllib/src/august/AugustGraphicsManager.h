//////////////////////////////////////////////////////////
//
//	AugustGraphicsManager
//
//////////////////////////////////////////////////////////

#ifndef __AugustGraphicsManager_H__
#define __AugustGraphicsManager_H__

#include "AugustCommon2.h"
//#include "AugustImage2.h"


//	�N���X�錾  /////////////////////////////////////////////////////////

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
	//agh::AGH_COLOR m_rgbBackground;	2009/05/10  GetColor()������΂悩�낤�H
	CAugustWindow2* m_pWindow;

_AGH_EVENT_ACCESS_MODIFIER:
	///// �I�[�o�[���C�h�\�ȃC�x���g /////////////////////////////////////////////////

	/**
	  �����ɂ����� OnControl, OnBackground �͉��Ɉړ����Ƃ�����B
	**/

	virtual void OnDraw();
	virtual bool DoFrame();

	//	���̃N���X����
	virtual bool OnFrameDoUser(){return true;}

protected:

private:
	//void ScreenUpdate();

public:
	//	�R���X�g���N�^
	/*CAugustGraphicsManager(CAugustGlobalCommon &g_in) : g_(g_in),
		m_mouse(g_in.input.mouse), m_grp(g_in.grp), m_input(g_in.input), m_audio(g_in.audio),
		m_imgCache(g_in.imgCache)
	{
		//m_hWnd = NULL;
		m_rgbBackground = D3DCOLOR_WHITE;
	}*/
	//	�R���X�g���N�^
	CAugustGraphicsManager();
	virtual ~CAugustGraphicsManager();

	//////////////////////////////////////////////////////

	virtual void Init(bool bIsFullscreen=false);
	virtual void Release();
	virtual void Clear();
	virtual void Clear(agh::COLOR color);

	void FrameEnd();
	void FrameStart();

	///// �R���g���[���̓o�^ /////////////////////////////////////////////////

	//////////////////////////////////////////////////////

	//BOOL IsExistPool(const char* szAlias); <- ?

	//void SetBackgroundColor(agh::AGHCOLOR color){ m_rgbBackground = color; }

public:
	virtual void* GetInternalPtr(){ return m_pGrp; }
	virtual CMglGraphicManager* GetMglGrp(){ return m_pGrp; }
	//virtual CMglImage* LoadImage(const char* szImageFilepath){ return m_pImageLoader->Load(szImageFilepath); }
	virtual CMglImage* LoadImage(const char* szImageFilepath, D3DCOLOR colorKey);
};

typedef CAugustGraphicsManager CAugustGraphicManager;

#endif//__AugustGraphicsManager_H__
