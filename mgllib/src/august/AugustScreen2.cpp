//////////////////////////////////////////////////////////
//
//	AugustScreen2
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustScreen2.h"
#include "MglGraphicManager.h"
#include "MyuFPS.h"

using namespace agh;
using namespace std;

//////////////////////////////////////////////////

CAugustFpsManager::CAugustFpsManager()
{
	m_pInternal = new CMyuFPS();
}

CAugustFpsManager::~CAugustFpsManager()
{
	delete m_pInternal;
}

void CAugustFpsManager::SetFps(int nFps){
	m_pInternal->SetFPS(nFps);
}
float CAugustFpsManager::GetAveFps(){
	return m_pInternal->GetAveFps();
}
float CAugustFpsManager::GetFps(){
	return m_pInternal->GetFps();
}

void CAugustFpsManager::DoWait(){
	m_pInternal->Sleep();
}

//////////////////////////////////////////////////

/*
//	コンストラクタ
CAugustScreen2::CAugustScreen2()
{
}

//	デストラクタ
CAugustScreen2::~CAugustScreen2()
{
}
*/

//////////////////////////////////////////////////

#define m_hWnd (HWND)m_vphWnd

//構造化例外が発生すると、この関数が呼ばれる
void _MglAugust2_se_translator_function(unsigned int code, struct _EXCEPTION_POINTERS* ep)
{
	throw ep; //標準C++の例外を発生させる
}

bool CAugustScreen2::ThreadFunc(int anyParam)
{
	m_bEndFlg = false;

	if ( OnInitFirst() == false )
		return false;

	_set_se_translator(_MglAugust2_se_translator_function);

	//__try{
		try	//	例外処理受け付け開始
		{
			CMglStackInstance("CAugustEzGameFrame::PrivateMainMethod");

			m_grp.Init();

			//	ユーザコールバック
			if ( OnGraphicInitEnded() == false )
				return false;

			/*
			_MGL_DEBUGLOG("input.Init()..." );
			input.Init( m_window.GetWindowHandle() );
			_MGL_DEBUGLOG("input.Init() end." );

			//	2008/11/29
			if ( m_bEnabledAudio ){
				_MGL_DEBUGLOG("audio.Init()..." );
				InitAudio();
				_MGL_DEBUGLOG("audio.Init() end." );
			}

			_MGL_DEBUGLOG("Create Debug/FPS Fonts..." );
			//m_txtDebug.InitAndEzCreate( &grp, 14 );
			//m_txtFps.InitAndEzCreate( &grp, 14 );
			m_txtDebug.Init( &grp );
			m_txtFps.Init( &grp );
			m_txtDebug.Create( 14 );
			m_txtFps.Create( 14 );
			//fps.SetFPS(60); <- 勝手に上書きしちゃだめ！てかデフォルト60なってるし
			//grp.Clear();
			_MGL_DEBUGLOG("end." );

			//	2009/01/23  CAugustWindow側のOnInit()呼び出し
			_MGL_DEBUGLOG("EzFrame_OnInit()..." );
			EzFrame_OnInit();

			//	MGL S3.1からは呼び出すだけにする（ループはこの中でやってもらう）- 2006/11/25
			_MGL_DEBUGLOG("Call User MainMethod." );
			m_userMainThread((void*)dwUserThreadParam);
			//→ やっぱやめ -> ない！（どっちだよ：笑）
			*/

			MainLoop();
		}
		//	例外処理 V3.0
		catch( MglException exp )
		{
			char work[1024];
			snprintf( work, sizeof(work),
				"Myu Game Library Error :\r\n"
				"  Location : %s::%s()   Error Code : 0x%08X\r\n"
				"\r\n"
				"%s",
				exp.szClass, exp.szMethod, exp.nInternalCode, exp.szMsg );

			::MessageBox( m_hWnd, work, NULL, MB_ICONERROR );
		}
		//	例外処理
		catch( MyuCommonException except )
		{
			char work[512];
			//snprintf( work,sizeof(work), "ErrNo : 0x%08X\r\n%s", except.nErrCode, except.szErrMsg );
			snprintf( work,sizeof(work),
				"ErrNo : 0x%08X\r\n%s\r\n"
				"\r\n"
				"%s",
				except.nErrCode, except.szErrMsg,
				g_stackTrace.Dump().c_str() );
			::MessageBox( m_hWnd, work, NULL, MB_ICONERROR );
		}
#ifndef _DEBUG
		//	VC++の例外か
		catch(_EXCEPTION_POINTERS *ep)
		{
			//_EXCEPTION_POINTERS *ep = GetExceptionInformation();
			PEXCEPTION_RECORD rec = ep->ExceptionRecord;

			switch(rec->ExceptionCode){
			case 0xc0000094:
				::MessageBox( m_hWnd, "0 で除算されました。", NULL, MB_ICONERROR ); break;
			}

			char work[1024];
			snprintf(work,sizeof(work), ("内部アクセス保護違反です。\r\n"
					"code:%x flag:%x addr:%p params:%d\n"),
				rec->ExceptionCode,
				rec->ExceptionFlags,
				rec->ExceptionAddress,
				rec->NumberParameters
			);
			::MessageBox( m_hWnd, work, NULL, MB_ICONERROR );
		}
		//	VC++の例外か
		catch(...)
		{
			::MessageBox( m_hWnd, "fdssdff", NULL, MB_ICONERROR );
		}
#endif//_DEBUG
	/*}
	__except(_EXCEPTION_POINTERS *ep = GetExceptionInformation())
	{
		_EXCEPTION_POINTERS *ep = GetExceptionInformation();
		PEXCEPTION_RECORD rec = ep->ExceptionRecord;

		char work[1024];
		snprintf(work,sizeof(work), ("内部アクセス保護違反です。\r\n"
				"code:%x flag:%x addr:%p params:%d\n"),
			rec->ExceptionCode,
			rec->ExceptionFlags,
			rec->ExceptionAddress,
			rec->NumberParameters
		);
		::MessageBox( NULL, work, NULL, MB_ICONERROR );
	}*/

	//	↓try-catch内でなくていいのか…？
	//	ここで開放しとかないとスレッド外で開放されて落ちる
	//if ( m_bEnabledAudio )	<- 別にInitしてないならしてないでReleaseしても問題ないんでね・・・？
/*	audio.Release();
	input.Release();
	input.FinalRelease();
	m_txtDebug.Release();*/
	m_grp.Release();

	//m_bEndFlg = false; <- 違くない？
	m_bEndFlg = true;

	ExitWindow();

	return true;
}

