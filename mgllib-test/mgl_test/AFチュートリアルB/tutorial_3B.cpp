#include "stdafx.h"

//	���C���t���[���N���X
class CMglTestFrame : public CAugustWindow
{
private:
	CMglAghImage m_img;
public:
	void OnInit(){
		m_img.Load("test.jpg");
		RegistControl(&m_img);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i���j- �����Ă���Ԉړ�
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_PRESS,
			DIK_LEFT,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)MoveLeft);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i�E�j- �����Ă���Ԉړ�
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_PRESS,
			DIK_RIGHT,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)MoveRight);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i��j- �������u�Ԃ����ړ�
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP,
			DIK_UP,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)MoveUp);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i���j- �������u�Ԃ����ړ�
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_DOWN,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)MoveDown);
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

};
CMglTestFrame g_frame;

//	WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	g_frame.Start();
	return 0;
}
