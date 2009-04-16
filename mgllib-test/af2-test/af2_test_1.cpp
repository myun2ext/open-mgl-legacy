#include <windows.h>
#include "mwlagh.h"

class CMyWindow : public agh::IWindow
{
public:
	virtual bool OnClose(){ MessageBox(NULL,"sdfa","sfda",0); return true; }
	virtual bool OnDropFiles(std::vector<std::string> &files){
		for(int i=0; i<files.size(); i++)
			MessageBox(NULL,files[i].c_str(),"Drop",0);
		return true;
	}
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

	delete pWindow;

	return 0;
}


