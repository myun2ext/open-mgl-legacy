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
	CMglTexture *m_pMglTex;
	int m_nPitch;
	BYTE* m_pBits;
	int m_nHeight;

	void _Init(D3DLOCKED_RECT lockedRect, int nHeight){
		//m_lockedRect = lockedRect;
		m_nPitch = lockedRect.Pitch;
		m_pBits = (BYTE*)lockedRect.pBits;
		m_nHeight = nHeight;
	}
	void _Init(_MGL_IDirect3DSurface *pSurface, int nHeight, CONST RECT* pTargetRect=NULL, DWORD dwFlags=0);

public:
	//	コンストラクタ・デストラクタ
	CMglBitmapData(CMglTexture *pMglTex, CONST RECT* pTargetRect=NULL, DWORD dwFlags=0);
	CMglBitmapData(_MGL_IDirect3DSurface *pSurface, int nHeight, CONST RECT* pTargetRect=NULL, DWORD dwFlags=0){
		m_pMglTex = NULL;
		_Init(pSurface,nHeight,pTargetRect,dwFlags);
	}
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

	////////////////////////////////////////////////

	D3DCOLOR* GetHorizontalLine(int y){
		if ( y >= m_nHeight )
			MyuThrow( 0, "CMglInternalBitmapData::GetHorizontalLine() y=%d は縦 %d の範囲を超えています。",y,m_nHeight);
			//return NULL;
		return (D3DCOLOR*)(m_pBits + m_nPitch*y);
	}
	D3DCOLOR* GetLine(int y){ return GetHorizontalLine(y); }
	D3DCOLOR* GetPtr(int x,int y){
		D3DCOLOR* p = GetHorizontalLine(y);
		if ( p == NULL )
			MyuThrow( 0, "CMglInternalBitmapData::GetHorizontalLine(%d) は失敗しました。",y);
			//return NULL;
		if ( x >= m_nPitch )
			MyuThrow( 0, "CMglInternalBitmapData::GetPtr() x=%d は横の範囲を超えています。",x);
			//return NULL;
		return &p[x];
	}
	D3DCOLOR Get(int x,int y){
		D3DCOLOR *p = GetPtr(x,y);
		if ( p == NULL )
			MyuThrow( 0, "CMglInternalBitmapData::Get(%d,%d) は失敗しました。",x,y);
		return *p;
	}
	void Set(int x, int y, D3DCOLOR color){
		D3DCOLOR *p = GetPtr(x,y);
		if ( p == NULL )
			MyuThrow( 0, "CMglInternalBitmapData::Set(%d,%d) は失敗しました。",x,y);
		*p = color;
	}
	void Fill(D3DCOLOR color){
		for(int i=0; i<GetHeight(); i++)
			memset(GetLine(i), color, GetWidth());
	}

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
