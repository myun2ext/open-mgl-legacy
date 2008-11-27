// mgl_test.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include "MglguiScreen.h"
#include "MglAghImage.h"

//	メインフレームクラス
class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
public:
	//	初期化時に呼ばれる
	void OnInit(){
		EnableEscEnd();
		m_img.EnableDragMovable();
		m_img.Load("font_big.tga");
		CMglguiWindow::RegistControl(&m_img);
	}
	//	ウインドウ生成前に呼ばれる
	void OnCreateWindow(agh::CREATE_WINDOW_INFO *pWindowInfo){
		pWindowInfo->nWinWidthSize = 640;
		pWindowInfo->nWinHeightSize = 480;
		pWindowInfo->strWindowTitle = "August Framework Test";
	}
	//	クリック時に呼ばれる
	void OnLButtonDown(int x, int y){
		::MessageBox(NULL,"test","test",NULL);
	}
};
CMglTestFrame g_frame;

//	WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	g_frame.Start();
	return 0;
}
