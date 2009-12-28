#include "mglaugust2.h"

class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustImage2 m_img;
	CAugustKeyboardInput m_kb;

public:
	//	初期化時に呼ばれる
	bool OnGraphicInitEnded()
	{
		RegistControl(&m_img);
		RegistControl(&m_kb);
		
		m_img.Load("test.jpg");

		//	キーボードイベントハンドラ登録（左）- 押している間移動
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			AGH_KEYCODE_LEFT,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveLeft,
			this);

		//	キーボードイベントハンドラ登録（右）- 押している間移動
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			AGH_KEYCODE_RIGHT,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveRight,
			this);

		//	キーボードイベントハンドラ登録（上）- 離した瞬間だけ移動
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_UP,
			AGH_KEYCODE_UP,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveUp,
			this);

		//	キーボードイベントハンドラ登録（下）- 押した瞬間だけ移動
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_DOWN,
			AGH_KEYCODE_DOWN,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveDown,
			this);

		return true;
	}

	//	各ハンドラメソッド
	bool MoveLeft(){
		m_img.Move(-1,0);
		return true;
	}
	bool MoveRight(){
		m_img.Move(1,0);
		return true;
	}
	bool MoveUp(){
		m_img.Move(0,-10);
		return true;
	}
	bool MoveDown(){
		m_img.Move(0,10);
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
