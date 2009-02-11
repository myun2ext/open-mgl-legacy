#include "stdafx.h"
#include "MglVertex.h"

//	頂点情報(MGL_VERTEX) の生成
#ifdef _MGLVERTEX_USE_RHW
	void MglVertexGen( MGL_VERTEX *pVertexOut, float x, float y, float z, float tu, float tv, D3DCOLOR color, float rhw )
#else
	void MglVertexGen( MGL_VERTEX *pVertexOut, float x, float y, float z, float tu, float tv, D3DCOLOR color )
#endif
{
	ZeroMemory( pVertexOut, sizeof(MGL_VERTEX) );
	pVertexOut->x = x;
	pVertexOut->y = y;
	pVertexOut->z = z;
#ifdef _MGLVERTEX_USE_RHW
	pVertexOut->rhw = rhw;
#endif
	pVertexOut->color = color;
#ifdef _MGLVERTEX_USE_MULTITEX
	pVertexOut->tPosAry[0].x = tu;
	pVertexOut->tPosAry[0].y = tv;
#else
	pVertexOut->tu = tu;
	pVertexOut->tv = tv;
#endif
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
/*DLL_EXP void MglMoveVertexs( MGL_VERTEX *pVertexs, float x, float y, int vertexCount )
{
	for( int i=0; i<4; i++ )
	{
		MGL_VERTEX* p = &pVertexs[i];
		p->x += x;
		p->y += y;
	}
}*/

DLL_EXP void MglMoveVertexs( MGL_VERTEX *pVertexs, float x, float y, float z, int vertexCount )
{
	for( int i=0; i<vertexCount; i++ )
	{
		pVertexs->x += x;
		pVertexs->y += y;
		pVertexs->z += z;
		pVertexs++;
		/*
		MGL_VERTEX* p = &pVertexs[i];
		p->x += x;
		p->y += y;
		p->z += z;
		*/
	}
}

DLL_EXP void MglVertexsFillColor( MGL_VERTEX *pVertexs, D3DCOLOR color, int vertexCount )
{
	for(int i=0; i<vertexCount; i++)
	{
		pVertexs->color = color;
		pVertexs++;
	}
}
