//////////////////////////////////////////////////////////
//
//	MglImage
//		- MglGraphicManager �T�[�t�F�X�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglImage.h"

//	�R���X�g���N�^
CMglImage::CMglImage()
{
	m_nSfcID = g_nSfcCount;
	g_nSfcCount++;
	//_MGL_DEBUGLOG( "+ CMglImage::CMglImage( ID : %d )", g_nSfcCount );

	m_myudg = NULL;
	m_pTexture = NULL;
	m_pSurface = NULL;
	m_pSprite = NULL;
	d3d = NULL;

	//	�t���O��������
	initFlg = FALSE;
	createFlg = FALSE;
	m_bCenterDraw = FALSE;
}

//	�f�X�g���N�^
CMglImage::~CMglImage()
{
	//_MGL_DEBUGLOG( "+ CMglImage::~CMglImage( ID : %d )", m_nSfcID );
//	_MGL_DEBUGLOG( "+ CMglImage::�f�X�g���N�^" );
	Release();
//	_MGL_DEBUGLOG( "- CMglImage::�f�X�g���N�^" );
}


//	������
void CMglImage::Init( CMglGraphicManager* in_myudg, const char* szName )
{
	//_MGL_DEBUGLOG( "+ CMglImage::Init()" );

	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();
	m_colorKey = D3DCOLOR_BLACK;
	if ( szName != NULL )
		m_sfcName = szName;

	//	�����J���p�Ƀ��t�@�����X��ǉ�
	m_myudg->AddRefOfAutoRelease( this );

	initFlg = TRUE;
	//_MGL_DEBUGLOG( "- CMglImage::Init()" );
}

//	�����I�J��
void CMglImage::Release()
{
//	_MGL_DEBUGLOG( "+ CMglImage::Release()" );

	//	�����J���p�̃��t�@�����X���폜
	DELREF();

	SAFE_RELEASE( m_pSurface );
	SAFE_RELEASE( m_pTexture );
//	SAFE_RELEASE( m_pSprite );
//	_MGL_DEBUGLOG( "- CMglImage::Release()" );
}

