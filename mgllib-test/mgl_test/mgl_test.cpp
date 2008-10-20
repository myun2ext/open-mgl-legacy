// mgl_test.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"
#include "MglguiScreen.h"
#include "MglAghImage.h"

class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
	CMglAghImage m_img2;
	CMglBitmapData m_bitmap;
public:
	CMglTestFrame(){}
	void OnInit(){
		//	2008/10/15
		EnableEscEnd();
		m_img.EnableDragMovable();
		m_img.Load("font_big.tga");
		m_img2.Load("font_big.tga");
		CMglguiWindow::RegistControl(&m_img);
		//CMglguiWindow::RegistControl(&m_img2);
		/*m_bitmap.Init(&m_img);*/
	}
	/*void OnControlLButtonDown(agh::CControlBase* p, int x, int y)
	{
		//MessageBox("bbb");
		p->OnLButtonDown(x,y);
	}*/
	void OnBackgroundLButtonDown(int x, int y)
	//void OnLButtonDown(int x, int y)
	{
		if ( m_ctrlPtrAry.size() == 0 )
			MessageBox("ccc");
		else
			MessageBox("aaa");
		//inBitmap.Set(point.x, point.y, D3DCOLOR_WHITE);
		//inBitmap.Set(point.x, point.y, D3DCOLOR_RED);
		/*if ( D3DCOLOR_GETA(m_bitmap.Get(x, y)) != 0 )
			m_bitmap.Fill(D3DCOLOR_RED,Rect(x, y, x+3, y+3));*/
	}
	void OnBackgroundMouseMove(int nPosX, int nPosY, int nMoveX, int nMoveY){
		//MessageBox("aaa");
		/*m_img.m_rect.top = nPosY;
		m_img.m_rect.left = nPosX;*/
		//m_img2.SetPos(nPosX, nPosY);
	}


};
CMglTestFrame g_frame;

///////////////////////////////////////////////////

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	//g_frame.EnableEscEnd();
	//g_frame.StartWindow( 640, 480, (LPTHREAD_START_ROUTINE)MainThread,
	//g_frame.StartWindow( 640, 480, (LPTHREAD_START_ROUTINE)MainThread );
	g_frame.Start();

	return 0;
}
