#include "stdafx.h"
#include "MglAghImage.h"

class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
	CMglAghText m_text;
public:
	//	���������ɌĂ΂��
	void OnInit(){
		m_img.Load("huukei.jpg");

		CMglguiWindow::RegistControl(&m_img);
		CMglguiWindow::RegistControl(&m_text);

		m_text.SetOption( AGH_FONT_OPTION_BOLD | AGH_FONT_OPTION_UNDERLINE );
		m_text.SetFontName( "MS P�S�V�b�N" );
		m_text.SetFontSize(40);
		m_text.SetPos(20,350);
		m_text.SetColor(AGHCOLOR_ARGB(150,120,255,200));
		m_text.SetText("�Ă��Ƃ�\n��[��B");
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
