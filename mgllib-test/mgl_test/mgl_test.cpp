// mgl_test.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"

//	soutei.bmpの画像クラス
class CImgSoutei : public CMglAghImage
{
public:
	//	コンストラクタ内にて画像ファイルをロードするようにしてみた。
	CImgSoutei(){
		Load("soutei.bmp");
	}
	//	クリック時に呼ばれる
	void OnLButtonDown(int x, int y){
		::MessageBox(NULL,"想定の範囲内です。","想定していましたか？",NULL);
	}
};

//	メインフレームクラス
class CMglTestFrame : public CMglguiWindow
{
private:
	//CMglAghImage m_img;
	CImgSoutei m_img;
public:
	//	初期化時に呼ばれる
	void OnInit(){
		CMglguiWindow::RegistControl(&m_img);
		RegistKbHandler(0,0,OnKbA);
	}
	//	ウインドウ生成前に呼ばれる
	void OnCreateWindow(agh::CREATE_WINDOW_INFO *pWindowInfo){
		pWindowInfo->strWindowTitle = "ライ○ドアプログラム";
	}
	//	クリック時に呼ばれる
	void OnLButtonDown(int x, int y){
		::MessageBox(NULL,"想定の範囲外です。","想定していましたか？",NULL);
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
