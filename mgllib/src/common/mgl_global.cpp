#include "stdafx.h"
#include "mgl_global.h"

/*	���� MglGraphicManager �ɒ�`�ςł������c
CMglGraphicManager *g_pMglDefaultDg=NULL;

//	g_pMglDefaultDg �̐ݒ�
void SetDefaultGraphicManager( CMglGraphicManager* pDg )
{
	/*if ( g_pMglDefaultDg != NULL )
		MyuThrow2( 0, 0x0100, "SetDefaultGraphicManager()  �f�t�H���gGraphicManager�͊��ɐݒ�ςł��B" );*//*

	//	2007/01/03 ���ɐݒ�ρ����� CMglGraphicManager �����݂Ȃ�NULL�ɂ��g�p�s�Ƃ���B
}
*/

/*	MyuFunctions�Ɋ��ɂ���c -> �������ֈړ�*/
HWND g_hWndDefault=NULL;
CMyuSimpleStackTrace g_stackTrace;

/////////////////////////////////////////////////////////

//	g_hWndDefault �̐ݒ�
void MglDefaultInitialize( HWND hWnd )
{
	g_hWndDefault = hWnd;
}

//	g_hWndDefault �̎擾�i�G���[�`�F�b�N�t���j
HWND GetDefaultHwnd()
{
	if ( g_hWndDefault == NULL )
	{
		MyuThrow2( 0, MSGMSLNO_GLOBAL_HWND_DEFAULT, "g_hWndDefault �����ݒ�ł��B" );
	}
	return g_hWndDefault;
}
