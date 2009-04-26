//////////////////////////////////////////////////////////
//
//	MglDxSprite
//		- DirectX Graphics �Ǘ��N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglDxSprite.h"

//	�R���X�g���N�^
CMglDxSprite::CMglDxSprite()
{
	m_bSpriteBegun = FALSE;
}

//	�f�X�g���N�^
CMglDxSprite::~CMglDxSprite()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#define m_pSprite m_pI

void CMglDxSprite::InitSprite()
{
	if ( m_pD3dDev == NULL )
		MyuThrow( MGLMSGNO_GRPMGR(80), "CMglDxSprite::InitSprite()  m_pD3dDev��NULL" );
	if ( m_pSprite != NULL )	//	���ɂ���΃X�L�b�v
		return;

	MyuAssert2( D3DXCreateSprite( m_pD3dDev, &m_pSprite ), D3D_OK,
		MGLMSGNO_GRPMGR(81), "CMglDxSprite::Init()  D3DXCreateSprite()�Ɏ��s" );
}

//	�X�v���C�g�`��
void CMglDxSprite::SpriteDraw( _TEX *pTexture, float x, float y, CONST RECT* pSrcRect, D3DCOLOR color,
		float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle )
{
	//	�`�F�b�N
	if ( m_pSprite == NULL )
		MyuThrow( MGLMSGNO_GRPMGR(83), "CMglGraphicManage::SpriteDraw()  �X�v���C�g�������ɂȂ��Ă��邩�A�X�v���C�g�̏������Ɏ��s���܂����B" );
	if ( pTexture->GetDirect3dTexturePtr() == NULL )
		MyuThrow( MGLMSGNO_GRPMGR(84), "CMglGraphicManage::SpriteDraw()  IDirect3DTexture8 ��NULL�ł��B�e�N�X�`��������������Ă��Ȃ��\��������܂��B" );

	//	2009/01/07
	SpriteBegin();

	////// �v�Z���� /////////////////////////////////

	/*	2009/03/31  CMglImage ���ł��������������ł͂Ȃ����Ȃ�
	//	srcRect��NULL���w�肳�ꂽ�ꍇ��BMP�S�Ă�RECT�Ɏw��
	RECT texFullRect;
	if ( pSrcRect == NULL ||
		pSrcRect->left == pSrcRect->right || pSrcRect->top == pSrcRect->bottom ) // 2009/03/31
	{
		ZeroMemory(&texFullRect,sizeof(texFullRect));

		//	�T�C�Y�ݒ�
		texFullRect.left = 0;
		texFullRect.top = 0;
		texFullRect.right = pTexture->GetBmpWidth();
		texFullRect.bottom = pTexture->GetBmpHeight();

		//	pSrcRect �Ƀ|�C���^��ݒ�
		pSrcRect = &texFullRect;
	}
	*/

	//	���S��_�G��@�\
	/*if ( m_bSpriteCenterDraw == TRUE )
	{
		int nSizeX = pSrcRect->right - pSrcRect->left;
		int nSizeY = pSrcRect->bottom - pSrcRect->top;
		x -= (nSizeX/2) * fScaleX;
		y -= (nSizeY/2) * fScaleY;
	}*/

	/* 2007/02/12 ����͑����v��Ȃ��i0.5f�w�肷��΂����j
	//	���S��_�G��@�\
	if ( fRotationCenterX == -1 )	{
		int nSizeX = pSrcRect->right - pSrcRect->left;
		x -= (nSizeX/2) * fScaleX;
	}
	if ( fRotationCenterY == -1 )	{
		int nSizeY = pSrcRect->bottom - pSrcRect->top;
		y -= (nSizeY/2) * fScaleY;
	}
	*/


	//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
	//	DirectX 9
	//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//#if _MGL_DXVER == 9
#if _MGL_D3DXVER >= MGL_D3DXVER_ID3DXSPRITE_CHANGED
	//	DirectX9�̏ꍇ�͂��[��Ȋ����炵���B

	//	�g��E�k��
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, fScaleX, fScaleY, 0.0f);

	//	��]�̒��S
	//float fCenterX = (pSrcRect->right - pSrcRect->left) * fRotationCenterX * fScaleX;
	//float fCenterY = (pSrcRect->bottom - pSrcRect->top) * fRotationCenterY * fScaleY;
	/*float fCenterX = (pSrcRect->right - pSrcRect->left) * fRotationCenterX; // 2009/03/31 CMglImage ���ֈړ�
	float fCenterY = (pSrcRect->bottom - pSrcRect->top) * fRotationCenterY;*/
	float fCenterX = fRotationCenterX; // 2009/03/31 CMglImage ���ֈړ�
	float fCenterY = fRotationCenterY; // 2009/03/31 CMglImage ���ֈړ�

	D3DXMATRIX matTrans1;
	D3DXMATRIX matTrans2;
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans1, fCenterX, fCenterY, 0);
	D3DXMatrixTranslation(&matTrans2, -fCenterX, -fCenterY, 0);
	D3DXMatrixTranslation(&matTrans, x, y, 0);

	//	�p�x
	D3DXMATRIX matRotation;
	D3DXMatrixRotationZ(&matRotation, D3DXToRadian(fAngle));

	//	����
	/*D3DXMATRIX matrix1;
	D3DXMATRIX matrix;
	D3DXMatrixMultiply(&matrix1, &matRotation, &matTrans);
	D3DXMatrixMultiply(&matrix, &matrix1, &matScale);*/
