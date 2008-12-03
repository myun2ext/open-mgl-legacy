#ifndef __MglEzGameFrame_H__
#define __MglEzGameFrame_H__

#include "MyuEzWindow.h"
#include "MglGraphicManager.h"
#include "MglText.h"
#include "MyuFPS.h"
#include "MglInput.h"
#include "MglAudio.h"

//typedef int (WINAPI *MGL_EZGAME_FRAME_FUNCPTR)();

//	クラス宣言
class DLL_EXP CMglEzGameFrame
{
private:
	//	インスタンスの数をカウント (多重インスタンス抑止)
	static int ms_nInstanceCount;

	/*
	//	クラス
	static CMyuEzWindow m_window;
	static CMglText m_txtDebug;
	static CMglText m_txtFps;
	static string m_strDebugText;

	//	ウインドウ関連
	static int m_nWidth;
	static int m_nHeight;
	//static MGL_EZGAME_FRAME_FUNCPTR m_userMainThread;
	static LPTHREAD_START_ROUTINE m_userMainThread;
	static string m_strCaption;

	static BOOL m_bFpsShow;
	*/
	string m_strDebugText;
	string m_strWindowClassName;
	LPTHREAD_START_ROUTINE m_userMainThread;

	BOOL m_bFpsShow;
	BOOL m_bBreak;
	BOOL m_bEscEnd;
	BOOL m_bFullscreen;
	BOOL m_bEnabledAudio;	//	2008/11/30

protected:
	//	クラス
	CMyuEzWindow m_window;
	CMglText m_txtDebug;
	CMglText m_txtFps;
	//string m_strWindowTitle;
	//CMglGraphicText m_text;	-> 毎回作る

	//	ウインドウ関連
	int m_nWidth;
	int m_nHeight;
	//MGL_EZGAME_FRAME_FUNCPTR m_userMainThread;
	//string m_strCaption;

public:
	/*static CMglGraphicManager grp;
	static CMyuFPS fps;
	static CMglInput input;*/
	CMglGraphicManager grp;
	CMyuFPS fps;
	CMglInput input;
	CMglAudio audio;

	//	コンストラクタ・デストラクタ
	CMglEzGameFrame();
	virtual ~CMglEzGameFrame();

	/////////////////////////////////////////////////////
	//
	//		公開メンバメソッド群
	//

	//	ウインドウの開始
	/*int StartWindow( int nWinWidthSize, int nWinHeightSize,
		MGL_EZGAME_FRAME_FUNCPTR mainThreadFuncPtr );*/
	int StartWindow( int nWinWidthSize, int nWinHeightSize,
		LPTHREAD_START_ROUTINE mainThreadFuncPtr,
		const char *szWindowTitle="MGL Application", BOOL bFullscreen=FALSE )
	{
		return StartWindowEx(nWinWidthSize, nWinHeightSize, mainThreadFuncPtr,
			this, szWindowTitle, bFullscreen);
	}
	int StartWindowEx( int nWinWidthSize, int nWinHeightSize,
		LPTHREAD_START_ROUTINE mainThreadFuncPtr, void* threadFuncParam,
		const char *szWindowTitle="MGL Application", BOOL bFullscreen=FALSE );

	//	FPSで待つ
	BOOL DoFpsWait();
	BOOL DoEvent(){ return DoFpsWait(); }	//	VB風
	BOOL DoFrameEnd(){ return DoFpsWait(); }
	void SetBreak(){ m_bBreak = TRUE; }

	//	各種設定
	/*void SetWindowTitle( const char *szCaption );	//	ウインドウのタイトル*/
	void SetFPS( int nFps ){ fps.SetFPS(nFps); }	//	FPSの設定
	void SetFps( int nFps ){ fps.SetFPS(nFps); }	//	FPSの設定
	void SetFpsShow( BOOL bFpsShow ){ m_bFpsShow = bFpsShow; }
	void EnableEscEnd(){ m_bEscEnd = TRUE; }
	void DisableEscEnd(){ m_bEscEnd = FALSE; }
	void SetWindowClassName(const char* szWindowClass){ m_strWindowClassName = szWindowClass; }
	void SetWindowTitle(const char* szWindowTitle){
		/*if ( m_window.GetWindowHandle() == NULL )
			m_strWindowTitle = szWindowTitle;
		else*/
		::SetWindowText(m_window.GetWindowHandle(), szWindowTitle);
	}
	//const char* GetWindowTitle(){ ::GetWindowText(m_window.GetWindowHandle(), szWindowTitle); }
	//void SetStartupFillColor( D3DCOLOR color ){}

	//	デバッグ用
	void PrintDebug( const char* szFormat, ... );

	//	内部で使用
	int PrivateMainMethod();
	int PrivateMainMethod(DWORD dwUserThreadParam);

	//	取得とか拡張とか
	HWND GetWindowHandle(){ return m_window.GetWindowHandle(); }
	int MessageBox( LPCSTR lpText, LPCSTR lpCaption=NULL, UINT uType=0 ){
		return ::MessageBox( m_window.GetWindowHandle(), lpText, lpCaption, uType ); }
	int MsgBox( LPCSTR lpText, LPCSTR lpCaption=NULL, UINT uType=0 ){
		return ::MessageBox( m_window.GetWindowHandle(), lpText, lpCaption, uType ); }

	//	テキスト絵画
	void DrawText( const char* szText, int x=0, int y=0, int size=12, D3DCOLOR color=D3DCOLOR_BLACK ){
		CMglGraphicText text;
		text.InitAndCreate( &grp, size );
		text.Draw( szText, x, y, color );
	}
	void DrawText( const char* szText, int x, int y, HFONT hFont, D3DCOLOR color=D3DCOLOR_BLACK ){
		CMglGraphicText text;
		text.InitAndCreate( &grp, hFont );
		text.Draw( szText, x, y, color );
	}
	void DrawText( int x, int y, int size, D3DCOLOR color, const char* szText, ... ){
		char work[1024];
		va_list vl;
		va_start(vl,szText);
		vsnprintf( work,sizeof(work), szText, vl );
		va_end(vl);

		DrawText( work, x, y, size, color );
	}
	void DrawText( int x, int y, HFONT hFont, D3DCOLOR color, const char* szText, ... ){
		char work[1024];
		va_list vl;
		va_start(vl,szText);
		vsnprintf( work,sizeof(work), szText, vl );
		va_end(vl);

		DrawText( work, x, y, hFont, color );
	}

	//	キー入力
	char Getc(){ return input.GetOnKey(); }
	char GetChar(){ return input.GetOnKey(); }
	char GetKey(){ return input.GetOnKey(); }


	void InitAudio(){
		audio.Init( m_window.GetWindowHandle() );
		m_bEnabledAudio = TRUE;
	}
	void EnableAudio(){ InitAudio(); }

protected:
	virtual void OnGraphicInitializeEnded(){}
};

typedef CMglEzGameFrame CMglEzFramework;

#endif//__MglEzGameFrame_H__