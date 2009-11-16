//////////////////////////////////////////////////////////
//
//	MglDxTexture - テクスチャ管理クラス
//

#ifndef __MglDxTexture_H__
#define __MglDxTexture_H__

#include "MglGraphicManager.h"
#include "MglVertex.h"
#include "MglBitmapData.h"

/*
//	ADJ S1
#define X_ADJ (-0.66f)
#define Y_ADJ (-0.96f)
*/

//	ADJ S2 - 2007/01/10  D3DX_FILTER_NONE 版
//	頂点計算がfloatで行われるため、計算誤差で画像が崩れないようズラしておく
//	0.5fで良いような気もするが、頂点計算がどのようなロジックなのか不明なので
//	一応 -0.66f、-0.96f に則って -0.75f くらいに設定しておく。
//	（0.66fとかにしていないのは、確か0.75fとかの方がCPUは計算しやすかった気がしたから）
//	ちなみに試した限り、0.00010000001f:OK　0.0001f:NG　っぽい <- 2008/03/16 RADEONの場合だけかも・・・
//#define TEXTURE_FLOAT_ADJ	(-0.75f)
#define TEXTURE_FLOAT_ADJ	(-0.75f)

//#define X_ADJ (0)
//#define Y_ADJ (0)
#define DEF_COLORKEY			D3DCOLOR_PINK
#define RENDER_TARGET_DEFAULT	(FALSE)

#define MGL_TEXTURE_STAGE_MAX	(8)

//	クラス宣言
class DLL_EXP CMglDxTexture : public CMglDgBase
{
public:
	typedef CMglLockedRectIterator iterator;

protected:
	//CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納

	//	Direct3D系
	//_MGL_IDirect3DDevice* d3d;			//	D3DDeviceへのポインタ
	_MGL_IDirect3DTexture* m_pTexture;	//	テクスチャ
	_MGL_IDirect3DSurface* m_pSurface;	//	サーフェス

	//	画像情報
	D3DXIMAGE_INFO m_imgInfo;
	MGLTUTV m_tutv;

	//	記憶しておく
	D3DCOLOR m_colorKey;			//	カラーキー
	BOOL m_bRenderTarget;			//	bRenderTarget

	BOOL m_bLocked;					//	ロック - 2008/06/28
	CMglBitmapData *m_pBitmapData;

	//	頂点情報
	//float fRealTexTu, fRealTexTv;	//	テクスチャ上で実際に使用されるtu,uv

	//	内部メソッド（チェック用）
	/*void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}*/
	void CreateCheck() {
		InitCheck();	//	2008/06/28 これもやらないと駄目でない・・・？
		//if ( createFlg == FALSE ){
		if ( m_pTexture == NULL )
			MyuThrow( 0, "CMglDxTexture 未作成であるにも関わらず操作を行おうとしました。Create()系メソッドを呼んでください。" );
	}

	void LockedCheck(){
		if ( m_bLocked == TRUE )
			MyuThrow(0, "CMglDxTexture ロックされています。ロックを開放してください。\r\n\r\n"
				"考えられる可能性 :\r\n"
				"  CMglInternalBitmapData::Release() の呼び出し漏れ。");
	}

	void UpdateTexture( _MGL_IDirect3DTexture* pDestTexture );
	void UpdateSurface( CONST RECT* pSourceRect, _MGL_IDirect3DSurface* pDestSurface, CONST POINT* pDestinationPoint );

private:
	//	テクスチャのサーフェスを取得する
	void _GetSurface(){
		MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
			"CMglDxTexture::GetSurface()  GetSurfaceLevel()に失敗" );
	}