//	D3DXMATRIX matrix = matTrans2 * matRotation * matTrans1 * matScale * matTrans;
	//D3DXMATRIX matrix = matTrans2 * matRotation * matTrans1 * matScale * matTrans;
	D3DXMATRIX matrix = matTrans1;

/*	
D3DXMATRIX *WINAPI D3DXMatrixTransformation2D(
	&matrix,
	&D3DXVECTOR2(0.5f,0.5f),
	FLOAT ScalingRotation,
	CONST D3DXVECTOR2 * pScaling,
	CONST D3DXVECTOR2 * pRotationCenter,
	FLOAT Rotation,
	CONST D3DXVECTOR2 * pTranslation
);
*/
	//int nWidth = pSrcRect;

	D3DXMatrixTransformation2D(&matrix,
		//&D3DXVECTOR2(200,200),
		&D3DXVECTOR2(0,0),
		0,
		&D3DXVECTOR2(fScaleX,fScaleY),
		&D3DXVECTOR2(0,0),//&D3DXVECTOR2(0.5f,0.5f),
		D3DXToRadian(fAngle),
		//&D3DXVECTOR2(x,y));
		&D3DXVECTOR2(x+fCenterX*fScaleX,y+fCenterY*fScaleY));

	//	�g�����X�t�H�[���Ƃ��Ĕ��f
	MyuAssert2( m_pSprite->SetTransform(&matrix), D3D_OK,
		MGLMSGNO_GRPMGR(85), "CMglDxSprite::SpriteDraw()  m_pSprite->SetTransform()�Ɏ��s" );

	MyuAssert2( m_pSprite->Draw( pTexture->GetDirect3dTexturePtr(), pSrcRect, 
					 &D3DXVECTOR3(fCenterX, fCenterY, 0),
//					 &D3DXVECTOR3(0.5f, 0.5f, 0),
					 NULL, color), D3D_OK,
					 //&D3DXVECTOR3(fCenterX, fCenterY, 0), color), D3D_OK,
		MGLMSGNO_GRPMGR(86), "CMglDxSprite::SpriteDraw()  m_pSprite->Draw()�Ɏ��s" );

//	MyuAssert2( m_pSprite->Draw( pTexture->GetDirect3dTexturePtr(), NULL, NULL, NULL, color), D3D_OK,
//		MGLMSGNO_GRPMGR(86), "CMglDxSprite::SpriteDraw()  m_pSprite->Draw()�Ɏ��s" );

	//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
	//	DirectX 8
	//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
#else
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
	vctRtCenter.x = (pSrcRect->right - pSrcRect->left) * fRotationCenterX * fScaleX;
	vctRtCenter.y = (pSrcRect->bottom - pSrcRect->top) * fRotationCenterY * fScaleY;

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

	//////////////////////////////////////////////////////////////////////////////

	//	�G��
	MyuAssert2( m_pSprite->Draw( pTexture->GetDirect3dTexturePtr(),
		pSrcRect, &vctScale, &vctRtCenter, fRad, &vctPos, color ), D3D_OK,
		MGLMSGNO_GRPMGR(87), "CMglDxSprite::SpriteDraw()  m_pSprite->Draw()�Ɏ��s" );
#endif
}

//	�X�v���C�g��Begin()
void CMglDxSprite::SpriteBegin()
{
	if( m_pSprite == NULL )
		MyuThrow(MGLMSGNO_GRPMGR(91), "Sprite���쐬����Ă��܂���B");

	if( m_pSprite != NULL && m_bSpriteBegun == FALSE ){
//#if _MGL_DXVER == 9
#if _MGL_D3DXVER >= MGL_D3DXVER_ID3DXSPRITE_CHANGED
		MyuAssert2( m_pSprite->Begin(0), D3D_OK,
		//MyuAssert2( m_pSprite->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK), D3D_OK,
#else
		MyuAssert2( m_pSprite->Begin(), D3D_OK,
#endif
			MGLMSGNO_GRPMGR(89), "CMglDxSprite::SpriteBegin()  m_pSprite->Begin()�Ɏ��s" );
		m_bSpriteBegun = TRUE;
	}
}
//	�X�v���C�g��End()
void CMglDxSprite::SpriteEnd()
{
	if( m_pSprite == NULL )
		MyuThrow(MGLMSGNO_GRPMGR(92), "Sprite���쐬����Ă��܂���B");

	if( m_pSprite != NULL && m_bSpriteBegun == TRUE ){
		MyuAssert2( m_pSprite->End(), D3D_OK,
			MGLMSGNO_GRPMGR(90), "CMglDxSprite::SpriteEnd()  m_pSprite->End()�Ɏ��s" );
		m_bSpriteBegun = FALSE;
	}
}
