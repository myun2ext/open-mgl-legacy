#include "stdafx.h"
#include "MglAghImage.h"

class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
public:
	//	���������ɌĂ΂��
	void OnInit(){
		EnableEscEnd();
		m_img.Load("test.jpg");
		CMglguiWindow::RegistControl(&m_img);
	}
	//	�E�C���h�E�����O�ɌĂ΂��
	void OnCreateWindow(agh::CREATE_WINDOW_INFO *pWindowInfo){
		pWindowInfo->nWinWidthSize = 800;
		pWindowInfo->nWinHeightSize = 600;
		pWindowInfo->strWindowTitle = "����Ղ�Ղ낮���";
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
