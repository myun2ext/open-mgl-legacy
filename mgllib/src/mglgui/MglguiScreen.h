//////////////////////////////////////////////////////////
//
//	MglguiScreen
//
//////////////////////////////////////////////////////////

#ifndef __MglguiScreen_H__
#define __MglguiScreen_H__

#include "agh.h"
#include "MglLayers4.h"

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglguiScreen : public agh::CScreenBase
{
public:
	CMglGraphicManager m_grp;
	CMglImagePool m_imgPool;
protected:
	HWND m_hWnd;
	CMglLayers4 m_layer;

public:
	//	コンストラクタ
	CMglguiScreen(){
		m_hWnd = NULL;
	}
	void Init( HWND hWnd, int nDispX, int nDispY );

	//////////////////////////////////////////////////////

	void ScreenUpdate();

	BOOL IsExistPool(const char* szAlias);

	//////////////////////////////////////////////////////

	/*BOOL InsertImage(IMGLIST_ITR it);
	BOOL InsertImage(){ return InsertImage(GetScene()->m_images.begin()); }*/
};

#endif//__MglguiScreen_H__
