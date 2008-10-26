// mgl_test.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include "MglguiScreen.h"
#include "MglAghImage.h"

class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
public:
	CMglTestFrame(){}
	void OnInit(){
		EnableEscEnd();
		m_img.EnableDragMovable();
		m_img.Load("font_big.tga");
		CMglguiWindow::RegistControl(&m_img);
	}
};
CMglTestFrame g_frame;

///////////////////////////////////////////////////

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	g_frame.Start();
	return 0;
}
