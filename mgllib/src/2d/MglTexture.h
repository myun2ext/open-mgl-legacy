//////////////////////////////////////////////////////////
//
//	MglTexture - �e�N�X�`���Ǘ��N���X
//
//	�Ȃ��ACreateTextureFromFile() �ō쐬���ꂽ�e�N�X�`����
//	�O�p�`��񖇑g�ݍ��킹���l�p�`�ł���̂ł��̎��ɒ��ӂ��ꂽ���I

#ifndef __MglTexture_H__
#define __MglTexture_H__

#include "MglGraphicManager.h"
#include "MglVertex.h"
#include "MglBitmapData.h"

/*
//	ADJ S1
#define X_ADJ (-0.66f)
#define Y_ADJ (-0.96f)
*/

//	ADJ S2 - 2007/01/10  D3DX_FILTER_NONE ��
//	���_�v�Z��float�ōs���邽�߁A�v�Z�덷�ŉ摜������Ȃ��悤�Y�����Ă���
//	0.5f�ŗǂ��悤�ȋC�����邪�A���_�v�Z���ǂ̂悤�ȃ��W�b�N�Ȃ̂��s���Ȃ̂�
//	�ꉞ -0.66f�A-0.96f �ɑ����� -0.75f ���炢�ɐݒ肵�Ă����B
//	�i0.66f�Ƃ��ɂ��Ă��Ȃ��̂́A�m��0.75f�Ƃ��̕���CPU�͌v�Z���₷�������C����������j
//	���Ȃ݂Ɏ���������A0.00010000001f:OK�@0.0001f:NG�@���ۂ� <- 2008/03/16 RADEON�̏ꍇ���������E�E�E
//#define TEXTURE_FLOAT_ADJ	(-0.75f)
#define TEXTURE_FLOAT_ADJ	(-0.75f)

//#define X_ADJ (0)
//#define Y_ADJ (0)
#define DEF_COLORKEY			D3DCOLOR_PINK
#define RENDER_TARGET_DEFAULT	(FALSE)

/*
//	 -> �폜�\��
#define VERTEXNO_LT		(0)
#define VERTEXNO_RT		(1)
#define VERTEXNO_LB		(3)
#define VERTEXNO_RB		(2)

//	���_�F -> �폜�\��
typedef struct
{
	D3DCOLOR leftTop;
	D3DCOLOR leftBottom;
	D3DCOLOR rightTop;
	D3DCOLOR rightBottom;
}
VERTEX_COLORS;

typedef MYU_VERTEX	MGL_VERTEX;
typedef struct
{
	MGL_VERTEX lt;
	MGL_VERTEX rt;
	MGL_VERTEX lb;
	MGL_VERTEX rb;
}
MGL_SQUARE_VERTEXS;
*/


//	�N���X�錾
class DLL_EXP CMglTexture// : public CMyuReleaseBase
{
public:
	typedef CMglLockedRectIterator iterator;

protected:
	CMglGraphicManager* m_myudg;	//	DG�N���X�ւ̃|�C���^���i�[

	//	Direct3D�n
	_MGL_IDirect3DDevice* d3d;			//	D3DDevice�ւ̃|�C���^
	_MGL_IDirect3DTexture* m_pTexture;	//	�e�N�X�`��
	_MGL_IDirect3DSurface* m_pSurface;	//	�T�[�t�F�X

	//	�摜���
	D3DXIMAGE_INFO m_imgInfo;

	//	�L�����Ă���
	D3DCOLOR m_colorKey;			//	�J���[�L�[
	BOOL m_bRenderTarget;			//	bRenderTarget

	CMglBitmapData *m_pBitmapData;

	//	���_���
	//MYU_VERTEX m_vertices[4];		//	���_ -> �ʂɃ����o�ϐ��Ŏ��K�v�i�N�l
	//float fRealTexTu, fRealTexTv;	//	�e�N�X�`����Ŏ��ۂɎg�p�����tu,uv

	//	�Â��`������p
	//BOOL m_bCenterDraw;			//	�Z���^�[�G��L��/�����t���O

	//	�������\�b�h�i�`�F�b�N�p�j
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}
	void CreateCheck() {
		//if ( createFlg == FALSE ){
		if ( m_pTexture == NULL )
			MyuThrow( 0, "CMglTexture ���쐬�ł���ɂ��ւ�炸������s�����Ƃ��܂����B" );
	}

	//	�Â��`������p
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

