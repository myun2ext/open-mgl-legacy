//////////////////////////////////////////////////////////
//
//	MglImage - �摜�C���[�W�Ǘ��N���X
//
//	v0.10.20 04/11/19
//	�ECreate�̃`�F�b�N�������Ă��Ȃ������I�I_|�P|��
//	�ECopyRect�n���C���B
//
//	v0.10.21 04/11/22
//	�EGet�`�n���\�b�h�Ƀ`�F�b�N�ǉ��B
//
//	v0.10.25 04/12/14
//	�E���S��_�G��@�\�ǉ��B
//
//	v0.10.26 04/12/16
//	�E���S��_�G��@�\�ARECT���g�p�����ꍇ������
//	�@�\������Ȃ��o�O���C���B
//
//	v0.10.32 04/12/17
//	�EDrawEx()�ɃA���t�@�I�v�V������ǉ�
//	�EGetBmpSizeX(), GetBmpSizeY()�ǉ�
//
//	v0.20.00 05/03/03
//	�E��{�@�\��CMglImagePrimitive�֕���
//
//	v0.40.00 06/11/25
//	�ECMglImage�֖��̕ύX�B
//
//	v0.60.00 07/02/12
//	�ECMglTexture���g���`����
//
//////////////////////////////////////////////////////////

#ifndef __MglImage_H__
#define __MglImage_H__

#include "MglGraphicManager.h"
#include "MglTexture.h"
#include "MglLayerBase4.h"

//	�N���X�錾
//class DLL_EXP CMglImage : public CMglTexture
class DLL_EXP CMglImage : public CMglTexture//, public CMglLayerBase4
{
protected:
	int m_nSfcID;
	string m_sfcName;		//	�֘A�t����ꂽ���O

	//IDirect3DSurface8* m_pSurface;//	�T�[�t�F�X�iCopyRect�p�j

	BOOL m_bCenterDraw;		//	�Z���^�[�G��L��/�����t���O

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglImage();
	CMglImage( LPCSTR szFileName ){
		m_nSfcID = g_nSfcCount;
		g_nSfcCount++;
		Create( szFileName );
	}
	virtual ~CMglImage();

	//	Create
	void CreateFromFile( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CMglTexture::CreateTextureFromFile( szFileName, bRenderTarget, colorKey ); }
	void Create( BOOL bRenderTarget=RENDER_TARGET_DEFAULT ){ CMglTexture::Create(0,0,bRenderTarget); }
	void Create( int x, int y, BOOL bRenderTarget=RENDER_TARGET_DEFAULT ){ CMglTexture::Create(x,y,bRenderTarget); }
	void Create( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFile( szFileName, bRenderTarget, colorKey ); }

	//	Create - CMglGraphicManager* in_myudg �L���
	void CreateFromFile( CMglGraphicManager* in_myudg,
		LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY )
	{
		CMglTexture::Init(in_myudg);
		CMglTexture::CreateTextureFromFile( szFileName, bRenderTarget, colorKey );
	}
	void Create( CMglGraphicManager* in_myudg, BOOL bRenderTarget=RENDER_TARGET_DEFAULT ){
		CMglTexture::Init(in_myudg); CMglTexture::Create(0,0,bRenderTarget); }
	void Create( CMglGraphicManager* in_myudg, int x, int y, BOOL bRenderTarget=RENDER_TARGET_DEFAULT ){
		CMglTexture::Init(in_myudg); CMglTexture::Create(x,y,bRenderTarget); }
	void Create( CMglGraphicManager* in_myudg,
		LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CMglTexture::Init(in_myudg); CreateFromFile( szFileName, bRenderTarget, colorKey ); }

	/////////////////////////////////////////////////////////////////////////////////////////////

	void Draw(){ Draw(0,0); }
	void Draw(
		float x, float y, CONST RECT *pSrcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f );
	void Draw( CMglImage* destSurface,
		float x, float y, CONST RECT *pSrcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )
	{
		destSurface->SetRender();
		Draw( x, y, pSrcRect, color, fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle );
		m_myudg->SetRenderBackBuffer(); // 2007/02/12 ����������K�v
	}

	/*
	//	Draw
	void Draw( CMglImage* destSurface, float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
		{ destSurface->SetRender(); Draw( x, y, srcRect, color );
			m_myudg->SetRenderBackBuffer(); // 2007/02/12 ����������K�v
		}
	void Draw( float x=0, float y=0, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
	{ CMglImage::DrawEx( 1.0f, 1.0f, 0.5f, 0.5f, 0, x, y, srcRect, color ); }

	//	DrawEx - �X�v���C�g���g���o�[�W����
	void DrawEx( CMglImage* destSurface, float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
		//float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE )
		//{ destSurface->SetRender(); DrawEx( fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, srcRect, color, dwAlphaOption );
		{ destSurface->SetRender(); DrawEx( fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, srcRect, color );
			m_myudg->SetRenderBackBuffer(); // 2007/02/12 ����������K�v
		}
	void DrawEx( float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff );
		//float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE );
	*/

	/*
	//	DrawEx - �X�v���C�g���g���o�[�W����
	void DrawEx( CMglImage* destSurface, float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
		//float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE )
		//{ destSurface->SetRender(); DrawEx( fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, srcRect, color, dwAlphaOption );
		{ destSurface->SetRender(); DrawEx( fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, srcRect, color );
			m_myudg->SetRenderBackBuffer(); // 2007/02/12 ����������K�v
		}
	void DrawEx( float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff );
		//float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE );
	*/

	/*	TextureDraw���g���o�[�W����
	void DrawEx( float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE )
	{
		VERTEX_COLORS tVertexColors;
		GenerateEqVertexColors( &tVertexColors, color );
		TextureDraw( x, y, srcRect, fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, &tVertexColors, 0 );
	}
	*/
	
	//	CopyRect�n
	void CopyRectToOther( CMglImage* destSurface, RECT *srcRect=NULL, int x=0, int y=0 );
	void CopyRectToThis( CMglImage* srcSurface, RECT *srcRect=NULL, int x=0, int y=0 );
	//void CopyRect( int x=0, int y=0, RECT *srcRect=NULL );

	//	�Z���^�[�G��
	void EnableCenterDraw() {	m_bCenterDraw = TRUE; }
	void DisableCenterDraw() {	m_bCenterDraw = FALSE; }

	//	�O���f�[�V����
	//void SetGradation() { SetGradation(0xffffffff,0xffffffff,0xffffffff,0xffffffff); }
	//void SetGradation( D3DCOLOR colorLeftTop, D3DCOLOR colorRightTop, D3DCOLOR colorLeftBottom, D3DCOLOR colorRightBottom );


	//	�v���p�e�B�n���\�b�h
	//IDirect3DTexture8* GetTexturePtr() { CreateCheck(); return m_pTexture; }
	//IDirect3DSurface8* GetSurfacePtr() { CreateCheck(); return m_pSurface; }
	//ID3DXSprite* GetSpritePtr() { CreateCheck(); return m_pSprite; }
	//MYU_VERTEX* GetVerticesPtr() { CreateCheck(); return m_vertices; }

	//	�f�o�b�O�p�ɖ��O��t����
	void SetName( const char* szName ){ m_sfcName = szName; }
};

typedef CMglImage CMglBitmap;
//typedef CMglImage CMglSprite;

#endif//__MglImage_H__
