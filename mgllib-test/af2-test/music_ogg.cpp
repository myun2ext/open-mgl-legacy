#include "mglaugust2.h"
#include <string>


//	���C���t���[���N���X
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
	
	//	���f�B�A�t�@�C���I���_�C�A���O
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
		ofn.lpstrFilter = "�Đ��\�ȃ��f�B�A(mp3,wma,ogg,mid,wav)\0*.mp3;*.wma;*.ogg;*.mid;*.wav\0";
		ofn.lpstrTitle = "�t�@�C�����J��";
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;

		//	���s
		if ( GetOpenFileName(&ofn) )
			return szOutFilePath;
		else
			return "";
	}

public:

	//	���������ɌĂ΂��
	bool OnGraphicInitEnded()
	{
//	���O�̓o�^�������ɁE�E�E�i##�Łj
#define __AGH_REGIST_CONTROL_AUTO(CTRL)		RegistControl(&CTRL);

		m_nVolume = 100;
		m_nPan = 0;
		m_bMediaLoaded = false;

		//	�R���g���[���N���X�̓o�^
		RegistControl(&m_kb);
		RegistControl(&m_music);
		RegistControl(&m_music2);
		RegistControl(&m_music3);
		RegistControl(&m_text);
		RegistControl(&m_text2);

		//	�摜�̓ǂݍ���
		//m_music.Load("test.mp3");
		m_music2.Load("test.mp3");
		m_music3.Load("test.wma");

		m_text2.SetPos(0,120);
		//m_music.Play();
		//m_music2.Play();

		//	�}�E�X�N���b�N�n���h���̓o�^
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
			"O: �t�@�C�����J��\n"
			"Z: �Đ�\n"
			"X: ��~\n"
			"C: �|�[�Y\n"
			"N: �{�����[���_�E��\n"
			"M: �{�����[���A�b�v\n"
			",: �p��(��)\n"
			".: �p��(�E)\n");

		return true;
	}

	//	�t�@�C�����J��
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

	//	�Đ�
	bool Play(){
		if ( !m_bMediaLoaded )
			Open();
		else
			m_music.Play();
		return true;
	}

	//	��~
	bool Stop(){
		if ( m_bMediaLoaded )
			m_music.Stop();
		return true;
	}

	//	�|�[�Y
	bool Pause(){
		if ( m_bMediaLoaded )
			m_music.Pause();
		return true;
	}

	//	�{�����[���_�E��
	bool VolumeDown(){
		m_nVolume -= 5;
		if ( m_nVolume < 0 )
			m_nVolume = 0;
		if ( m_bMediaLoaded )
			m_music.SetVolume(m_nVolume);
		return true;
	}

	//	�{�����[���A�b�v
	bool VolumeUp(){
		m_nVolume += 5;
		if ( m_nVolume > 100 )
			m_nVolume = 100;
		if ( m_bMediaLoaded )
			m_music.SetVolume(m_nVolume); 
		return true;
	}

	//	�p��������
	bool PanLeft(){
		m_nPan -= 10;
		if ( m_nPan < -100 )
			m_nPan = -100;
		if ( m_bMediaLoaded )
			m_music.SetPan(m_nPan);
		return true;
	}

	//	�p�����E��
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
