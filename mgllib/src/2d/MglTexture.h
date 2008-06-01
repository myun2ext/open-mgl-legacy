//////////////////////////////////////////////////////////
//
//	MglTexture - テクスチャ管理クラス
//
//	なお、CreateTextureFromFile() で作成されたテクスチャは
//	三角形を二枚組み合わせた四角形であるのでこの事に注意されたし！

#ifndef __MglTexture_H__
#define __MglTexture_H__

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

/*
//	 -> 削除予定
#define VERTEXNO_LT		(0)
#define VERTEXNO_RT		(1)
#define VERTEXNO_LB		(3)
#define VERTEXNO_RB		(2)

//	頂点色 -> 削除予定
typedef struct
{
	D3DCOLOR leftTop;
	D3DCOLOR leftBottom;
	D3DCOLOR rightTop;
	D3DCOLOR rightBottom;
}
VERTEX_COLORS;

typedef MYU_VERTEX	MGL_VERTEX;
typedef struct
{
	MGL_VERTEX lt;
	MGL_VERTEX rt;
	MGL_VERTEX lb;
	MGL_VERTEX rb;
}
MGL_SQUARE_VERTEXS;
*/


//	クラス宣言
class DLL_EXP CMglTexture// : public CMyuReleaseBase
{
public:
	typedef CMglLockedRectIterator iterator;

protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納

	//	Direct3D系
	_MGL_IDirect3DDevice* d3d;			//	D3DDeviceへのポインタ
	_MGL_IDirect3DTexture* m_pTexture;	//	テクスチャ
	_MGL_IDirect3DSurface* m_pSurface;	//	サーフェス

	//	画像情報
	D3DXIMAGE_INFO m_imgInfo;

	//	記憶しておく
	D3DCOLOR m_colorKey;			//	カラーキー
	BOOL m_bRenderTarget;			//	bRenderTarget

	CMglBitmapData *m_pBitmapData;

	//	頂点情報
	//MYU_VERTEX m_vertices[4];		//	頂点 -> 別にメンバ変数で持つ必要ナクネ
	//float fRealTexTu, fRealTexTv;	//	テクスチャ上で実際に使用されるtu,uv

	//	古い描画方式用
	//BOOL m_bCenterDraw;			//	センター絵画有効/無効フラグ

	//	内部メソッド（チェック用）
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}
	void CreateCheck() {
		//if ( createFlg == FALSE ){
		if ( m_pTexture == NULL )
			MyuThrow( 0, "CMglTexture 未作成であるにも関わらず操作を行おうとしました。" );
	}

	//	古い描画方式用
	void GenerateEqVertexColors( VERTEX_COLORS* dest, D3DCOLOR color )
	{
		for( D3DCOLOR* p=(D3DCOLOR*)dest; p<((D3DCOLOR*)dest)+4; p++ )
		{
			*p = color;
		}

		/*
		dest->leftTop = color;
		dest->leftBottom = color;
		dest->rightTop = color;
		dest->rightBottom = color;
		*/
	}

private:
	//	テクスチャのサーフェスを取得する
	void _GetSurface(){
		MyuAssert( m_pTexture->GetSurfaceLevel(0, &m_pSurface), D3D_OK,
			"CMglTexture::GetSurface()  GetSurfaceLevel()に失敗" );
	}
public:
	//	コンストラクタ・デストラクタ
	CMglTexture();
	virtual ~CMglTexture(){ Release(); }

	//	初期化と開放
	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd );
	void Release();

	//	作成
	void CreateTextureFromFile( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		//CreateTextureFromFileEx( szFileName, D3DX_DEFAULT, D3DX_DEFAULT, bRenderTarget, colorKey ); }
		CreateTextureFromFileEx( szFileName, 0, 0, bRenderTarget, colorKey ); }
	void CreateTextureFromFileEx( LPCSTR szFileName, int nForceBmpWidth, int nForceBmpHeight,
		BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY,
		DWORD dwFilter=D3DX_FILTER_NONE, DWORD dwMapFilter=D3DX_FILTER_NONE );
	//void Create( int x=0, int y=0, BOOL bRenderTarget=TRUE );
	/*void Create( LPCSTR szFileName, BOOL bRenderTarget=TRUE, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFile( szFileName, bRenderTarget, colorKey );}*/
	void Create( int x, int y, BOOL bRenderTarget );

	//	描画
	void Draw(float x=0.0f, float y=0.0f, D3DCOLOR color=D3DCOLOR_WHITE );

	//	頂点データで書く
	void Draw( MGL_SQUARE_VERTEXS *pMglSqVertexs, BOOL bVertexRevise=TRUE );
	void Draw( MYU_VERTEX *pMyuVertex, UINT nPrimitiveCount=2, BOOL bVertexRevise=TRUE );

	//	PrimitiveUP
	void DrawPrimitiveUP( D3DPRIMITIVETYPE primitiveType, UINT nPrimitiveCount,
		const void *pVertexStreamZeroData, UINT nVertexStreamZeroStride );

	//	BMPの頂点データ取得
	void GetBmpVertexs( MGL_SQUARE_VERTEXS *pMglSqVertexs );

	//	内部変数取得系
	_MGL_IDirect3DTexture* GetDirect3dTexturePtr(){ CreateCheck(); return m_pTexture; }
	_MGL_IDirect3DSurface* GetSurfacePtr() { CreateCheck(); return m_pSurface; }

	//	サイズ取得
	int GetBmpWidth(){ return m_imgInfo.Width; }
	int GetBmpHeight(){ return m_imgInfo.Height; }

	////////////////////////////////////////////////////////////////////////////////

	//	2008/06/01  Bitmapデータ取得（クラスだけ用意して実装してなかったっぽい・・・？）
	CMglBitmapData* GetIternalBitmapData();

	/*
	iterator begin();
	iterator end(){ return NULL; }
	*/

	/////////////////////////////////////////////////////////////////////////

	//	古い描画方式
	void TextureDraw( float x=0.0f, float y=0.0f, RECT* srcRect=NULL, float fScaleX=1.0f, float fScaleY=1.0f, D3DCOLOR color=D3DCOLOR_WHITE, DWORD dwAlphaOption=MGL_ALPHA_OPT_DEFAULT )
	{
		VERTEX_COLORS tVertexColors;
		GenerateEqVertexColors( &tVertexColors, color );
		TextureDraw( x, y, srcRect, fScaleX, fScaleY, 0.5f, 0.5f, 0.0f, &tVertexColors, dwAlphaOption );
	}
	//	↓fAngleは実は実装してない
	void TextureDraw( float x, float y, RECT* srcRect, float fScaleX, float fScaleY,
		float fRotationCenterX, float fRotationCenterY, float fAngle,
		VERTEX_COLORS* vertexColors, DWORD dwAlphaOption );
	//void TextureDraw( float x=0.0f, float y=0.0f, float fSizeX=1.0f, float fSizeY=1.0f, D3DCOLOR color=0xffffffff );

	//D3DCOLOR* GetSurfaceIterator(){ ;
	/*
	//	設定
	void EnableCenterDraw() {	m_bCenterDraw = TRUE; }
	void DisableCenterDraw() {	m_bCenterDraw = FALSE; }
	*/
};


#endif//__MglTexture_H__
