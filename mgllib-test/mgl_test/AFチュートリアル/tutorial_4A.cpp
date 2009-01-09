#include "stdafx.h"

class CMglTestFrame : public CMglguiWindow
{
private:
public:
	void OnInit(){
		//	wav�t�@�C���̓ǂݍ���
		m_audio.Load("hoge.wav");
		m_audio.Load("hoge2.wav","�ق��Q");

		//	�L�[�{�[�h�C�x���g�n���h���o�^
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_Z,
			(MGL_KB_EVT_HANDLER_CALLBACK)PlaySoundHoge);
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_X,
			(MGL_KB_EVT_HANDLER_CALLBACK)PlaySoundHoge2);
	}

	//	Z�Ƃ�X��������wav�Đ�
	bool PlaySoundHoge(){
		m_audio.Play("hoge.wav");
		return true;
	}
	bool PlaySoundHoge2(){
		m_audio.Play("�ق��Q");
		return true;
	}
};

//	WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	CMglTestFrame frame;
	frame.Start();
	return 0;
}
