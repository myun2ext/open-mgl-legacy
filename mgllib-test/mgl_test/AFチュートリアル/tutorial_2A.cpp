#include "stdafx.h"

//	���C���t���[���N���X
class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
public:
	//	���������ɌĂ΂��
	void OnInit(){
		m_img.Load("test.jpg");
		CMglguiWindow::RegistControl(&m_img);
	}
	//	�N���b�N���ɌĂ΂��
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
