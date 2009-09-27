#include "mglaugust2.h"
#include <string>

//	メインフレームクラス
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustMusic m_music;
	CAugustKeyboardInput m_kb;
	CAugustText2 m_text;

	bool m_bMediaLoaded;	//	メディアが読み込み済ならtrueにする
	
	//	メディアファイル選択ダイアログ
	std::string SelectMedia()
	{
		OPENFILENAME ofn;
		char szOutFilePath[1024];

		ZeroMemory( &ofn, sizeof(ofn) );
		ZeroMemory( szOutFilePath, sizeof(szOutFilePath) );

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = (HWND)this->GetHwnd();
		ofn.lpstrFile = szOutFilePath;
		ofn.nMaxFile = sizeof(szOutFilePath);
		ofn.lpstrFilter = "再生可能なメディア(mp3,wma,ogg,mid,wav)\0*.mp3;*.wma;*.ogg;*.mid;*.wav\0";
		ofn.lpstrTitle = "ファイルを開く";
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;

		//	実行
		if ( ::GetOpenFileName(&ofn) )
			return szOutFilePath;
		else
			return "";
	}

public:

	//	初期化時に呼ばれる
	bool OnGraphicInitEnded()
	{
		//	メディアが読みこまれていないのでfalseを設定
		m_bMediaLoaded = false;

		//	コントロールクラスの登録
		RegistControl(&m_kb);
		RegistControl(&m_music);
		RegistControl(&m_text);

		//	キーボードハンドラの登録
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'O',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::Open,
			this);
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'Z',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::Play,
			this);
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'X',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::Stop,
			this);
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'C',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::Pause,
			this);

		m_text.SetText(
			"O: ファイルを開く\n"
			"Z: 再生\n"
			"X: 停止\n"
			"C: ポーズ\n");

		return true;
	}

	//	ファイルを開く
	bool Open(){
		std::string strMedia = SelectMedia();
		if ( strMedia.length() != 0 )
		{
			m_music.Load(strMedia.c_str());
			m_bMediaLoaded = true;
			Play();
		}
		return true;
	}

	//	再生
	bool Play(){
		if ( !m_bMediaLoaded )
			Open();
		else
			m_music.Play();
		return true;
	}

	//	停止
	bool Stop(){
		if ( m_bMediaLoaded )
			m_music.Stop();
		return true;
	}

	//	ポーズ
	bool Pause(){
		if ( m_bMediaLoaded )
			m_music.Pause();
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
