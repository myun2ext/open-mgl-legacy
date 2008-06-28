//////////////////////////////////////////////////////////
//
//	MglBitmapData - D3DLOCKED_RECT管理クラス

#ifndef __MglBitmapData_H__
#define __MglBitmapData_H__

class CMglTexture;

//	クラス宣言
class DLL_EXP CMglBitmapData : public CMyuReleaseBase
{
protected:
	//D3DLOCKED_RECT m_lockedRect;
	_MGL_IDirect3DSurface *m_pSurface;
	CONST RECT* m_pTargetRect;
	CMglTexture* m_pMglTex;
	DWORD m_dwFlags;
	BOOL m_bLocked;
	int m_nHeight;

	BYTE* m_pBits;
	int m_nPitch;

	/*void _Init(D3DLOCKED_RECT lockedRect, int nHeight){
		//m_lockedRect = lockedRect;
		m_nPitch = lockedRect.Pitch;
		m_pBits = (BYTE*)lockedRect.pBits;
		m_nHeight = nHeight;
	}*/
	void SetupLockedRect(D3DLOCKED_RECT lockedRect){
		m_nPitch = lockedRect.Pitch;
		m_pBits = (BYTE*)lockedRect.pBits;
	}
	//void _Init(_MGL_IDirect3DSurface *pSurface, int nHeight, CONST RECT* pTargetRect=NULL, DWORD dwFlags=0);
	/*void _Init(){
		m_pSurface = NULL;
		m_pTargetRect = NULL;
		m_nHeight = -1;
		m_pMglTex = -1
		m_nPitch = -1;
		m_nHeight = -1;
		m_dwFlags = 0;
		m_bLocked = FALSE;
	}*/
	void _Init(CMglTexture* pMglTex, _MGL_IDirect3DSurface *pSurface, int nHeight, CONST RECT* pTargetRect, DWORD dwFlags){
		m_pBits = NULL;
		m_nPitch = -1;
		m_pSurface = pSurface;
		m_pTargetRect = pTargetRect;
		m_nHeight = nHeight;
		m_pMglTex = pMglTex;
		m_dwFlags = dwFlags;
		m_bLocked = FALSE;
	}

public:
	//	コンストラクタ・デストラクタ
	CMglBitmapData(CMglTexture *pMglTex, CONST RECT* pTargetRect=NULL, DWORD dwFlags=0);
	CMglBitmapData(_MGL_IDirect3DSurface *pSurface, int nHeight, CONST RECT* pTargetRect=NULL, DWORD dwFlags=0);
	/*
	//	コンストラクタ・デストラクタ
	CMglBitmapData(D3DLOCKED_RECT lockedRect, int nHeight){
		//m_lockedRect = lockedRect;
		m_nPitch = lockedRect.Pitch;
		m_pBits = (BYTE*)lockedRect.pBits;
		m_nHeight = nHeight;
	}
	*/
	virtual ~CMglBitmapData(){
		Release();
	}
	void Release();

	//	2008/06/28  ロック、アンロックを別メソッドに分離
	void Lock(DWORD dwMode=0);
	void Unlock();

	/////////////////////////////////////////////////////////////////

	D3DCOLOR* GetHorizontalLine(int y){
		Lock();
		if ( y >= m_nHeight )
			//MyuThrow( 0, "CMglInternalBitmapData::GetHorizontalLine() y=%d は縦 %d の範囲を超えています。",y,m_nHeight);
			return NULL;
		return (D3DCOLOR*)(m_pBits + m_nPitch*y);
	}
	D3DCOLOR* GetLine(int y){ return GetHorizontalLine(y); }
	D3DCOLOR* GetPtr(int x,int y){
		D3DCOLOR* p = GetHorizontalLine(y);
		if ( p == NULL )
			//MyuThrow( 0, "CMglInternalBitmapData::GetHorizontalLine(%d) は失敗しました。",y);
			return NULL;
		if ( x >= m_nPitch )
			//MyuThrow( 0, "CMglInternalBitmapData::GetPtr() x=%d は横の範囲を超えています。",x);
			return NULL;
		return &p[x];
	}
	D3DCOLOR Get(int x,int y){
		Lock(D3DLOCK_READONLY);

		D3DCOLOR *p = GetPtr(x,y);
		if ( p == NULL )
			MyuThrow( 0, "CMglInternalBitmapData::Get(%d,%d) は失敗しました。",x,y);

		D3DCOLOR work = *p;
		Unlock();
		return work;
	}
	void Set(int x, int y, D3DCOLOR color){
		Lock();

		D3DCOLOR *p = GetPtr(x,y);
		/*if ( p == NULL )
			MyuThrow( 0, "CMglInternalBitmapData::Set(%d,%d) は失敗しました。",x,y);
		*p = color;*/
		if ( p != NULL )
			*p = color;

		Unlock();
	}

	void Fill(D3DCOLOR color);
	void Fill(D3DCOLOR color, RECT rect);

	//////////////////////////////////////////////////////////////////////////////

	int GetWidth(){ return m_nPitch; }
	int GetHeight(){ return m_nHeight; }
};

typedef CMglBitmapData CMglInternalBitmapData;

/////////////////////////////////////////////////////

class DLL_EXP CMglLockedRectIterator : public CMglBitmapData
{
public:
	CMglLockedRectIterator(_MGL_IDirect3DSurface *pSurface, int nHeight, CONST RECT* pTargetRect=NULL, DWORD dwFlags=0)
		: CMglBitmapData(pSurface,nHeight,pTargetRect,dwFlags){}


};

#endif//__MglBitmapData_H__
