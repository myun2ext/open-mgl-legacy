//////////////////////////////////////////////////////////
//
//	MyuDirectInput
//		- DirectInput�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyuDirectInput.h"

//	�R���X�g���N�^
CMyuDirectInput::CMyuDirectInput()
{
	nRelateCnt = 0;
	m_autoGetBuf = FALSE;
}

//	�f�X�g���N�^
CMyuDirectInput::~CMyuDirectInput()
{

}

//	������
void CMyuDirectInput::Init( HWND hWnd, BOOL in_autoGetBuf )
{
	CMyuKeyboardInput::Init( hWnd );
	m_autoGetBuf = in_autoGetBuf;
}


//	�L�[�{�[�h���͂𖼑O�Ɋ֘A�t����
void CMyuDirectInput::RelateKey( const char *szInputName, BYTE keyCode )
{
	if( nRelateCnt+1 >= RELATE_MAX )
		MyuThrow( 0, "CMyuDirectInput::RelateKey()  ����ȏ�֘A�t���邱�Ƃ͏o���܂���" );

	if( strlen(szInputName) >= RELATE_NAME_MAX )
		MyuThrow( 0, "CMyuDirectInput::RelateKey()  szInputName(%s)���������܂�", szInputName );

	strcpy( relate[nRelateCnt].szInputName, szInputName );
	relate[nRelateCnt].keyCode = keyCode;
	relate[nRelateCnt].oldKeyPush = FALSE;
	relate[nRelateCnt].keyPool = FALSE;

	nRelateCnt++;
}

//	�L�[�����̏u�Ԃɉ�����Ă��邩(�֌W����)
BOOL CMyuDirectInput::IsPushKey( const char *szInputName )
{
	//	������GetBuf()�����s
	if ( m_autoGetBuf == TRUE )
		GetBuf();

	return CMyuKeyboardInput::IsPushKey( GetRelate(szInputName)->keyCode );
}

//	�L�[�������ꂽ���iOnEvent�I�Ȃ��́j(�֌W����)
BOOL CMyuDirectInput::IsDownKey( const char *szInputName )
{
	if ( m_autoGetBuf == TRUE )
		MyuThrow( 0, "IsDownKey()���g�p����ꍇ�AAutoGetBuf���g�p���邱�Ƃ͏o���܂���B" );

	INPUT_RELATE *relate = GetRelate(szInputName);

	if ( relate->keyPool == TRUE )
	{
		relate->keyPool = FALSE;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//	IsKeyPress�̂��߂ɃI�[�o�[���[�h
void CMyuDirectInput::GetBuf()
{
	//	�܂��͕��ʂ�CMyuKeyboardInput�̂��Ăяo��
	CMyuKeyboardInput::GetBuf();

	//	IsKeyPress�̂��߂�
	INPUT_RELATE *p;
	for( int i=0; i<nRelateCnt; i++ )
	{
		p = &relate[i];
		BOOL nowIsPush = CMyuKeyboardInput::IsPushKey( p->keyCode );
		if ( nowIsPush )
		{
			int a =0;
		}

		//	�O�̃L�[��������Ă��Ȃ��A���񉟂���Ă����ꍇ
		if( p->oldKeyPush == FALSE && nowIsPush == TRUE )
		{
			p->keyPool = TRUE;
		}
		p->oldKeyPush = nowIsPush;
	}
}


//	���O����Relate[i]�ւ̃|�C���^���擾
INPUT_RELATE* CMyuDirectInput::GetRelate( const char *szInputName )
{
	INPUT_RELATE *p;
	for( int i=0; i<nRelateCnt; i++ )
	{
		p = &relate[i];

		if( strcmp( szInputName, p->szInputName ) == 0 )
		{
			return p;
		}
	}
	MyuThrow( 0, "CMyuDirectInput::GetRelate()  ���͖� %s �͑��݂��܂���", szInputName );
	return NULL;	//	�����ɗ��邱�Ƃ͂��肦�܂��񂪌x�����������̂�
}