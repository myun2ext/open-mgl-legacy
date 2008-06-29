//////////////////////////////////////////////////////////
//
//	MglTexture
//		- MglGraphicManager �T�[�t�F�X�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglTexture.h"

////////////////////////////////////////////////////////////////////

//	�R���X�g���N�^
CMglTexture::CMglTexture()
{
	m_myudg = NULL;
	m_pTexture = NULL;
	m_pSurface = NULL;
	d3d = NULL;
	//m_bCenterDraw = FALSE;
	m_colorKey = D3DCOLOR_PINK;
	m_bRenderTarget = FALSE;
	m_bLocked = FALSE;
	m_pBitmapData = NULL;
	ZeroMemory(&m_imgInfo,sizeof(m_imgInfo));
}


//	������
void CMglTexture::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();
}

//	�J��
void CMglTexture::Release()
{
	SAFE_DELETE( m_pBitmapData );
	SAFE_RELEASE( m_pTexture );
	SAFE_RELEASE( m_pSurface );
}


//	�t�@�C������ǂݍ���
//	bRenderTarget��TRUE�ɂ����ꍇ��POOL�� D3DPOOL_MANAGED �Ƃ��ēǂݍ��܂��B
//void CMglTexture::CreateTextureFromFile( LPCSTR szFileName, BOOL bRenderTarget, D3DCOLOR colorKey )
void CMglTexture::CreateTextureFromFileEx( LPCSTR szFileName, int nForceBmpWidth, int nForceBmpHeight,
	BOOL bRenderTarget, D3DCOLOR colorKey, DWORD dwFilter, DWORD dwMapFilter )
{
	InitCheck();	//	�������`�F�b�N

	//	���ڈȍ~�̌Ăяo�����l������[Release
	Release();

	//	bRenderTarget�̔��f
	DWORD usage;
	D3DPOOL pool;
	if ( bRenderTarget ){
		usage = D3DUSAGE_RENDERTARGET;
		pool = D3DPOOL_DEFAULT; // D3DPOOL_MANAGED; <= �t�c�H
	}
	else{
		usage = 0;
		pool = D3DPOOL_MANAGED; // D3DPOOL_DEFAULT; <= �t�c�H
	}

	//	�L�����Ă���
	m_colorKey = colorKey;
	m_bRenderTarget = bRenderTarget;

	/*	2007/01/10  D3DX_FILTER_NONE �ɂ�����v��Ȃ��Ȃ�n����Ȃ��n�݂����Ȍn�H
	m_imgInfo.Width = nForceBmpWidth;
	m_imgInfo.Height = nForceBmpHeight;*/

	//	�쐬
	//DWORD r = D3DXCreateTextureFromFileEx( d3d, szFileName, x, y, D3DX_DEFAULT,
	DWORD r = D3DXCreateTextureFromFileEx(
		d3d, szFileName,
/*		D3DX_DEFAULT,	//	Width -  ���̒l�� 0 �܂��� D3DX_DEFAULT �̏ꍇ�A�f�B�����W�����̓t�@�C������擾�����B
		D3DX_DEFAULT,	//	Height - ���̒l�� 0 �܂��� D3DX_DEFAULT �̏ꍇ�A�f�B�����W�����̓t�@�C������擾�����B*/
		nForceBmpWidth,	//	Width -  ���̒l�� 0 �܂��� D3DX_DEFAULT �̏ꍇ�A�f�B�����W�����̓t�@�C������擾�����B
		nForceBmpHeight,//	Height - ���̒l�� 0 �܂��� D3DX_DEFAULT �̏ꍇ�A�f�B�����W�����̓t�@�C������擾�����B
		D3DX_DEFAULT,	//	MipLevels
		usage,			//	Usage - 0 �܂��� D3DUSAGE_RENDERTARGET�B���̃t���O�� D3DUSAGE_RENDERTARGET ��ݒ肷��ƁA���̃T�[�t�F�X�̓����_�����O �^�[�Q�b�g�Ƃ��Ďg�p����邱�Ƃ������B
		m_myudg->GetFormat(),//	Format - �e�N�X�`���ɑ΂��ėv�����ꂽ�s�N�Z�� �t�H�[�}�b�g���L�q����AD3DFORMAT �񋓌^�̃����o�B
		pool,			//	Pool - �e�N�X�`���̔z�u��ƂȂ郁���� �N���X���L�q����AD3DPOOL �񋓌^�̃����o�B
		dwFilter, dwMapFilter, colorKey, &m_imgInfo, NULL, &m_pTexture );
//		D3DX_FILTER_NONE, D3DX_FILTER_NONE, colorKey, &m_imgInfo, NULL, &m_pTexture );
//		D3DX_FILTER_POINT, D3DX_FILTER_POINT, colorKey, &m_imgInfo, NULL, &m_pTexture );

	//	�G���[�R�[�h�ɂ���ă��b�Z�[�W��ύX����
	if ( r == E_OUTOFMEMORY )
		MyuThrow2( r, 0x0201, "%s �̓ǂݍ��݂Ɏ��s�BVRAM�܂��̓��������s�����Ă��܂��B", szFileName );
	else if ( r == D3DERR_OUTOFVIDEOMEMORY )
		MyuThrow2( r, 0x0202, "%s �̓ǂݍ��݂Ɏ��s�BVRAM���s�����Ă��܂��B", szFileName );
	else if ( r == D3DERR_NOTAVAILABLE ) 
		MyuThrow2( r, 0x0202, "%s �̓ǂݍ��݂Ɏ��s�B(DxErr=D3DERR_NOTAVAILABLE)", szFileName );
	else if ( r == D3DERR_INVALIDCALL ) 
		MyuThrow2( r, 0x0202, "%s �̓ǂݍ��݂Ɏ��s�B(DxErr=D3DERR_INVALIDCALL)", szFileName );
	else if ( r == D3DXERR_INVALIDDATA ) 
		MyuThrow2( r, 0x0202, "%s �̓ǂݍ��݂Ɏ��s�B(DxErr=D3DXERR_INVALIDDATA)", szFileName );
	else if ( r != S_OK ) 
		MyuThrow2( r, 0x0203, "CMglImage::CreateFromFile()  D3DXCreateTextureFromFileEx(%s)�Ɏ��s", szFileName );

	//	SetRender�Ƃ��ŕK�v�Ȃ̂ŃT�[�t�F�X�擾���Ă���
	_GetSurface();
}


