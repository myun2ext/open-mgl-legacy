//////////////////////////////////////////////////////////
//
//	AugustWindow2
//
//////////////////////////////////////////////////////////

#ifndef __AugustWindow2_H__
#define __AugustWindow2_H__

#include "AugustCommon2.h"

class /*_AGST_DLL_EXP*/ CMwlAghWindow;
class /*_AGST_DLL_EXP*/ CMyuThreadBase;

class /*_AGST_DLL_EXP*/ CAugustWindow2 : public CMwlAghWindow
{
public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CAugustWindow2(){}
	virtual ~CAugustWindow2(){}

	virtual void OnCreatedWindow(){
		//MessageBox(NULL,"sdfa","sfda",0);
		/*
		RECT rcPos;
		rcPos.left = 10;
		rcPos.right = 100;
		rcPos.top = 50;
		rcPos.bottom = 100;

		HWND hParent = (HWND)GetHwnd();

		HWND hWnd = ::CreateWindowEx(0, "BUTTON", "test",
		0, rcPos.left, rcPos.top, rcPos.right - rcPos.left,
		rcPos.bottom - rcPos.top, (HWND)GetHwnd(), NULL,
		g_hInstance, NULL);

		//	�E�C���h�E�̕\�����ǂ����邩
		ShowWindow( hWnd, SW_SHOWDEFAULT );
		UpdateWindow( hWnd );
		*/
	}
};

#endif//__AugustWindow2_H__
