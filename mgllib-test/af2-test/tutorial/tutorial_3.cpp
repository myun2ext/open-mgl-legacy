#include "mglaugust2.h"

class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustImage2 m_img;
public:
	//	初期化時に呼ばれる
	bool OnGraphicInitEnded(){
		RegistControl(&m_img);
		m_img.Load("test.jpg");

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
