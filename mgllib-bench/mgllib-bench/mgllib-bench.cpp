#include "StdAfx.h"

//	�t���[��
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustImage2 m_img;
public:
	//	���������ɌĂ΂��
	bool OnReady(){
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