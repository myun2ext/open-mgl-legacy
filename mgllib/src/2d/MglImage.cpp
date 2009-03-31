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
	float x, float y, CONST RECT *pSrcRect, D3DCOLOR color,
	float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle )
{
	CreateCheck();
	LockedCheck();

	/////////////////////////////////////////////////////////////////////////

	//	2009/03/31  CMglGraphicsManager::DrawSprite()���ړ����Ă݂��B

	//	srcRect��NULL���w�肳�ꂽ�ꍇ��BMP�S�Ă�RECT�Ɏw��
	RECT texFullRect;
	if ( pSrcRect == NULL ||
		pSrcRect->left == pSrcRect->right || pSrcRect->top == pSrcRect->bottom ) // 2009/03/31
	{
		ZeroMemory(&texFullRect,sizeof(texFullRect));

		//	�T�C�Y�ݒ�
		texFullRect.left = 0;
		texFullRect.top = 0;
		texFullRect.right = GetBmpWidth();
		texFullRect.bottom = GetBmpHeight();

		//	pSrcRect �Ƀ|�C���^��ݒ�
		pSrcRect = &texFullRect;
	}

	//	�X�P�[������Ȃ��o�[�W����
	float fRotationCenterXReal = (pSrcRect->right - pSrcRect->left) * fRotationCenterX;
	float fRotationCenterYReal = (pSrcRect->bottom - pSrcRect->top) * fRotationCenterY;

	//////////////////////////////////////////////////////////////////////

	if ( m_bCenterDraw ){
		/*x -= CMglTexture::GetBmpWidth()/2;
		y -= CMglTexture::GetBmpHeight()/2;*/

		//	2008/01/19 �g��k���̍ۂɒ��S�ɂȂ�Ȃ����킴�ƂȂ̂��Ȃ�Ȃ̂��E�E�E�H
		//x -= (CMglTexture::GetBmpWidth() - ((1.0f-fScaleX)*CMglTexture::GetBmpWidth())/2);
		//x -= fScaleX * CMglTexture::GetBmpWidth() / 2; <= NG
		//y -= fScaleY * CMglTexture::GetBmpHeight() / 2; <= NG
		x -= fScaleX * fRotationCenterXReal;
		y -= fScaleY * fRotationCenterYReal;
	}

	//	CMglGraphicsManager::DrawSprite() �Ăяo��
	m_myudg->SpriteDraw( this, x, y, pSrcRect, color, fScaleX, fScaleY,
		fRotationCenterXReal, fRotationCenterYReal, fAngle );
}


//	�G��iCopyRect���g�p�j
void CMglImage::CopyRectToOther( CMglImage* destSurface, RECT *srcRect, int x, int y )
{
	CreateCheck();	//	Create�`�F�b�N
	LockedCheck();

	//if ( m_pSurface == NULL )
	//	MyuThrow( 0, "CMglImage::CopyRectToOther()  m_pSurface���擾����Ă��܂���B");
	//	srcRect��NULL���w�肳�ꂽ�ꍇ�̓t���ŊG��

	D3DXLoadSurfaceFromSurface(
		destSurface->GetSurfacePtr(), NULL, srcRect,
		m_pSurface, NULL, srcRect,
		D3DX_FILTER_POINT, 0 );

	/*
	RECT srcRect2;
	_Rect(0,0, this->GetBmpWidth(), this->GetBmpHeight(), &srcRect2);
	D3DXLoadSurfaceFromSurface(
		destSurface->GetSurfacePtr(), NULL, &srcRect2,
		this->m_pSurface, NULL, &srcRect2,
		D3DX_FILTER_POINT, 0 );
	*/

	/*	����͑S�R�ʖ�
	d3d->UpdateTexture(this->m_pTexture, destSurface->GetDirect3dTexturePtr());
	*/

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
