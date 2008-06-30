#include "stdafx.h"
#include "mgl_global.h"

/*	既に MglGraphicManager に定義済であった…
CMglGraphicManager *g_pMglDefaultDg=NULL;

//	g_pMglDefaultDg の設定
void SetDefaultGraphicManager( CMglGraphicManager* pDg )
{
	/*if ( g_pMglDefaultDg != NULL )
		MyuThrow2( 0, 0x0100, "SetDefaultGraphicManager()  デフォルトGraphicManagerは既に設定済です。" );*//*

	//	2007/01/03 既に設定済＝複数 CMglGraphicManager が存在ならNULLにし使用不可とする。
}
*/

/*	MyuFunctionsに既にある… -> こっちへ移動*/
HWND g_hWndDefault=NULL;
CMyuSimpleStackTrace g_stackTrace;

/////////////////////////////////////////////////////////

//	g_hWndDefault の設定
void MglDefaultInitialize( HWND hWnd )
{
	g_hWndDefault = hWnd;
}

//	g_hWndDefault の取得（エラーチェック付き）
HWND GetDefaultHwnd()
{
	if ( g_hWndDefault == NULL )
	{
		MyuThrow2( 0, MSGMSLNO_GLOBAL_HWND_DEFAULT, "g_hWndDefault が未設定です。" );
	}
	return g_hWndDefault;
}
