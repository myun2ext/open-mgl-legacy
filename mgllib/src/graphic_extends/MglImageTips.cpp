//////////////////////////////////////////////////////////
//
//	MglImageTips
//		- MglGraphicManager �T�[�t�F�X�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglImageTips.h"
#include "MyuSpecialIniReader.h"

//	�ǂݍ���
void CMglImageTips::Load( LPCSTR szFileName )
{
	CMyuSpecialIniReader ini;
	ini.Setup(szFileName);

	//	�C���[�W�t�@�C�����擾
	const char* szImageFileName = ini.GetString("FILE::IMAGE_FILE");
	if ( *szImageFileName == '\0' )
		MyuThrow( 0, "CMglImageTips::Load()  [FILE]->IMAGE_FILE ��������Ȃ�����ł��B" );
	//	�J���[�L�[�擾
	const char* szColorKeyHex = ini.GetString("FILE::COLOR_KEY","FF00FF");
	D3DCOLOR colorKey = hextonum(szColorKeyHex);
	
	//	��`�e�[�u���ǂݍ���
	map<string,string> rectTable;
	ini.GetSectionLinesMap( "RECT_TABLE", rectTable );

/*
	//	�ǂݍ���
	Load( szImageFileName, rectTable, colorKey );
	//Load( szImageFileName, szFileName, colorKey );
}

//	�ǂݍ���
//void CMglImageTips::Load( LPCSTR szImageFile, map<string,RECT> &rectTable, D3DCOLOR colorKey )
void CMglImageTips::Load( LPCSTR szImageFile, map<string,string> &rectTable, D3DCOLOR colorKey )
{
*/
	m_rectTable.clear();

	//	��`�e�[�u�����
	map<string,string>::iterator it = rectTable.begin();
	for( ; it!=rectTable.end(); it++ )
	{
		const char* szKeyName = it->first.c_str();
		const char* szValueStr = it->second.c_str();
		
		vector<string> ary;
		if ( string_tokenize( szValueStr, ",", ary ) != 4 )
		{
			MyuThrow( 2,"CMglImageTips::Load()  �t�H�[�}�b�g���s���ł��B\r\n"
						"File: \"%s\"\r\n"
						"Key: %s\r\n"
						"Value: %s", szFileName, szKeyName, szValueStr );
		}

		//	���l�ɂȂ��Ă邩�`�F�b�N
		if ( isnumstr(ary[0].c_str()) == FALSE ||
			 isnumstr(ary[1].c_str()) == FALSE ||
			 isnumstr(ary[2].c_str()) == FALSE ||
			 isnumstr(ary[3].c_str()) == FALSE )
		{
			MyuThrow( 2,"CMglImageTips::Load()  ���l�ȊO���܂܂�Ă��܂��B\r\n"
						"File: \"%s\"\r\n"
						"Key: %s\r\n"
						"Value: %s", szFileName, szKeyName, szValueStr );
		}

		//	RECT�쐬
		RECT rect;
		rect.left = atoi(ary[0].c_str());
		rect.top = atoi(ary[1].c_str());
		rect.right = atoi(ary[2].c_str());
		rect.bottom = atoi(ary[3].c_str());

		//	�e�[�u���֊i�[
		m_rectTable[szKeyName] = rect;
	}

	//	�摜�t�@�C���A�{���ɂ���E�E�E�H
	char work[512+10];
	if ( exist_file(szImageFileName) != true )
	{
		//	���������ē����f�B���N�g���ɂ��񂶂�ˁE�E�E�H
		safe_strcpy( work, szFileName, 256 );
		char *p = strrchr(work,'\\');
		if ( p != NULL )
			safe_strcpy( p+1, szImageFileName, 256 );

		if ( exist_file(work) != true )
			MyuThrow( 0, "CMglImageTips::Load() �摜�t�@�C�� \"%s\" ��������܂���B", szImageFileName );
		else
			szImageFileName = work;
	}

	//	�摜�ǂݍ���
	m_image.Create( szImageFileName, FALSE, colorKey );
	//CMglTexture::CreateTextureFromFile( szImageFileName, FALSE, colorKey );
}

//	�V�E�`�����
void CMglImageTips::Draw( const char* szRectName, float x, float y,
						 float fScaleX, float fScaleY, D3DCOLOR color )
{
	//	���邩�`�F�b�N
	if ( m_rectTable.find( szRectName ) == m_rectTable.end() )
		MyuThrow( 3, "CMglImageTips::Draw() %s �͕s���ȋ�`�e�[�u���L�[���ł��B", szRectName );

	RECT &rect = m_rectTable[szRectName];
	//m_myudg->SpriteDraw( this, x, y, &rect, color, fScaleX, fScaleY, 0, 0, 0 );
	m_image.Draw( x, y, &rect, color, fScaleX, fScaleY, 0, 0, 0 );

	/*
	//	���_�������擾
	MGL_SQUARE_VERTEXS vertexs;
	this->GetBmpVertexs( &vertexs );

	//	x, y�Ɉړ�
	MglMoveVertexs( &vertexs, x, y );

	//	���_�̐F
	vertexs.lt.color = color;
	vertexs.rt.color = color;
	vertexs.lb.color = color;
	vertexs.rb.color = color;

	//	�`��
	CMglTexture::Draw( &vertexs );
	*/
}

int CMglImageTips::GetTipWidth( const char* szRectName )
{
	//	���邩�`�F�b�N
	if ( m_rectTable.find( szRectName ) == m_rectTable.end() )
		MyuThrow( 3, "CMglImageTips::GetTipWidth() %s �͕s���ȋ�`�e�[�u���L�[���ł��B", szRectName );

	RECT *pRect = &m_rectTable[szRectName];
	return pRect->right - pRect->left;
}

int CMglImageTips::GetTipHeight( const char* szRectName )
{
	//	���邩�`�F�b�N
	if ( m_rectTable.find( szRectName ) == m_rectTable.end() )
		MyuThrow( 3, "CMglImageTips::GetTipHeight() %s �͕s���ȋ�`�e�[�u���L�[���ł��B", szRectName );

	RECT *pRect = &m_rectTable[szRectName];
	return pRect->bottom - pRect->top;
}
