//////////////////////////////////////////////////////////
//
//	MglBitmapData
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglBitmapData.h"
#include "MglTexture.h"

//	コンストラクタ
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
		"CMglBitmapData::CMglBitmapData()  pSurface->LockRect()に失敗" );

	m_pSurface = pSurface;
	_Init(lockedRectInfo, nHeight);
}

void CMglBitmapData::Release()
{
	//	TODO
	MyuAssert( m_pSurface->UnlockRect(), D3D_OK,
		"CMglBitmapData::CMglBitmapData()  pSurface->UnlockRect()に失敗" );
	if ( m_pMglTex != NULL )
		m_pMglTex->Unlock();
}

