#include "stdafx.h"

class CMglTestFrame : public CAugustWindow
{
private:
	CAugustImage m_img;
public:
	//	���������ɌĂ΂��
	void OnInit(){
		EnableEscEnd();
		RegistControl(&m_img);
		m_img.Load("test.jpg");
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
