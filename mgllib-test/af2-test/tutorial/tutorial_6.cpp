#include "mglaugust2.h"

class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustImage2 m_img;
	CAugustKeyboardInput m_kb;
	
	//	今回新たに追加
	int m_moveX;
	int m_moveY;

public:
	//	初期化時に呼ばれる
	bool OnGraphicInitEnded()
	{
		RegistControl(&m_img);
		RegistControl(&m_kb);
		
		m_img.Load("test.jpg");

		//	キーボードイベントハンドラ登録（左）
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			AGH_KEYCODE_LEFT,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveLeft,
			this);

		//	キーボードイベントハンドラ登録（右）
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			AGH_KEYCODE_RIGHT,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveRight,
			this);

		//	キーボードイベントハンドラ登録（上）
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			AGH_KEYCODE_UP,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveUp,
			this);

		//	キーボードイベントハンドラ登録（下）
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			AGH_KEYCODE_DOWN,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveDown,
			this);

		//	キーボードイベントハンドラ登録（スペースキー）
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			' ',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveStop,
			this);

		//	キーボードイベントハンドラ登録（Zキー）
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			'Z',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveToInitial,
			this);
		
		//	move変数の初期化
		m_moveX = 0;
		m_moveY = 0;

		return true;
	}

	//	各ハンドラメソッド
	bool MoveLeft(){
		m_moveX = -1;
		m_moveY = 0;
		return true;
	}
	bool MoveRight(){
		m_moveX = 1;
		m_moveY = 0;
		return true;
	}
	bool MoveUp(){
		m_moveX = 0;
		m_moveY = -1;
		return true;
	}
	bool MoveDown(){
		m_moveX = 0;
		m_moveY = 1;
		return true;
	}

	//	今回は以下を追加
	bool MoveStop(){
		m_moveX = 0;
		m_moveY = 0;
		return true;
	}
	bool MoveToInitial(){
		m_img.SetPos(0,0);
		MoveStop();
		return true;
	}
	bool OnFrameDoUser(){
		m_img.Move(m_moveX, m_moveY);
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
