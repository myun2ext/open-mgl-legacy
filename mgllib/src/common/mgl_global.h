//	2007/01/03 Add. ���C�u�������ŃO���[�o���Ɏg�p����ϐ�����錾����

#ifndef __mgl_global_H__
#define __mgl_global_H__

#include "mgl_common.h"

/*	���� MglGraphicManager �ɒ�`�ςł������c
class CMglGraphicManager;

extern CMglGraphicManager *g_pMglDefaultDg;

//	g_pMglDefaultDg �̐ݒ�
void SetDefaultGraphicManager( CMglGraphicManager* pDg );
*/

/*	MyuFunctions�Ɋ��ɂ���c
//extern HWND g_hWndDefault;

*/
DLL_EXP void MglDefaultInitialize( HWND hWnd );
DLL_EXP HWND GetDefaultHwnd();

//	�O���[�o���ϐ�
extern CMyuDebugLog g_workLog;

#endif//__mgl_global_H__
