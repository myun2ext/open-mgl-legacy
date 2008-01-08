//////////////////////////////////////////////////////////
//
//	Myu2DGraphicsSurface - �摜�C���[�W�Ǘ��N���X
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
//	�E��{�@�\��CMyu2DGraphicsSurfacePrimitive�֕���
//
//	v0.40.00 06/11/25
//	�ECMyu2DGraphicsSurface�֖��̕ύX�B
//
//////////////////////////////////////////////////////////

#ifndef __Myu2DGraphicsSurface_H__
#define __Myu2DGraphicsSurface_H__

//#include <D3dx8tex.h>		stdafx��

#include "MglGraphicManager.h"
#include "MglTexture.h"	//	2007/01/10  MglTexture �Ɠ�d��`�ɂȂ�̂Łc

#define X_ADJ (-0.66f)
#define Y_ADJ (-0.96f)
/*	2007/01/10  MglTexture �Ɠ�d��`�ɂȂ�̂Łc
//#define X_ADJ (0)
//#define Y_ADJ (0)
#define DEF_COLORKEY	D3DCOLOR_PINK

#define VERTEXNO_LT		(0)
#define VERTEXNO_RT		(1)
#define VERTEXNO_LB		(3)
#define VERTEXNO_RB		(2)

//	���_�F
typedef struct
{
	D3DCOLOR leftTop;
	D3DCOLOR leftBottom;
	D3DCOLOR rightTop;
	D3DCOLOR rightBottom;
}
VERTEX_COLORS;
*/

//	�N���X�錾
class DLL_EXP CMyu2DGraphicsSurface : public CMyuReleaseBase	//	CMglDirect3dTexture
{
protected:
	CMglGraphicManager* m_myudg;	//	DG�N���X�ւ̃|�C���^���i�[
	IDirect3DDevice8* d3d;			//	D3DDevice�ւ̃|�C���^
	BOOL m_bRenderTarget;			//	bRenderTarget�̃R�s�[

	int m_nBmpSizeX, m_nBmpSizeY;	//	BMP�̃T�C�Y
	int nRealSizeX, nRealSizeY;		//	���T�C�Y(�e�N�X�`����̃T�C�Y)
	float fRealTexTu, fRealTexTv;	//	�e�N�X�`����Ŏ��ۂɎg�p�����tu,uv
	D3DCOLOR m_colorKey;			//	�J���[�L�[
	BOOL m_bCenterDraw;				//	�Z���^�[�G��L��/�����t���O

	MYU_VERTEX m_vertices[4];		//	���_

	IDirect3DTexture8* m_pTexture;	//	�e�N�X�`��
	IDirect3DSurface8* m_pSurface;	//	�T�[�t�F�X
	ID3DXSprite* m_pSprite;			//	�X�v���C�g

	int m_nSfcID;

	string m_sfcName;				//	�֘A�t����ꂽ���O

	//	Init/Create�`�F�b�N
	BOOL initFlg;					//	�������t���O
	BOOL createFlg;					//	Create�t���O

	void InitCheck() {
		/*
		if ( initFlg == FALSE ){
			if ( m_sfcName != "" )
				MyuThrow( 0, "MglSurface[%s]::Init()����ԍŏ��ɌĂ�ł��������B", m_sfcName.c_str() );
			else
				MyuThrow( 0, "MglSurface::Init()����ԍŏ��ɌĂ�ł��������B" );
		}
		*/

		//	2007/01/09
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}
	void CreateCheck() {
		if ( createFlg == FALSE ){
			if ( m_sfcName != "" )
				MyuThrow( 0, "MglSurface[%s]::Create()���Ă�ł��������B", m_sfcName.c_str() );
			else
				MyuThrow( 0, "MglSurface::Create()���Ă�ł��������B" );
		}
	}
public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMyu2DGraphicsSurface();
	virtual ~CMyu2DGraphicsSurface();

	void Init( CMglGraphicManager* in_myudg, const char* szName=NULL );
	void Release();

	//	�ߋ��Ƃ̌݊��̂��߂ɑ���
	void CreateFromFile( LPCSTR szFileName, BOOL bRenderTarget=TRUE, D3DCOLOR colorKey=DEF_COLORKEY );

	void Create( int x=0, int y=0, BOOL bRenderTarget=TRUE );
	void Create( LPCSTR szFileName, BOOL bRenderTarget=TRUE, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFile( szFileName, bRenderTarget, colorKey );}
	
	//	Draw�̊�{
	void TextureDraw( float x, float y, RECT* srcRect, float fScaleX, float fScaleY, D3DCOLOR color, DWORD dwAlphaOption=MGL_ALPHA_OPT_DEFAULT )
	{
		VERTEX_COLORS tVertexColors;
		GenerateEqVertexColors( &tVertexColors, color );
		TextureDraw( x, y, srcRect, fScaleX, fScaleY, 0.5f, 0.5f, 0.0f, &tVertexColors, dwAlphaOption );
	}

