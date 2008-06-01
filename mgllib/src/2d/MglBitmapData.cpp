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
CMglBitmapData::CMglBitmapData(CMglTexture &mglTex, CONST RECT* pTargetRect, DWORD dwFlags)
{
	_Init(mglTex.GetSurfacePtr(), mglTex.GetBmpHeight(), pTargetRect, dwFlags);
}

void CMglBitmapData::_Init(_MGL_IDirect3DSurface *pSurface, int nHeight, CONST RECT* pTargetRect, DWORD dwFlags)
{
	//D3DLOCKED_RECT* pLockedRect = NULL;
	D3DLOCKED_RECT lockedRectInfo;
	MyuAssert( pSurface->LockRect(&lockedRectInfo, pTargetRect, 0), D3D_OK,
		"CMglBitmapData::CMglBitmapData()  pSurface->LockRect()に失敗" );

	_Init(lockedRectInfo, nHeight);
}