//	����
void CMglTexture::Create( int x, int y, BOOL bRenderTarget )
{
	_MGL_DEBUGLOG( "+ CMglTexture::Create()" );

	InitCheck();	//	�������`�F�b�N

	//	���ڈȍ~�̌Ăяo�����l������[Release
	Release();

	if ( x <= 0 )	x = m_myudg->GetDispX();
	if ( y <= 0 )	y = m_myudg->GetDispY();
	/*m_nBmpSizeX = x;
	m_nBmpSizeY = y;*/

	//	2008/06/28  m_imgInfo���ݒ肵�Ă��E���E��B
	m_imgInfo.Width = x;
	m_imgInfo.Height = y;

	/*int i;
	ZeroMemory( m_vertices, sizeof(MYU_VERTEX)*4 );*/

	//	m_myudg->backBufferDesc.Format
	if ( bRenderTarget == TRUE ) {
		MyuAssert( D3DXCreateTexture( d3d, x, y, D3DX_DEFAULT, D3DUSAGE_RENDERTARGET, m_myudg->GetFormat(), D3DPOOL_DEFAULT, &m_pTexture ), D3D_OK,
			"CMglTexture::Create()  D3DXCreateTexture(VRAM)�Ɏ��s" );
	}
	else {
		MyuAssert( D3DXCreateTexture( d3d, x, y, D3DX_DEFAULT, 0, m_myudg->GetFormat(), D3DPOOL_MANAGED, &m_pTexture ), D3D_OK,
			"CMglTexture::Create()  D3DXCreateTexture(SYSMEM)�Ɏ��s" );
	}

	//	�L�����Ă���
	m_bRenderTarget = bRenderTarget;

	/*
	//SetGradation();

	//	�e�N�X�`���̃T�[�t�F�X���擾����
	MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
		"CMglTexture::Create()  GetSurfaceLevel()�Ɏ��s" );

	//	�X�v���C�g�쐬
	MyuAssert( D3DXCreateSprite( d3d, &this->m_pSprite ), D3D_OK,
		"CMglTexture::Init  D3DXCreateSprite()�Ɏ��s" );

	//	�N���A����
	//Clear();

	createFlg = TRUE;
	*/

	//	SetRender�Ƃ��ŕK�v�Ȃ̂ŃT�[�t�F�X�擾���Ă���
	_GetSurface();

	_MGL_DEBUGLOG( "- CMglTexture::Create()" );
}

