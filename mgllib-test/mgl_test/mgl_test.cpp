// mgl_test.cpp : �A�v���P�[�V�����p�̃G���g�� �|�C���g�̒�`
//

#include "stdafx.h"
#include "MglguiScreen.h"
#include "MglAghImage.h"

//	���C���t���[���N���X
class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
public:
	//	���������ɌĂ΂��
	void OnInit(){
		EnableEscEnd();
		m_img.EnableDragMovable();
		m_img.Load("font_big.tga");
		CMglguiWindow::RegistControl(&m_img);
	}
	//	�E�C���h�E�����O�ɌĂ΂��
	void OnCreateWindow(agh::CREATE_WINDOW_INFO *pWindowInfo){
		pWindowInfo->nWinWidthSize = 640;
		pWindowInfo->nWinHeightSize = 480;
		pWindowInfo->strWindowTitle = "August Framework Test";
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
