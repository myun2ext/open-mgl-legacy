#include "mglaugust2.h"

class CMyFrame : public CAugustWindowFrame2
{
private:
	CAugustText2 m_text;
	CAugustText2 m_text2;

public:
	//	���������ɌĂ΂��
	bool OnGraphicInitEnded()
	{
		RegistControl(&m_text);
		RegistControl(&m_text2);
		
		m_text.SetText("����̓e�X�g�Ȃ�[�B");

		m_text2.SetText("�f�J�������Ȃ�[");
		m_text2.SetFontSize(60);
		m_text2.SetPos(0,20);
		m_text2.SetColor(AGHCOLOR_RGB(40,100,200));

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
