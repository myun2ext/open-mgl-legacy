// mgl_test.cpp : �A�v���P�[�V�����p�̃G���g�� �|�C���g�̒�`
//

#include "stdafx.h"

//	soutei.bmp�̉摜�N���X
class CImgSoutei : public CMglAghImage
{
public:
	//	�R���X�g���N�^���ɂĉ摜�t�@�C�������[�h����悤�ɂ��Ă݂��B
	CImgSoutei(){
		Load("soutei.bmp");
	}
	//	�N���b�N���ɌĂ΂��
	void OnLButtonDown(int x, int y){
		::MessageBox(NULL,"�z��͈͓̔��ł��B","�z�肵�Ă��܂������H",NULL);
	}
};

//	���C���t���[���N���X
class CMglTestFrame : public CMglguiWindow
{
private:
	//CMglAghImage m_img;
	CImgSoutei m_img;
public:
	//	���������ɌĂ΂��
	void OnInit(){
		CMglguiWindow::RegistControl(&m_img);
		RegistKbHandler(0,0,OnKbA);
	}
	//	�E�C���h�E�����O�ɌĂ΂��
	void OnCreateWindow(agh::CREATE_WINDOW_INFO *pWindowInfo){
		pWindowInfo->strWindowTitle = "���C���h�A�v���O����";
	}
	//	�N���b�N���ɌĂ΂��
	void OnLButtonDown(int x, int y){
		::MessageBox(NULL,"�z��͈̔͊O�ł��B","�z�肵�Ă��܂������H",NULL);
	}
	bool OnKbA(){
		::MessageBox(NULL,"test","test",NULL);
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
