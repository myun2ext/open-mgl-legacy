//////////////////////////////////////////////////////////
//
//	MglDxTexture
//		- MglGraphicManager �T�[�t�F�X�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglDxTexture.h"

////////////////////////////////////////////////////////////////////

//	�R���X�g���N�^
CMglDxTexture::CMglDxTexture()
{
	//m_myudg = NULL;
	//d3d = NULL;
	m_pTexture = NULL;
	m_pSurface = NULL;
	//m_bCenterDraw = FALSE;
	m_colorKey = D3DCOLOR_PINK;
	m_bRenderTarget = FALSE;
	m_bLocked = FALSE;
	m_pBitmapData = NULL;
	ZeroMemory(&m_imgInfo,sizeof(m_imgInfo));
	ZeroMemory(&m_tutv,sizeof(m_tutv));
}

/*
//	������
void CMglDxTexture::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();
}
*/

//	�J��
void CMglDxTexture::Release()
{
	CMglDgBase::Release();

	SAFE_DELETE( m_pBitmapData );
	SAFE_RELEASE( m_pTexture );
	SAFE_RELEASE( m_pSurface );
}

///////////////////////////////////////////////////////////////////////////////////////////

//	����
void CMglDxTexture::Create( int x, int y, BOOL bRenderTarget )
{
	_MGL_DEBUGLOG( "+ CMglDxTexture::Create()" );

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
			"CMglDxTexture::Create()  D3DXCreateTexture(VRAM)�Ɏ��s" );
	}
	else {
		MyuAssert( D3DXCreateTexture( d3d, x, y, D3DX_DEFAULT, 0, m_myudg->GetFormat(), D3DPOOL_MANAGED, &m_pTexture ), D3D_OK,
			"CMglDxTexture::Create()  D3DXCreateTexture(SYSMEM)�Ɏ��s" );
	}

	//	�L�����Ă���
	m_bRenderTarget = bRenderTarget;

	/*
	//SetGradation();

	//	�e�N�X�`���̃T�[�t�F�X���擾����
	MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
		"CMglDxTexture::Create()  GetSurfaceLevel()�Ɏ��s" );

	//	�X�v���C�g�쐬
	MyuAssert( D3DXCreateSprite( d3d, &this->m_pSprite ), D3D_OK,
		"CMglDxTexture::Init  D3DXCreateSprite()�Ɏ��s" );

	//	�N���A����
	//Clear();

	createFlg = TRUE;
	*/

	//	SetRender�Ƃ��ŕK�v�Ȃ̂ŃT�[�t�F�X�擾���Ă���
	_GetSurface();

	//	2008/06/30 �Ȃ�ŃN���A���Ȃ��񂾂낤���[�H
	//Clear();
	Clear(0);	//	0�ɂ��Ȃ��ƃJ���[�L�[�{���ɏ���ɂ���Ă��܂��E�E�E

	_MGL_DEBUGLOG( "- CMglDxTexture::Create()" );
}

//	�t�@�C������ǂݍ���
//	bRenderTarget��TRUE�ɂ����ꍇ��POOL�� D3DPOOL_MANAGED �Ƃ��ēǂݍ��܂��B
//void CMglDxTexture::CreateFromFile( LPCSTR szFileName, BOOL bRenderTarget, D3DCOLOR colorKey )
void CMglDxTexture::CreateFromFileEx( LPCSTR szFileName, int nForceBmpWidth, int nForceBmpHeight,
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

	D3DSURFACE_DESC texDesc;
	//m_pTexture->GetLevelDesc( 0, &texDesc );
	m_pSurface->GetDesc( &texDesc );
	m_tutv.tu = m_imgInfo.Width / (float)texDesc.Width;
	m_tutv.tv = m_imgInfo.Height / (float)texDesc.Height;
}


