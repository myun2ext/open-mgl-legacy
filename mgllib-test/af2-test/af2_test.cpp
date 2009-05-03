#include <windows.h>
//#include "mwlagh.h"
//#include "AugustWindow2.h"
#include "mglaugust2.h"
//#include "AugustGraphicsManager.h"

//class __declspec(dllimport) CMwlAghWindow;

/*
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
*/
_MWL_HINSTANCE g_hInstance;

class CMyWindow : public CMwlAghWindow
{
private:
	CAugustGraphicsManager m_grp;
public:
	CMyWindow(){
		RegistSubControl(&m_grp);
	}
	virtual void OnCreatedWindow(){
		//MessageBox(NULL,"sdfa","sfda",0);
		
		RECT rcPos;
		rcPos.left = 10;
		rcPos.right = 100;
		rcPos.top = 50;
		rcPos.bottom = 100;

		HWND hParent = (HWND)GetHwnd();

		HWND hWnd = ::CreateWindowEx(0, "BUTTON", "test",
		0, rcPos.left, rcPos.top, rcPos.right - rcPos.left,
		rcPos.bottom - rcPos.top, (HWND)GetHwnd(), NULL,
		g_hInstance, NULL);

		//	ウインドウの表示をどうするか
		ShowWindow( hWnd, SW_SHOWDEFAULT );
		UpdateWindow( hWnd );
	}
	virtual bool OnClose(){ MessageBox(NULL,"sdfa","sfda",0); return true; }
	virtual bool OnDropFiles(std::vector<std::string> &files){
		for(int i=0; i<files.size(); i++)
			MessageBox((HWND)GetHwnd(),files[i].c_str(),"Drop",0);

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
	g_hInstance = hInstance;
//::FreeConsole();
	//CMyWindow myWindow;
	CAugustScreen2 myWindow;
	myWindow.EnableDropFiles();
	myWindow.Start();

	return 0;
}


