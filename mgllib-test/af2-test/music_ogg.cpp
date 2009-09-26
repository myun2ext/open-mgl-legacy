#include "mglaugust2.h"
#include <string>


//	メインフレームクラス
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustMusic m_music;
	CAugustMusic m_music2;
	CAugustMusic m_music3;
	CAugustKeyboardInput m_kb;
	CAugustText2 m_text;
	CAugustText2 m_text2;

	bool m_bMediaLoaded;
	int m_nVolume;
	int m_nPan;
	
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
		if ( GetOpenFileName(&ofn) )
			return szOutFilePath;
		else
			return "";
	}

public:

	//	初期化時に呼ばれる
	bool OnGraphicInitEnded()
	{
//	名前の登録も自動に・・・（##で）
#define __AGH_REGIST_CONTROL_AUTO(CTRL)		RegistControl(&CTRL);

		m_nVolume = 100;
		m_nPan = 0;
		m_bMediaLoaded = false;

		//	コントロールクラスの登録
		RegistControl(&m_kb);
		RegistControl(&m_music);
		RegistControl(&m_music2);
		RegistControl(&m_music3);
		RegistControl(&m_text);
		RegistControl(&m_text2);

		//	画像の読み込み
		//m_music.Load("test.mp3");
		m_music2.Load("test.mp3");
		m_music3.Load("test.wma");

		m_text2.SetPos(0,120);
		//m_music.Play();
		//m_music2.Play();

		//	マウスクリックハンドラの登録
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

		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'N',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::VolumeDown,
			this);
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'M',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::VolumeUp,
			this);
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			',',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::PanLeft,
			this);
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'.',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::PanRight,
			this);

		m_text.SetText(
			"O: ファイルを開く\n"
			"Z: 再生\n"
			"X: 停止\n"
			"C: ポーズ\n"
			"N: ボリュームダウン\n"
			"M: ボリュームアップ\n"
			",: パン(左)\n"
			".: パン(右)\n");

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

	//	ボリュームダウン
	bool VolumeDown(){
		m_nVolume -= 5;
		if ( m_nVolume < 0 )
			m_nVolume = 0;
		if ( m_bMediaLoaded )
			m_music.SetVolume(m_nVolume);
		return true;
	}

	//	ボリュームアップ
	bool VolumeUp(){
		m_nVolume += 5;
		if ( m_nVolume > 100 )
			m_nVolume = 100;
		if ( m_bMediaLoaded )
			m_music.SetVolume(m_nVolume); 
		return true;
	}

	//	パンを左へ
	bool PanLeft(){
		m_nPan -= 10;
		if ( m_nPan < -100 )
			m_nPan = -100;
		if ( m_bMediaLoaded )
			m_music.SetPan(m_nPan);
		return true;
	}

	//	パンを右へ
	bool PanRight(){
		m_nPan += 10;
		if ( m_nPan > 100 )
			m_nPan = 100;
		if ( m_bMediaLoaded )
			m_music.SetPan(m_nPan);
		return true;
	}

	bool OnFrameDoUser()
	{
		char work[256];
		sprintf(work, "Volume:%d Pan:%d", m_nVolume, m_nPan);
		m_text2.SetText(work);
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
