//////////////////////////////////////////////////////////
//
//	MglBitmapData
//		- MglGraphicManager �T�[�t�F�X�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglBitmapData.h"
#include "MglTexture.h"

//	�R���X�g���N�^
CMglBitmapData::CMglBitmapData(CMglTexture *pMglTex, CONST RECT* pTargetRect, DWORD dwFlags)
{
	m_pMglTex = pMglTex;
	m_pMglTex->Lock();
	_Init(pMglTex->GetSurfacePtr(), pMglTex->GetBmpHeight(), pTargetRect, dwFlags);
}

void CMglBitmapData::_Init(_MGL_IDirect3DSurface *pSurface, int nHeight, CONST RECT* pTargetRect, DWORD dwFlags)
{
	//D3DLOCKED_RECT* pLockedRect = NULL;
	D3DLOCKED_RECT lockedRectInfo;
	MyuAssert( pSurface->LockRect(&lockedRectInfo, pTargetRect, 0), D3D_OK,
		"CMglBitmapData::CMglBitmapData()  pSurface->LockRect()�Ɏ��s" );

	m_pSurface = pSurface;
	_Init(lockedRectInfo, nHeight);
}

void CMglBitmapData::Release()
{
	//	TODO
	MyuAssert( m_pSurface->UnlockRect(), D3D_OK,
		"CMglBitmapData::CMglBitmapData()  pSurface->UnlockRect()�Ɏ��s" );
	if ( m_pMglTex != NULL )
		m_pMglTex->Unlock();
}

