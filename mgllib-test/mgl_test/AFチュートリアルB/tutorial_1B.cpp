#include "stdafx.h"

class CTestScreen : public CAugustScreen
{
private:
	CMglAghImage m_img;
public:
	//	初期化時に呼ばれる
	void OnInit(){
		m_img.Load("test.jpg");
		RegistControl(&m_img);
	}
};

class CTestWindow : public CAugustWindow
{
private:
	CTestScreen m_testScreen;
public:
	CTestWindow(){
		EnableEscEnd();
		SetActiveScreenControl(&m_testScreen);
	}
	//	ウインドウ生成前に呼ばれる
	void OnCreateWindow(agh::CREATE_WINDOW_INFO *pWindowInfo){
		pWindowInfo->nWinWidthSize = 800;
		pWindowInfo->nWinHeightSize = 600;
		pWindowInfo->strWindowTitle = "さんぷるぷろぐらむ";
	}
};

//	WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	CTestWindow window;
	window.Start();
	return 0;
}
