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
	//for(int i=0; i<m_ctrlPtrAry.size(); i++)
	for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	{
		//m_ctrlPtrAry[i]->Draw();
		GetVCtrlPtr(i)->Draw();
	}
}

//	フレーム処理
bool CMglguiScreen::DoFrame()
{
	try{
		//	イベント処理
		OnFrameMouseInput();	//	なんか拾わないとfalseを返す仕様になってるっぽい・・・
		/*if ( OnFrameMouseInput() != true )
			return false;*/

		if ( OnFrameKeyboardInput() != true )
			return false;

		//	2008/11/02 ユーザイベント処理
		if ( OnFrameDoUser() != true )
			return false;

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
		//EzErrBox(this->m_hWnd, );
		MyuMessageBox(this->m_hWnd, "Application Error", MB_ICONSTOP,
			"次のエラーが発生したためアプリケーションを終了します。\r\n\r\n"
			"%s", e.szErrMsg);
	}
	catch( agh::CAghException e )
	{
		//EzErrBox(this->m_hWnd, e.GetMessage());
		MyuMessageBox(this->m_hWnd, "Application Error", MB_ICONSTOP,
			"次のエラーが発生したためアプリケーションを終了します。\r\n\r\n"
			"AGH : %s", e.GetMessage());
	}

	return true;
}

/////////////////////////////////////////////////////////////

//	Eventsへ。

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

void CMglguiScreen::RegistControl(CMglAghText* pText)
{
	//	せっとあっぷ
	pText->_Setup(&m_grp);

	//	そして登録
	_RegistControl(pText);
}

void CMglguiScreen::_RegistControl(agh::CControlBase* pCtrl)
{
	m_ctrlPtrAry.push_back(pCtrl);
}
