//////////////////////////////////////////////////////////
//
//	MyuDebugLog
//		- �f�o�b�O���O�N���X
//
//////////////////////////////////////////////////////////

#include <windows.h>
#include "MyuDebugLog.h"

//	�R���X�g���N�^
CMyuDebugLog::CMyuDebugLog()
{
	m_fp = NULL;
	m_nSpace = 0;
}

//	�f�X�g���N�^
CMyuDebugLog::~CMyuDebugLog()
{
	Close();
}

//	�I�[�v��
void CMyuDebugLog::Open( const char* szLogFile )
{
	m_fp = fopen( szLogFile, "w" );
	//if ( m_fp == NULL )
	//	MyuThrow( 0, "CMyuDebugLog::Open()  ���O�t�@�C�� %s �̃I�[�v���Ɏ��s�B", szLogFile );
}

//	�N���[�Y
void CMyuDebugLog::Close()
{
	if ( m_fp != NULL )
	{
		fclose( m_fp );
		m_fp = NULL;
	}
}

//	�o��
/*
################# �C���f���g�@�\�ɂ��� #################

	format�̊J�n������'+'�ɂ���ƁA�C���f���g�������܂��B
	format�̊J�n������'-'�ɂ���ƁA�C���f���g���グ�܂��B
*/
void CMyuDebugLog::Print( const char* format, ... )
{
	if ( m_fp == NULL )
		return;
		//MyuThrow( 0, "���O�t�@�C�����I�[�v������Ă��܂���B" );

	//////////////////////////
	//
	//		�C���f���g
	//

	//	�}�C�i�X�͐��
	if ( *format == '-' )
		m_nSpace-=2;
	
	char szIndent[256];
	ZeroMemory( szIndent, sizeof( szIndent ));
	if ( m_nSpace < 0 )
		strcpy( szIndent, "<<Indent Error!!>>" );
	else
		memset( szIndent, ' ', m_nSpace );

	//	�v���X�͌��
	if ( *format == '+' )
		m_nSpace+=2;

	//////////////////////////////

	char szTime[256];
	char szWork[2048];

	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);//getting current time
	sprintf( szTime, "%02d:%02d:%02d.%03d", SysTime.wHour,SysTime.wMinute, SysTime.wSecond,SysTime.wMilliseconds);
	sprintf( szWork, "%s  %s%s\n", szTime, szIndent, format );

	va_list vl;
	va_start( vl, format );
	vfprintf( m_fp, szWork, vl );
	va_end( vl );
	fflush( m_fp );
}
