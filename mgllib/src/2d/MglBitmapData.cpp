//////////////////////////////////////////////////////////
//
//	MglBitmapData
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglBitmapData.h"
#include "MglTexture.h"

/*void CMglBitmapData::_Init(_MGL_IDirect3DSurface *pSurface, int nHeight, CONST RECT* pTargetRect, DWORD dwFlags)
{
	//D3DLOCKED_RECT* pLockedRect = NULL;
	D3DLOCKED_RECT lockedRectInfo;
	MyuAssert( pSurface->LockRect(&lockedRectInfo, pTargetRect, 0), D3D_OK,
		"CMglBitmapData::CMglBitmapData()  pSurface->LockRect()に失敗" );

	m_pSurface = pSurface;
	_Init(lockedRectInfo, nHeight);
}*/

//	コンストラクタ1
CMglBitmapData::CMglBitmapData(_MGL_IDirect3DSurface *pSurface, int nHeight, CONST RECT* pTargetRect, DWORD dwFlags)
{
	/*_Init();
	m_pSurface = pSurface;
	m_nHeight = nHeight;
	m_pTargetRect = pTargetRect;
	m_dwFlags = dwFlags;*/
	_Init(NULL,pSurface,nHeight,pTargetRect,dwFlags);
}

//	コンストラクタ2
CMglBitmapData::CMglBitmapData(CMglTexture *pMglTex, CONST RECT* pTargetRect, DWORD dwFlags)
{
	/*_Init();
	m_pMglTex = pMglTex;
	m_pTargetRect = pTargetRect;
	m_dwFlags = dwFlags;
	m_nHeight = */
	_Init(pMglTex, pMglTex->GetSurfacePtr(), pMglTex->GetBmpHeight(), pTargetRect, dwFlags);
}

void CMglBitmapData::Release()
{
	//	こんな単純でいいんだっけか（ほかにも何かあったような肝・・・
	Unlock();
}

//	2008/06/28
void CMglBitmapData::Lock(DWORD dwMode)
{
	if ( m_bLocked == TRUE )
		return;

	D3DLOCKED_RECT lockedRectInfo;
	MyuAssert( m_pSurface->LockRect(&lockedRectInfo, m_pTargetRect, 0), D3D_OK,
		"CMglBitmapData::CMglBitmapData()  pSurface->LockRect()に失敗" );
	if ( m_pMglTex != NULL )
		m_pMglTex->Lock();
	SetupLockedRect(lockedRectInfo);

	m_bLocked = TRUE;
}

//	2008/06/28
void CMglBitmapData::Unlock()
{
	if ( m_bLocked == FALSE )
		return;

	MyuAssert( m_pSurface->UnlockRect(), D3D_OK,
		"CMglBitmapData::CMglBitmapData()  pSurface->UnlockRect()に失敗" );
	if ( m_pMglTex != NULL )
		m_pMglTex->Unlock();

	m_bLocked = FALSE;
}

//	塗りつぶし
void CMglBitmapData::Fill(D3DCOLOR color){
	Fill(color,Rect(0,0,GetWidth(),GetHeight()));
	/*Lock();
	for(int i=0; i<GetHeight(); i++)
		memset(GetLine(i), color, GetWidth());
	Unlock();*/
}

//	塗りつぶし
void CMglBitmapData::Fill(D3DCOLOR color, RECT rect){
	if ( rect.left > GetWidth() )
		return;
	if ( rect.top > GetHeight() )
		return;

	Lock();

	int nEndX = rect.right;
	if ( nEndX > GetWidth() )
		nEndX = GetWidth();

	int nEndY = rect.bottom;
	if ( nEndY > GetHeight() )
		nEndY = GetHeight();

	for(int i=rect.top; i<nEndY; i++)
		memset(GetLine(i)+rect.left, color, nEndX);

	Unlock();
}