void CAugustScreen2::MainLoop()
{
	for(;;)
	{
		DoFrame();

		//	フレーム分待つよん
		if ( DoFpsWait() == false )
			break;
	}
}

//	有効かどうか復帰します（FALSEになったら終了すること！）
bool CAugustScreen2::DoFpsWait()
{
	//	ウインドウが生きてるかのチェック
	//if ( m_window.IsAlive() != TRUE )
	if ( m_bEndFlg )
		return false;

	/*
	//	抜ける？
	if ( m_bBreak )
		return FALSE;
	*/

	//	スプライト終了
	m_grp.GetMglGrp()->SpriteEnd();

	//	スクリーンのアップデート
	m_grp.GetMglGrp()->UpdateScreen();

	//	待つよん
	m_fps.DoWait();

	//	キーボード入力の更新
	/*input.Update();

	if ( m_bEscEnd ){
		if ( input.GetOnKey(ASCII_ESC) )
			return FALSE;
	}*/

	//	スプライト開始
	m_grp.GetMglGrp()->SpriteBegin();

	return true;
}

//	閉じるー
bool CAugustScreen2::OnClose()
{
	m_bEndFlg = true;
	return true;
}

//	描画ー
void CAugustScreen2::OnDraw()
{

	m_grp.OnDraw();
}

//	フレーム処理
bool CAugustScreen2::DoFrame()
{
	//	2009/01/23 マウスのハンドルは無効に出来るように。
	//	（結構処理長いし、うっかりクリックとかで余計な処理走るとまずいし・・・）
	if ( m_bUseMouseHandle == true )
	{
		//OnFrameMouseInput();	//	なんか拾わないとfalseを返す仕様になってるっぽい・・・
		/*if ( OnFrameMouseInput() != true )
			return false;*/
	}

	//	キーボードのハンドル処理
	/*if ( OnFrameKeyboardInput() != true )
		return false;*/

	//	2008/11/02 ユーザイベント処理
	if ( OnFrameDoUser() != true )
		return false;

	//	各コントロールのフレーム処理
	//for(int i=0; i<m_ctrlPtrAry.size(); i++)
	//for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	for(citr it=cbegin(); it != cend(); it++)
	//for(vector<CControlBase*>::iterator it=cbegin(); it != cend(); it++)
	{
		it->OnFrame();
		//(*it)->OnFrame();
		//((CControlBase*)it)->OnFrame();
		//m_ctrlPtrAry[i]->OnFrame();
		//GetVCtrlPtr(i)->Draw();
	}

	return true;
}

