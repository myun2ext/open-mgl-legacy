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
class CMyColorFade : public agh::TColorFadeEffect<agh::math::CIntTriWave>
{
public:
	virtual bool OnFadeStop(){return false;}
};

#define BLUR_COUNT	(8)

class QQQQ{};






class CFileItem : public CAugustText2
{
public:
	CFileItem(){}
	
_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnRegist()
	{
		SetText("dsfd");
	}
};

class CFileItemArray : public agh::CControlVector<CFileItem>
{
private:
	typedef agh::CControlVector<CFileItem> _BASE;
protected:
public:
	void Add(){
		CFileItem *pAddedItem = &(_BASE::Add( CFileItem() ));

		pAddedItem->SetPos(8, m_ctrlAry.size()*17);
	}

_AGH_EVENT_ACCESS_MODIFIER:
};

class CFileItemArray1 : public agh::CVisualControlBase
{
protected:
	std::vector<CFileItem> m_items;
public:
	void Add(){
		m_items.push_back( CFileItem() );

		CFileItem *pAddedItem = m_items.rbegin().operator ->();
		RegistControl(pAddedItem);

		pAddedItem->SetPos(7, m_items.size()*17);
	}
};




//class CMyWindow : public CMwlAghWindow
class CMyWindow : public CAugustScreen2//, public agh::_CKeyboardBase_CDummyBase
{
private:
	typedef CAugustScreen2 _BASE;
//	CAugustGraphicsManager m_grp;

	//agh::CFadeEffect m_fade1;
	//agh::TColorFadeEffect<agh::math::CIntSineWave> m_fade1;
	CMyColorFade m_fade1;
	CMyColorFade m_fade2;
	agh::math::CIntSineWave m_waveY;
	agh::math::CIntCosWave m_waveX;

	CAugustImage2 m_img;
	CAugustImage2 m_img_bl[BLUR_COUNT];

	CAugustText2 m_text;
	CAugustText2 m_text2;
	CAugustText2 m_text2_bl[BLUR_COUNT];
	agh::CControlVector<CAugustText2> m_textAry;
	CFileItemArray1 m_textAry1;
	CFileItemArray m_itemAry;

	//std::vector::iterator it;

public:
	CAugustKeyboardInput m_input;
	CAugustMouseInput m_mouse;

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
		//RegistSubControl(&m_text);
		RegistSubControl(&m_text2);
		RegistSubControl(&m_input);
		RegistSubControl(&m_mouse);
		RegistSubControl(&m_textAry);
		RegistSubControl(&m_textAry1);
		RegistSubControl(&m_itemAry);

		CAugustText2 m_text3 = m_text2;

		//m_textAry.Add().SetText("ZZZZZZZZZZZZZZZZ");
		//m_textAry.Add().SetText("YYYYYYYYYYYYYY");
		m_textAry1.Add();
		m_textAry1.Add();
		//m_itemAry.Add();
		//m_itemAry.Add();

		m_img.SetScale(0.4f);
		m_img.Load("shana_36-1.jpg");
		m_img.SetAlpha(0x80);

		m_text.SetText("ほげほげほげほげほげおｇへごえｇへおｇ");
		m_text.SetColor(0x99006600);
		m_text.SetPoint(56);
		m_text.SetFontName("MS Mincho");
		m_text.SetOption(AGH_FONT_OPTION_BOLD);
		m_text.SetPos(10,50);

		//m_input.RegistHandler(AGH_KB_EVT_HANDLER_EVTTYPE_ON_PRESS, 'Z', (agh::KB_EVT_HANDLER_CALLBACK)&CMyWindow::OnZ);
		//m_input.RegistHandler(CAugustKeyboardInput::ON_PRESS, 'Z', (agh::KB_EVT_HANDLER_CALLBACK)&CMyWindow::OnZ);
		m_input.RegistHandler(CAugustKeyboardInput::ON_PRESS, 'Z', (CAugustKeyboardInput::CALLBACK_TYPE_MI)&CMyWindow::OnZ, this);
		//m_input.RegistHandler(CAugustKeyboardInput::ON_PRESS, 'Z', dynamic_cast<CAugustKeyboardInput::CALLBACK_TYPE*>(&CMyWindow::OnZ) );

		/*CAugustKeyboardInput::CALLBACK_TYPE c = (CAugustKeyboardInput::CALLBACK_TYPE)&CMyWindow::OnZ;

		(bool (QQQQ::*)())&CMyWindow::OnZ;
		(bool (QQQQ::*)(long,long))&CMyWindow::OnClick;
		CAugustMouseInput::CALLBACK_TYPE b = (bool (QQQQ::*)(long,long))&CMyWindow::OnClick;*/

		m_mouse.RegistHandler(CAugustMouseInput::ON_PRESS, CAugustMouseInput::LBUTTON, (CAugustMouseInput::CALLBACK_TYPE_MI)&CMyWindow::OnClick, this);

		m_mouse.RegistHandler(CAugustMouseInput::ON_MOVE, CAugustMouseInput::CBUTTON, (CAugustMouseInput::CALLBACK_TYPE_MI)&CMyWindow::OnClick, this);

		///////////////////////
		CAugustImage2 *pImg ;
		int a = 0x80;
		for(int i=0; i<BLUR_COUNT; i++){
			pImg = &m_img_bl[i];
			RegistSubControl(pImg);

			pImg->SetScale(0.4f);
			pImg->Load("shana_36-1.jpg");

			a *= (int)0.7f;
			//pImg->SetAlpha(0x60-(0x0c*i));
			pImg->SetAlpha(a);
		}
		/////////////////////