//	�t�@�C������ǂݍ���
//	bRenderTarget��TRUE�ɂ����ꍇ��POOL�� D3DPOOL_MANAGED �Ƃ��ēǂݍ��܂��B
//void CMglDxTexture::CreateFromFile( LPCSTR szFileName, BOOL bRenderTarget, D3DCOLOR colorKey )
void CMglDxTexture::CreateFromMemoryFileEx( LPCVOID lpFileData, UINT nDataSize, int nForceBmpWidth, int nForceBmpHeight,
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
	DWORD r = D3DXCreateTextureFromFileInMemoryEx(
		d3d, lpFileData, nDataSize,
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
		MyuThrow2( r, 0x0201, "��������̃t�@�C�� 0x%X �̓ǂݍ��݂Ɏ��s�BVRAM�܂��̓��������s�����Ă��܂��B", lpFileData );
	else if ( r == D3DERR_OUTOFVIDEOMEMORY )
		MyuThrow2( r, 0x0202, "��������̃t�@�C�� 0x%X �̓ǂݍ��݂Ɏ��s�BVRAM���s�����Ă��܂��B", lpFileData );
	else if ( r == D3DERR_NOTAVAILABLE ) 
		MyuThrow2( r, 0x0202, "��������̃t�@�C�� 0x%X �̓ǂݍ��݂Ɏ��s�B(DxErr=D3DERR_NOTAVAILABLE)", lpFileData );
	else if ( r == D3DERR_INVALIDCALL ) 
		MyuThrow2( r, 0x0202, "��������̃t�@�C�� 0x%X �̓ǂݍ��݂Ɏ��s�B(DxErr=D3DERR_INVALIDCALL)", lpFileData );
	else if ( r == D3DXERR_INVALIDDATA ) 
		MyuThrow2( r, 0x0202, "��������̃t�@�C�� 0x%X �̓ǂݍ��݂Ɏ��s�B(DxErr=D3DXERR_INVALIDDATA)", lpFileData );
	else if ( r != S_OK ) 
		MyuThrow2( r, 0x0203, "CMglImage::CreateFromFile()  D3DXCreateTextureFromFileEx(%s)�Ɏ��s", lpFileData );

	//	SetRender�Ƃ��ŕK�v�Ȃ̂ŃT�[�t�F�X�擾���Ă���
	_GetSurface();

	D3DSURFACE_DESC texDesc;
	//m_pTexture->GetLevelDesc( 0, &texDesc );
	m_pSurface->GetDesc( &texDesc );
	m_tutv.tu = m_imgInfo.Width / (float)texDesc.Width;
	m_tutv.tv = m_imgInfo.Height / (float)texDesc.Height;
}


//////////////////////////////////////////////////////////////////////////////////////

//	UpdateTexture
void CMglDxTexture::UpdateTexture( _MGL_IDirect3DTexture* pDestTexture )
{
	CreateCheck();	//	Create�`�F�b�N

	MyuAssert( d3d->UpdateTexture( m_pTexture, pDestTexture ), D3D_OK,
		"CMglImage::UpdateTexture()  UpdateTexture()�Ɏ��s" );
}

//	UpdateSurface
void CMglDxTexture::UpdateSurface( CONST RECT* pSourceRect, _MGL_IDirect3DSurface* pDestSurface, CONST POINT* pDestinationPoint )
{
	CreateCheck();	//	Create�`�F�b�N

	MyuAssert( d3d->UpdateSurface( m_pSurface, pSourceRect, pDestSurface, pDestinationPoint ), D3D_OK,
		"CMglImage::UpdateSurface()  UpdateSurface()�Ɏ��s" );
}

/*
void CMglDxTexture::CopyToOtherTexture( CMglDxTexture &toTex )
{
	UpdateTexture(
}

void CMglDxTexture::CopyFromOtherTexture( CMglDxTexture &fromTex )
{

}
*/

//////////////////////////////////////////////////////////////////////////////////////

void CMglDxTexture::SetD3dStageTexture(DWORD nStage)
{
	CreateCheck();	//	Create�`�F�b�N

	//	�e�N�X�`���̐ݒ�
	MyuAssert( d3d->SetTexture(nStage, m_pTexture), D3D_OK,
		"CMglDxTexture::SetD3dTexture()  d3d->SetTexture()�Ɏ��s" );
}

//	�G�������̃T�[�t�F�X�ɐݒ肷��
void CMglDxTexture::SetRender()
{
	CreateCheck();	//	Create�`�F�b�N
	LockedCheck();

#if _MGL_DXVER == 9
	MyuAssert( d3d->SetRenderTarget( 0, m_pSurface ), D3D_OK,
#else
	MyuAssert( d3d->SetRenderTarget( m_pSurface, NULL ), D3D_OK, //m_myudg->lpZbuffer
#endif
		"CMglDxTexture::SetRender()  SetRenderTarget()�Ɏ��s" );
}

//	�N���A����
/*void CMglImage::Clear()
{
	//	m_colorKey���֘A����̂Ńf�t�H���g�����ɂ͏o���Ȃ��̂łꂷ
	Clear( m_colorKey & 0x00ffffff );
}*/

/*
	######## D3DXCreateRenderToSurface �ł��悤�ɂ��悤�c ########
*/

//	�N���A����
void CMglDxTexture::Clear( D3DCOLOR color )
{
	Paint(NULL,color);
}

void CMglDxTexture::Clear__( D3DCOLOR color )
{
	CreateCheck();	//	Create�`�F�b�N
	LockedCheck();

	if ( m_bRenderTarget == TRUE )
	{
		//	���݂̃����_�[��ێ��i����ɏ�����������}�Y������Ȃ��j
		_MGL_IDirect3DSurface* bkupRender;
#if _MGL_DXVER == 9
		d3d->GetRenderTarget( 0, &bkupRender );
#else
		d3d->GetRenderTarget( &bkupRender );
#endif
		SetRender();
		//d3d->Clear( 0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0 );	//	|D3DCLEAR_ZBUFFER
		m_myudg->Clear( color );	//	|D3DCLEAR_ZBUFFER
		//	D3DCOLOR_FULLALPHA

		//	�����_�[�����ɖ߂�
#if _MGL_DXVER == 9
		MyuAssert( d3d->SetRenderTarget( 0, bkupRender ), D3D_OK,
#else
		MyuAssert( d3d->SetRenderTarget( bkupRender, NULL ), D3D_OK, //m_myudg->lpZbuffer
#endif
			"CMglDxTexture::Clear()  �����_�[��߂��̂Ɏ��s" );
	}
	else
	{
		/*
		//	�ʂɃN���A���ꂽ�T�[�t�F�X���쐬���Ă�������R�s�[�A�ƌ����ʓ|�ȏ���(�L�D`)
		CMglDxTexture workSurface;
		workSurface.Init( m_myudg );
		//workSurface.Create();	//	�����_�����O���TRUE�ɂ��Ȃ��Ɩ����ċA���Ă��܂�
		workSurface.Create(TRUE);	//	�����_�����O���TRUE�ɂ��Ȃ��Ɩ����ċA���Ă��܂�
		workSurface.Clear( color );
		CopyRectToThis( &workSurface );
		*/

		//	2008/06/29  CMglBitmapData::Fill()���������񂾂���Fill()�g���΂悭�l�H
		this->GetIternalBitmapData()->Fill(color);
	}
}

//	�w�肳�ꂽ��`�̈��h��Ԃ�
void CMglDxTexture::Paint( RECT* pRect, D3DCOLOR color )
{
	CreateCheck();	//	Create�`�F�b�N
	LockedCheck();

	if ( m_bRenderTarget == TRUE )
	{
		//	���݂̃����_�[��ێ��i����ɏ�����������}�Y������Ȃ��j
		_MGL_IDirect3DSurface* bkupRender;
#if _MGL_DXVER == 9
		d3d->GetRenderTarget( 0, &bkupRender );
#else
		d3d->GetRenderTarget( &bkupRender );
#endif
		SetRender();
		//d3d->Clear( 0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0 );	//	|D3DCLEAR_ZBUFFER
		m_myudg->Paint( pRect, color );	//	|D3DCLEAR_ZBUFFER

		//	�����_�[�����ɖ߂�
#if _MGL_DXVER == 9
		MyuAssert( d3d->SetRenderTarget( 0, bkupRender ), D3D_OK,
#else
		MyuAssert( d3d->SetRenderTarget( bkupRender, NULL ), D3D_OK, //m_myudg->lpZbuffer
#endif
			"CMglDxTexture::Clear()  �����_�[��߂��̂Ɏ��s" );
	}
	else
	{
		/*
		//	�ʂɃN���A���ꂽ�T�[�t�F�X���쐬���Ă�������R�s�[�A�ƌ����ʓ|�ȏ���(�L�D`)
		CMglImage workSurface;
		workSurface.Init( m_myudg );
		//workSurface.Create();
		workSurface.Create(TRUE);	//	�����_�����O���TRUE�ɂ��Ȃ��Ɩ����ċA���Ă��܂�
		workSurface.Paint( rect, color );
		workSurface.Paint( rect, color );
		CopyRectToThis( &workSurface );
		*/

		//	2008/06/29  CMglBitmapData::Fill()���������񂾂���Fill()�g���΂悭�l�H
		if ( pRect != NULL )
			this->GetIternalBitmapData()->Fill(color,*pRect);
		else
			this->GetIternalBitmapData()->Fill(color);
	}
}


//	�C�e���[�^ ////////////////////////////////////////////////

CMglBitmapData* CMglDxTexture::GetIternalBitmapData()
{
	CreateCheck();	//	Create�`�F�b�N

	/*if ( m_pBitmapData == NULL )
		m_pBitmapData = new CMglBitmapData(this);*/
	return m_pBitmapData;
}

/*
CMglDxTexture::iterator CMglDxTexture::begin()
{

}

CMglDxTexture::iterator CMglDxTexture::end()
{


}
*/


//	2007/01/10  �X�P�[���擾
//	# �e�N�X�`���̈��2�̔{���ɂȂ�B���̓���0.?f��BMP�̗̈悩���Z�o����
//MGLTUTV CMglDxTexture::GetTuTv()
const MGLTUTV& CMglDxTexture::GetTuTv()
{
	/*CreateCheck();	//	Create�`�F�b�N

	MGLTUTV t;
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	t.tu = m_imgInfo.Width / (float)texDesc.Width;
	t.tv = m_imgInfo.Height / (float)texDesc.Height;
	return t;*/
	return m_tutv;
}


void CMglTextureStageStateManager::Set(int nStage, D3DTEXTURESTAGESTATETYPE tssType, DWORD value){
	m_tssList[nStage][tssType] = value;
}
