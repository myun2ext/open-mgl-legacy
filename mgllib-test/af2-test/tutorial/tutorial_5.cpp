#include "mglaugust2.h"

//	���C���t���[���N���X
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustImage2 m_img;
	CAugustMouseInput m_mouse;
public:

	//	���������ɌĂ΂��
	bool OnGraphicInitEnded()
	{
		//	�R���g���[���N���X�̓o�^
		RegistControl(&m_img);
		RegistControl(&m_mouse);

		//	�摜�̓ǂݍ���
		m_img.Load("test.jpg");

		//	�}�E�X�N���b�N�n���h���̓o�^
		m_mouse.RegistHandler(
			CAugustMouseInput::EVTTYPE_ON_DOWN,
			CAugustMouseInput::LBUTTON,
			(CAugustMouseInput::CALLBACK_TYPE_MI)&CMyFrame::OnMouseLDown,
			this);

		return true;
	}

	//	�N���b�N���ɌĂ΂��
	bool OnMouseLDown(int x, int y)
	{
		if ( x >= 200 && x <= 400 && y >= 100 && y <= 200 )
			::MessageBoxA((HWND)GetHwnd(),  "����[��", "�����Ȃ��N���b�N", NULL);

		else if ( x >= 200 && x <= 400 && y >= 300 && y <= 400 )
			::MessageBoxA((HWND)GetHwnd(),"�����͂��߂�E�E�E", "�����Ȃ��N���b�N", NULL);

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
