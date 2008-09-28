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
void CMglguiScreen::DoFrame()
{
	try{
		/*
		//	ウインドウが生きてるかのチェック
		if ( m_window.IsAlive() != TRUE )
			return FALSE;

		//	抜ける？
		if ( m_bBreak )
			return FALSE;

		//	FPS/デバッグ文字列出力
		if ( m_bFpsShow == TRUE )
		{
			char szFps[64];
			sprintf( szFps, "FPS : %.01f", fps.GetAveFps() );
			m_txtFps.Draw( szFps, 6, 6, D3DCOLORW_XRGB(0,0,0) );
			m_txtFps.Draw( szFps, 5, 5, D3DCOLORW_XRGB(255,255,255) );
		}
		m_txtDebug.Draw( m_strDebugText.c_str(), 6, 21, D3DCOLORW_XRGB(0,0,0) );
		m_txtDebug.Draw( m_strDebugText.c_str(), 5, 20, D3DCOLORW_XRGB(255,255,255) );

		//	スプライト終了
		grp.SpriteEnd();

		//	スクリーンのアップデート
		grp.UpdateScreen();

		//	待つよん
		fps.Sleep();

		//	キーボード入力の更新
		input.Update();

		if ( m_bEscEnd ){
			if ( input.GetOnKey(ASCII_ESC) )
				return FALSE;
		}

		//	スプライト開始
		grp.SpriteBegin();

		return TRUE;
		*/
	}
	catch( MyuCommonException e )
	{
		EzErrBox(e.szErrMsg);
	}
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
		
	}
	catch( MyuCommonException e )
	{
		EzErrBox(e.szErrMsg);
	}

	return true;
}