//	�t�@�C������ǂݍ���
//	�J���[�L�[�̓A���t�@���g�p�̂Ƃ��̂ݗL��
//	�J���[�L�[���g�p�������Ȃ��ꍇ��colorKey��0��
//	�J���[�L�[��L���ɂ������ꍇ��0xff******�ɂ���
void CMglImage::CreateFromFile( LPCSTR szFileName, BOOL bRenderTarget, D3DCOLOR colorKey )
{
	_MGL_DEBUGLOG( "+ CMglImage::CreateFromFile( \"%s\", %d, 0x%08X )", szFileName, bRenderTarget, colorKey );

	InitCheck();	//	�������`�F�b�N

	//	���ڈȍ~�̌Ăяo�����l������[Release
	Release();

	//////////////////////////////////////////////////////////////////////////////
	//
	//	D3DXGetImageInfoFromFile()�������̂Ŗ�����T�C�Y�擾�ł��B���ق�����(�L�D`)
	//

	IDirect3DTexture8* m_pTexture2;	//	�e�N�X�`��
	D3DXIMAGE_INFO imgInfo;

	MyuAssert( D3DXCreateTextureFromFileEx( d3d, szFileName, 256, 256, D3DX_DEFAULT,
		0, /* m_myudg->backBufferDesc.Format */ m_myudg->GetFormat(), D3DPOOL_SYSTEMMEM,
		D3DX_FILTER_POINT, D3DX_FILTER_POINT, colorKey, &imgInfo, NULL, &m_pTexture2 ),
		D3D_OK, "CMglImage::CreateFromFile()  %s �̃C���[�W���擾�Ɏ��s�B", szFileName );

	int x = imgInfo.Width;
	int y = imgInfo.Height;

	SAFE_RELEASE( m_pTexture2 );

	///////////////////////////////////////////////////////////////////
	//
	//	�e�N�X�`�����쐬����
	//
	//	D3DXCreateTextureFromFileEx()�ɂč쐬���s�����A
	//	����͂����܂ŃJ���[�L�[��ݒ肷�邽�߂����B
	//	�Ȃ��A�摜�͈����L�΂���Ĉ��܂��̂ŁA��X�ēǂݍ��݂���
	//

	if ( bRenderTarget == TRUE ) {
		DWORD r = D3DXCreateTextureFromFileEx( d3d, szFileName, x, y, D3DX_DEFAULT,
			D3DUSAGE_RENDERTARGET, /* m_myudg->backBufferDesc.Format */ m_myudg->GetFormat(), D3DPOOL_DEFAULT,
			D3DX_FILTER_POINT, D3DX_FILTER_POINT, colorKey, &imgInfo, NULL, &m_pTexture );

		if ( r == E_OUTOFMEMORY )
			MyuThrow2( r, 0x0201, "%s �̓ǂݍ��݂Ɏ��s�BVRAM�܂��̓��������s�����Ă��܂��B", szFileName );
		else if ( r == D3DERR_OUTOFVIDEOMEMORY )
			MyuThrow2( r, 0x0202, "%s �̓ǂݍ��݂Ɏ��s�BVRAM���s�����Ă��܂��B", szFileName );
		else if ( r != S_OK ) 
			MyuThrow2( r, 0x0203, "CMglImage::CreateFromFile()  D3DXCreateTextureFromFileEx(VRAM,%s)�Ɏ��s", szFileName );
	}
	else {
		DWORD r = D3DXCreateTextureFromFileEx( d3d, szFileName, x, y, D3DX_DEFAULT,
			0, /* m_myudg->backBufferDesc.Format */ m_myudg->GetFormat(), D3DPOOL_MANAGED,
			D3DX_FILTER_POINT, D3DX_FILTER_POINT, colorKey, &imgInfo, NULL, &m_pTexture );

		if ( r == E_OUTOFMEMORY )
			MyuThrow( r, "%s �̓ǂݍ��݂Ɏ��s�B������������܂���B", szFileName );
		else if ( r != S_OK ) 
			MyuThrow( r, "CMglImage::CreateFromFile()  D3DXCreateTextureFromFileEx(MANAGED,%s)�Ɏ��s", szFileName );
	}

	m_nBmpSizeX = x;
	m_nBmpSizeY = y;

	int i;
	ZeroMemory( m_vertices, sizeof(MYU_VERTEX)*4 );

	//	���T�C�Y���Z�o(GetRealTexSize���g�����@�����邪�A�ꉞ�e�N�X�`���������Ă���)
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	nRealSizeX = texDesc.Width;
	nRealSizeY = texDesc.Height;

	//	�䗦�ݒ�
	fRealTexTu = (float)x / (float)nRealSizeX;
	fRealTexTv = (float)y / (float)nRealSizeY;

	//	�������Ƃ��v�������ꉞ�f�t�H���g�l�Ƃ��ē���Ă������c
	//	X,Y���܂���
	m_vertices[VERTEXNO_LT].x = m_vertices[VERTEXNO_LB].x = 0+X_ADJ;
	m_vertices[VERTEXNO_LT].y = m_vertices[VERTEXNO_RT].y = 0+Y_ADJ;
	m_vertices[VERTEXNO_RB].x = m_vertices[VERTEXNO_RT].x = x+X_ADJ;
	m_vertices[VERTEXNO_RB].y = m_vertices[VERTEXNO_LB].y = y+Y_ADJ;

	//	U,V��
	m_vertices[VERTEXNO_LT].tu = m_vertices[VERTEXNO_LB].tu = 0.0f;
	m_vertices[VERTEXNO_LT].tv = m_vertices[VERTEXNO_RT].tv = 0.0f;
	//m_vertices[VERTEXNO_RB].tu = m_vertices[VERTEXNO_RT].tu = 1.0f;
	//m_vertices[VERTEXNO_RB].tv = m_vertices[VERTEXNO_LB].tv = 1.0f;
	m_vertices[VERTEXNO_RT].tu = m_vertices[VERTEXNO_RB].tu = fRealTexTu;
	m_vertices[VERTEXNO_LB].tv = m_vertices[VERTEXNO_RB].tv = fRealTexTv;


	//	���̑�����
	for ( i=0; i<4; i++ )
	{
		m_vertices[i].z = 0.0f;
		m_vertices[i].rhw = 1.0f;
		m_vertices[i].color = 0xffffffff;
	}
	//SetGradation();

	//	�e�N�X�`���̃T�[�t�F�X���擾����
	MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
		"CMglImage::Create()  GetSurfaceLevel()�Ɏ��s" );

	m_colorKey = colorKey;
	if ( m_colorKey != 0 )	//	�J���[�L�[���g�p����ꍇ��0xff��O�̂��߂��Ă���
		m_colorKey |= 0xff000000;

	//	�X�v���C�g�쐬
	MyuAssert( D3DXCreateSprite( d3d, &this->m_pSprite ), D3D_OK,
		"CMglImage::Init  D3DXCreateSprite()�Ɏ��s" );

	/////////////////////////////////////////////////////////////////////////
	//
	//	�C���[�W���ēǂݍ��݂���
	//

	IDirect3DSurface8* m_pTempSurface;	//	�ꎞ�T�[�t�F�X
	MyuAssert( d3d->CreateImageSurface( x, y, m_myudg->GetFormat(), &m_pTempSurface ),
		D3D_OK, "CMglImage::CreateFromFile()  CreateImageSurface()�Ɏ��s" );

	MyuAssert( D3DXLoadSurfaceFromFile( m_pTempSurface, NULL, NULL, szFileName, NULL, D3DX_FILTER_POINT, 0xffff00ff, NULL ),
		D3D_OK, "CMglImage::CreateFromFile()  D3DXLoadSurfaceFromFile()�Ɏ��s" );

	//MyuAssert( d3d->CopyRects(m_pTempSurface, NULL, 0, m_pSurface, NULL),
	MyuAssert( d3d->CopyRects(m_pTempSurface, NULL, 0, m_pSurface, NULL),
		D3D_OK, "CMglImage::CreateFromFile()  CopyRects()�Ɏ��s" );

	SAFE_RELEASE( m_pTempSurface );

	m_bRenderTarget = bRenderTarget;
	createFlg = TRUE;

	_MGL_DEBUGLOG( "- CMglImage::CreateFromFile( \"%s\" )", szFileName );
}