		CAugustText2 *pText = &m_text2;
		for(int i=-1; i<BLUR_COUNT; i++){
			if ( i == -1 ){
				pText = &m_text2;
				//pText->SetColor(AGHCOLOR_ARGB(0x99-((0x25*i)), 0,0, 0x77));
				pText->SetColor(AGHCOLOR_ARGB(0, 0,0, 0x77));
			}
			else{
				pText = &m_text2_bl[i];
				RegistSubControl(pText);
				//pText->SetColor(AGHCOLOR_ARGB(0x40-((0x04*i)), 0,0, 0x77));
				pText->SetColor(AGHCOLOR_ARGB(0, 0,0, 0x77));
			}

			pText->SetText("刑事い");
			//pText->SetColor(0x99000077);
			pText->SetPoint(150);
			pText->SetFontName("MS Mincho");
			pText->SetOption(AGH_FONT_OPTION_BOLD);
			pText->SetPos(50,80);
		}
		
		//m_fade1.Setup(this, 0, 0xffffffff, 100);
		//m_fade1.Setup(this, AGHCOLOR_BLACK, AGHCOLOR_WHITE, 4);
		//m_fade1.Setup(this, AGHCOLOR_BLUE, AGHCOLOR_YELLOW, 30);
		//m_fade1.Setup(this, 0xffbbffff, 0xffff6600, 600);
		//m_fade1.Setup(this, 0xffbbffff, 0xffff6600, 40);
		m_fade1.Setup(this, 0xffff6600, 0xffbbffff, 600);
		m_fade2.Setup(&m_img, 0xffffffff, 0x00ffffff, 60);
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
		for(int i=0; i<(int)files.size(); i++)
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
		static const int _SPEED = 10;
		static const float _SPEEDF = 10;
		static const float _BLUR = 60;
		static int i=-_SPEED;
		//Sleep(1000);
		//m_grp.Clear();
		/*
		SetColor(AGHCOLOR_RGB(i,i,i));
		*/
		m_text2.SetPos(
			m_waveX.Get(i/_SPEEDF),
			m_waveY.Get(i/_SPEEDF)
			);

		m_img.SetPos(
			m_waveX.Get(i/_SPEEDF),
			m_waveY.Get(i/_SPEEDF)
			);

		CAugustText2 *pText = &m_text2;
		for(int j=-1; j<BLUR_COUNT; j++){
			if ( j == -1 )
				pText = &m_text2;
			else
				pText = &m_text2_bl[j];

			pText->SetPos(
				m_waveX.Get(i/_SPEEDF - (j/_BLUR)),
				m_waveY.Get(i/_SPEEDF - (j/_BLUR))
				);
		}

		CAugustImage2 *pImg ;
		for(int j=0; j<BLUR_COUNT; j++){
			pImg = &m_img_bl[j];

			pImg->SetPos(
				m_waveX.Get(i/_SPEEDF - (j/_BLUR)),
				m_waveY.Get(i/_SPEEDF - (j/_BLUR))
				);
		}

		i++;
		return true;
	}

	bool OnZ(){
		MessageBox(NULL,NULL,NULL,NULL);
		return true;
	}
	bool OnClick(long x, long y){
		MessageBox(NULL,"OnClick",NULL,NULL);
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
	class CNag{
	private:
		int nag;
	public:
		CNag(){ nag = 6566; }
		virtual void Nag(){ 
			MessageBox(NULL,"Nag",NULL,NULL);
			/*printf("Nag=%d\n", nag );*/
		}
	};
	class CNag3{
	public:
		void Nag2(){
			MessageBox(NULL,"Nag3",NULL,NULL);
		}
	};
	class CNag2 : public CNag, public CNag3 {
	private:
		int nag;
	public:
		CNag2(){ nag = 6566; }
		void Nag2(){ 
			MessageBox(NULL,"Nag2",NULL,NULL);
			/*printf("Nag=%d\n", nag );*/
		}
	};

	CNag nag;

	g_hInstance = hInstance;
//::FreeConsole();
	CMyWindow myWindow;
	myWindow.m_input.RegistHandler(CAugustKeyboardInput::ON_PRESS, 'X', (CAugustKeyboardInput::CALLBACK_TYPE_SI)&CNag::Nag, &nag);
	myWindow.m_input.RegistHandler(CAugustKeyboardInput::ON_PRESS, 'C', (CAugustKeyboardInput::CALLBACK_TYPE_MI)&CNag2::Nag2, &nag);
	//CAugustScreen2 myWindow;
	myWindow.EnableDropFiles();
	myWindow.Start();

	return 0;
}



/////////////////////////////////////////////////////////

/*
//class CMyWindow : public CMwlAghWindow
class CMyWindow2 : public CAugustScreen2//, public agh::_CKeyboardBase_CDummyBase
{
private:
	typedef CAugustScreen2 _BASE;

	CAugustKeyboardInput m_input;
	CAugustMouseInput m_mouse;

public:
	//	コンストラクタ・デストラクタ
	CMyWindow2(){}
	virtual ~CMyWindow2(){}
	
	bool OnGraphicInitEnded()
	{
		(bool (QQQQ::*)())&CMyWindow2::OnZ;
		(bool (QQQQ::*)(long,long))&CMyWindow2::OnClick;
	}

	bool OnZ(){
		MessageBox(NULL,NULL,NULL,NULL);
		return true;
	}
	bool OnClick(long x, long y){
		MessageBox(NULL,NULL,NULL,NULL);
		return true;
	}
};
*/