//////////////////////////////////////////////////////////////////////////////////////

//	�V�E�`�����
void CMglTexture::Draw(float x, float y, D3DCOLOR color )
{
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
	Draw( &vertexs );
}

//	�`��i�񎟌��Œ�j
void CMglTexture::Draw( MGL_SQUARE_VERTEXS *pMglSqVertexs, BOOL bVertexRevise )
{
	Draw( (MYU_VERTEX*)pMglSqVertexs, 2, bVertexRevise );
}

//	�`��i���_���s��j
void CMglTexture::Draw( MYU_VERTEX *pMyuVertex, UINT nPrimitiveCount, BOOL bVertexRevise )
{
	CreateCheck();	//	Create�`�F�b�N
	LockedCheck();

	//	���_�␳
	if ( bVertexRevise )
		MglMoveVertexs( pMyuVertex, TEXTURE_FLOAT_ADJ, TEXTURE_FLOAT_ADJ, 2+nPrimitiveCount );

	//	�e�N�X�`���̐ݒ�
	MyuAssert( d3d->SetTexture(0, m_pTexture), D3D_OK,
		"CMglImage::TextureDrawPrimitive()  SetTexture()�Ɏ��s" );

	DrawPrimitiveUP( D3DPT_TRIANGLEFAN, nPrimitiveCount, pMyuVertex, sizeof(MYU_VERTEX) );
	//	�G��
	/*MyuAssert( d3d->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, nPrimitiveCount, pMyuVertex, sizeof(MYU_VERTEX) ), D3D_OK,
		"CMglImage::TextureDrawPrimitive()  DrawPrimitiveUP()�Ɏ��s" );*/
}

//	DrawPrimitiveUP
void CMglTexture::DrawPrimitiveUP( D3DPRIMITIVETYPE primitiveType, UINT nPrimitiveCount,
								  const void *pVertexStreamZeroData, UINT nVertexStreamZeroStride )
{
	CreateCheck();	//	Create�`�F�b�N
	LockedCheck();

	//	�G��
	MyuAssert( d3d->DrawPrimitiveUP( primitiveType, nPrimitiveCount, pVertexStreamZeroData, nVertexStreamZeroStride ), D3D_OK,
		"CMglImage::TextureDrawPrimitive()  DrawPrimitiveUP()�Ɏ��s" );
}

   
///////////////////////////////////////////////////////////////////////////