//	�T�[�t�F�C�X�̐���
void CMglImage::Create( int x, int y, BOOL bRenderTarget )
{
	_MGL_DEBUGLOG( "+ CMglImage::Create()" );

	InitCheck();	//	�������`�F�b�N

	if ( x == 0 )	x = m_myudg->GetDispX();
	if ( y == 0 )	y = m_myudg->GetDispY();
	m_nBmpSizeX = x;
	m_nBmpSizeY = y;

	int i;
	ZeroMemory( m_vertices, sizeof(MYU_VERTEX)*4 );

	//	m_myudg->backBufferDesc.Format
	if ( bRenderTarget == TRUE ) {
		MyuAssert( D3DXCreateTexture( d3d, x, y, D3DX_DEFAULT, D3DUSAGE_RENDERTARGET, m_myudg->GetFormat(), D3DPOOL_DEFAULT, &m_pTexture ), D3D_OK,
			"CMglImage::Create()  D3DXCreateTexture(VRAM)�Ɏ��s" );
	}
	else {
		MyuAssert( D3DXCreateTexture( d3d, x, y, D3DX_DEFAULT, 0, m_myudg->GetFormat(), D3DPOOL_MANAGED, &m_pTexture ), D3D_OK,
			"CMglImage::Create()  D3DXCreateTexture(SYSMEM)�Ɏ��s" );
	}

	//	���T�C�Y���Z�o(GetRealTexSize���g�����@�����邪�A�ꉞ�e�N�X�`���������Ă���)
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	nRealSizeX = texDesc.Width;
	nRealSizeY = texDesc.Height;

	//	�䗦�ݒ�
	fRealTexTu = (float)x / (float)nRealSizeX;
	fRealTexTv = (float)y / (float)nRealSizeY;

	//	�������Ƃ��v�������ꉞ�f�t�H���g�l�Ƃ��ē���Ă������c
	//	X,Y���܂���
	m_vertices[VERTEXNO_LT].x = m_vertices[VERTEXNO_LB].x = 0+X_ADJ;
	m_vertices[VERTEXNO_LT].y = m_vertices[VERTEXNO_RT].y = 0+Y_ADJ;
	m_vertices[VERTEXNO_RB].x = m_vertices[VERTEXNO_RT].x = x+X_ADJ;
	m_vertices[VERTEXNO_RB].y = m_vertices[VERTEXNO_LB].y = y+Y_ADJ;

	//	U,V��
	m_vertices[VERTEXNO_LT].tu = m_vertices[VERTEXNO_LB].tu = 0.0f;
	m_vertices[VERTEXNO_LT].tv = m_vertices[VERTEXNO_RT].tv = 0.0f;
	//m_vertices[VERTEXNO_RB].tu = m_vertices[VERTEXNO_RT].tu = 1.0f;
	//m_vertices[VERTEXNO_RB].tv = m_vertices[VERTEXNO_LB].tv = 1.0f;
	m_vertices[VERTEXNO_RT].tu = m_vertices[VERTEXNO_RB].tu = fRealTexTu;
	m_vertices[VERTEXNO_LB].tv = m_vertices[VERTEXNO_RB].tv = fRealTexTv;

	//	���̑�����
	for ( i=0; i<4; i++ )
	{
		m_vertices[i].z = 0.0f;
		m_vertices[i].rhw = 1.0f;
		m_vertices[i].color = 0xffffffff;
	}
	//SetGradation();

	//	�e�N�X�`���̃T�[�t�F�X���擾����
	MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
		"CMglImage::Create()  GetSurfaceLevel()�Ɏ��s" );

	//	�X�v���C�g�쐬
	MyuAssert( D3DXCreateSprite( d3d, &this->m_pSprite ), D3D_OK,
		"CMglImage::Init  D3DXCreateSprite()�Ɏ��s" );

	//	�N���A����
	//Clear();

	m_bRenderTarget = bRenderTarget;

	createFlg = TRUE;

	_MGL_DEBUGLOG( "- CMglImage::Create()" );
}


