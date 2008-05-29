#ifndef __MyuFunctions_H__
#define __MyuFunctions_H__

//DLL_EXP void MglDefaultInitialize( HWND hWnd );

//	エラーチェック付きatoi()
DLL_EXP BOOL ec_atoi( const char* s, int* npOut );

/*	-> GraphicUtilへ移動
//	画面サイズの取得
DLL_EXP BOOL GetScreenSize( int* pnWidth, int* pnHeight );
*/

#endif//__MyuFunctions_H__