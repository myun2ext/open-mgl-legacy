//////////////////////////////////////////////////////////
//
//	MglDxTexture - �e�N�X�`���Ǘ��N���X
//

#ifndef __MglDxTexture_H__
#define __MglDxTexture_H__

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

#define MGL_TEXTURE_STAGE_MAX	(8)

//	�N���X�錾
class DLL_EXP CMglDxTexture : public CMglDgBase
{
public:
	typedef CMglLockedRectIterator iterator;

protected:
	//CMglGraphicManager* m_myudg;	//	DG�N���X�ւ̃|�C���^���i�[

	//	Direct3D�n
	//_MGL_IDirect3DDevice* d3d;			//	D3DDevice�ւ̃|�C���^
	_MGL_IDirect3DTexture* m_pTexture;	//	�e�N�X�`��
	_MGL_IDirect3DSurface* m_pSurface;	//	�T�[�t�F�X

	//	�摜���
	D3DXIMAGE_INFO m_imgInfo;
	MGLTUTV m_tutv;

	//	�L�����Ă���
	D3DCOLOR m_colorKey;			//	�J���[�L�[
	BOOL m_bRenderTarget;			//	bRenderTarget

	BOOL m_bLocked;					//	���b�N - 2008/06/28
	CMglBitmapData *m_pBitmapData;

	//	���_���
	//float fRealTexTu, fRealTexTv;	//	�e�N�X�`����Ŏ��ۂɎg�p�����tu,uv

	//	�������\�b�h�i�`�F�b�N�p�j
	/*void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}*/
	void CreateCheck() {
		InitCheck();	//	2008/06/28 ��������Ȃ��ƑʖڂłȂ��E�E�E�H
		//if ( createFlg == FALSE ){
		if ( m_pTexture == NULL )
			MyuThrow( 0, "CMglDxTexture ���쐬�ł���ɂ��ւ�炸������s�����Ƃ��܂����BCreate()�n���\�b�h���Ă�ł��������B" );
	}

	void LockedCheck(){
		if ( m_bLocked == TRUE )
			MyuThrow(0, "CMglDxTexture ���b�N����Ă��܂��B���b�N���J�����Ă��������B\r\n\r\n"
				"�l������\�� :\r\n"
				"  CMglInternalBitmapData::Release() �̌Ăяo���R��B");
	}

	void UpdateTexture( _MGL_IDirect3DTexture* pDestTexture );
	void UpdateSurface( CONST RECT* pSourceRect, _MGL_IDirect3DSurface* pDestSurface, CONST POINT* pDestinationPoint );

private:
	//	�e�N�X�`���̃T�[�t�F�X���擾����
	void _GetSurface(){
		MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
			"CMglDxTexture::GetSurface()  GetSurfaceLevel()�Ɏ��s" );
	}
