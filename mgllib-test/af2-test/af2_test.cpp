#include <windows.h>
//#include "mwlagh.h"
//#include "AugustWindow2.h"
#include "mglaugust2.h"
//#include "AugustGraphicsManager.h"

//class __declspec(dllimport) CMwlAghWindow;

/*
class CMyWindow : public agh::IWindow
{
public:
	virtual bool OnClose(){ MessageBox(NULL,"sdfa","sfda",0); return true; }
	virtual bool OnDropFiles(std::vector<std::string> &files){
		for(int i=0; i<files.size(); i++)
			MessageBox(NULL,files[i].c_str(),"Drop",0);
		return true;
	}
};
*/
_MWL_HINSTANCE g_hInstance;

//class CMyColorFade : public agh::TColorFadeEffect<agh::math::CIntSineWave>
class CMyColorFade : public agh::TColorFadeEffect<agh::math::CIntSquareWave>
{
public:
	virtual bool OnFadeStop(){return false;}
};

//class CMyWindow : public CMwlAghWindow
class CMyWindow : public CAugustScreen2
{
private:
	typedef CAugustScreen2 _BASE;
//	CAugustGraphicsManager m_grp;

	//agh::CFadeEffect m_fade1;
	//agh::TColorFadeEffect<agh::math::CIntSineWave> m_fade1;
	CMyColorFade m_fade1;
	agh::math::CIntSineWave m_waveY;
	agh::math::CIntCosWave m_waveX;

	CAugustImage2 m_img;
	CAugustText2 m_text;
	CAugustText2 m_text2;

public:
	//	コンストラクタ・デストラクタ
	CMyWindow(){}
	virtual ~CMyWindow(){}

	/*virtual bool OnInit(){
		return false;
	}*/
	
	virtual bool OnGraphicInitEnded()
	{
		//m_sinX.SetRange(-2147483648, 2147483647);
		m_waveX.SetRange(0, 300);
		m_waveY.SetRange(0, 300);

		/////////////////////////////////////////////////////

		RegistSubControl(&m_fade1);
		RegistSubControl(&m_img);
		RegistSubControl(&m_text);
		RegistSubControl(&m_text2);

		m_img.SetScale(0.4f);
		m_img.Load("shana_36-1.jpg");
		m_img.SetAlpha(0x80);

		m_text.SetText("ほげほげほげほげほげおｇへごえｇへおｇ");
		m_text.SetColor(0x99006600);
		m_text.SetPoint(56);
		m_text.SetFontName("MS Mincho");
		m_text.SetOption(AGH_FONT_OPTION_BOLD);
		m_text.SetPos(10,50);

		m_text2.SetText("刑事い");
		m_text2.SetColor(0x99000077);
		m_text2.SetPoint(150);
		m_text2.SetFontName("MS Mincho");
		m_text2.SetOption(AGH_FONT_OPTION_BOLD);
		m_text2.SetPos(50,80);
		
		//m_fade1.Setup(this, 0, 0xffffffff, 100);
		//m_fade1.Setup(this, AGHCOLOR_BLACK, AGHCOLOR_WHITE, 4);
		//m_fade1.Setup(this, AGHCOLOR_BLUE, AGHCOLOR_YELLOW, 30);
		//m_fade1.Setup(this, 0xffbbffff, 0xffff6600, 600);
		m_fade1.Setup(this, 0xffbbffff, 0xffff6600, 4);
		//m_fade1.FadeIn(this, 100);
		return true;
	}

	virtual void OnCreatedWindow(){
		//MessageBox(NULL,"sdfa","sfda",0);
		_BASE::OnCreatedWindow();
		
		RECT rcPos;
		rcPos.left = 10;
		rcPos.right = 100;
		rcPos.top = 50;
		rcPos.bottom = 100;

		HWND hParent = (HWND)GetHwnd();

		HWND hWnd = ::CreateWindowEx(0, "BUTTON", "test",
			0, rcPos.left, rcPos.top, rcPos.right - rcPos.left,
			rcPos.bottom - rcPos.top, (HWND)GetHwnd(), NULL,
			g_hInstance, NULL);

		//	ウインドウの表示をどうするか
		ShowWindow( hWnd, SW_SHOWDEFAULT );
		UpdateWindow( hWnd );

		SetColor(12131);
	}
	//virtual bool OnClose(){ MessageBox(NULL,"sdfa","sfda",0); return true; }
	virtual bool OnDropFiles(std::vector<std::string> &files){
		for(int i=0; i<files.size(); i++)
			MessageBox((HWND)GetHwnd(),files[i].c_str(),"Drop",0);

		return true;
	}
	//	ウインドウ生成前に呼ばれる
	virtual void OnCreateWindow(agh::CREATE_WINDOW_INFO *pWindowInfo){
		pWindowInfo->nWinWidthSize = 800;
		pWindowInfo->nWinHeightSize = 600;
		pWindowInfo->strWindowTitle = "aa";
		//pWindowInfo->strWindowTitle = "さんぷるぷろぐらむｆさｄふぁｓｄふぁあｓｄふぁｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄｄふぁ";
	}

	virtual bool OnFrameDoUser(){
		static int i=-20;
		//Sleep(1000);
		//m_grp.Clear();
		/*
		SetColor(AGHCOLOR_RGB(i,i,i));
		*/
		m_text2.SetPos(
			m_waveX.Get(i/20.0f),
			m_waveY.Get(i/20.0f)
			);

		i++;
		return true;
	}
};

int _MWL_APIENTRY WinMain(
					_MWL_HINSTANCE hInstance,
                    _MWL_HINSTANCE hPrevInstance,
                    char*     lpCmdLine,
                    int       nCmdShow )
//int main()
{
	g_hInstance = hInstance;
//::FreeConsole();
	CMyWindow myWindow;
	//CAugustScreen2 myWindow;
	myWindow.EnableDropFiles();
	myWindow.Start();

	return 0;
}


