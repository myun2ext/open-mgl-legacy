#include "mglaugust2.h"

//	���C���t���[���N���X
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustKeyboardInput m_kb;

	CAugustSoundManager m_soundMgr;
	CAugustSound m_sound1;
	CAugustSound m_sound2;

public:

	//	���������ɌĂ΂��
	bool OnGraphicInitEnded()
	{
		//	�R���g���[���N���X�̓o�^
		RegistControl(&m_kb);
		RegistControl(&m_soundMgr);

		m_soundMgr.RegistControl(&m_sound1);
		m_soundMgr.RegistControl(&m_sound2);

		//	�摜�̓ǂݍ���
		m_sound1.Load("hoge.wav");
		m_sound2.Load("hoge2.wav");

		//	Z�L�[�n���h���̓o�^
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'Z',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::OnZ,
			this);

		//	X�L�[�n���h���̓o�^
		m_kb.RegistHandler(
			CAugustKeyboardInput::EVTTYPE_ON_DOWN,
			'X',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::OnX,
			this);

		return true;
	}

	//	Z�L�[�ɂčĐ�
	bool OnZ(){
		m_sound1.Play();
		return true;
	}

	//	X�L�[�ɂčĐ�
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