//	BMP�̒��_���擾
void CMglTexture::GetBmpVertexs( MGL_SQUARE_VERTEXS *pMglSqVertexs )
{
	int nBmpSrcX = m_imgInfo.Width;
	int nBmpSrcY = m_imgInfo.Height;

	//	2007/01/10  �X�P�[���擾
	//	# �e�N�X�`���̈��2�̔{���ɂȂ�B���̓���0.?f��BMP�̗̈悩���Z�o����
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	const float fBmpScaleX = (float)nBmpSrcX / (float)texDesc.Width;
	const float fBmpScaleY = (float)nBmpSrcY / (float)texDesc.Height;

	//	���_��񐶐�
	MglVertexGen( &pMglSqVertexs->lt, 0, 0,					0.0f, 0.0f );
	MglVertexGen( &pMglSqVertexs->rt, nBmpSrcX,				0,	fBmpScaleX, 0.0f );
	MglVertexGen( &pMglSqVertexs->lb, 0, nBmpSrcY,			0.0f, fBmpScaleY );
	MglVertexGen( &pMglSqVertexs->rb, nBmpSrcX, nBmpSrcY,	fBmpScaleX, fBmpScaleY );

	//	���_�̃Y����
	//MglMoveVertexs( pMglSqVertexs, TEXTURE_FLOAT_ADJ, TEXTURE_FLOAT_ADJ );
}




/////////////////////////////////////////////////////////////////////////////////////////////

//	�������@�Â��`������@������


