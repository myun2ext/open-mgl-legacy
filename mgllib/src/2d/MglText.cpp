//////////////////////////////////////////////////////////
//
//	MglText
//		- �e�L�X�g
//
//////////////////////////////////////////////////////////

#include "stdafx.h"

//#if _MGL_DXVER == 8
#if _MGL_D3DXVER < MGL_D3DXVER_ID3DXFONT_CHANGED
#include "MglText.h"

//	�R���X�g���N�^
/*CMglText::CMglText()
{
	_Init();

	//	�f�t�H���g�t�H���g
	Create();
}*/

//	�f�X�g���N�^
CMglText::~CMglText()
{
	Release();
}

////// �쐬�n //////////////////////////////////////////////////////

//	�T�C�Y�w��ɂ��쐬
void CMglText::InitAndCreate( CMglGraphicManager* in_myudg, int nHeight )
{
	Release();	//	�ꉞ�����[�X

	HFONT hFont = CreateFont( nHeight, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 0, 0, 4, 0, "" );
	if ( hFont == NULL )
		MyuThrow( 0, "CMglText::InitAndCreate()  CreateFont()�Ɏ��s�B" );

	InitAndCreate( in_myudg, hFont );

	//	20007/01/02
	DeleteObject(hFont);
}

//	szFontName�̃f�t�H���g�͋󕶎��܂���NULL
void CMglText::Create( CMglGraphicManager* in_myudg, int nHeight, const char* szFontName,
		BOOL bItalic, BOOL bBold, BOOL bUnderLine, BOOL bStrikeOut, float fAngle )
{
	Release();	//	�ꉞ�����[�X

	int nWeight = FW_DONTCARE;
	if ( bBold )
		nWeight = FW_BOLD;

	HFONT hFont = CreateFont( nHeight, 0, (int)(fAngle*10), (int)(fAngle*10),
		nWeight, bItalic, bUnderLine, bStrikeOut, DEFAULT_CHARSET, 0, 0, 4, 0, szFontName );

	if ( hFont == NULL )
		MyuThrow( 0, "CMglText::InitAndCreate()  CreateFont()�Ɏ��s�B" );

	InitAndCreate( in_myudg, hFont );

	//	20007/01/02
	DeleteObject(hFont);
}
	
//	�������y�э쐬
void CMglText::InitAndCreate( CMglGraphicManager* in_myudg, HFONT hFont )
{
	Release();	//	�ꉞ�����[�X

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

	bCreateFlg = FALSE;
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
#if _MGL_D3DXVER >= MGL_D3DXVER_ID3DXSPRITE_CHANGED
	//	DirectX9�ł͑������Ƃ��ăX�v���C�g���w�肷��ƃp�t�H�[�}���X�����シ��炵���B�Ƃ肠������񂵂ŁE�E�E (TODO)
	m_text->DrawText( NULL, szString, -1, &rect, DT_NOCLIP | DT_NOPREFIX | dwOption, color );
#else
	m_text->DrawText( szString, -1, &rect, DT_NOCLIP | DT_NOPREFIX | dwOption, color );
#endif
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

#endif