#include "stdafx.h"

class CMglTestFrame : public CMglguiWindow
{
private:
public:
	void OnInit(){
		//	wavファイルの読み込み
		m_audio.Load("hoge.wav");
		m_audio.Load("hoge2.wav","ほげ２");

		//	キーボードイベントハンドラ登録
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_Z,
			(MGL_KB_EVT_HANDLER_CALLBACK)PlaySoundHoge);
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_X,
			(MGL_KB_EVT_HANDLER_CALLBACK)PlaySoundHoge2);
	}

	//	ZとかXを押すとwav再生
	bool PlaySoundHoge(){
		m_audio.Play("hoge.wav");
		return true;
	}
	bool PlaySoundHoge2(){
		m_audio.Play("ほげ２");
		return true;
	}
};

//	WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	CMglTestFrame frame;
	frame.Start();
	return 0;
}
