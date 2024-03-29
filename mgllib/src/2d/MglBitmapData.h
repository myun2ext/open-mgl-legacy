//////////////////////////////////////////////////////////
//
//	MglBitmapData - D3DLOCKED_RECT管理クラス

#ifndef __MglBitmapData_H__
#define __MglBitmapData_H__

/*
　参考資料：http://msdn.microsoft.com/ja-jp/library/cc373032.aspx

  ピッチはメモリ上の幅。実際の横幅とは異なるよ！
*/

class CMglTexture;

//	クラス宣言
class DLL_EXP CMglBitmapData : public CMyuReleaseBase
{
protected:
	//D3DLOCKED_RECT m_lockedRect;
	_MGL_IDirect3DSurface *m_pSurface;
	CONST RECT* m_pTargetRect;
	CMglTexture* m_pMglTex;
	//DWORD m_dwFlags;
	BOOL m_bLocked;
	int m_nWidth;	//	実際のBMPデータの横幅
	int m_nHeight;	//	実際のBMPデータの縦幅

	BYTE* m_pBits;	//	privateビット
	int m_nPitch;	//	ピッチ（メモリ上の幅。高さが1増えた際のインクリメント値）

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
	void _Init(CMglTexture* pMglTex, _MGL_IDirect3DSurface *pSurface,
			int nWidth, int nHeight,
			CONST RECT* pTargetRect/*, DWORD dwFlags*/)
	{
		m_pBits = NULL;
		m_nPitch = -1;
		m_pSurface = pSurface;
		m_pTargetRect = pTargetRect;
		m_nWidth = nWidth;
		m_nHeight = nHeight;
		m_pMglTex = pMglTex;
		//m_dwFlags = dwFlags;
		m_bLocked = FALSE;
	}

	void InitChk(){
		if ( m_pSurface == NULL )
			MyuThrow(0,"CMglBitmapData: 引数なしコンストラクタ呼び出しの場合は Init() メソッドを呼んでください。");
	}

public:
	//	コンストラクタ・デストラクタ
	CMglBitmapData(CMglTexture *pMglTex, CONST RECT* pTargetRect=NULL/*, DWORD dwFlags=0*/){
		Init(pMglTex,pTargetRect);
	}
	CMglBitmapData(_MGL_IDirect3DSurface *pSurface,
		int nWidth, int nHeight, CONST RECT* pTargetRect=NULL/*, DWORD dwFlags=0*/){
		Init(pSurface,nWidth,nHeight,pTargetRect);
	}
	CMglBitmapData(){ _Init(NULL,NULL,-1,-1,NULL); }

	void Init(CMglTexture *pMglTex, CONST RECT* pTargetRect=NULL);
	void Init(_MGL_IDirect3DSurface *pSurface,
		int nWidth, int nHeight, CONST RECT* pTargetRect=NULL/*, DWORD dwFlags=0*/);
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
		//	2008/10/03  デストラクタで呼ばれて落ちる・・・。初期化されてないなら使われてないわけで、なにもしないでいくない？
		if ( m_pSurface == NULL )
			return;
		Release();
	}
	void Release();

	//	2008/06/28  ロック、アンロックを別メソッドに分離
	void Lock(DWORD dwMode=0);
	void Unlock();

	/////////////////////////////////////////////////////////////////

	D3DCOLOR* GetHorizontalLine(int y, DWORD dwMode=0){
		Lock(dwMode);
		if ( y >= m_nHeight || y < 0 )
			//MyuThrow( 0, "CMglInternalBitmapData::GetHorizontalLine() y=%d は縦 %d の範囲を超えています。",y,m_nHeight);
			return NULL;
		return (D3DCOLOR*)(m_pBits + m_nPitch*y);
	}
	D3DCOLOR* GetLine(int y, DWORD dwMode=0){ return GetHorizontalLine(y, dwMode); }
	D3DCOLOR* GetPtr(int x,int y, DWORD dwMode=0){
		D3DCOLOR* p = GetHorizontalLine(y, dwMode);
		if ( p == NULL )
			//MyuThrow( 0, "CMglInternalBitmapData::GetHorizontalLine(%d) は失敗しました。",y);
			return NULL;
		if ( x >= m_nWidth || x < 0  )
			//MyuThrow( 0, "CMglInternalBitmapData::GetPtr() x=%d は横の範囲を超えています。",x);
			return NULL;
		return &p[x];
	}
	D3DCOLOR Get(int x,int y);
	D3DCOLOR GetNE(int x,int y, BOOL *pbSuccess);
	void Set(int x, int y, D3DCOLOR color);

	void Fill(D3DCOLOR color);
	void Fill(D3DCOLOR color, RECT rect);

	//////////////////////////////////////////////////////////////////////////////

	//int GetWidth(){ return m_nPitch; }
	int GetWidth(){ return m_nWidth; }
	int GetHeight(){ return m_nHeight; }
};

typedef CMglBitmapData CMglInternalBitmapData;

/////////////////////////////////////////////////////

class DLL_EXP CMglLockedRectIterator : public CMglBitmapData
{
public:
	CMglLockedRectIterator(_MGL_IDirect3DSurface *pSurface,
		int nWidth, int nHeight, CONST RECT* pTargetRect=NULL/*, DWORD dwFlags=0*/)
		: CMglBitmapData(pSurface,nWidth,nHeight,pTargetRect){}
};

/////////////////////////////////////////////////////

class DLL_EXP CMglBitmapDataLocker
{
protected:
	CMglBitmapData &m_target;
public:
	CMglBitmapDataLocker(CMglBitmapData &target, DWORD dwMode=0) : m_target(target) { m_target.Lock(dwMode); }
	virtual ~CMglBitmapDataLocker(){ m_target.Unlock(); }
};

#endif//__MglBitmapData_H__
