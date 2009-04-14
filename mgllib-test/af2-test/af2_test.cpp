#include <windows.h>
#include "mwlagh.h"

class CMyWindow : public agh::IWindow
{
public:
//	virtual bool OnClose(){ MessageBox(NULL,"sdfa","sfda",0); return true; }
};

int _MWL_APIENTRY WinMain(
					_MWL_HINSTANCE hInstance,
                    _MWL_HINSTANCE hPrevInstance,
                    char*     lpCmdLine,
                    int       nCmdShow )
//int main()
{
//::FreeConsole();

	CMwlAghFactory fact;
	CMyWindow myWindow;
	//agh::IWindow* pWindow = fact.CreateWindow(new CMyWindow);
	agh::IWindow* pWindow = fact.CreateWindow(&myWindow);
	pWindow->Start();

	return 0;
}


