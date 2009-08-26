#include "mglaugust2.h"

//	���C���t���[���N���X
class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustImage2 m_img;
	CAugustText2 m_text;
	CAugustMouseInput m_mouse;

	bool m_bFlg;
public:

	//	���������ɌĂ΂��
	bool OnGraphicInitEnded()
	{
		//m_fps.SetFps(1);
		//	�R���g���[���N���X�̓o�^
		RegistControl(&m_img);
		RegistControl(&m_text);
		RegistControl(&m_mouse);

		//	�摜�̓ǂݍ���
		m_img.Load("test.jpg");

		//	�}�E�X�N���b�N�n���h���̓o�^
		m_mouse.RegistHandler(
			CAugustMouseInput::EVTTYPE_ON_DOWN,
			CAugustMouseInput::LBUTTON,
			(CAugustMouseInput::CALLBACK_TYPE_MI)&CMyFrame::OnMouseLDown,
			this);
		m_mouse.RegistHandler(
			CAugustMouseInput::EVTTYPE_ON_UP,
			CAugustMouseInput::LBUTTON,
			(CAugustMouseInput::CALLBACK_TYPE_MI)&CMyFrame::OnMouseLUp,
			this);

		//	�}�E�X�ړ��n���h���̓o�^
		m_mouse.RegistHandler(
			CAugustMouseInput::EVTTYPE_ON_MOVE,
			0,
			(CAugustMouseInput::CALLBACK_TYPE_MI)&CMyFrame::OnMouseMove,
			this);

		//	�}�E�X�z�C�[���n���h���̓o�^
		m_mouse.RegistHandler(
			CAugustMouseInput::EVTTYPE_ON_MOVE,
			CAugustMouseInput::CBUTTON,
			(CAugustMouseInput::CALLBACK_TYPE_MI)&CMyFrame::OnMouseZoom,
			this);

		m_bFlg = false;

		return true;
	}

	//	�N���b�N���ɌĂ΂��
	bool OnMouseLDown(int x, int y){
		char msg[256];
		sprintf(msg, "(%d, %d) ���N���b�N����܂����B", x, y);
		//::MessageBoxA(NULL,msg,"OnLButtonDown",NULL);
		m_bFlg = true;
		return true;
	}

	//	�N���b�N���ɌĂ΂��
	bool OnMouseLUp(int x, int y){
		m_bFlg = false;
		return true;
	}

	//	�}�E�X�ړ����ɌĂ΂��
	bool OnMouseMove(int x, int y){
		char msg[256];
		sprintf(msg, "(%d, %d)", x, y);
		m_text.SetText(msg);

		if ( !m_bFlg )
			m_img.Move(x,y);
		return true;
	}

	//	�}�E�X�z�C�[�����ɌĂ΂��
	bool OnMouseZoom(int x, int y){
		m_img.SetScale(m_img.GetScale()+(x/500.0f));
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
