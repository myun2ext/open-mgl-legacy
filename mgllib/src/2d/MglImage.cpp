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
	//m_pSurface = NULL;
	m_bCenterDraw = FALSE;
}

//	�f�X�g���N�^
CMglImage::~CMglImage()
{

}

////////////////////////////////////////////////////////////////////////////////


//	�`��
void CMglImage::Draw(
	float x, float y, CONST RECT *srcRect, D3DCOLOR color,
	float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle )
{
	if ( m_bCenterDraw ){
		x -= CMglTexture::GetBmpWidth()/2;
		y -= CMglTexture::GetBmpHeight()/2;
	}
	m_myudg->SpriteDraw( this, x, y, srcRect, color, fScaleX, fScaleY,
		fRotationCenterX, fRotationCenterY, fAngle );
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

/*
	######## D3DXCreateRenderToSurface �ł��悤�ɂ��悤�c ########
*/
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
		//workSurface.Create();	//	�����_�����O���TRUE�ɂ��Ȃ��Ɩ����ċA���Ă��܂�
		workSurface.Create(TRUE);	//	�����_�����O���TRUE�ɂ��Ȃ��Ɩ����ċA���Ă��܂�
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
		//workSurface.Create();
		workSurface.Create(TRUE);	//	�����_�����O���TRUE�ɂ��Ȃ��Ɩ����ċA���Ă��܂�
		workSurface.Paint( rect, color );
		workSurface.Paint( rect, color );
		CopyRectToThis( &workSurface );
	}
}
