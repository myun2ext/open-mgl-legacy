#include "mglaugust2.h"

//	メインフレームクラス
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustSound m_sound;
	CAugustKeyboardInput m_kb;

public:

	//	初期化時に呼ばれる
	bool OnGraphicInitEnded()
	{
		//	コントロールクラスの登録
		RegistControl(&m_sound);
		RegistControl(&m_kb);

		//	画像の読み込み
		m_sound.Load("hoge.wav");

		//	マウスクリックハンドラの登録
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'Z',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::OnZ,
			this);

		return true;
	}

	//	クリック時に呼ばれる
	bool OnZ(){
		m_sound.Play("hoge.wav");
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
