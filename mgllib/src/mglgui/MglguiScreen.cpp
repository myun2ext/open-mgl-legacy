//////////////////////////////////////////////////////////
//
//	MglguiScreen
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglguiScreen.h"

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
	m_grp.Init(hWnd, nDispX, nDispY, FALSE );

	//	複数のインスタンスを作成する事になるのでInit()が必要
	m_imgPool.Init(&m_grp);
	m_layer.Init(&m_grp);

	m_hWnd = hWnd;
	ScreenUpdate();
}

//////////////////////////////////////////////////

//	画面を更新
void CMglguiScreen::ScreenUpdate()
{
	//if ( m_grp.GetD3dDevPtr() != NULL ) {
	m_grp.Clear(m_rgbBackground);

	m_layer.Draw();

	m_grp.UpdateScreen();
}

//	フレーム処理
bool CMglguiScreen::DoFrame()
{
	try{
		//	イベント処理
		OnFrameMouseInput();

		//	フレーム処理 (CMglEzGameFrame)
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

