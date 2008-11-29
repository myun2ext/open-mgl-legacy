#include "stdafx.h"
#include "AugustEzGameFrame.h"
#include "MyuFunctions.h"

/*
//	static変数の実体
MGL_EZGAME_FRAME_FUNCPTR	CAugustEzGameFrame::m_userMainThread;
CMyuEzWindow		CAugustEzGameFrame::m_window;
CMglText	CAugustEzGameFrame::m_txtFps;
CMglText	CAugustEzGameFrame::m_txtDebug;
CMglGraphicManager		CAugustEzGameFrame::grp;
CMyuFPS				CAugustEzGameFrame::fps;
CMglInput			CAugustEzGameFrame::input;
string	CAugustEzGameFrame::m_strCaption;
string	CAugustEzGameFrame::m_strDebugText;
int		CAugustEzGameFrame::m_nWindowWidth=0;
int		CAugustEzGameFrame::m_nWindowHeight=0;
BOOL	CAugustEzGameFrame::m_bFpsShow = TRUE;
*/
int		CAugustEzGameFrame::ms_nInstanceCount=0;

//	MainMethodを呼び出す
/*DWORD CallMainThread( DWORD dwInstancePtr )
{
	CAugustEzGameFrame *pInstance = (CAugustEzGameFrame*)(dwInstancePtr);
	return (DWORD)( pInstance->PrivateMainMethod() );
}*/

//	自分自身のメインスレッドを呼び出す
DWORD August_CallMainThread( CAugustEzGameFrame *pFrameInstance )
{
	return (DWORD)( pFrameInstance->PrivateMainMethod() );
}

//	2008/01/22  ユーザパラメータ対応
typedef struct {
	CAugustEzGameFrame *pFrameInstance;
	DWORD dwUserParam;
}
AUGUST_CALL_THREAD_EX_PARAM;

//
DWORD August_CallMainThreadEx( AUGUST_CALL_THREAD_EX_PARAM *pParam )
{
	return (DWORD)( pParam->pFrameInstance->PrivateMainMethod(pParam->dwUserParam) );
}


//	コンストラクタ
CAugustEzGameFrame::CAugustEzGameFrame()
{
	ms_nInstanceCount++;
	//m_strCaption = "MGL Apprication";
	m_bBreak = FALSE;
	m_bEscEnd = FALSE;
	m_bFpsShow = FALSE;	//	2007/01/02 無かったのだけれど…
	m_bFullscreen = FALSE;
}

//	デストラクタ
CAugustEzGameFrame::~CAugustEzGameFrame()
{
	ms_nInstanceCount--;
}

//	ウインドウの開始
int CAugustEzGameFrame::StartWindowEx( int nWinWidthSize, int nWinHeightSize,
//	MGL_EZGAME_FRAME_FUNCPTR mainThreadFuncPtr )
	LPTHREAD_START_ROUTINE mainThreadFuncPtr, void* threadFuncParam, const char *szWindowTitle, BOOL bFullscreen )
{
	_MGL_DEBUGLOG("StartWindowEx() start." );
	CMglStackInstance("CAugustEzGameFrame::StartWindowEx");

	if ( ms_nInstanceCount >= 2 )
	{
		::MessageBox( NULL, "CAugustEzGameFrame のインスタンスが複数あります。", "MyuGameLibrary", MB_ICONERROR );
		return -1;
	}
	
	m_nWindowWidth = nWinWidthSize;
	m_nWindowHeight = nWinHeightSize;
	m_userMainThread = mainThreadFuncPtr;
	m_bFullscreen = bFullscreen;
	m_bBreak = FALSE;

	//	画面サイズ取得
	int nScreenWidth=0;
	int nScreenHeight=0;
	int nWinStartPosX=100;
	int nWinStartPosY=150;
	if ( GetScreenSize( &nScreenWidth, &nScreenHeight ) == TRUE )
	{
		nWinStartPosX = (nScreenWidth/2)-(m_nWindowWidth/2);
		nWinStartPosY = (nScreenHeight/2)-(m_nWindowHeight/2)-16;
	}

	if ( m_strWindowClassName == "" ){
		//	WindowClass名生成（"MGL Appllication WindowClass"＋タイトル）
		m_strWindowClassName = "MGL Appllication WindowClass";
		m_strWindowClassName += szWindowTitle;
		/*string strWindowClassName = "MGL Appllication WindowClass";
		strWindowClassName += szWindowTitle;*/
	}

	AUGUST_CALL_THREAD_EX_PARAM param;
	param.pFrameInstance = this;
	param.dwUserParam = (DWORD)threadFuncParam;

	//	簡易Window処理呼び出し
	_MGL_DEBUGLOG("m_window.StartWindow()" );
	return m_window.StartWindow(
		szWindowTitle, m_strWindowClassName.c_str(),
		nWinStartPosX, nWinStartPosY, m_nWindowWidth, m_nWindowHeight,
		WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		(LPTHREAD_START_ROUTINE)August_CallMainThreadEx, &param );
//		(LPTHREAD_START_ROUTINE)CallMainThread, (DWORD)(this) );
}