private:
	//	�e�N�X�`���̃T�[�t�F�X���擾����
	void _GetSurface(){
		MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
			"CMglTexture::GetSurface()  GetSurfaceLevel()�Ɏ��s" );
	}
public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglTexture();
	virtual ~CMglTexture(){ Release(); }

	//	�������ƊJ��
	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd );
	void Release();

	//	�쐬
	void CreateTextureFromFile( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		//CreateTextureFromFileEx( szFileName, D3DX_DEFAULT, D3DX_DEFAULT, bRenderTarget, colorKey ); }
		CreateTextureFromFileEx( szFileName, 0, 0, bRenderTarget, colorKey ); }
	void CreateTextureFromFileEx( LPCSTR szFileName, int nForceBmpWidth, int nForceBmpHeight,
		BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY,
		DWORD dwFilter=D3DX_FILTER_NONE, DWORD dwMapFilter=D3DX_FILTER_NONE );
	//void Create( int x=0, int y=0, BOOL bRenderTarget=TRUE );
	/*void Create( LPCSTR szFileName, BOOL bRenderTarget=TRUE, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFile( szFileName, bRenderTarget, colorKey );}*/
	void Create( int x, int y, BOOL bRenderTarget );

	//	�`��
	void Draw(float x=0.0f, float y=0.0f, D3DCOLOR color=D3DCOLOR_WHITE );

	//	���_�f�[�^�ŏ���
	void Draw( MGL_SQUARE_VERTEXS *pMglSqVertexs, BOOL bVertexRevise=TRUE );
	void Draw( MYU_VERTEX *pMyuVertex, UINT nPrimitiveCount=2, BOOL bVertexRevise=TRUE );

	//	PrimitiveUP
	void DrawPrimitiveUP( D3DPRIMITIVETYPE primitiveType, UINT nPrimitiveCount,
		const void *pVertexStreamZeroData, UINT nVertexStreamZeroStride );

	//	BMP�̒��_�f�[�^�擾
	void GetBmpVertexs( MGL_SQUARE_VERTEXS *pMglSqVertexs );

	//	�����ϐ��擾�n
	_MGL_IDirect3DTexture* GetDirect3dTexturePtr(){ CreateCheck(); return m_pTexture; }
	_MGL_IDirect3DSurface* GetSurfacePtr() { CreateCheck(); return m_pSurface; }

	//	�T�C�Y�擾
	int GetBmpWidth(){ return m_imgInfo.Width; }
	int GetBmpHeight(){ return m_imgInfo.Height; }

	////////////////////////////////////////////////////////////////////////////////

	//	2008/06/01  Bitmap�f�[�^�擾�i�N���X�����p�ӂ��Ď������ĂȂ��������ۂ��E�E�E�H�j
	CMglBitmapData* GetIternalBitmapData();

	/*
	iterator begin();
	iterator end(){ return NULL; }
	*/

	/////////////////////////////////////////////////////////////////////////

	//	�Â��`�����
	void TextureDraw( float x=0.0f, float y=0.0f, RECT* srcRect=NULL, float fScaleX=1.0f, float fScaleY=1.0f, D3DCOLOR color=D3DCOLOR_WHITE, DWORD dwAlphaOption=MGL_ALPHA_OPT_DEFAULT )
	{
		VERTEX_COLORS tVertexColors;
		GenerateEqVertexColors( &tVertexColors, color );
		TextureDraw( x, y, srcRect, fScaleX, fScaleY, 0.5f, 0.5f, 0.0f, &tVertexColors, dwAlphaOption );
	}
	//	��fAngle�͎��͎������ĂȂ�
	void TextureDraw( float x, float y, RECT* srcRect, float fScaleX, float fScaleY,
		float fRotationCenterX, float fRotationCenterY, float fAngle,
		VERTEX_COLORS* vertexColors, DWORD dwAlphaOption );
	//void TextureDraw( float x=0.0f, float y=0.0f, float fSizeX=1.0f, float fSizeY=1.0f, D3DCOLOR color=0xffffffff );

	//D3DCOLOR* GetSurfaceIterator(){ ;
	/*
	//	�ݒ�
	void EnableCenterDraw() {	m_bCenterDraw = TRUE; }
	void DisableCenterDraw() {	m_bCenterDraw = FALSE; }
	*/
};


#endif//__MglTexture_H__
