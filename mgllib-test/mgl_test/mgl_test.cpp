#include "stdafx.h"

//	メインフレームクラス
class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
public:
	void OnInit(){
		m_img.Load("test.jpg");
		CMglguiWindow::RegistControl(&m_img);


		m_audio.Load("D2 HH2-005.wav");
		m_audio.Load("tr909closed05.wav");

		//	キーボードイベントハンドラ登録
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_Z,
			(MGL_KB_EVT_HANDLER_CALLBACK)PlaySoundZ);

		//	キーボードイベントハンドラ登録
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_X,
			(MGL_KB_EVT_HANDLER_CALLBACK)PlaySoundX);
	}
	bool PlaySoundZ(){
		m_audio.Play("D2 HH2-005.wav");
		return true;
	}

	bool PlaySoundX(){
		m_audio.Play("tr909closed05.wav");
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
