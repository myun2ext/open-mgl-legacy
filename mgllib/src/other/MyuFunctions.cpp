#include "stdafx.h"
#include "MyuFunctions.h"

/*
HWND g_hWndDefault=NULL;

void MglDefaultInitialize( HWND hWnd )
{
	g_hWndDefault = hWnd;
}
*/

//	�G���[�`�F�b�N�t��atoi()
BOOL ec_atoi( const char* s, int* npOut )
{
	char *endptr=NULL;
	*npOut = (int)strtol( s, &endptr, 10 );
	if ( *endptr != '\0' )
		return FALSE;

	return TRUE;
}

/*
//	��ʃT�C�Y�̎擾
BOOL GetScreenSize( int* pnWidth, int* pnHeight )
{
	HDC hDc = GetDC(NULL);
	if ( hDc == NULL )
		return FALSE;

	*pnWidth = GetDeviceCaps( hDc, HORZRES );
	*pnHeight = GetDeviceCaps( hDc, VERTRES );

	return TRUE;
}
*/
