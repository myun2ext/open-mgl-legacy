#ifndef __MglVertex_H__
#define __MglVertex_H__

#include "MglGraphicUtil.h"

//#define _MGLVERTEX_USE_RHW

//	頂点構造体
#ifdef _MGLVERTEX_USE_RHW
	#define	FVF_MYU_VERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#else
	#define	FVF_MYU_VERTEX ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#endif
typedef struct
{
	float		x,y,z;				//位置情報
	//D3DXVECTOR3 pos;		// ←こっちの方が色々関数ついてるっぽくて良いかもね・・・
#ifdef _MGLVERTEX_USE_RHW
	float		rhw;				//頂点変換値
#endif
	D3DCOLOR	color;				//ポリゴンカラー
	float		tu,tv;				//テクスチャ座標
}MYU_VERTEX;
typedef MYU_VERTEX	MGL_VERTEX;

/*
//+++++++++++++++++++++++++++++++++++++++++++++
//	頂点構造体2 (2009/01/10
//+++++++++++++++++++++++++++++++++++++++++++++
#define	FVF_MYU_VERTEX2 ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1 )
typedef struct
{
	float		x,y,z;				//位置情報
	//D3DXVECTOR3 pos;		// ←こっちの方が色々関数ついてるっぽくて良いかもね・・・
	D3DCOLOR	color;				//ポリゴンカラー
	DWORD		specular;			// スペキュラ色
	float		tu,tv;				//テクスチャ座標
}MYU_VERTEX2;
typedef MYU_VERTEX2	MGL_VERTEX2;
typedef MYU_VERTEX2	MGL_VERTEX_3D;
*/


//	↓使ってねっす・・・
/*typedef struct
{
	float		drawX,drawY,drawZ;	//位置情報
	float		rhw;				//頂点変換値
	D3DCOLOR	color;				//ポリゴンカラー
	float		textureX,textureY;
}MYU_VERTEX2;*/

//typedef MYU_VERTEX2	MGL_VERTEX2;

//	四角形の頂点
typedef struct
{
	MGL_VERTEX lt;	//	0
	MGL_VERTEX rt;	//	1
	MGL_VERTEX rb;	//	2
	MGL_VERTEX lb;	//	3
}
MGL_SQUARE_VERTEXS;
typedef MGL_SQUARE_VERTEXS MGL_SQ_VERTEXS;

/*
//	四角形の頂点
typedef struct
{
	MGL_VERTEX2 lt;	//	0
	MGL_VERTEX2 rt;	//	1
	MGL_VERTEX2 rb;	//	2
	MGL_VERTEX2 lb;	//	3
}
MGL_SQUARE_VERTEXS2;
typedef MGL_SQUARE_VERTEXS2 MGL_SQ_VERTEXS2;
*/

//// Methods //////////////////////////////////////////////////////////////////////////////

#ifdef _MGLVERTEX_USE_RHW
	DLL_EXP void MglVertexGen( MGL_VERTEX *pVertexOut, float x, float y, float tu, float tv,
							  D3DCOLOR color=D3DCOLOR_WHITE, float z=0.0f, float rhw=1.0f );
#else
	DLL_EXP void MglVertexGen( MGL_VERTEX *pVertexOut, float x, float y, float tu, float tv,
							  D3DCOLOR color=D3DCOLOR_WHITE, float z=0.0f );
#endif

DLL_EXP void MglMoveVertexs( MGL_VERTEX *pVertexs, float x, float y, int vertexCount );
inline void MglMoveVertexs( MGL_SQUARE_VERTEXS *pVertexs, float x, float y ){
	MglMoveVertexs( (MGL_VERTEX*)pVertexs, x, y, 4 ); }

#define MGL_VERTEX_SIZE		(sizeof(MYU_VERTEX))
#define MGL_VERTEXES_SIZE		(sizeof(MYU_VERTEX)*4)

/////////////////////////////////////////////

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

#endif//__MglVertex_H__
