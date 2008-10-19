//////////////////////////////////////////////////////////
//
//	MglguiScreen
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglguiScreen.h"

using namespace agh;

class DLL_EXP agh::CScreenBase;

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
	m_imgCache.Init(&grp);
	//m_layer.Init(&grp);

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

	//m_layer.Draw();
	OnDraw();

	//m_grp.UpdateScreen(); -> DoFpsWait()ん中でやってるんですわ。
}
void CMglguiScreen::OnDraw()
{
	for(int i=0; i<m_ctrlPtrAry.size(); i++)
	{
		m_ctrlPtrAry[i]->Draw();
	}
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

bool CMglguiScreen::OnFrameMouseInput()
{
	/*int x = m_mouse.GetCursorPosX();
	int y = m_mouse.GetCursorPosY();*/
	//POINT point = m_mouse.GetCursorPos();
	m_nCachedCurPos = m_mouse.GetCursorPos();
	int x = m_nCachedCurPos.x;
	int y = m_nCachedCurPos.y;
	m_nCachedCurPosX = x;
	m_nCachedCurPosY = y;
	int nMoveX = m_mouse.GetXMoveCount();
	int nMoveY = m_mouse.GetYMoveCount();

#define _P this
	agh::CControlBase *pControl = GetPosControl(x,y);
	if ( pControl == NULL )
		pControl = this;

	/*	例えばドラッグで画面外の時に対応出来ないのでここではチェックしない事とする
	//	ウインドウの範囲外ならイベント範囲外とする
	if ( x < 0 || y < 0 ||
		 x > )
		return false;
	*/

	//	割り込み処理
	OnMouseEventInterrupt(pControl, x, y, nMoveX, nMoveY);

	bool ret = false;

	//	マウス移動
	if ( nMoveX != 0 || nMoveY != 0 ){
		//CScreenBase::OnMouseMove(x, y, nMoveX, nMoveY); <- これじゃあ継承した方が呼ばれないぢゃない・・・
		_P->OnMouseMove(x, y, nMoveX, nMoveY);
		ret = true;
	}

	//	真中ボタンを押した
	if ( m_mouse.IsOnDownCenterButton() ){
		//CScreenBase::OnCButtonDown(x,y);
		_P->OnCButtonDown(x,y);
		ret = true;
	}

	//	左ボタンを押した
	if ( m_mouse.IsOnDownLeftButton() ){

		//	ウインドウの範囲外ならイベント範囲外とする
		if ( x < 0 || y < 0 ||
			 x >= CMglEzGameFrame::m_nWidth || y >= CMglEzGameFrame::m_nHeight )
		{
			//	何もしない。（if文条件反転にすべきだったね...）
		}
		else
		{
			//CScreenBase::OnLButtonDown(x,y);
			_P->OnLButtonDown(x,y);
			ret = true;
		}
	}

	//	右ボタンを押した
	if ( m_mouse.IsOnDownRightButton() ){
		//CScreenBase::OnRButtonDown(x,y);
		_P->OnRButtonDown(x,y);
		ret = true;
	}

	return ret;
}

/////////////////////////////////////////////////////////////

void CMglguiScreen::RegistControl(CMglAghImage* pImage)
{
	const char* szFilePath = pImage->m_strFilePath.c_str();
	const char* szAlias = pImage->m_strLayerName.c_str();

	//	せっとあっぷ
	pImage->_Setup(&m_grp, &m_imgCache);
	
	//	きゃっしゅ
	m_imgCache.Cache(szFilePath);

	pImage->SetRect(0,0,m_imgCache.Get(szFilePath)->GetBmpWidth(),
		m_imgCache.Get(szFilePath)->GetBmpHeight());

	//	そして登録
	_RegistControl(pImage);
	//m_layer.RegistBegin( new CMglImageLayer(m_imgCache[szFilePath]), true );
}
void CMglguiScreen::_RegistControl(agh::CControlBase* pCtrl)
{
	m_ctrlPtrAry.push_back(pCtrl);
}

/////////////////////////////////////////////////////////////

DWORD WINAPI CMglguiWindow_ThreadFunc(CMglguiWindow *pWindow){ return (bool)pWindow->__ThreadFunc(); }

bool CMglguiWindow::__ThreadFunc()
{
	//Init(GetWindowHandle(), 640, 480);
	return ThreadFunc();
}

/*int CMglguiWindow::StartWindow( int nWinWidthSize, int nWinHeightSize,
	const char *szWindowTitle, BOOL bFullscreen )
{
	return StartWindowEx(nWinWidthSize, nWinHeightSize, (LPTHREAD_START_ROUTINE)CMglguiWindow_ThreadFunc,
		this, szWindowTitle, bFullscreen);
}*/
void CMglguiWindow::Start()
{
	CREATE_WINDOW_INFO winInfo;
	MGLGUI_WINDOW_ON_CREATE_EXTEND extendInfo;

	winInfo.nWinWidthSize = 640;
	winInfo.nWinHeightSize = 480;
	winInfo.nWinXPos = 0;	//	現在つかってないお・・・
	winInfo.nWinYPos = 0;	//	現在つかってないお・・・
	winInfo.pExtendStructure = &extendInfo;
	winInfo.strWindowClass = "";	//	現在つかってないお・・・
	winInfo.strWindowTitle = "Application";

	extendInfo.bFullScreen = FALSE;

	//	オーバーロード呼び出し
	OnCreateWindow(&winInfo);

	/*return*/ StartWindowEx(
		winInfo.nWinWidthSize,
		winInfo.nWinHeightSize, (LPTHREAD_START_ROUTINE)CMglguiWindow_ThreadFunc,
		this, winInfo.strWindowTitle.c_str(), extendInfo.bFullScreen);
}