public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglDxTexture();
	virtual ~CMglDxTexture(){ Release(); }

	//	�������ƊJ��
	//void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	void Release();

	//	�쐬
	void Create( int x, int y, BOOL bRenderTarget );

	//	�t�@�C������̓ǂݍ��݌n
	void Load( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFileEx( szFileName, 0, 0, bRenderTarget, colorKey ); }

	void Create( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFileEx( szFileName, 0, 0, bRenderTarget, colorKey ); }

	void CreateFromFile( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		//CreateFromFileEx( szFileName, D3DX_DEFAULT, D3DX_DEFAULT, bRenderTarget, colorKey ); }
		CreateFromFileEx( szFileName, 0, 0, bRenderTarget, colorKey ); }

	void CreateFromFileEx( LPCSTR szFileName, int nForceBmpWidth, int nForceBmpHeight,
		BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY,
		DWORD dwFilter=D3DX_FILTER_NONE, DWORD dwMapFilter=D3DX_FILTER_BOX );
	//	DWORD dwFilter=D3DX_FILTER_NONE, DWORD dwMapFilter=D3DX_FILTER_NONE );

	//void Create( int x=0, int y=0, BOOL bRenderTarget=TRUE );
	/*void Create( LPCSTR szFileName, BOOL bRenderTarget=TRUE, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFile( szFileName, bRenderTarget, colorKey );}*/
	void CreateTextureFromFileEx( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFileEx( szFileName, 0, 0, bRenderTarget, colorKey ); }

	void CreateTextureFromFileEx( LPCSTR szFileName, int nForceBmpWidth, int nForceBmpHeight,
		BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY,
		DWORD dwFilter=D3DX_FILTER_NONE, DWORD dwMapFilter=D3DX_FILTER_NONE ){
		CreateFromFileEx( szFileName, nForceBmpWidth, nForceBmpHeight, bRenderTarget, colorKey, dwFilter, dwMapFilter); }

	//	����������쐬
	void CreateFromFile( LPCVOID lpFileData, UINT nDataSize, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromMemoryFileEx( lpFileData, nDataSize, 0, 0, bRenderTarget, colorKey ); }

	void CreateFromMemoryFileEx( LPCVOID lpFileData, UINT nDataSize, int nForceBmpWidth, int nForceBmpHeight,
		BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY,
		DWORD dwFilter=D3DX_FILTER_NONE, DWORD dwMapFilter=D3DX_FILTER_NONE );

	/////////////////////////////////////////////////////////////////////

	//	�R�s�[���\�b�h
	void Copy( CMglDxTexture &toTex ){ CopyToOtherTexture(toTex); }
	void CopyToOtherTexture( CMglDxTexture &toTex ){ UpdateTexture( toTex.GetD3dTexturePtr() ); }
	void CopyFromOtherTexture( CMglDxTexture &fromTex ){ fromTex.UpdateTexture( m_pTexture ); }

	////////////////////////////////////////////////////////////////////////////////

	void SetD3dStageTexture(DWORD nStage=0);
	void SetStageTexture(DWORD nStage=0){ SetD3dStageTexture(nStage); }
	void SetRenderTexture(DWORD nStage=0){ SetD3dStageTexture(nStage); }

	//	�����ϐ��擾�n
	_MGL_IDirect3DTexture* GetDirect3dTexturePtr(){ CreateCheck(); return m_pTexture; }
	_MGL_IDirect3DTexture* GetD3dTexturePtr(){ CreateCheck(); return m_pTexture; }
	_MGL_IDirect3DTexture* GetDxTexturePtr(){ CreateCheck(); return m_pTexture; }
	_MGL_IDirect3DTexture* GetTexturePtr(){ CreateCheck(); return m_pTexture; }
	_MGL_IDirect3DSurface* GetSurfacePtr() { CreateCheck(); return m_pSurface; }

	//	�T�C�Y�擾
	int GetBmpWidth(){ return m_imgInfo.Width; }
	int GetBmpHeight(){ return m_imgInfo.Height; }
	//MGLTUTV GetTuTv();
	const MGLTUTV& GetTuTv();

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

typedef CMglDxTexture CMglD3dTexture;
typedef CMglDxTexture CMglSquareTexture;
typedef CMglDxTexture CMglDxTexture;



////////////////////////////////////////////////////

//	TextureStageState���Ǘ�����N���X
class DLL_EXP CMglTextureStageStateManager : public virtual CMglDgBase
{
public:
	typedef std::map<D3DTEXTURESTAGESTATETYPE,DWORD> _MAP_t;

protected:
	//map<D3DTEXTURESTAGESTATETYPE> m_tssList;
	_MAP_t m_tssList[MGL_TEXTURE_STAGE_MAX];

public:
	void Set(int nStage, D3DTEXTURESTAGESTATETYPE tssType, DWORD value);/*{
		m_tssList[nStage][tssType] = value;
	}*/
	DWORD Get(int nStage, D3DTEXTURESTAGESTATETYPE tssType){
		return m_tssList[nStage][tssType];
	}
	void Erase(int nStage, D3DTEXTURESTAGESTATETYPE tssType){
		m_tssList[nStage].erase(tssType);
	}
	void ClearStage(int nStage){ m_tssList[nStage].clear(); }
	void StageClear(int nStage){ m_tssList[nStage].clear(); }
	
	void Sets(int nStage){ SetsTextureStageState(nStage); }
	void SetsTextureStageState(int nStage){
		InitCheck();
		_MAP_t &tssL = m_tssList[nStage];
		_MAP_t::iterator it = tssL.begin();
		for(; it != tssL.end(); it++){
			D3DTEXTURESTAGESTATETYPE tssType = it->first;
			DWORD value = it->second;
			CMglDgBase::m_d3d->SetTextureStageState( nStage, tssType, value);
		}
	}
};
typedef CMglTextureStageStateManager CMglTssManager;

#endif//__MglDxTexture_H__
