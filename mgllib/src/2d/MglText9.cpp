//////////////////////////////////////////////////////////
//
//	MglText
//		- �e�L�X�g
//
//////////////////////////////////////////////////////////

#include "stdafx.h"

//#if _MGL_DXVER == 9
#if _MGL_D3DXVER >= MGL_D3DXVER_ID3DXFONT_CHANGED

#include "MglText.h"

//	�R���X�g���N�^
CMglText::CMglText()
{
	_Init();
}

//	�f�X�g���N�^
CMglText::~CMglText()
{
	//Release();
}

////// �쐬�n //////////////////////////////////////////////////////

//	�쐬
void CMglText::Create( int nHeight, const char* szFontName, BOOL bItalic, BOOL bBold )
{
	//CreatedCheck();
	Release();	//	�R�C�c�̓t�H���g�ύX��Create���܂���̂�Release���Ȃ��Ƒʖڂ��E�E�E

	int nWeight = FW_DONTCARE;
	if ( bBold )
		nWeight = FW_BOLD;

	if ( szFontName == NULL || *szFontName == '\0' )
		szFontName = "�l�r �o�S�V�b�N";

	MyuAssert( D3DXCreateFont( m_d3d, nHeight, nHeight, nWeight, 1, bItalic,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		szFontName, &m_pI ), D3D_OK,
		"CMglText::Create()  D3DXCreateFont()�Ɏ��s�B" );

	//m_text = m_pI;
}

//	�����I�J��
/*void CMglText::Release()
{
	//SAFE_RELEASE( m_text );
	//bCreateFlg = FALSE;
}*/


////// �G��n //////////////////////////////////////////////////////


//	�G��
void CMglText::Draw( const char* szString, int nX, int nY, D3DCOLOR color, DWORD dwOption )
{
	CreateCheck();

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
#if _MGL_DXVER == 9
	//	DirectX9�ł͑������Ƃ��ăX�v���C�g���w�肷��ƃp�t�H�[�}���X�����シ��炵���B�Ƃ肠������񂵂ŁE�E�E (TODO)
	m_pI->DrawText( NULL, szString, -1, &rect, DT_NOCLIP | DT_NOPREFIX | dwOption, color );
#else
	m_pI->DrawText( szString, -1, &rect, DT_NOCLIP | DT_NOPREFIX | dwOption, color );
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