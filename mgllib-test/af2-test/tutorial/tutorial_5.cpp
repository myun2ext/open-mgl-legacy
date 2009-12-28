#include "mglaugust2.h"

//	メインフレームクラス
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustImage2 m_img;
	CAugustMouseInput m_mouse;
public:

	//	初期化時に呼ばれる
	bool OnGraphicInitEnded()
	{
		//	コントロールクラスの登録
		RegistControl(&m_img);
		RegistControl(&m_mouse);

		//	画像の読み込み
		m_img.Load("test.jpg");

		//	マウスクリックハンドラの登録
		m_mouse.RegistHandler(
			CAugustMouseInput::EVTTYPE_ON_DOWN,
			CAugustMouseInput::LBUTTON,
			(CAugustMouseInput::CALLBACK_TYPE_MI)&CMyFrame::OnMouseLDown,
			this);

		return true;
	}

	//	クリック時に呼ばれる
	bool OnMouseLDown(int x, int y)
	{
		if ( x >= 200 && x <= 400 && y >= 100 && y <= 200 )
			::MessageBoxA((HWND)GetHwnd(),  "いやーん", "いけないクリック", NULL);

		else if ( x >= 200 && x <= 400 && y >= 300 && y <= 400 )
			::MessageBoxA((HWND)GetHwnd(),"そこはだめよ・・・", "いけないクリック", NULL);

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