	//	�ŏI�I�Ɂ��̂悤�ȃT�|�[�g�ɂ���\��
	void TextureDraw( float x, float y, RECT* srcRect, float fScaleX, float fScaleY,
		float fRotationCenterX, float fRotationCenterY, float fAngle,
		VERTEX_COLORS* vertexColors, DWORD dwAlphaOption );

	//void TextureDraw( float x=0.0f, float y=0.0f, float fSizeX=1.0f, float fSizeY=1.0f, D3DCOLOR color=0xffffffff );
	void TextureDrawPrimitive();

	/*void TextureDraw( float x=0.0f, float y=0.0f, float fSizeX=1.0f, float fSizeY=1.0f, D3DCOLOR color=0xffffffff )
		{}*/

	/////////////////////////////////////////////////////////////////////////////////////////////

	//	Draw
	void Draw( CMyu2DGraphicsSurface* destSurface, float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
		{ destSurface->SetRender(); Draw( x, y, srcRect, color );
			m_myudg->SetRenderBackBuffer(); // 2007/02/12 ����������K�v
		}
	void Draw( float x=0, float y=0, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
	{ CMyu2DGraphicsSurface::DrawEx( 1.0f, 1.0f, 0.5f, 0.5f, 0, x, y, srcRect, color ); }

	//	2007/02/12  DrawEx() �������ёւ�

	//	DrawEx - �X�v���C�g���g���o�[�W����
	void DrawEx( CMyu2DGraphicsSurface* destSurface, float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
		//float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE )
		//{ destSurface->SetRender(); DrawEx( fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, srcRect, color, dwAlphaOption );
		{ destSurface->SetRender(); DrawEx( fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, srcRect, color );
			m_myudg->SetRenderBackBuffer(); // 2007/02/12 ����������K�v
		}
	void DrawEx( float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff );
		//float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE );

	/*
	//	DrawEx - �X�v���C�g���g���o�[�W����
	void DrawEx( CMyu2DGraphicsSurface* destSurface, float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
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
	void CopyRectToOther( CMyu2DGraphicsSurface* destSurface, RECT *srcRect=NULL, int x=0, int y=0 );
	void CopyRectToThis( CMyu2DGraphicsSurface* srcSurface, RECT *srcRect=NULL, int x=0, int y=0 );
	//void CopyRect( int x=0, int y=0, RECT *srcRect=NULL );

	//	�Z���^�[�G��
	void EnableCenterDraw() {	m_bCenterDraw = TRUE; }
	void DisableCenterDraw() {	m_bCenterDraw = FALSE; }

	//	�O���f�[�V����
	//void SetGradation() { SetGradation(0xffffffff,0xffffffff,0xffffffff,0xffffffff); }
	//void SetGradation( D3DCOLOR colorLeftTop, D3DCOLOR colorRightTop, D3DCOLOR colorLeftBottom, D3DCOLOR colorRightBottom );

	void GenerateEqVertexColors( VERTEX_COLORS* dest, D3DCOLOR color )
	{
		for( D3DCOLOR* p=(D3DCOLOR*)dest; p<((D3DCOLOR*)dest)+4; p++ )
		{
			*p = color;
		}

		/*
		dest->leftTop = color;
		dest->leftBottom = color;
		dest->rightTop = color;
		dest->rightBottom = color;
		*/
	}

	void SetRender();
	void Clear(){ Clear( m_colorKey & 0x00ffffff ); } // m_colorKey���֘A����̂Ńf�t�H���g�����ɂ͏o���Ȃ��̂łꂷ
	void Clear( D3DCOLOR color );
	void Paint( RECT* rect, D3DCOLOR color );

	//	�v���p�e�B�n���\�b�h
	IDirect3DTexture8* GetTexturePtr() { CreateCheck(); return m_pTexture; }
	IDirect3DSurface8* GetSurfacePtr() { CreateCheck(); return m_pSurface; }
	ID3DXSprite* GetSpritePtr() { CreateCheck(); return m_pSprite; }
	MYU_VERTEX* GetVerticesPtr() { CreateCheck(); return m_vertices; }
	int GetBmpSizeX() { return m_nBmpSizeX; }
	int GetBmpSizeY() { return m_nBmpSizeY; }

	//	�f�o�b�O�p�ɖ��O��t����
	void SetName( const char* szName ){ m_sfcName = szName; }
};

typedef CMyu2DGraphicsSurface CMglBitmap;
typedef CMyu2DGraphicsSurface CMglSprite;

#endif//__Myu2DGraphicsSurface_H__
