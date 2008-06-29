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
CMglBitmapData::CMglBitmapData(_MGL_IDirect3DSurface *pSurface, int nWidth, int nHeight, CONST RECT* pTargetRect, DWORD dwFlags)
{
	/*_Init();
	m_pSurface = pSurface;
	m_nHeight = nHeight;
	m_pTargetRect = pTargetRect;
	m_dwFlags = dwFlags;*/
	_Init(NULL,pSurface,nWidth,nHeight,pTargetRect,dwFlags);
}

//	コンストラクタ2
CMglBitmapData::CMglBitmapData(CMglTexture *pMglTex, CONST RECT* pTargetRect, DWORD dwFlags)
{
	/*_Init();
	m_pMglTex = pMglTex;
	m_pTargetRect = pTargetRect;
	m_dwFlags = dwFlags;
	m_nHeight = */
	_Init(pMglTex, pMglTex->GetSurfacePtr(),
		pMglTex->GetBmpWidth(), pMglTex->GetBmpHeight(),
		pTargetRect, dwFlags);
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

D3DCOLOR CMglBitmapData::Get(int x,int y)
{
	//Lock(D3DLOCK_READONLY);
	CMglBitmapDataLocker locker(*this);

	D3DCOLOR *p = GetPtr(x,y);
	if ( p == NULL )
		MyuThrow( MSGMSLNO_BITMAP_DATA_INVALID_POS,
			"CMglInternalBitmapData::Get(%d,%d) は失敗しました。",x,y);

	D3DCOLOR work = *p;
	//Unlock();
	return work;
}

D3DCOLOR CMglBitmapData::GetNE(int x,int y, BOOL *pbSuccess)
{
	Lock(D3DLOCK_READONLY);

	D3DCOLOR *p = GetPtr(x,y);
	if ( p == NULL ){
		*pbSuccess = FALSE;
		return 0;
	}

	D3DCOLOR work = *p;
	Unlock();
	
	*pbSuccess = TRUE;
	return work;
}

void CMglBitmapData::Set(int x, int y, D3DCOLOR color)
{
	//Lock();
	CMglBitmapDataLocker locker(*this);

	D3DCOLOR *p = GetPtr(x,y);
	/*if ( p == NULL )
		MyuThrow( 0, "CMglInternalBitmapData::Set(%d,%d) は失敗しました。",x,y);
	*p = color;*/
	if ( p != NULL )
		*p = color;

	//Unlock();
}

////////////////////////////////////////////////////////////////////////

//	塗りつぶし
void CMglBitmapData::Fill(D3DCOLOR color){
	Fill(color,Rect(0,0,m_nWidth,m_nHeight));
	/*Lock();
	for(int i=0; i<m_nHeight; i++)
		memset(GetLine(i), color, m_nWidth);
	Unlock();*/
}

#define MEMSET4_TYPE	unsigned long

void *memset4(MEMSET4_TYPE *s, MEMSET4_TYPE ul, size_t n){
	MEMSET4_TYPE *p = s;
	//for(; p-s != n*sizeof(MEMSET4_TYPE); p++)
	for(; p-s != n; p++)
		*p = ul;
	return s;
}

//	塗りつぶし
void CMglBitmapData::Fill(D3DCOLOR color, RECT rect){
	CMglBitmapDataLocker locker(*this);

	if ( rect.left >= m_nWidth || rect.top >= m_nHeight )
		return;

	int nStartX = rect.left;
	if ( nStartX < 0 )
		nStartX = 0;

	int nStartY = rect.top;
	if ( nStartY < 0 )
		nStartY = 0;

	int nEndX = rect.right;
	if ( nEndX > m_nWidth )
		nEndX = m_nWidth;

	int nEndY = rect.bottom;
	if ( nEndY > m_nHeight )
		nEndY = m_nHeight;

	//size_t nFillSize = (nStartX) * sizeof(D3DCOLOR);
	int nFillSize = nEndX - nStartX + 1;
	if ( nFillSize <= 0 )
		return;

	for(int i=nStartY; i<nEndY; i++)
		memset4(GetLine(i)+nStartX, color, nFillSize);
		//memset(GetLine(i)+rect.left, color, nFillSize);
		//memset(GetLine(i)+rect.left, color, nEndX); <- うそっぴー！
}

/*
//	塗りつぶし
void CMglBitmapData::Fill(D3DCOLOR color, RECT rect){
	Lock();

	if ( rect.left < m_nWidth	&& rect.top < m_nHeight )
	{
		int nStartX = rect.left;
		if ( nStartX < 0 )
			nStartX = 0;

		int nStartY = rect.top;
		if ( nStartY < 0 )
			nStartY = 0;

		int nEndX = rect.right;
		if ( nEndX > m_nWidth )
			nEndX = m_nWidth;

		int nEndY = rect.bottom;
		if ( nEndY > m_nHeight )
			nEndY = m_nHeight;

		//size_t nFillSize = (nStartX) * sizeof(D3DCOLOR);
		size_t nFillSize = nEndX - nStartX + 1;
		if ( nFillSize > 0 )
		{
			for(int i=nStartY; i<=nEndY; i++)
				memset4(GetLine(i)+nStartX, color, nFillSize);
				//memset(GetLine(i)+rect.left, color, nFillSize);
				//memset(GetLine(i)+rect.left, color, nEndX); <- うそっぴー！
		}
	}

	Unlock();
}
*/