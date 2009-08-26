#include "mglaugust2.h"

//	メインフレームクラス
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustImage2 m_img;
	CAugustText2 m_text;
	CAugustMouseInput m_mouse;

	bool m_bFlg;
public:

	//	初期化時に呼ばれる
	bool OnGraphicInitEnded()
	{
		//m_fps.SetFps(1);
		//	コントロールクラスの登録
		RegistControl(&m_img);
		RegistControl(&m_text);
		RegistControl(&m_mouse);

		//	画像の読み込み
		m_img.Load("test.jpg");

		//	マウスクリックハンドラの登録
		m_mouse.RegistHandler(
			CAugustMouseInput::EVTTYPE_ON_DOWN,
			CAugustMouseInput::LBUTTON,
			(CAugustMouseInput::CALLBACK_TYPE_MI)&CMyFrame::OnMouseLDown,
			this);
		m_mouse.RegistHandler(
			CAugustMouseInput::EVTTYPE_ON_UP,
			CAugustMouseInput::LBUTTON,
			(CAugustMouseInput::CALLBACK_TYPE_MI)&CMyFrame::OnMouseLUp,
			this);

		//	マウス移動ハンドラの登録
		m_mouse.RegistHandler(
			CAugustMouseInput::EVTTYPE_ON_MOVE,
			0,
			(CAugustMouseInput::CALLBACK_TYPE_MI)&CMyFrame::OnMouseMove,
			this);

		//	マウスホイールハンドラの登録
		m_mouse.RegistHandler(
			CAugustMouseInput::EVTTYPE_ON_MOVE,
			CAugustMouseInput::CBUTTON,
			(CAugustMouseInput::CALLBACK_TYPE_MI)&CMyFrame::OnMouseZoom,
			this);

		m_bFlg = false;

		return true;
	}

	//	クリック時に呼ばれる
	bool OnMouseLDown(int x, int y){
		char msg[256];
		sprintf(msg, "(%d, %d) がクリックされました。", x, y);
		//::MessageBoxA(NULL,msg,"OnLButtonDown",NULL);
		m_bFlg = true;
		return true;
	}

	//	クリック時に呼ばれる
	bool OnMouseLUp(int x, int y){
		m_bFlg = false;
		return true;
	}

	//	マウス移動時に呼ばれる
	bool OnMouseMove(int x, int y){
		char msg[256];
		sprintf(msg, "(%d, %d)", x, y);
		m_text.SetText(msg);

		if ( !m_bFlg )
			m_img.Move(x,y);
		return true;
	}

	//	マウスホイール時に呼ばれる
	bool OnMouseZoom(int x, int y){
		m_img.SetScale(m_img.GetScale()+(x/500.0f));
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