//	スレッド
int CAugustEzGameFrame::PrivateMainMethod(){
	return PrivateMainMethod((DWORD)this);
}

//構造化例外が発生すると、この関数が呼ばれる
void _MglAugust_se_translator_function(unsigned int code, struct _EXCEPTION_POINTERS* ep)
{
	throw ep; //標準C++の例外を発生させる
}

//	スレッド - 2008/01/22
int CAugustEzGameFrame::PrivateMainMethod(DWORD dwUserThreadParam)
{
	_set_se_translator(_MglAugust_se_translator_function);

	//__try{
		try	//	例外処理受け付け開始
		{
			_MGL_DEBUGLOG("+ CAugustEzGameFrame::PrivateMainMethod()" );
			CMglStackInstance("CAugustEzGameFrame::PrivateMainMethod");

			_MGL_DEBUGLOG("CoInitialize()..." );
			CoInitialize(NULL);

			_MGL_DEBUGLOG("grp.Init()..." );
			grp.Init( m_window.GetWindowHandle(), m_nWindowWidth, m_nWindowHeight, m_bFullscreen );
			grp.Clear();

			//	2008/10/14
			OnGraphicInitializeEnded();

			_MGL_DEBUGLOG("input.Init()..." );
			input.Init( m_window.GetWindowHandle() );

			//	2008/11/29
			_MGL_DEBUGLOG("audio.Init()..." );
			audio.Init( m_window.GetWindowHandle() );

			m_txtDebug.InitAndEzCreate( &grp, 14 );
			m_txtFps.InitAndEzCreate( &grp, 14 );
			//fps.SetFPS(60); <- 勝手に上書きしちゃだめ！てかデフォルト60なってるし
			//grp.Clear();

			//	MGL S3.1からは呼び出すだけにする（ループはこの中でやってもらう）- 2006/11/25
			_MGL_DEBUGLOG("Call User MainMethod." );
			m_userMainThread((void*)dwUserThreadParam);
			//→ やっぱやめ -> ない！（どっちだよ：笑）

			/*
			//	MGL 3.0まで
			for(;;)
			{
				//	ユーザメソッドを呼び出す
				//if ( m_userMainThread() == 1 )
				//if ( m_userMainThread(this) == FALSE )
				if ( m_userMainThread(this) == TRUE )
					break;

				//	フレーム分待つよん
				if ( DoFpsWait() == FALSE )
					break;
			}
			*/
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

			::MessageBox( NULL, work, NULL, MB_ICONERROR );
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
			::MessageBox( NULL, work, NULL, MB_ICONERROR );
		}
#ifndef _DEBUG
		//	VC++の例外か
		catch(_EXCEPTION_POINTERS *ep)
		{
			//_EXCEPTION_POINTERS *ep = GetExceptionInformation();
			PEXCEPTION_RECORD rec = ep->ExceptionRecord;

			switch(rec->ExceptionCode){
			case 0xc0000094:
				::MessageBox( NULL, "0 で除算されました。", NULL, MB_ICONERROR ); break;
			}

			char work[1024];
			snprintf(work,sizeof(work), ("内部アクセス保護違反です。\r\n"
					"code:%x flag:%x addr:%p params:%d\n"),
				rec->ExceptionCode,
				rec->ExceptionFlags,
				rec->ExceptionAddress,
				rec->NumberParameters
			);
			::MessageBox( NULL, work, NULL, MB_ICONERROR );
		}
		//	VC++の例外か
		catch(...)
		{
			::MessageBox( NULL, "fdssdff", NULL, MB_ICONERROR );
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
	input.Release();
	input.FinalRelease();
	m_txtDebug.Release();
	grp.Release();

	CoUninitialize();

	return 0;
}

//	有効かどうか復帰します（FALSEになったら終了すること！）
BOOL CAugustEzGameFrame::DoFpsWait()
{
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
}

//	ウインドウタイトルの設定
//void CAugustEzGameFrame::SetWindowTitle( const char *szCaption ){ m_strCaption = szCaption; }

//	デバッグ出力
void CAugustEzGameFrame::PrintDebug( const char* szFormat, ... )
{
	char work[512];
	va_list vl;
	va_start( vl, szFormat );
	vsnprintf( work, sizeof(work), szFormat, vl );
	va_end( vl );
	m_strDebugText = work;
}
