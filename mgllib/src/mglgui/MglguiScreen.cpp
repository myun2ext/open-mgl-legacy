//////////////////////////////////////////////////////////
//
//	MglguiScreen
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglguiScreen.h"

using namespace agh;

/*
//	コンストラクタ
CMglguiScreen::CMglguiScreen()
{
}

//	デストラクタ
CMglguiScreen::~CMglguiScreen()
{
}
*/

//	初期化
void CMglguiScreen::Init( HWND hWnd, int nDispX, int nDispY )
{
	//m_grp.Init(hWnd, nDispX, nDispY, FALSE );

	//	複数のインスタンスを作成する事になるのでInit()が必要
	m_imgPool.Init(&grp);
	m_layer.Init(&grp);

	m_hWnd = hWnd;

	//	virtualな
	OnInit();
	//ScreenUpdate();
}

//////////////////////////////////////////////////

//	画面を更新
void CMglguiScreen::ScreenUpdate()
{
	//if ( m_grp.GetD3dDevPtr() != NULL ) {
	grp.Clear(m_rgbBackground);
	//grp.Clear(D3DCOLOR_BLUE);

	m_layer.Draw();

	//m_grp.UpdateScreen(); -> DoFpsWait()ん中でやってるんですわ。
}

//	フレーム処理
bool CMglguiScreen::DoFrame()
{
	try{
		//	イベント処理
		OnFrameMouseInput();

		//	描画処理
		ScreenUpdate();

		//	フレームレート制御＋α処理 (CMglEzGameFrame)
		if ( CMglEzGameFrame::DoFpsWait() == FALSE )
			return false;
	}
	catch( MyuCommonException e )
	{
		EzErrBox(e.szErrMsg);
		return false;
	}

	return true;
}

bool CMglguiScreen::OnFrameMouseInput()
{
	int x = m_mouse.GetCursorPosX();
	int y = m_mouse.GetCursorPosX();
	int nMoveX = m_mouse.GetXMoveCount();
	int nMoveY = m_mouse.GetYMoveCount();

	//	マウス移動
	if ( nMoveX > 0 || nMoveY > 0)
		CScreenBase::OnMouseMove(x, y, nMoveX, nMoveY);

	//	真中ボタンを押した
	if ( m_mouse.IsOnDownCenterButton() )
		CScreenBase::OnCButtonDown(x,y);

	//	左ボタンを押した
	if ( m_mouse.IsOnDownLeftButton() )
		CScreenBase::OnLButtonDown(x,y);

	//	右ボタンを押した
	if ( m_mouse.IsOnDownRightButton() )
		CScreenBase::OnRButtonDown(x,y);

	return true;
}

//	左ボタンが押された
void CMglguiScreen::OnLButtonDown(int x, int y)
{
	//	コントロールで該当するものがあるか？
	for(int i=0; i<m_controlPtrAry.size(); i++)
	{
		CControlBase *p = m_controlPtrAry[i];
		_AGL_RECT& rect = p->m_rect;

		if ( IsRectInternal((_MSL_RECT*)&rect, x, y) ){
			OnControlLButtonDown(p,x,y);
			return;
		}
	}

	//	どのコントロールにも一致しない場合はバックグラウンド
	OnBackgroundLButtonDown(x,y);
}

//////////////////////////////////////////////////

//	スレッド開始
void CMglguiScreen::AutoLoopThreadStart()
{
	if ( CMyuThreadBase::Execute() != true )
		MyuThrow(64929, "CMglguiScreen: CMyuThreadBase::Execute() failed.");
}

//	スレッド関数
bool CMglguiScreen::ThreadFunc()
{
	try{
		Init(GetWindowHandle(), CMglEzGameFrame::m_nWidth, CMglEzGameFrame::m_nHeight);

		for(;;){
			if ( DoFrame() == false )
				return true;
		}
	}
	catch( MyuCommonException e )
	{
		EzErrBox(e.szErrMsg);
	}

	return true;
}

/////////////////////////////////////////////////////////////

void CMglguiScreen::RegistControl(CMglAghImage* pImage)
{
	const char* szFilePath = pImage->m_strFilePath.c_str();
	const char* szAlias = pImage->m_strLayerName.c_str();
	
	m_imgPool.Cache(szFilePath);
	m_layer.RegistBegin( new CMglImageLayer(m_imgPool[szFilePath]), true );
}

/////////////////////////////////////////////////////////////

DWORD WINAPI CMglguiWindow_ThreadFunc(CMglguiWindow *pWindow){ return (bool)pWindow->__ThreadFunc(); }

bool CMglguiWindow::__ThreadFunc()
{
	//Init(GetWindowHandle(), 640, 480);
	return ThreadFunc();
}

int CMglguiWindow::StartWindow( int nWinWidthSize, int nWinHeightSize,
	const char *szWindowTitle, BOOL bFullscreen )
{
	return StartWindowEx(nWinWidthSize, nWinHeightSize, (LPTHREAD_START_ROUTINE)CMglguiWindow_ThreadFunc,
		this, szWindowTitle, bFullscreen);
}
