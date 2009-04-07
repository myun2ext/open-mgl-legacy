#include "stdafx.h"
#include "AugustImage1.h"

LPD3DXFONT pFont;	//フォント

HRESULT InitFont(IDirect3DDevice9* pDevice)
{
    //文字列フォントの設定
    if(FAILED(D3DXCreateFont(pDevice,
        14,                     //文字高さ
        7,                      //文字幅
        FW_BOLD,                //フォントスタイル
        NULL,                   //ミップマップモデルの数
        FALSE,                  //斜体にするかどうか
        SHIFTJIS_CHARSET,       //文字セット
        OUT_DEFAULT_PRECIS,
        PROOF_QUALITY,
        FIXED_PITCH | FF_MODERN,
        "tahoma",               //フォントの種類
        &pFont)))
    {
        return E_FAIL;
    }
    return TRUE;
}

//文字列レンダリング関数
VOID RenderString(LPSTR szStr,    //表示する文字列
            INT iX,         //表示X座標
            INT iY)         //表示Y座標
{
    RECT rect = {iX, iY, 0, 0}; //表示領域
    //RECT rect = {iX, iY, 200, 200}; //表示領域

    //文字列サイズを計算
    pFont->DrawText(
        NULL,
        szStr,
        -1,             //表示サイズ(-1で全部)
        &rect,          //表示範囲
        DT_CALCRECT,    //表示範囲に調整
        NULL);

    //そのサイズでレンダリング
    pFont->DrawText(
        NULL,
        szStr,
        -1,                     //表示サイズ(-1で全部)
        &rect,                  //表示範囲
        DT_LEFT | DT_BOTTOM,    //左詰めで両端揃え
        0xff00ff00);            //色
}

//////////////////////////////////////////

//	メインフレームクラス
class CTestScreem : public CAugustScreen
{
private:
	CAugustImage m_img;
	CAugustText m_text;
	float m_f;

public:
	void OnInit(){
		RegistControl(&m_img);
		RegistControl(&m_text);

		m_img.Load("test.jpg");
		//m_img.Load("pilot.dds");
		m_img.SetAngle(45);
		m_img.SetScale(0.8f);
		//m_img.SetSrcRect(10,10,200,200);
		m_img.Move(150,150);

		m_text.SetText("hogeaaああああaaaaa\ndddああ111llk");
		m_text.SetFontSize(320);
		//m_text.SetFontName("MS PGothic");
		m_text.SetFontName(MGL_FONT_NAME_TAHOMA);
		m_text.SetColor(0x99000022);

		m_img.EnableCentering();
		m_img.EnableDrag();
		m_text.EnableDrag();

		InitFont(CAugustScreen::g_->grp.GetD3dDevPtr());

		m_f = 0.0f;
	}

/*	void OnDraw(){
		m_text.Draw();
		//RenderString("hoge",0,0);
	}*/

	bool OnFrameDoUser(){
		//m_img.SetAngle(80);
		m_f += 0.005f;
		m_img.SetScale(m_f);
		m_img.SetAngle(m_f*200);

		return true;
	}
};

class CTestFrame : public CAugustWindow
{
private:
	CTestScreem m_screen;
public:
	void OnInit(){
		this->SetActiveScreen(&m_screen);
		this->EnableEscEnd();
	}

	bool OnFrame(){
		return true;
	}
};
CTestFrame g_frame;

//	WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	g_frame.Start();
	return 0;
}
