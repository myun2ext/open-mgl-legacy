//////////////////////////////////////////////////////////
//
//	MglBitmapData - D3DLOCKED_RECT管理クラス

#ifndef __MglBitmapData_H__
#define __MglBitmapData_H__

class CMglTexture;

//	クラス宣言
class DLL_EXP CMglBitmapData
{
protected:
	//D3DLOCKED_RECT m_lockedRect;
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
	CMglBitmapData(CMglTexture &mglTex, CONST RECT* pTargetRect=NULL, DWORD dwFlags=0);
	CMglBitmapData(_MGL_IDirect3DSurface *pSurface, int nHeight, CONST RECT* pTargetRect=NULL, DWORD dwFlags=0){
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
	virtual ~CMglBitmapData(){}
	void Release();

	////////////////////////////////////////////////

	D3DCOLOR* GetHorizontalLine(int y){
		if ( y >= m_nHeight )
			return NULL;
		return (D3DCOLOR*)(m_pBits + m_nPitch*y);
	}
	D3DCOLOR* GetLine(int y){ return GetHorizontalLine(y); }
	D3DCOLOR Get(int x,int y){
		D3DCOLOR* p = GetHorizontalLine(y);
		if ( p == NULL )
			return NULL;
		if ( x >= m_nPitch )
			return NULL;
		return p[x];
	}
	void Fill(D3DCOLOR color){
		for(int i=0; i<GetHeight(); i++)
			memset(GetLine(i), color, GetWidth());
	}

	int GetWidth(){ return m_nPitch; }
	int GetHeight(){ return m_nHeight; }
};

/////////////////////////////////////////////////////

class DLL_EXP CMglLockedRectIterator : public CMglBitmapData
{
public:
	CMglLockedRectIterator(_MGL_IDirect3DSurface *pSurface, int nHeight, CONST RECT* pTargetRect=NULL, DWORD dwFlags=0)
		: CMglBitmapData(pSurface,nHeight,pTargetRect,dwFlags){}


};

#endif//__MglBitmapData_H__
