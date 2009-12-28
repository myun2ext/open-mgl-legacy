#include "mglaugust2.h"

class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustImage2 m_img;
	CAugustKeyboardInput m_kb;
	
	//	����V���ɒǉ�
	int m_moveX;
	int m_moveY;

public:
	//	���������ɌĂ΂��
	bool OnGraphicInitEnded()
	{
		RegistControl(&m_img);
		RegistControl(&m_kb);
		
		m_img.Load("test.jpg");

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i���j
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			AGH_KEYCODE_LEFT,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveLeft,
			this);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i�E�j
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			AGH_KEYCODE_RIGHT,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveRight,
			this);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i��j
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			AGH_KEYCODE_UP,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveUp,
			this);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i���j
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			AGH_KEYCODE_DOWN,
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveDown,
			this);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i�X�y�[�X�L�[�j
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			' ',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveStop,
			this);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�iZ�L�[�j
		m_kb.RegistHandler(
			CAugustKeyboardInput::ON_PRESS,
			'Z',
			(CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyFrame::MoveToInitial,
			this);
		
		//	move�ϐ��̏�����
		m_moveX = 0;
		m_moveY = 0;

		return true;
	}

	//	�e�n���h�����\�b�h
	bool MoveLeft(){
		m_moveX = -1;
		m_moveY = 0;
		return true;
	}
	bool MoveRight(){
		m_moveX = 1;
		m_moveY = 0;
		return true;
	}
	bool MoveUp(){
		m_moveX = 0;
		m_moveY = -1;
		return true;
	}
	bool MoveDown(){
		m_moveX = 0;
		m_moveY = 1;
		return true;
	}

	//	����͈ȉ���ǉ�
	bool MoveStop(){
		m_moveX = 0;
		m_moveY = 0;
		return true;
	}
	bool MoveToInitial(){
		m_img.SetPos(0,0);
		MoveStop();
		return true;
	}
	bool OnFrameDoUser(){
		m_img.Move(m_moveX, m_moveY);
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
