#include "stdafx.h"
#include "MglAghImage.h"

class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
public:
	//	初期化時に呼ばれる
	void OnInit(){
		EnableEscEnd();
		m_img.Load("test.jpg");
		CMglguiWindow::RegistControl(&m_img);
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
	CMglTestFrame frame;
	frame.Start();
	return 0;
}
