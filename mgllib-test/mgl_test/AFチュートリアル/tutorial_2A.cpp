#include "stdafx.h"

//	メインフレームクラス
class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
public:
	//	初期化時に呼ばれる
	void OnInit(){
		m_img.Load("test.jpg");
		CMglguiWindow::RegistControl(&m_img);
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
