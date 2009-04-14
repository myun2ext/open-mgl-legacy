#include <windows.h>
#include "mwlagh.h"

class CMyWindow : public agh::IWindow
{
public:
	virtual bool OnClose(){ MessageBox(NULL,"sdfa","sfda",0); return true; }
};

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
 	CMwlAghFactory fact;
	CMyWindow myWindow;
	//agh::IWindow* pWindow = fact.CreateWindow(new CMyWindow);
	agh::IWindow* pWindow = fact.CreateWindow(&myWindow);
	pWindow->Start();

	return 0;
}


