//////////////////////////////////////////////////////////
//
//	MglDxSurface
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglDxSurface.h"

////////////////////////////////////////////////////////////////////

//	コンストラクタ
CMglDxSurface::CMglDxSurface()
	: m_pSurface(m_pI)
{
	//m_pI = NULL;
}

//	デストラクタ
CMglDxSurface::~CMglDxSurface()
{
	//	ReleaseはCMglDgIBaseがやる
}

/*
//	初期化
void CMglDxSurface::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();
}
*/

///////////////////////////////////////////////////////////////////////////////////////////


//	スクリーンショット
void CMglDxSurface::CaptureToFile( const char* szFilename, D3DXIMAGE_FILEFORMAT fileType, const ::RECT *pSrcRect)
{
	CreateCheck();
	MyuAssert( D3DXSaveSurfaceToFile( szFilename, fileType, m_pSurface, NULL, pSrcRect), D3D_OK,
		"CMglDxSurface::CaptureToFile()  D3DXSaveSurfaceToFile() に失敗。" );


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

//	コピー
void CMglDxSurface::UpdateSurface( CONST RECT* pSourceRect, _MGL_IDirect3DSurface* pDestSurface, CONST POINT* pDestinationPoint )
{
	CreateCheck();	//	Createチェック
	MyuAssert( d3d->UpdateSurface( m_pSurface, pSourceRect, pDestSurface, pDestinationPoint ), D3D_OK,
		"CMglDxSurface::UpdateSurface()  d3d->UpdateSurface() に失敗" );
}

//	スクリーンバッファをコピー
void CMglDxSurface::UpdateToScreenBuffer()
{
	Release();

	//	Create()

	MyuAssert( d3d->GetFrontBufferData(0, m_pSurface ), D3D_OK,
		"CMglDxSurface::UpdateToScreenBuffer()  d3d->GetFrontBufferData() に失敗" );

	//	ウィンドウ モードの場合、転送先サーフェイスのサイズは、デスクトップのサイズでなければならない。
	//	フルスクリーン モードの場合、転送先サーフェイスのサイズは、スクリーンのサイズでなければならない。
}


/*


void CMglD3dTexture::SetRenderTarget() からコピー
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