#include "stdafx.h"

//	メインフレームクラス
class CTestScreem : public CAugustScreen
{
private:
	CAugustImage m_img;
	CAugustText m_text;

public:
	void OnInit(){
		RegistControl(&m_img);
/*		RegistControl(&m_text);*/

		m_img.Load("test.jpg");
/*		m_text.SetText("hoge");
		m_text.SetFontSize(64);
		m_text.SetColor(0x77000000);*/

		m_img.EnableDrag();
		m_text.EnableDrag();
	}
};

class CTestFrame : public CAugustWindow
{
private:
	CTestScreem m_screen;
public:
	void OnInit(){
		this->SetActiveScreen(&m_screen);
		this->EnableEscEnd();
	}
};
CTestFrame g_frame;

//	WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	g_frame.Start();
	return 0;
}
