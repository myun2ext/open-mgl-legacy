#include "mglaugust2.h"

#define MESSAGE	\
	"とある宇宙の果てに、おじいさんとおばあさんが居ました。 \n"	\
	"おじいさんとおばあさんは空気が無くて死んでしまいました。"
#define MSG_WAIT	(2)

class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustImage2 m_imgBack;
	CAugustImage2 m_imgWindow;
	CAugustText2 m_txtName;
	CAugustText2 m_txtMsg;
	int m_nCounter;

public:
	//	初期化時に呼ばれる
	bool OnGraphicInitEnded()
	{
		RegistControl(&m_imgBack);
		RegistControl(&m_imgWindow);
		RegistControl(&m_txtName);
		RegistControl(&m_txtMsg);

		m_imgBack.Load("back.jpg");
		m_imgWindow.Load("window.bmp");
		m_imgWindow.SetAlpha(180);

		m_txtName.SetText("ナレーター");
		m_txtName.SetPos(40,285);
		m_txtName.SetFontSize(24);

		m_txtMsg.SetPos(45,350);
		m_txtMsg.SetFontSize(22);
		m_txtMsg.SetColor(AGHCOLOR_WHITE);

		m_nCounter = 0;

		return true;
	}

	//	ウインドウ生成前に呼ばれる
	void OnCreateWindow(agh::CREATE_WINDOW_INFO *pWindowInfo){
		pWindowInfo->strWindowTitle = "おじいさんとおばあさんプログラム";
	}

	bool OnFrameDoUser()
	{
		if ( (m_nCounter/MSG_WAIT) <= (int)strlen(MESSAGE) ){
			m_nCounter++;
			if ( m_nCounter % (MSG_WAIT*2) == 0 )
				m_txtMsg.SetText(std::string(MESSAGE,(m_nCounter/MSG_WAIT)).c_str());
		}

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
