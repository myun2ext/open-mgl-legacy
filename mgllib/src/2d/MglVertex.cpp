#include "stdafx.h"
#include "MglVertex.h"

//	頂点情報(MGL_VERTEX) の生成
void MglVertexGen( MGL_VERTEX *pVertexOut, float x, float y, float tu, float tv, D3DCOLOR color, float z, float rhw )
{
	ZeroMemory( pVertexOut, sizeof(MGL_VERTEX) );
	pVertexOut->x = x;
	pVertexOut->y = y;
	pVertexOut->z = z;
	pVertexOut->rhw = rhw;
	pVertexOut->color = color;
	pVertexOut->tu = tu;
	pVertexOut->tv = tv;
}

//	頂点群の移動（まとめて）
/*void MglMoveVertexs( MGL_SQUARE_VERTEXS *pVertexs, float x, float y )
{
	for( int i=0; i<4; i++ )
	{
		MGL_VERTEX* pVertex = &((MGL_VERTEX*)pVertexs)[i];
		pVertex->x += x;
		pVertex->y += y;
	}
}*/
DLL_EXP void MglMoveVertexs( MGL_VERTEX *pVertexs, float x, float y, int vertexCount )
{
	for( int i=0; i<4; i++ )
	{
		MGL_VERTEX* p = &pVertexs[i];
		p->x += x;
		p->y += y;
	}
}