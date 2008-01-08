//////////////////////////////////////////////////////////
//
//	MglText
//		- �e�L�X�g
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglText.h"

//	�R���X�g���N�^
CMglText::CMglText()
{
	m_myudg = NULL;
	m_d3d = NULL;
	m_text = NULL;
	bCreateFlg = FALSE;
	bSetParamFlg = FALSE;
}

//	�f�X�g���N�^
CMglText::~CMglText()
{
	Release();
}

////// �쐬�n //////////////////////////////////////////////////////

//	�T�C�Y�w��ɂ��쐬
void CMglText::InitAndCreate( CMglGraphicManager* in_myudg, int nHeight )
{
	HFONT hFont = CreateFont( nHeight, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 0, 0, 4, 0, "" );
	if ( hFont == NULL )
		MyuThrow( 0, "CMglText::InitAndCreate()  CreateFont()�Ɏ��s�B" );

	InitAndCreate( in_myudg, hFont );

	//	20007/01/02
	DeleteObject(hFont);
}

//	�������y�э쐬
void CMglText::InitAndCreate( CMglGraphicManager* in_myudg, HFONT hFont )
{
	if ( bCreateFlg == TRUE )
		MyuThrow( 0, "CMglText::InitAndCreate()  ���� InitAndCreate() �͎��s����Ă��܂��B" );

	if ( hFont == NULL )
		MyuThrow( 0, "CMglText::InitAndCreate()  hFont��NULL�ł��B" );

	m_myudg = in_myudg;
	m_d3d = m_myudg->GetD3dDevPtr();

	//	�����J���p�Ƀ��t�@�����X��ǉ�
	m_myudg->AddRefOfAutoRelease( this );

	MyuAssert( D3DXCreateFont( m_d3d, hFont, &m_text ),
		D3D_OK, "CMglText::InitAndCreate()  D3DXCreateFont()�Ɏ��s�B" );

	bCreateFlg = TRUE;
}

//	�����I�J��
void CMglText::Release()
{
	//	�����J���p�̃��t�@�����X���폜
	DELREF();

	SAFE_RELEASE( m_text );
}


////// �G��n //////////////////////////////////////////////////////


//	�G��
void CMglText::Draw( const char* szString, int nX, int nY, D3DCOLOR color, DWORD dwOption )
{
	if ( bCreateFlg == FALSE )
		MyuThrow( 0, "CMglText::Draw()  InitAndCreate() �܂��� InitAndEzCreate() �����s���Ă��������B" );

	RECT rect;
	if ( (dwOption & DT_RIGHT) != 0 )
		_Rect( 0, nY, nX, m_myudg->GetDispY(), &rect );
	else
		_Rect( nX, nY, m_myudg->GetDispX(), m_myudg->GetDispY(), &rect );

	//MyuAssert( m_text->DrawText( szString, -1, &rect, DT_NOCLIP | dwOption, color ),
	//	D3D_OK, "CMglText::Draw()  m_text->DrawText()�Ɏ��s�B" );

	//	DirectX8�̃w���v���Ɛ���I����0�����ŐV��DirectX9�̃w���v�������
	//	�u�_���I�P�ʂ��g���ăe�L�X�g�̍�����Ԃ��v�ɂȂ��Ă���c�B
	//	�_���I�P�ʂŃ`�F�b�N����DirectX8�œ����Ȃ������猙�Ȃ̂Ń`�F�b�N����̂�߂܂�(;�L�D`)�U
	m_text->DrawText( szString, -1, &rect, DT_NOCLIP | DT_NOPREFIX | dwOption, color );
}

//	�t�H�[�}�b�gDraw()
void CMglText::FDraw( const char* szString, ... )
{
	SetParamCheck();

	char szFormatedString[1024];
	if ( strlen( szString ) > sizeof(szFormatedString)-1 )
		MyuThrow( 0, "CMglText::FDraw()�� %d �o�C�g���z���镶������������Ƃ͏o���܂���B", sizeof(szFormatedString)-1 );

	va_list vl;
	va_start( vl, szString );
	vsprintf( szFormatedString, szString, vl );
	va_end( vl );

	Draw( szFormatedString, m_nX, m_nY, m_color, m_dwOption );
}

//	�t�H���g��ݒ�
void CMglText::SetDrawParam( int in_nX, int in_nY, D3DCOLOR in_color, DWORD in_dwOption )
{
	m_nX = in_nX;
	m_nY = in_nY;
	m_dwOption = in_dwOption;
	m_color = in_color;
	bSetParamFlg = TRUE;
}