//void DrawEx( float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
//	float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE );

//	Texture(DrawPrimitiveUP)�ŊG��
void CMglImage::TextureDraw(
	float x, float y, RECT* srcRect, float fScaleX, float fScaleY,
	float fRotationCenterX, float fRotationCenterY, float fAngle,
	VERTEX_COLORS* vertexColors, DWORD dwAlphaOption )
{
	CreateCheck();	//	Create�`�F�b�N

	//	srcRect���l������BMP�T�C�Y
	int nBmpSrcX = m_nBmpSizeX;
	int nBmpSrcY = m_nBmpSizeY;

	//	�]�������ǂ��̐ݒ�
	if ( srcRect == NULL )
	{
		m_vertices[VERTEXNO_LT].tu = m_vertices[VERTEXNO_LB].tu = 0.0f;
		m_vertices[VERTEXNO_LT].tv = m_vertices[VERTEXNO_RT].tv = 0.0f;
		//m_vertices[VERTEXNO_RB].tu = m_vertices[VERTEXNO_RT].tu = 1.0f;
		//m_vertices[VERTEXNO_RB].tv = m_vertices[VERTEXNO_LB].tv = 1.0f;
		m_vertices[VERTEXNO_RT].tu = m_vertices[VERTEXNO_RB].tu = fRealTexTu;
		m_vertices[VERTEXNO_LB].tv = m_vertices[VERTEXNO_RB].tv = fRealTexTv;
	}
	else
	{
		float fLeftTu = ((float)srcRect->left / m_nBmpSizeX) * fRealTexTu;
		float fRightTu = ((float)srcRect->right / m_nBmpSizeX) * fRealTexTu;
		float fTopTv = ((float)srcRect->top / m_nBmpSizeY) * fRealTexTv;
		float fBottomTv = ((float)srcRect->bottom / m_nBmpSizeY) * fRealTexTv;

		/*
		m_vertices[VERTEXNO_LT].tu = m_vertices[VERTEXNO_LB].tu = fLeftTu;
		m_vertices[VERTEXNO_RT].tu = m_vertices[VERTEXNO_RB].tu = fRightTu;
		m_vertices[VERTEXNO_LT].tv = m_vertices[VERTEXNO_RT].tv = fTopTv;
		m_vertices[VERTEXNO_LB].tv = m_vertices[VERTEXNO_RB].tv = fBottomTv;
		*/
		m_vertices[VERTEXNO_LT].tu = m_vertices[VERTEXNO_LB].tu = fLeftTu;
		m_vertices[VERTEXNO_RT].tu = m_vertices[VERTEXNO_RB].tu = fRightTu;
		m_vertices[VERTEXNO_LT].tv = m_vertices[VERTEXNO_RT].tv = fTopTv;
		m_vertices[VERTEXNO_LB].tv = m_vertices[VERTEXNO_RB].tv = fBottomTv;

		nBmpSrcX = srcRect->right - srcRect->left;
		nBmpSrcY = srcRect->bottom - srcRect->top;
	}
	//	���S��_�G��@�\
	if ( m_bCenterDraw == TRUE )
	{
		int nSizeX = srcRect->right - srcRect->left;
		int nSizeY = srcRect->bottom - srcRect->top;
		x -= (nSizeX/2) * fScaleX;
		y -= (nSizeY/2) * fScaleY;
	}

	//	�G���ʒu�A�y�ѐL�k���̐ݒ�
	m_vertices[VERTEXNO_LT].x = m_vertices[VERTEXNO_LB].x = x + X_ADJ;	//	�G���ʒuX
	m_vertices[VERTEXNO_LT].y = m_vertices[VERTEXNO_RT].y = y + Y_ADJ;	//	�G���ʒuY
	m_vertices[VERTEXNO_RB].x = m_vertices[VERTEXNO_RT].x = x + X_ADJ + nBmpSrcX * fScaleX;	//	�L�k��X
	m_vertices[VERTEXNO_RB].y = m_vertices[VERTEXNO_LB].y = y + Y_ADJ + nBmpSrcY * fScaleY;	//	�L�k��Y

	//	�F
	m_vertices[VERTEXNO_LT].color = vertexColors->leftTop;
	m_vertices[VERTEXNO_RT].color = vertexColors->rightTop;
	m_vertices[VERTEXNO_LB].color = vertexColors->leftBottom;
	m_vertices[VERTEXNO_RB].color = vertexColors->rightBottom;

	//	�A���t�@�I�v�V����
	m_myudg->SetAlphaMode( dwAlphaOption );

	//	�G��
	TextureDrawPrimitive();
}


