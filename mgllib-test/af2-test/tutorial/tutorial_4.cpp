#include "mglaugust2.h"

class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustImage2 m_img;
	CAugustKeyboardInput m_kb;

public:
	//	���������ɌĂ΂��
	bool OnGraphicInitEnded()
	{
		RegistControl(&m_img);
		RegistControl(&m_kb);
		
		m_img.Load("test.jpg");

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i���j- �����Ă���Ԉړ�
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			AGH_KEYCODE_LEFT,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveLeft,
			this);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i�E�j- �����Ă���Ԉړ�
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			AGH_KEYCODE_RIGHT,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveRight,
			this);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i��j- �������u�Ԃ����ړ�
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_UP,
			AGH_KEYCODE_UP,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveUp,
			this);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i���j- �������u�Ԃ����ړ�
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_DOWN,
			AGH_KEYCODE_DOWN,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveDown,
			this);

		return true;
	}

	//	�e�n���h�����\�b�h
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
