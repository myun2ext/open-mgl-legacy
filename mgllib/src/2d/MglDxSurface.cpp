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

void CMglDxSurface::CaptureToFile( const char* szFilename, D3DXIMAGE_FILEFORMAT fileType, const ::RECT *pSrcRect)
{
	MyuAssert( D3DXSaveSurfaceToFile( szFilename, fileType, m_pSurface, NULL, pSrcRect), D3D_OK,
		"CMglDxSurface::CaptureToFile()  D3DXSaveSurfaceToFile() �Ɏ��s�B" );
}