void CMglImage::TextureDrawPrimitive()
{
	CreateCheck();	//	Create�`�F�b�N

	//	�e�N�X�`���̐ݒ�
	MyuAssert( d3d->SetTexture(0, m_pTexture), D3D_OK,
		"CMglImage::TextureDrawPrimitive()  SetTexture()�Ɏ��s" );

	//	�G��
	MyuAssert( d3d->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, m_vertices, sizeof(MYU_VERTEX) ), D3D_OK,
		"CMglImage::TextureDrawPrimitive()  DrawPrimitiveUP()�Ɏ��s" );
}


//	��]�E�X�P�[�����O�E�A���t�@�I�v�V�����t���G��i�X�v���C�g���g�p�j
void CMglImage::DrawEx(
	float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
	float x, float y, RECT *srcRect, D3DCOLOR color )
//	float x, float y, RECT *srcRect, D3DCOLOR color, DWORD dwAlphaOption )
{
	CreateCheck();	//	Create�`�F�b�N

	//	srcRect��NULL���w�肳�ꂽ�ꍇ�̓t���ŊG��
	RECT _srcRect;
	if ( srcRect == NULL )
	{
		srcRect = &_srcRect;
		_Rect( 0, 0, m_nBmpSizeX, m_nBmpSizeY, srcRect );
	}

	//	���S��_�G��@�\
	if ( m_bCenterDraw == TRUE )
	{
		int nSizeX = srcRect->right - srcRect->left;
		int nSizeY = srcRect->bottom - srcRect->top;
		x -= (nSizeX/2) * fScaleX;
		y -= (nSizeY/2) * fScaleY;
	}

	//	x, y��D3DXVECTOR2�\���̂Ɋi�[
	D3DXVECTOR2 vctPos;
	vctPos.x = x;
	vctPos.y = y;

	//	�X�P�[��
	D3DXVECTOR2 vctScale;
	vctScale.x = fScaleX;
	vctScale.y = fScaleY;

	//	��]�̒��S
	D3DXVECTOR2 vctRtCenter;
	vctRtCenter.x = (srcRect->right - srcRect->left) * fRotationCenterX * fScaleX;
	vctRtCenter.y = (srcRect->bottom - srcRect->top) * fRotationCenterY * fScaleY;

	/*	�X�v���C�g�̓A���t�@�I�v�V���������Ȃ����ۂ�
	//	�A���t�@�I�v�V����
	DWORD dwAlphaOptionBkup=0;
	if ( dwAlphaOption != MGL_ALPHA_OPT_NOCHANGE )
	{
		//	�߂����̂��߂Ƀo�b�N�A�b�v������Ă���
		dwAlphaOptionBkup = m_myudg->GetAlphaMode();
		m_myudg->SetAlphaMode( dwAlphaOption );
	}*/

	//	�p�x����Radian�ɁB�X�ɍ���]�ɂȂ��Ă���̂ŉE��]��
	float fRad = AngleToRad(-fAngle);

	//	�G��
	MyuAssert( m_pSprite->Draw( m_pTexture, srcRect, &vctScale, &vctRtCenter, fRad, &vctPos, color ), D3D_OK,
		"CMglImage::Draw()  m_pSprite->Draw()�Ɏ��s" );

	/*	�X�v���C�g�̓A���t�@�I�v�V���������Ȃ����ۂ�
	//	�A���t�@�I�v�V���������ɖ߂�
	if ( dwAlphaOption != MGL_ALPHA_OPT_NOCHANGE )
	{
		m_myudg->SetAlphaMode( dwAlphaOptionBkup );
	}*/
}


