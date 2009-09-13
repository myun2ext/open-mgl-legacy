#include "mglaugust2.h"

//	���C���t���[���N���X
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustSoundManager m_sound;
	CAugustMusic m_music;
	CAugustMusic m_music2;
	CAugustMusic m_music3;
	CAugustKeyboardInput m_kb;

public:

	//	���������ɌĂ΂��
	bool OnGraphicInitEnded()
	{
//	���O�̓o�^�������ɁE�E�E�i##�Łj
#define __AGH_REGIST_CONTROL_AUTO(CTRL)		RegistControl(&CTRL);

		//	�R���g���[���N���X�̓o�^
		RegistControl(&m_sound);
		RegistControl(&m_kb);
		RegistControl(&m_music);
		RegistControl(&m_music2);
		RegistControl(&m_music3);

		//	�摜�̓ǂݍ���
		m_sound.Load("hoge.wav");

		m_music.Load("test.wma");
		m_music2.Load("test.mp3");
		m_music3.Load("test.wma");

		//m_music.Play();
		//m_music2.Play();

		//	�}�E�X�N���b�N�n���h���̓o�^
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'Z',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::OnZ,
			this);

		return true;
	}

	//	�N���b�N���ɌĂ΂��
	bool OnZ(){
		m_sound.Play("hoge.wav");
		m_music3.Play();
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
