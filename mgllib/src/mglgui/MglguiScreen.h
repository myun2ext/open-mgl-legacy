//////////////////////////////////////////////////////////
//
//	MglguiScreen
//
//////////////////////////////////////////////////////////

#ifndef __MglguiScreen_H__
#define __MglguiScreen_H__

#include "agh.h"
#include "MglLayers4.h"
#include "MglEzGameFrame.h"
//#include "MglMouseInput.h"

class DLL_EXP agh::CScreenBase;
class DLL_EXP CMyuThreadBase;

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglguiScreen : public agh::CScreenBase, public CMyuThreadBase, public CMglEzGameFrame
{
public:
	CMglGraphicManager m_grp;
	CMglImageLoader m_imgPool;

protected:
	HWND m_hWnd;
	CMglLayers4 m_layer;
	CMglMouseInput &m_mouse;
	D3DCOLOR m_rgbBackground;

public:
	//	コンストラクタ
	CMglguiScreen() : m_mouse(input.mouse) {
		m_hWnd = NULL;
		m_rgbBackground = D3DCOLOR_WHITE;
	}
	void Init( HWND hWnd, int nDispX, int nDispY );

	//////////////////////////////////////////////////////

	void ScreenUpdate();
	bool DoFrame();
	void AutoLoopThreadStart();

	BOOL IsExistPool(const char* szAlias);

	//////////////////////////////////////////////////////

	/*BOOL InsertImage(IMGLIST_ITR it);
	BOOL InsertImage(){ return InsertImage(GetScene()->m_images.begin()); }*/

	void SetBackgroundColor(D3DCOLOR color){ m_rgbBackground = color; }

private:
	bool ThreadFunc();
	bool OnFrameMouseInput();
};

#endif//__MglguiScreen_H__
