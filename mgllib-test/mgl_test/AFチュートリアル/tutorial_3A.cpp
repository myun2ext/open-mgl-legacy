#include "stdafx.h"

//	���C���t���[���N���X
class CMglTestFrame : public CMglguiWindow
{
public:
	//	���������ɌĂ΂��
	void OnInit(){
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_PRESS,
			DIK_A,
			(MGL_KB_EVT_HANDLER_CALLBACK)OnKbA);
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
