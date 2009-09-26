#include "mglaugust2.h"

//	メインフレームクラス
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustKeyboardInput m_kb;

	CAugustSoundManager m_soundMgr;
	CAugustSound m_sound1;
	CAugustSound m_sound2;

public:

	//	初期化時に呼ばれる
	bool OnGraphicInitEnded()
	{
		//	コントロールクラスの登録
		RegistControl(&m_kb);
		RegistControl(&m_soundMgr);

		m_soundMgr.RegistControl(&m_sound1);
		m_soundMgr.RegistControl(&m_sound2);

		//	画像の読み込み
		m_sound1.Load("hoge.wav");
		m_sound2.Load("hoge2.wav");

		//	Zキーハンドラの登録
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'Z',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::OnZ,
			this);

		//	Xキーハンドラの登録
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'X',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::OnX,
			this);

		return true;
	}

	//	Zキーにて再生
	bool OnZ(){
		m_sound1.Play();
		return true;
	}

	//	Xキーにて再生
	bool OnX(){
		m_sound2.Play();
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