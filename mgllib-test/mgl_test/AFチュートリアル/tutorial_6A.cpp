#include "stdafx.h"

class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
	CMglAghText m_text;
public:
	//	���������ɌĂ΂��
	void OnInit(){
		m_img.Load("test.jpg");

		CMglguiWindow::RegistControl(&m_img);
		CMglguiWindow::RegistControl(&m_text);

		m_text.SetOption( AGH_FONT_OPTION_BOLD | AGH_FONT_OPTION_UNDERLINE );
		m_text.SetFontName( "MS P�S�V�b�N" );
		m_text.SetFontSize(28);
		m_text.SetPos(20,380);
		m_text.SetColor(AGHCOLOR_ARGB(120,180,180,255));
		m_text.SetText("�e�X�g�ł��B\n���s���o���܂��B");
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
