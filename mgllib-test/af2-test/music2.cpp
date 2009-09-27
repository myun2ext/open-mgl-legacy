#include "mglaugust2.h"
#include <string>

//	���C���t���[���N���X
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustMusic m_music;
	CAugustKeyboardInput m_kb;
	CAugustText2 m_text;

	bool m_bMediaLoaded;	//	���f�B�A���ǂݍ��ݍςȂ�true�ɂ���
	
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
		if ( ::GetOpenFileName(&ofn) )
			return szOutFilePath;
		else
			return "";
	}

public:

	//	���������ɌĂ΂��
	bool OnGraphicInitEnded()
	{
		//	���f�B�A���ǂ݂��܂�Ă��Ȃ��̂�false��ݒ�
		m_bMediaLoaded = false;

		//	�R���g���[���N���X�̓o�^
		RegistControl(&m_kb);
		RegistControl(&m_music);
		RegistControl(&m_text);

		//	�L�[�{�[�h�n���h���̓o�^
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
			"O: �t�@�C�����J��\n"
			"Z: �Đ�\n"
			"X: ��~\n"
			"C: �|�[�Y\n");

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
