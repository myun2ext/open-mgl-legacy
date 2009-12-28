#include "mglaugust2.h"

class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustText2 m_text;
	CAugustText2 m_text2;

public:
	//	初期化時に呼ばれる
	bool OnGraphicInitEnded()
	{
		RegistControl(&m_text);
		RegistControl(&m_text2);
		
		m_text.SetText("これはテストなりー。");

		m_text2.SetText("デカい文字なりー");
		m_text2.SetFontSize(60);
		m_text2.SetPos(0,20);
		m_text2.SetColor(AGHCOLOR_RGB(40,100,200));

		return true;
	}
};

//	WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	CMyFrame frame;
	frame.Start();
	return 0;
}
