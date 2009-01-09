////////////////////////////////////////////////////////////////////////////
//	ファイル名	：	dx_graphic.h
//	ファイル概要：	dx_graphic モジュールヘッダ
//	作成		：	M.Minami
////////////////////////////////////////////////////////////////////////////
#ifndef __DX_GRAPHIC_H_
#define __DX_GRAPHIC_H_

////////////////////////////////////////////////////////////////////////////
//						ヘッダファイルのインクルード
////////////////////////////////////////////////////////////////////////////
#include <d3d8.h>								// DirectXGraphics ヘッダファイル
#include <d3dx8.h>								// D3DX ヘッダファイル

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

////////////////////////////////////////////////////////////////////////////
//							マクロ、構造体定義
////////////////////////////////////////////////////////////////////////////
// テクスチャ用 ------------------------------------------------------------
// テクスチャ管理構造体
typedef struct  {
	LPDIRECT3DTEXTURE8	Tex;					// テクスチャバッファ
	unsigned int		Width;					// テクスチャ高さ
	unsigned int		Height;					// テクスチャ幅
} TEXTURE_DATA;

// テクスチャバッファサイズ
#define TEX_MAX		100

// スプライト用 ------------------------------------------------------------
// ブレンドモード
typedef enum {
	D3DBLEND_NORMAL,							// 通常アルファブレンド
	D3DBLEND_ADD								// 加算アルファブレンド
} BLEND_MODE;

// 頂点フォーマット --------------------------------------------------------
// 光源計算無し、座標変換無し頂点フォーマット
typedef struct {
	float	x, y, z;							// 座標変換済み頂点座標
	float	rhw;								 
	DWORD	color;								// 頂点色（ＲＧＢＡ）
	DWORD	specular;							// スペキュラ色
	float	tu0, tv0;							// テクスチャ座標
} D3DTLVERTEX;

#define D3DFVF_TLVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE |  D3DFVF_SPECULAR | D3DFVF_TEX1)

// 座標変換有り、ライティング無し頂点フォーマット
typedef struct {
	float x, y, z;								// 頂点座標
	DWORD color;								// 頂点色（ＲＧＢＡ）
	DWORD specular;								// スペキュラ色
	float tu0, tv0;								// テクスチャ座標
} D3DLVERTEX;

#define D3DFVF_LVERTEX 		(D3DFVF_XYZ | D3DFVF_DIFFUSE |  D3DFVF_SPECULAR | D3DFVF_TEX1)

// 座標変換有り、ライティング有り頂点フォーマット
typedef struct {
	float x,  y,  z;							// 頂点座標
	float nx, ny, nz;							// 法線ベクトル
	float tu0, tv0;								// テクスチャ座標
} D3DVERTEX;

#define D3DFVF_VERTEX 		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

//	ライト用 ---------------------------------------------------------------
typedef enum {
	D3DLIGHT_INIT,		// ライト初期化
	D3DLIGHT_ON,		// ライトＯＮ
	D3DLIGHT_OFF		// ライトＯＦＦ
} D3DLIGHT_MODE;

////////////////////////////////////////////////////////////////////////////
//                     ファイル間インターフェース関数
////////////////////////////////////////////////////////////////////////////
// テクスチャバッファ取得
extern TEXTURE_DATA* GetTextureBuf(int idx);
// ３Ｄデバイス取得
extern LPDIRECT3DDEVICE8  GetD3DDevice(void);
extern LPDIRECT3DDEVICE8 g_pD3DDevice;

////////////////////////////////////////////////////////////////////////////
//                             外部参照宣言
////////////////////////////////////////////////////////////////////////////
// ダイレクトグラフィックス初期化関数
extern BOOL GrpInit(HWND hwnd);
// ダイレクトグラフィックス開放関数
extern void GrpRelease(void);

// テクスチャロード処理関数
extern BOOL GrpLoadTexture(int idx, char *bmp_name, D3DCOLOR rgba = 0);
// テクスチャ開放処理関数
extern void GrpReleaseTexture(int idx);