//	�G��iCopyRect���g�p�j
void CMglImage::CopyRectToOther( CMglImage* destSurface, RECT *srcRect, int x, int y )
{
	CreateCheck();	//	Create�`�F�b�N

	//if ( m_pSurface == NULL )
	//	MyuThrow( 0, "CMglImage::CopyRectToOther()  m_pSurface���擾����Ă��܂���B");
	//	srcRect��NULL���w�肳�ꂽ�ꍇ�̓t���ŊG��

	D3DXLoadSurfaceFromSurface(
		destSurface->GetSurfacePtr(), NULL, NULL,
		m_pSurface, NULL, NULL,
		D3DX_FILTER_POINT, 0 );

	/*
	RECT _srcRect;
	if ( srcRect == NULL )
	{
		srcRect = &_srcRect;
		_Rect( m_nBmpSizeX, m_nBmpSizeY, srcRect );
	}
	POINT destPoint;
	destPoint.x = x;
	destPoint.y = y;

	//	���̂����N���b�s���O���ہ[�Ƃ����那

	if ( m_pSurface == destSurface->GetSurfacePtr() )
		MyuThrow(0,"CMglImage::CopyRectToOther()  destSurface�Ɏ������g�̃T�[�t�F�X���w�肷�邱�Ƃ͏o���܂���B");

	//if (FAILED(d3d->CopyRects(m_pSurface, srcRect, 1, destSurface, &destPoint))) {
	//MyuAssert( d3d->CopyRects(m_pSurface, NULL, 1, destSurface, NULL), D3D_OK,
	MyuAssert( d3d->CopyRects(m_pSurface, srcRect, 1, destSurface->GetSurfacePtr(), &destPoint), D3D_OK,
		"CMglImage::CopyRectToOther()  CopyRect()�Ɏ��s" );
	*/
}

//	���̃T�[�t�F�X��CopyRect
void CMglImage::CopyRectToThis( CMglImage* srcSurface, RECT *srcRect, int x, int y )
{
	srcSurface->CopyRectToOther( this, srcRect, x, y );
}

/*
//	���̃T�[�t�F�X��CopyRect
void CMglImage::CopyRectToThis( CMglImage* srcSurface, RECT *srcRect, int x, int y )
{
	CreateCheck();	//	Create�`�F�b�N

	//if ( m_pSurface == NULL )
	//	MyuThrow( 0, "CMglImage::CopyRectToThis()  m_pSurface���擾����Ă��܂���B");
	//	srcRect��NULL���w�肳�ꂽ�ꍇ�̓t���ŊG��
	RECT _srcRect;
	if ( srcRect == NULL )
	{
		srcRect = &_srcRect;
		_Rect( m_nBmpSizeX, m_nBmpSizeY, srcRect );
	}
	POINT destPoint;
	destPoint.x = x;
	destPoint.y = y;

	if ( m_pSurface == srcSurface->GetSurfacePtr() )
		MyuThrow(0,"CMglImage::CopyRectToThis()  srcSurface�Ɏ������g�̃T�[�t�F�X���w�肷�邱�Ƃ͏o���܂���B");

	//if (FAILED(d3d->CopyRects(srcSurface, srcRect, 1, m_pSurface, &destPoint))) {
	MyuAssert( d3d->CopyRects(srcSurface->GetSurfacePtr(), NULL, 0, m_pSurface, NULL), D3D_OK,
		"CMglImage::CopyRectToThis()  CopyRect()�Ɏ��s" );
}
*/

