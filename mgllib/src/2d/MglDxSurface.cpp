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

//	CaptureToFile
void CMglDxSurface::CaptureToFile( const char* szFilename, D3DXIMAGE_FILEFORMAT fileType, const ::RECT *pSrcRect)
{
	CreateCheck();
	MyuAssert( D3DXSaveSurfaceToFile( szFilename, fileType, m_pSurface, NULL, pSrcRect), D3D_OK,
		"CMglDxSurface::CaptureToFile()  D3DXSaveSurfaceToFile() �Ɏ��s�B" );
}

//	UpdateSurface
void CMglDxSurface::UpdateSurface( CONST RECT* pSourceRect, _MGL_IDirect3DSurface* pDestSurface, CONST POINT* pDestinationPoint )
{
	CreateCheck();	//	Create�`�F�b�N
	MyuAssert( d3d->UpdateSurface( m_pSurface, pSourceRect, pDestSurface, pDestinationPoint ), D3D_OK,
		"CMglDxSurface::UpdateSurface()  d3d->UpdateSurface() �Ɏ��s" );
}