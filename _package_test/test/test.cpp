// test.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"

class CMglTestFrame : public CAugustWindow
{
private:
	CAugustImage m_img;
	CAugustText m_text;
	CMglBgm m_music;
public:
	//	初期化時に呼ばれる
	void OnInit(){
		EnableEscEnd();
		RegistControl(&m_img);
		RegistControl(&m_text);

		m_img.Load("test.jpg");
		m_text.SetText("ほげ。");
		m_text.SetFontSize(43);
		m_text.SetColor(0x90000000);

		//	キーボードイベントハンドラ登録（左）- 押している間移動
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_PRESS,
			DIK_LEFT,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)MoveLeft);

		//	キーボードイベントハンドラ登録（右）- 押している間移動
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_PRESS,
			DIK_RIGHT,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)MoveRight);

		//	キーボードイベントハンドラ登録（上）- 離した瞬間だけ移動
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP,
			DIK_UP,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)MoveUp);

		//	キーボードイベントハンドラ登録（下）- 押した瞬間だけ移動
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_DOWN,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)MoveDown);


		m_audio.Load("pwr_snr2.wav","a");
		//	キーボードイベントハンドラ登録
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_Z,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)PlaySoundZ);

		//m_music.Load("dante.ogg");
		m_music.Load("71.mp3");
		m_music.Play();
	}
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
	bool PlaySoundZ(){
		m_audio.LoopPlay("a");
		return true;
	}
	//	ウインドウ生成前に呼ばれる
	void OnCreateWindow(agh::CREATE_WINDOW_INFO *pWindowInfo){
		pWindowInfo->nWinWidthSize = 800;
		pWindowInfo->nWinHeightSize = 600;
		pWindowInfo->strWindowTitle = "さんぷるぷろぐらむ";
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