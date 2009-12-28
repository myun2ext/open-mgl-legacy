#include "mglaugust2.h"

class CMyFrame : public CAugustWindowFrame2
{
public:
	//	初期化時に呼ばれる
	bool OnGraphicInitEnded()
	{
		return true;
	}

	//	ウインドウ生成前に呼ばれる
	void OnCreateWindow(agh::CREATE_WINDOW_INFO *pWindowInfo){
		pWindowInfo->nWinWidthSize = 800;
		pWindowInfo->nWinHeightSize = 600;
		pWindowInfo->strWindowTitle = "タイトルを変更";
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