/*	�ǂ����t�H�[�}�b�g�G���[�N�����̂Ŗ��T�|�[�g
//	�G��iCopyRect���g�p�j
void CMglImage::CopyRect( int x, int y, RECT *srcRect )
{
	CreateCheck();	//	Create�`�F�b�N
	CopyRectToOther( x, y, srcRect, m_myudg->_GetBackBuffer() );
}
*/

//	�G�������̃T�[�t�F�X�ɐݒ肷��
void CMglImage::SetRender()
{
	CreateCheck();	//	Create�`�F�b�N

	MyuAssert( d3d->SetRenderTarget( m_pSurface, NULL ), D3D_OK, //m_myudg->lpZbuffer
		"CMglImage::SetRender()  SetRenderTarget()�Ɏ��s" );
}

//	�N���A����
/*void CMglImage::Clear()
{
	//	m_colorKey���֘A����̂Ńf�t�H���g�����ɂ͏o���Ȃ��̂łꂷ
	Clear( m_colorKey & 0x00ffffff );
}*/

//	�N���A����
void CMglImage::Clear( D3DCOLOR color )
{
	CreateCheck();	//	Create�`�F�b�N

	if ( m_bRenderTarget == TRUE )
	{
		//	���݂̃����_�[��ێ��i����ɏ�����������}�Y������Ȃ��j
		IDirect3DSurface8* bkupRender;
		d3d->GetRenderTarget( &bkupRender );

		SetRender();
		//d3d->Clear( 0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0 );	//	|D3DCLEAR_ZBUFFER
		m_myudg->Clear( color );	//	|D3DCLEAR_ZBUFFER
		//	D3DCOLOR_FULLALPHA

		//	�����_�[�����ɖ߂�
		MyuAssert( d3d->SetRenderTarget( bkupRender, NULL ), D3D_OK, //m_myudg->lpZbuffer
			"CMglImage::Clear()  �����_�[��߂��̂Ɏ��s" );
	}
	else
	{
		//	�ʂɃN���A���ꂽ�T�[�t�F�X���쐬���Ă�������R�s�[�A�ƌ����ʓ|�ȏ���(�L�D`)
		CMglImage workSurface;
		workSurface.Init( m_myudg );
		workSurface.Create();	//	�����_�����O���TRUE�ɂ��Ȃ��Ɩ����ċA���Ă��܂�
		workSurface.Clear( color );
		CopyRectToThis( &workSurface );
	}
}

//	�w�肳�ꂽ��`�̈��h��Ԃ�
void CMglImage::Paint( RECT* rect, D3DCOLOR color )
{
	CreateCheck();	//	Create�`�F�b�N

	if ( m_bRenderTarget == TRUE )
	{
		//	���݂̃����_�[��ێ��i����ɏ�����������}�Y������Ȃ��j
		IDirect3DSurface8* bkupRender;
		d3d->GetRenderTarget( &bkupRender );

		SetRender();
		//d3d->Clear( 0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0 );	//	|D3DCLEAR_ZBUFFER
		m_myudg->Paint( rect, color );	//	|D3DCLEAR_ZBUFFER

		//	�����_�[�����ɖ߂�
		MyuAssert( d3d->SetRenderTarget( bkupRender, NULL ), D3D_OK, //m_myudg->lpZbuffer
			"CMglImage::Clear()  �����_�[��߂��̂Ɏ��s" );
	}
	else
	{
		//	�ʂɃN���A���ꂽ�T�[�t�F�X���쐬���Ă�������R�s�[�A�ƌ����ʓ|�ȏ���(�L�D`)
		CMglImage workSurface;
		workSurface.Init( m_myudg );
		workSurface.Create();	//	�����_�����O���TRUE�ɂ��Ȃ��Ɩ����ċA���Ă��܂�
		workSurface.Paint( rect, color );
		CopyRectToThis( &workSurface );
	}
}