// スプライト初期化
extern void GrpSprInit(void);
// スプライトＲＧＢＡセット
extern void GrpSprRGBASet(BLEND_MODE mode, D3DCOLOR rgba);
// スプライト回転角セット
extern void GrpSprAngleSet(float angle, float cx, float cy);
// スプライトスケールセット
extern void GrpSprScaleSet(float sx, float sy);
// スプライト描画
extern void GrpSprDraw(int x, int y, int idx, int u, int v, int w, int h);

// 単色ポリゴン表示
extern void GrpPolyDraw(float x, float y, float w, float h, D3DCOLOR rgba);
// ＦＰＳ表示
extern void GrpFpsDisp(int x, int y);
// フォント表示関数
extern void GrpFontDisp(char *str, int x, int y, D3DCOLOR color);

// 透視変換行列の設定
extern void GrpSetProjMat(float clip_near, float clip_far);
// カメラ行列の設定
extern void GrpSetViewMat(D3DXVECTOR3 eye, D3DXVECTOR3 pos);
// ビルボート用マトリックス設定
extern void GrpSetBillBoardMat(D3DXMATRIX &wmat, D3DXVECTOR3 &t);
// 座標系マトリックス計算関数
extern void GrpSetRotTransMat(D3DXMATRIX &wmat, D3DXVECTOR3 &s, D3DXVECTOR3 &t, D3DXVECTOR3 &r);
// ライトの初期化、ＯＮ / ＯＦＦ切り替え
extern void GrpSetLight(D3DLIGHT_MODE mode);
// フォグの設定
extern void GrpSetFog(float st, float end, D3DCOLOR col);
// ３Ｄ座標　→　２Ｄ座標変換
extern void GrpVecCnv2d(D3DXVECTOR3* out_vec, D3DXVECTOR3* cnv_vec, D3DXMATRIX* world);
// 光源無し、座標変換無し頂点情報セット
extern inline void GrpTLVertexSet(D3DTLVERTEX *v, float x, float y, float z, float tu, float tv, D3DCOLOR rgba);
// 光源無し、座標変換有り頂点情報セット
extern inline void GrpLVertexSet(D3DLVERTEX *v, float x, float y, float z, float tu, float tv, D3DCOLOR rgba);
// 光源有り、座標変換有り頂点情報セット
extern inline void GrpVertexSet(D3DVERTEX *v, float x, float y, float z, float nx, float ny, float nz, float tu, float tv);

////////////////////////////////////////////////////////////////////////////
//                             クラス宣言
////////////////////////////////////////////////////////////////////////////
// 座標系管理クラス
class D3D_COORDINATE {
public:
	D3DXVECTOR3		scale;							// スケール
	D3DXVECTOR3		trans;							// 移動ベクトル
	D3DXVECTOR3		rotate;							// 回転ベクトル
	D3DXMATRIX		mat;							// 座標系の変換マトリックス
public:
	// コンストラクタ（ベクトルの初期化を行う）
	D3D_COORDINATE() {}
	D3D_COORDINATE(D3DXVECTOR3 s, D3DXVECTOR3 t, D3DXVECTOR3 r) {
		SetVect(s, t, r);
	}

	void SetVect(D3DXVECTOR3 s, D3DXVECTOR3 t, D3DXVECTOR3 r) {
		scale  = s;
		trans  = t;
		rotate = r;
		SetMat();
	}
	// スケール→回転→移動変換済みマトリックス作成
	void SetMat(void) {
		// GrpSetRotTransMatは、与えたスケールベクトル、移動ベクトル、回転ベクトルから
		// mat = スケールmat  ×　（Ｙ回転mat　×　Ｘ回転mat　×　Ｚ回転mat）　×　移動mat　
		// といった変換マトリックスを生成します
		// つまり、スケール -> 回転 -> 移動 と言った順で処理を行ったマトリックスを作成します。
		GrpSetRotTransMat(mat, scale, trans, rotate);
	}
};

#endif

