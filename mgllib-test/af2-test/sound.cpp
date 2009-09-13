#include "mglaugust2.h"

//	���C���t���[���N���X
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustSound m_sound;
	CAugustKeyboardInput m_kb;

public:

	//	���������ɌĂ΂��
	bool OnGraphicInitEnded()
	{
		//	�R���g���[���N���X�̓o�^
		RegistControl(&m_sound);
		RegistControl(&m_kb);

		//	�摜�̓ǂݍ���
		m_sound.Load("hoge.wav");

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
