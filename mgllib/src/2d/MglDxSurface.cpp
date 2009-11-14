//////////////////////////////////////////////////////////
//
//	MglDxSurface
//		- MglGraphicManager �T�[�t�F�X�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglDxSurface.h"

////////////////////////////////////////////////////////////////////

//	�R���X�g���N�^
CMglDxSurface::CMglDxSurface()
	: m_pSurface(m_pI)
{
	//m_pI = NULL;
}

//	�f�X�g���N�^
CMglDxSurface::~CMglDxSurface()
{
	//	Release��CMglDgIBase�����
}

/*
//	������
void CMglDxSurface::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();
}
*/

///////////////////////////////////////////////////////////////////////////////////////////


//	�X�N���[���V���b�g
void CMglDxSurface::CaptureToFile( const char* szFilename, D3DXIMAGE_FILEFORMAT fileType, const ::RECT *pSrcRect)
{
	CreateCheck();
	MyuAssert( D3DXSaveSurfaceToFile( szFilename, fileType, m_pSurface, NULL, pSrcRect), D3D_OK,
		"CMglDxSurface::CaptureToFile()  D3DXSaveSurfaceToFile() �Ɏ��s�B" );


/*
HRESULT D3DXLoadSurfaceFromFile(      
    LPDIRECT3DSURFACE9 pDestSurface,
    CONST PALETTEENTRY* pDestPalette,
    CONST RECT* pDestRect,
    LPCTSTR pSrcFile,
    CONST RECT* pSrcRect,
    DWORD Filter,
    D3DCOLOR ColorKey,
    D3DXIMAGE_INFO* pSrcInfo
);

http://msdn.microsoft.com/ja-jp/library/cc372767.aspx
*/
}

//	�R�s�[
void CMglDxSurface::UpdateSurface( CONST RECT* pSourceRect, _MGL_IDirect3DSurface* pDestSurface, CONST POINT* pDestinationPoint )
{
	CreateCheck();	//	Create�`�F�b�N
	MyuAssert( d3d->UpdateSurface( m_pSurface, pSourceRect, pDestSurface, pDestinationPoint ), D3D_OK,
		"CMglDxSurface::UpdateSurface()  d3d->UpdateSurface() �Ɏ��s" );
}

//	�X�N���[���o�b�t�@���R�s�[
void CMglDxSurface::UpdateToScreenBuffer()
{
	Release();

	//	Create()

	MyuAssert( d3d->GetFrontBufferData(0, m_pSurface ), D3D_OK,
		"CMglDxSurface::UpdateToScreenBuffer()  d3d->GetFrontBufferData() �Ɏ��s" );

	//	�E�B���h�E ���[�h�̏ꍇ�A�]����T�[�t�F�C�X�̃T�C�Y�́A�f�X�N�g�b�v�̃T�C�Y�łȂ���΂Ȃ�Ȃ��B
	//	�t���X�N���[�� ���[�h�̏ꍇ�A�]����T�[�t�F�C�X�̃T�C�Y�́A�X�N���[���̃T�C�Y�łȂ���΂Ȃ�Ȃ��B
}


/*


void CMglD3dTexture::SetRenderTarget() ����R�s�[
SetRenderTargetThis()

*/

/*

HRESULT CreateOffscreenPlainSurface(
    UINT Width,
    UINT Height,
    D3DFORMAT Format,
    DWORD Pool,
    IDirect3DSurface9** ppSurface,
    HANDLE* pHandle
);


HRESULT CreateRenderTarget(
    UINT Width,
    UINT Height,
    D3DFORMAT Format,
    D3DMULTISAMPLE_TYPE MultiSample,
    DWORD MultisampleQuality,
    BOOL Lockable,
    IDirect3DSurface9** ppSurface,
    HANDLE* pHandle
);
*/