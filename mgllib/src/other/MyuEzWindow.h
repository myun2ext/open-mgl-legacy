//////////////////////////////////////////////////////////
//
//	MyuEzWindow  v0.21.00 05/02/21
//		- Window処理を簡単に行うクラス
//
//	v0.10.00 04/11/07
//	・新規作成
//
//	v0.10.10 04/12/14
//	・dwWinStyleをdwExtendWinStyleに。
//	　Windowスタイルはデフォルトで WS_CAPTION | WS_SYSMENU
//	　を付加するように修正。
//
//	v0.10.50 04/12/22
//	・スレッドを正しく終了させるように修正
//
//	v0.20.00 05/02/21
//	・クラス化
//
//	v0.20.01 05/02/21
//	・Active→Aliveに。何かカコヨクネ？（何
//
//	v0.20.02 05/02/21
//	・メッセージ間違えてるんだけど。_|￣|○
//
//	v0.21.00 05/02/21
//	・CMyuEasyWinからCMyuEzWindowに名称変更
//
//////////////////////////////////////////////////////////

#ifndef __MyuEzWindow_H__
#define __MyuEzWindow_H__

//	スレッド終了待ちのデフォルトのタイムアウト
//#define DEFAULT_THREAD_EXIT_TIMEOUT	(3000)
#define DEFAULT_THREAD_EXIT_TIMEOUT		(10000)

//	クラス宣言
class DLL_EXP CMyuEzWindow
{
private:
	int m_nThreadExitTimeout;
	/*volatile */
	BOOL m_bAlive;
	HWND m_hWnd;

public:
	CMyuEzWindow();
	virtual ~CMyuEzWindow();

	int StartWindow( const char* szAppCaption, const char* szWinClassName,
					 int nWinXPos, int nWinYPos, int nWinWidthSize, int nWinHeightSize,
					 DWORD dwExtendWinStyle, LPTHREAD_START_ROUTINE threadFunc,
					 LPVOID threadFuncParam=NULL );
//					 DWORD dwThreadUserOption=0 );

	void SetThreadExitTimeout( int nTimeMs ) { m_nThreadExitTimeout = nTimeMs; }
	BOOL IsAlive() { return m_bAlive; }

	HWND GetWindowHandle() {
		if ( m_bAlive != TRUE )
			MyuThrow( MGLEC_WINDOW_NOT_ALIVE, "CMyuEzWindow::GetWindowHandle()  ウインドウは生存状態にありません。" );
		return m_hWnd;
	}
};

#endif//__MyuEzWindow_H__
