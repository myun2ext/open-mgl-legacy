////////////////////////////////////////////////////////////////////////////
//	ファイル名	：	dx_graphic.cpp
//	ファイル概要：	ダイレクトグラフィック関連の処理を行う。
//	作成		：	M.Minami
////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "dx_graphic.h"

////////////////////////////////////////////////////////////////////////////
//                        グローバル変数の宣言
////////////////////////////////////////////////////////////////////////////
// ダイレクトＸグラフィック系
LPDIRECT3DDEVICE8			g_pD3DDevice  = NULL;	// ダイレクト３Ｄデバイス

// 座標変換マトリックス ----------------------------------------------------
static D3DXMATRIX			g_ProjMat;				// 透視変換マトリックス
static D3DXMATRIX			g_ViewMat;				// カメラマトリックス

// ライト ------------------------------------------------------------------
static D3DMATERIAL8			g_Material;
static D3DLIGHT8			g_Light;

////////////////////////////////////////////////////////////////////////////
//                     ファイル間インターフェース関数
////////////////////////////////////////////////////////////////////////////
LPDIRECT3DDEVICE8  GetD3DDevice(void) { return g_pD3DDevice; }

void GrpSetProjMat(float clip_near, float clip_far);
void GrpSetViewMat(D3DXVECTOR3 eye, D3DXVECTOR3 pos);
void GrpSetRotTransMat(D3DXMATRIX &wmat, D3DXVECTOR3 &s, D3DXVECTOR3 &t, D3DXVECTOR3 &r);
void GrpSetLiht(D3DLIGHT_MODE mode);
inline void GrpTLVertexSet(D3DTLVERTEX *v, float x, float y, float z, float tu, float tv, D3DCOLOR rgba);
inline void GrpLVertexSet(D3DLVERTEX *v, float x, float y, float z, float tu, float tv, D3DCOLOR rgba);
inline void GrpVertexSet(D3DVERTEX *v, float x, float y, float z, float nx, float ny, float nz, float tu, float tv);

void GrpSetProjMat(float clip_near, float clip_far)
{
	// 透視変換行列作成（左手系）
	D3DXMatrixPerspectiveFovLH(&g_ProjMat,							// 作成プロジェクションマトリックスへのポインタ
					D3DXToRadian(45.0),								// 視野角
					640.0f / 480.0f,								// アスペクト比（縦、横比率）
					clip_near,										// Near クリップ
					clip_far);										// Far  クリップ
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &g_ProjMat);		// 透視変換行列を設定
}

void GrpSetViewMat(D3DXVECTOR3 eye, D3DXVECTOR3 pos)
{
	// カメラ行列作成（左手系）	
	D3DXMatrixLookAtLH(&g_ViewMat,									// 作成ビューマトリックスのポインタ
					   &pos,										// カメラ位置
					   &eye,										// カメラ凝視点
					   &D3DXVECTOR3(0,1,0));						// ワールド空間で上を示す３次元ベクトル指定	

	// カメラ行列を設定
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &g_ViewMat);
}

inline void GrpLVertexSet(D3DLVERTEX *v, float x, float y, float z, float tu, float tv, D3DCOLOR rgba)
{
	v->x		= x;	
	v->y		= y;	
	v->z		= z;
	v->color	= rgba;
	v->specular	= 0;
	v->tu0		= tu;	
	v->tv0		= tv;
}

void GrpSetLight(D3DLIGHT_MODE mode)
{
	if (mode == D3DLIGHT_INIT) {
		// ライト初期化 ----------------------------------------------------
		// マテリアルの設定
		g_Material.Diffuse.r  = 1;									// ディフューズ色設定
		g_Material.Diffuse.g  = 1;
		g_Material.Diffuse.b  = 1;
		g_Material.Ambient.r  = 0.5f;								// アンビエント色設定
		g_Material.Ambient.g  = 0.5f;
		g_Material.Ambient.b  = 0.5f;
		g_Material.Emissive.r = 0;									// エミッション色設定
		g_Material.Emissive.g = 0;
		g_Material.Emissive.b = 0;

		// 光源の作成
		ZeroMemory(&g_Light,sizeof(D3DLIGHT8));
		g_Light.Type		= D3DLIGHT_DIRECTIONAL;					// ディレクショナルライト
		g_Light.Diffuse.r = 1;										// ディフーズ色設定
		g_Light.Diffuse.g = 1;
		g_Light.Diffuse.b = 1;
		g_Light.Ambient.r = 0.5f;									// アンビエント色設定
		g_Light.Ambient.g = 0.5f;
		g_Light.Ambient.b = 0.5f;
		g_Light.Direction = D3DXVECTOR3(0,0,1);						// 光源照射方向
		g_Light.Position  = D3DXVECTOR3(0,0,0);						// 光源位置（ディレクション時は影響無し）

		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);			// ライティングする
		g_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);// グローシェーディングを行う
		g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);	// スペキュラを使用しない
		g_pD3DDevice->SetLight(0,&g_Light);							// ライトをシステムに設定

		g_pD3DDevice->SetMaterial(&g_Material);						// マテリアルをシステムに設定
		g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);	// 頂点法線の自動正規化を有効にする
		g_pD3DDevice->LightEnable(0, TRUE);							// ライトＯＮ
	} else if (mode == D3DLIGHT_ON) {
		// ライトＯＮ ------------------------------------------------------
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);			// ライティングＯＮ	
	} else {
		// ライトＯＦＦ ----------------------------------------------------
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);			// ライティングＯＦＦ	
	}
}

void GrpSetRotTransMat(D3DXMATRIX &wmat, D3DXVECTOR3 &s, D3DXVECTOR3 &t, D3DXVECTOR3 &r)
{
	D3DXMATRIX smat, tmat, rmat;

	D3DXMatrixScaling(&smat, s.x, s.y, s.z);					// スケールマトリックス生成
	D3DXMatrixTranslation(&tmat, t.x, t.y, t.z);				// 移動マトリックス生成
	D3DXMatrixRotationYawPitchRoll(&rmat, r.y, r.x, r.z);		// 回転マトリックス生成

	// スケールマトリックス ＝ スケールマトリックス × 回転マトリックス
	D3DXMatrixMultiply(&smat, &smat, &rmat);
	// ワークマトリックス   ＝ 上記計算結果         × 移動マトリックス
	D3DXMatrixMultiply(&wmat, &smat, &tmat); 
}

