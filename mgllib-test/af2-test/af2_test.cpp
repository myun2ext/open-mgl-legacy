#include <windows.h>
#include "mwlagh.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
 	CMwlAghFactory fact;
	agh::IWindow* pWindow = fact.CreateWindow(NULL);
	pWindow->Start();

	return 0;
}


