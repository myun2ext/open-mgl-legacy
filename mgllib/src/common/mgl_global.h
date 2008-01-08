//	2007/01/03 Add. ライブラリ内でグローバルに使用する変数等を宣言する

#ifndef __mgl_global_H__
#define __mgl_global_H__

/*	既に MglGraphicManager に定義済であった…
class CMglGraphicManager;

extern CMglGraphicManager *g_pMglDefaultDg;

//	g_pMglDefaultDg の設定
void SetDefaultGraphicManager( CMglGraphicManager* pDg );
*/

/*	MyuFunctionsに既にある…
//extern HWND g_hWndDefault;

*/
DLL_EXP void MglDefaultInitialize( HWND hWnd );
DLL_EXP HWND GetDefaultHwnd();

#endif//__mgl_global_H__