public:
	//	コンストラクタ・デストラクタ
	CMglDxTexture();
	virtual ~CMglDxTexture(){ Release(); }

	//	初期化と開放
	//void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	void Release();

	//	作成
	void Create( int x, int y, BOOL bRenderTarget );

	//	ファイルからの読み込み系
	void Load( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFileEx( szFileName, 0, 0, bRenderTarget, colorKey ); }

	void Create( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFileEx( szFileName, 0, 0, bRenderTarget, colorKey ); }

	void CreateFromFile( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		//CreateFromFileEx( szFileName, D3DX_DEFAULT, D3DX_DEFAULT, bRenderTarget, colorKey ); }
		CreateFromFileEx( szFileName, 0, 0, bRenderTarget, colorKey ); }

	void CreateFromFileEx( LPCSTR szFileName, int nForceBmpWidth, int nForceBmpHeight,
		BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY,
		DWORD dwFilter=D3DX_FILTER_NONE, DWORD dwMapFilter=D3DX_FILTER_BOX );
	//	DWORD dwFilter=D3DX_FILTER_NONE, DWORD dwMapFilter=D3DX_FILTER_NONE );

	//void Create( int x=0, int y=0, BOOL bRenderTarget=TRUE );
	/*void Create( LPCSTR szFileName, BOOL bRenderTarget=TRUE, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFile( szFileName, bRenderTarget, colorKey );}*/
	void CreateTextureFromFileEx( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFileEx( szFileName, 0, 0, bRenderTarget, colorKey ); }

	void CreateTextureFromFileEx( LPCSTR szFileName, int nForceBmpWidth, int nForceBmpHeight,
		BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY,
		DWORD dwFilter=D3DX_FILTER_NONE, DWORD dwMapFilter=D3DX_FILTER_NONE ){
		CreateFromFileEx( szFileName, nForceBmpWidth, nForceBmpHeight, bRenderTarget, colorKey, dwFilter, dwMapFilter); }

	//	メモリから作成
	void CreateFromFile( LPCVOID lpFileData, UINT nDataSize, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromMemoryFileEx( lpFileData, nDataSize, 0, 0, bRenderTarget, colorKey ); }

	void CreateFromMemoryFileEx( LPCVOID lpFileData, UINT nDataSize, int nForceBmpWidth, int nForceBmpHeight,
		BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY,
		DWORD dwFilter=D3DX_FILTER_NONE, DWORD dwMapFilter=D3DX_FILTER_NONE );

	/////////////////////////////////////////////////////////////////////

	//	コピーメソッド
	void Copy( CMglDxTexture &toTex ){ CopyToOtherTexture(toTex); }
	void CopyToOtherTexture( CMglDxTexture &toTex ){ UpdateTexture( toTex.GetD3dTexturePtr() ); }
	void CopyFromOtherTexture( CMglDxTexture &fromTex ){ fromTex.UpdateTexture( m_pTexture ); }

	////////////////////////////////////////////////////////////////////////////////

	void SetD3dStageTexture(DWORD nStage=0);
	void SetStageTexture(DWORD nStage=0){ SetD3dStageTexture(nStage); }
	void SetRenderTexture(DWORD nStage=0){ SetD3dStageTexture(nStage); }

	//	内部変数取得系
	_MGL_IDirect3DTexture* GetDirect3dTexturePtr(){ CreateCheck(); return m_pTexture; }
	_MGL_IDirect3DTexture* GetD3dTexturePtr(){ CreateCheck(); return m_pTexture; }
	_MGL_IDirect3DTexture* GetDxTexturePtr(){ CreateCheck(); return m_pTexture; }
	_MGL_IDirect3DTexture* GetTexturePtr(){ CreateCheck(); return m_pTexture; }
	_MGL_IDirect3DSurface* GetSurfacePtr() { CreateCheck(); return m_pSurface; }

	//	サイズ取得
	int GetBmpWidth(){ return m_imgInfo.Width; }
	int GetBmpHeight(){ return m_imgInfo.Height; }
	//MGLTUTV GetTuTv();
	const MGLTUTV& GetTuTv();

	////////////////////////////////////////////////////////////////////////////////

	//	2008/06/01  Bitmapデータ取得（クラスだけ用意して実装してなかったっぽい・・・？）
	CMglBitmapData* GetIternalBitmapData();

	/*
	iterator begin();
	iterator end(){ return NULL; }
	*/

	/////////////////////////////////////////////////////////////////////////

	//D3DCOLOR* GetSurfaceIterator(){ ;

	void SetRender();
	void SetRenderTarget(){ SetRender(); }
	void Clear(){ Clear( m_colorKey & 0x00ffffff ); } // m_colorKeyが関連するのでデフォルト引数には出来ないのでれす
	void Clear( D3DCOLOR color );
	void Clear__( D3DCOLOR color );
	void Paint( RECT* pRect, D3DCOLOR color );

	void Lock(){ m_bLocked = TRUE; }
	void Unlock(){ m_bLocked = FALSE; }
};

typedef CMglDxTexture CMglD3dTexture;
typedef CMglDxTexture CMglSquareTexture;
typedef CMglDxTexture CMglDxTexture;



////////////////////////////////////////////////////

//	TextureStageStateを管理するクラス
class DLL_EXP CMglTextureStageStateManager : public virtual CMglDgBase
{
public:
	typedef std::map<D3DTEXTURESTAGESTATETYPE,DWORD> _MAP_t;

protected:
	//map<D3DTEXTURESTAGESTATETYPE> m_tssList;
	_MAP_t m_tssList[MGL_TEXTURE_STAGE_MAX];

public:
	void Set(int nStage, D3DTEXTURESTAGESTATETYPE tssType, DWORD value);/*{
		m_tssList[nStage][tssType] = value;
	}*/
	DWORD Get(int nStage, D3DTEXTURESTAGESTATETYPE tssType){
		return m_tssList[nStage][tssType];
	}
	void Erase(int nStage, D3DTEXTURESTAGESTATETYPE tssType){
		m_tssList[nStage].erase(tssType);
	}
	void ClearStage(int nStage){ m_tssList[nStage].clear(); }
	void StageClear(int nStage){ m_tssList[nStage].clear(); }
	
	void Sets(int nStage){ SetsTextureStageState(nStage); }
	void SetsTextureStageState(int nStage){
		InitCheck();
		_MAP_t &tssL = m_tssList[nStage];
		_MAP_t::iterator it = tssL.begin();
		for(; it != tssL.end(); it++){
			D3DTEXTURESTAGESTATETYPE tssType = it->first;
			DWORD value = it->second;
			CMglDgBase::m_d3d->SetTextureStageState( nStage, tssType, value);
		}
	}
};
typedef CMglTextureStageStateManager CMglTssManager;

#endif//__MglDxTexture_H__
