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

void CMglDxSurface::CaptureToFile( const char* szFilename, D3DXIMAGE_FILEFORMAT fileType, const ::RECT *pSrcRect)
{
	MyuAssert( D3DXSaveSurfaceToFile( szFilename, fileType, m_pSurface, NULL, pSrcRect), D3D_OK,
		"CMglDxSurface::CaptureToFile()  D3DXSaveSurfaceToFile() に失敗。" );
}

