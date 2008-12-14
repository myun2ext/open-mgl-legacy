#include "stdafx.h"

//	メインフレームクラス
class CMglTestFrame : public CAugustWindow
{
private:
	CAugustImage m_img;
	CAugustText m_text;
public:
	void OnInit(){
		RegistControl(&m_img);
		RegistControl(&m_text);

		m_img.Load("test.jpg");

		m_text.SetText("hoge");
		m_text.SetFontSize(64);
		m_text.SetColor(0x77000000);

		m_audio.Load("hoge.wav");
		m_audio.Load("hoge2.wav");

		//	キーボードイベントハンドラ登録
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_Z,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)PlaySoundZ);

		//	キーボードイベントハンドラ登録
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_X,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)PlaySoundX);
	}
	bool PlaySoundZ(){
		m_audio.Play("hoge.wav");
		return true;
	}

	bool PlaySoundX(){
		m_audio.Play("hoge2.wav");
		return true;
	}
};
CMglTestFrame g_frame;

//	WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{

	g_frame.Start();
	return 0;
}