//	Texture(DrawPrimitiveUP)�ŊG��
void CMglTexture::TextureDraw(
	float x, float y, RECT* srcRect, float fScaleX, float fScaleY,
	float fRotationCenterX, float fRotationCenterY, float fAngle,
	VERTEX_COLORS* vertexColors, DWORD dwAlphaOption )
{
	CreateCheck();	//	Create�`�F�b�N
	LockedCheck();

	//	srcRect���l������BMP�T�C�Y
	//int nBmpSrcX = m_nBmpSizeX;
	//int nBmpSrcY = m_nBmpSizeY;
	int nBmpSrcX = m_imgInfo.Width;
	int nBmpSrcY = m_imgInfo.Height;

	//	2007/01/10  �X�P�[���擾
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	const float fRealTexTu = (float)nBmpSrcX / (float)texDesc.Width;
	const float fRealTexTv = (float)nBmpSrcY / (float)texDesc.Height;

	MYU_VERTEX vertices[4];		//	���_
	ZeroMemory( vertices, sizeof(vertices) );

	//	�]�������ǂ��̐ݒ�
	if ( srcRect == NULL )
	{
		vertices[VERTEXNO_LT].tu = vertices[VERTEXNO_LB].tu = 0.0f;
		vertices[VERTEXNO_LT].tv = vertices[VERTEXNO_RT].tv = 0.0f;
		//vertices[VERTEXNO_RB].tu = vertices[VERTEXNO_RT].tu = 1.0f; - 2007/01/10 1.0f������ϔp�~
		//vertices[VERTEXNO_RB].tv = vertices[VERTEXNO_LB].tv = 1.0f;
		vertices[VERTEXNO_RT].tu = vertices[VERTEXNO_RB].tu = fRealTexTu;
		vertices[VERTEXNO_LB].tv = vertices[VERTEXNO_RB].tv = fRealTexTv;
	}
	else
	{
		float fLeftTu = ((float)srcRect->left / nBmpSrcX) * fRealTexTu;
		float fRightTu = ((float)srcRect->right / nBmpSrcX) * fRealTexTu;
		float fTopTv = ((float)srcRect->top / nBmpSrcY) * fRealTexTv;
		float fBottomTv = ((float)srcRect->bottom / nBmpSrcY) * fRealTexTv;
		/*float fLeftTu = ((float)srcRect->left / nBmpSrcX);
		float fRightTu = ((float)srcRect->right / nBmpSrcX); - 2007/01/10 1.0f������ϔp�~
		float fTopTv = ((float)srcRect->top / nBmpSrcY);
		float fBottomTv = ((float)srcRect->bottom / nBmpSrcY);*/

		/*	2007/01/10  nBmpSrc*��
		float fLeftTu = ((float)srcRect->left / m_nBmpSizeX) * fRealTexTu;
		float fRightTu = ((float)srcRect->right / m_nBmpSizeX) * fRealTexTu;
		float fTopTv = ((float)srcRect->top / m_nBmpSizeY) * fRealTexTv;
		float fBottomTv = ((float)srcRect->bottom / m_nBmpSizeY) * fRealTexTv;
		*/

		/*
		vertices[VERTEXNO_LT].tu = vertices[VERTEXNO_LB].tu = fLeftTu;
		vertices[VERTEXNO_RT].tu = vertices[VERTEXNO_RB].tu = fRightTu;
		vertices[VERTEXNO_LT].tv = vertices[VERTEXNO_RT].tv = fTopTv;
		vertices[VERTEXNO_LB].tv = vertices[VERTEXNO_RB].tv = fBottomTv;
		*/
		vertices[VERTEXNO_LT].tu = vertices[VERTEXNO_LB].tu = fLeftTu;
		vertices[VERTEXNO_RT].tu = vertices[VERTEXNO_RB].tu = fRightTu;
		vertices[VERTEXNO_LT].tv = vertices[VERTEXNO_RT].tv = fTopTv;
		vertices[VERTEXNO_LB].tv = vertices[VERTEXNO_RB].tv = fBottomTv;

		nBmpSrcX = srcRect->right - srcRect->left;
		nBmpSrcY = srcRect->bottom - srcRect->top;
	}
	/*
	//	���S��_�G��@�\
	if ( m_bCenterDraw == TRUE )
	{
		int nSizeX = srcRect->right - srcRect->left;
		int nSizeY = srcRect->bottom - srcRect->top;
		x -= (nSizeX/2) * fScaleX;
		y -= (nSizeY/2) * fScaleY;
	}
	*/

	//	�G���ʒu�A�y�ѐL�k���̐ݒ�
	vertices[VERTEXNO_LT].x = vertices[VERTEXNO_LB].x = x + TEXTURE_FLOAT_ADJ;	//	�G���ʒuX
	vertices[VERTEXNO_LT].y = vertices[VERTEXNO_RT].y = y + TEXTURE_FLOAT_ADJ;	//	�G���ʒuY
	vertices[VERTEXNO_RB].x = vertices[VERTEXNO_RT].x = x + TEXTURE_FLOAT_ADJ + nBmpSrcX * fScaleX;	//	�L�k��X
	vertices[VERTEXNO_RB].y = vertices[VERTEXNO_LB].y = y + TEXTURE_FLOAT_ADJ + nBmpSrcY * fScaleY;	//	�L�k��Y
	/*vertices[VERTEXNO_LT].x = vertices[VERTEXNO_LB].x = x + X_ADJ;//	�G���ʒuX
	vertices[VERTEXNO_LT].y = vertices[VERTEXNO_RT].y = y + Y_ADJ;	//	�G���ʒuY
	vertices[VERTEXNO_RB].x = vertices[VERTEXNO_RT].x = x + X_ADJ + nBmpSrcX * fScaleX;	//	�L�k��X
	vertices[VERTEXNO_RB].y = vertices[VERTEXNO_LB].y = y + Y_ADJ + nBmpSrcY * fScaleY;	//	�L�k��Y*/

	//	�F
	vertices[VERTEXNO_LT].color = vertexColors->leftTop;
	vertices[VERTEXNO_RT].color = vertexColors->rightTop;
	vertices[VERTEXNO_LB].color = vertexColors->leftBottom;
	vertices[VERTEXNO_RB].color = vertexColors->rightBottom;

	//	�A���t�@�I�v�V����
	m_myudg->SetAlphaMode( dwAlphaOption );

	//	�`��
	Draw( vertices );
}

//	�C�e���[�^ ////////////////////////////////////////////////

CMglBitmapData* CMglTexture::GetIternalBitmapData()
{
	if ( m_pBitmapData == NULL )
		m_pBitmapData = new CMglBitmapData(this);
	return m_pBitmapData;
}

/*
CMglTexture::iterator CMglTexture::begin()
{

}

CMglTexture::iterator CMglTexture::end()
{


}
*/

