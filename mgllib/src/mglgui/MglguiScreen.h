//////////////////////////////////////////////////////////
//
//	MglguiScreen
//
//////////////////////////////////////////////////////////

#ifndef __MglguiScreen_H__
#define __MglguiScreen_H__

#include "agh.h"
#include "MglLayers4.h"
#include "MglMouseInput.h"

class DLL_EXP CMyuThreadBase;

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglguiScreen : public agh::CScreenBase, public CMyuThreadBase
{
public:
	CMglGraphicManager m_grp;
	CMglImageLoader m_imgPool;

protected:
	HWND m_hWnd;
	CMglLayers4 m_layer;
	CMglMouseInput m_mouse;
	D3DCOLOR m_rgbBackground;

public:
	//	コンストラクタ
	CMglguiScreen(){
		m_hWnd = NULL;
		m_rgbBackground = D3DCOLOR_WHITE;
	}
	void Init( HWND hWnd, int nDispX, int nDispY );

	//////////////////////////////////////////////////////

	void ScreenUpdate();
	void DoFrame();
	void AutoLoopThreadStart();

	BOOL IsExistPool(const char* szAlias);

	//////////////////////////////////////////////////////

	/*BOOL InsertImage(IMGLIST_ITR it);
	BOOL InsertImage(){ return InsertImage(GetScene()->m_images.begin()); }*/

	void SetBackgroundColor(D3DCOLOR color){ m_rgbBackground = color; }

private:
	bool ThreadFunc();
};

#endif//__MglguiScreen_H__
