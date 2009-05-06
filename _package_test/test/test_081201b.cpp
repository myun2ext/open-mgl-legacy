// test.cpp : �A�v���P�[�V�����p�̃G���g�� �|�C���g�̒�`
//

#include "stdafx.h"
//#include "MglOgg.h"

class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
	CMglAghText m_text;
	CMglBgm m_music;
public:
	//	���������ɌĂ΂��
	void OnInit(){
		EnableEscEnd();
		m_img.Load("test.jpg");
		CMglguiWindow::RegistControl(&m_img);
		CMglguiWindow::RegistControl(&m_text);

		m_text.SetText("�ق����ق���");
		m_text.SetFontSize(150);
		m_text.SetColor( AGHCOLOR_ARGB(120,180,180,255) );
		m_text.SetPos(80,380);

		m_img.SetColor(0xf0ffffff);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i���j- �����Ă���Ԉړ�
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_PRESS,
			DIK_LEFT,
			(MGL_KB_EVT_HANDLER_CALLBACK)&CMglTestFrame::MoveLeft);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i�E�j- �����Ă���Ԉړ�
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_PRESS,
			DIK_RIGHT,
			(MGL_KB_EVT_HANDLER_CALLBACK)&CMglTestFrame::MoveRight);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i��j- �������u�Ԃ����ړ�
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP,
			DIK_UP,
			(MGL_KB_EVT_HANDLER_CALLBACK)&CMglTestFrame::MoveUp);

		//	�L�[�{�[�h�C�x���g�n���h���o�^�i���j- �������u�Ԃ����ړ�
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_DOWN,
			(MGL_KB_EVT_HANDLER_CALLBACK)&CMglTestFrame::MoveDown);


		m_audio.Load("pwr_snr2.wav","a");
		//	�L�[�{�[�h�C�x���g�n���h���o�^
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_Z,
			(MGL_KB_EVT_HANDLER_CALLBACK)&CMglTestFrame::PlaySoundZ);

		//m_music.Load("dante.ogg");
		m_music.Load("kanon_lstrgt_org.mp3");
		m_music.Play();
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
	bool PlaySoundZ(){
		m_audio.LoopPlay("a");
		return true;
	}
	//	�E�C���h�E�����O�ɌĂ΂��
	void OnCreateWindow(agh::CREATE_WINDOW_INFO *pWindowInfo){
		pWindowInfo->nWinWidthSize = 800;
		pWindowInfo->nWinHeightSize = 600;
		//pWindowInfo->strWindowTitle = "����Ղ�Ղ낮���";
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