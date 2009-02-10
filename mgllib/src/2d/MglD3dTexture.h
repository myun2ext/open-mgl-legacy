//////////////////////////////////////////////////////////
//
//	MglD3dTexture - �e�N�X�`���Ǘ��N���X
//
//	�Ȃ��ACreateTextureFromFile() �ō쐬���ꂽ�e�N�X�`����
//	�O�p�`��񖇑g�ݍ��킹���l�p�`�ł���̂ł��̎��ɒ��ӂ��ꂽ���I

#ifndef __MglD3dTexture_H__
#define __MglD3dTexture_H__

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

//	�N���X�錾
class DLL_EXP CMglD3dTexture// : public CMyuReleaseBase
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

	BOOL m_bLocked;					//	���b�N - 2008/06/28
	CMglBitmapData *m_pBitmapData;

	//	���_���
	//float fRealTexTu, fRealTexTv;	//	�e�N�X�`����Ŏ��ۂɎg�p�����tu,uv

	//	�������\�b�h�i�`�F�b�N�p�j
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}
	void CreateCheck() {
		InitCheck();	//	2008/06/28 ��������Ȃ��ƑʖڂłȂ��E�E�E�H
		//if ( createFlg == FALSE ){
		if ( m_pTexture == NULL )
			MyuThrow( 0, "CMglD3dTexture ���쐬�ł���ɂ��ւ�炸������s�����Ƃ��܂����BCreate()�n���\�b�h���Ă�ł��������B" );
	}

	void LockedCheck(){
		if ( m_bLocked == TRUE )
			MyuThrow(0, "CMglD3dTexture ���b�N����Ă��܂��B���b�N���J�����Ă��������B\r\n\r\n"
				"�l������\�� :\r\n"
				"  CMglInternalBitmapData::Release() �̌Ăяo���R��B");
	}

private:
	//	�e�N�X�`���̃T�[�t�F�X���擾����
	void _GetSurface(){
		MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
			"CMglD3dTexture::GetSurface()  GetSurfaceLevel()�Ɏ��s" );
	}
public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglD3dTexture();
	virtual ~CMglD3dTexture(){ Release(); }

	//	�������ƊJ��
	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	void Release();

	//	�쐬
	void Load( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateTextureFromFileEx( szFileName, 0, 0, bRenderTarget, colorKey ); }
	void Create( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateTextureFromFileEx( szFileName, 0, 0, bRenderTarget, colorKey ); }
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

	void SetD3dStageTexture(DWORD nStage=0);
	void SetStageTexture(DWORD nStage=0){ SetD3dStageTexture(nStage); }
	void SetRenderTexture(DWORD nStage=0){ SetD3dStageTexture(nStage); }

	//	�����ϐ��擾�n
	_MGL_IDirect3DTexture* GetDirect3dTexturePtr(){ CreateCheck(); return m_pTexture; }
	_MGL_IDirect3DSurface* GetSurfacePtr() { CreateCheck(); return m_pSurface; }

	//	�T�C�Y�擾
	int GetBmpWidth(){ return m_imgInfo.Width; }
	int GetBmpHeight(){ return m_imgInfo.Height; }
	MGLTUTV GetTuTv();

	////////////////////////////////////////////////////////////////////////////////

	//	2008/06/01  Bitmap�f�[�^�擾�i�N���X�����p�ӂ��Ď������ĂȂ��������ۂ��E�E�E�H�j
	CMglBitmapData* GetIternalBitmapData();

	/*
	iterator begin();
	iterator end(){ return NULL; }
	*/

	/////////////////////////////////////////////////////////////////////////

	//D3DCOLOR* GetSurfaceIterator(){ ;

	void SetRender();
	void SetRenderTarget(){ SetRender(); }
	void Clear(){ Clear( m_colorKey & 0x00ffffff ); } // m_colorKey���֘A����̂Ńf�t�H���g�����ɂ͏o���Ȃ��̂łꂷ
	void Clear( D3DCOLOR color );
	void Clear__( D3DCOLOR color );
	void Paint( RECT* pRect, D3DCOLOR color );

	void Lock(){ m_bLocked = TRUE; }
	void Unlock(){ m_bLocked = FALSE; }
};

typedef CMglD3dTexture CMglSquareTexture;

#endif//__MglD3dTexture_H__
