#ifndef __MglVertex_H__
#define __MglVertex_H__

#include "MglGraphicUtil.h"

//	頂点構造体
#define	FVF_MYU_VERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
typedef struct
{
	float		x,y,z;				//位置情報
	float		rhw;				//頂点変換値
	D3DCOLOR	color;				//ポリゴンカラー
	float		tu,tv;				//テクスチャ座標
}MYU_VERTEX;
typedef struct
{
	float		drawX,drawY,drawZ;	//位置情報
	float		rhw;				//頂点変換値
	D3DCOLOR	color;				//ポリゴンカラー
	float		textureX,textureY;
}MYU_VERTEX2;
typedef MYU_VERTEX	MGL_VERTEX;
typedef MYU_VERTEX2	MGL_VERTEX2;

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

DLL_EXP void MglVertexGen( MGL_VERTEX *pVertexOut, float x, float y, float tu, float tv,
						  D3DCOLOR color=D3DCOLOR_WHITE, float z=0.0f, float rhw=1.0f );
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
