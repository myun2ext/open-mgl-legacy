#include "stdafx.h"
#include "MglMesh.h"

//	BMPの頂点情報取得
void CMglMesh::GetBmpVertexs3D( MGL_SQUARE_VERTEXS *pMglSqVertexs, float fScaleX, float fScaleY )
{
	//GetBmpVertexs(pMglSqVertexs);

	int nBmpSrcX = m_imgInfo.Width;
	int nBmpSrcY = m_imgInfo.Height;

	int nBmpMax;
	if ( m_imgInfo.Width > m_imgInfo.Height )
		nBmpMax = m_imgInfo.Width;
	else
		nBmpMax = m_imgInfo.Height;

	float fBmpSrcX = (m_imgInfo.Width*1.0f) / nBmpMax * fScaleX;
	float fBmpSrcY = (m_imgInfo.Height*1.0f) / nBmpMax * fScaleY;

	//	2007/01/10  スケール取得
	//	# テクスチャ領域は2の倍数になる。その内の0.?fがBMPの領域かを算出する
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	const float fBmpScaleX = (float)nBmpSrcX / (float)texDesc.Width;
	const float fBmpScaleY = (float)nBmpSrcY / (float)texDesc.Height;

	//	頂点情報生成
	MglVertexGen( &pMglSqVertexs->lt, 0,        0,			0, 0.0f, 0.0f );
	MglVertexGen( &pMglSqVertexs->rt, fBmpSrcX, 0,			0, fBmpScaleX, 0.0f );
	MglVertexGen( &pMglSqVertexs->lb, 0,        fBmpSrcY,	0, 0.0f, fBmpScaleY );
	MglVertexGen( &pMglSqVertexs->rb, fBmpSrcX, fBmpSrcY,	0, fBmpScaleX, fBmpScaleY );

	//	頂点のズラし
	//MglMoveVertexs( pMglSqVertexs, TEXTURE_FLOAT_ADJ, TEXTURE_FLOAT_ADJ );
}

/*
//	BMPの頂点情報取得
void CMglMesh::SetupVertexes( float x, float y, float z, RECT* srcRect, float fTexScaleX, float fTexScaleY, D3DCOLOR color )
{
	//GetBmpVertexs(pMglSqVertexs);

	int nBmpSrcX = m_imgInfo.Width;
	int nBmpSrcY = m_imgInfo.Height;

	int nBmpMax;
	if ( m_imgInfo.Width > m_imgInfo.Height )
		nBmpMax = m_imgInfo.Width;
	else
		nBmpMax = m_imgInfo.Height;

	float fBmpSrcX = m_imgInfo.Width / nBmpMax * fScaleX;
	float fBmpSrcY = m_imgInfo.Height / nBmpMax * fScaleY;

	//	2007/01/10  スケール取得
	//	# テクスチャ領域は2の倍数になる。その内の0.?fがBMPの領域かを算出する
	D3DSURFACE_DESC texDesc;
	m_pTexture->GetLevelDesc( 0, &texDesc );
	const float fBmpScaleX = (float)nBmpSrcX / (float)texDesc.Width;
	const float fBmpScaleY = (float)nBmpSrcY / (float)texDesc.Height;

	//	頂点情報生成
	MglVertexGen( &pMglSqVertexs->lt, 0+x,        0+y,			z, 0.0f, 0.0f, color );
	MglVertexGen( &pMglSqVertexs->rt, fBmpSrcX+x, 0+y,			z, fBmpScaleX, 0.0f, color );
	MglVertexGen( &pMglSqVertexs->lb, 0+x,        fBmpSrcY+y,	z, 0.0f, fBmpScaleY, color );
	MglVertexGen( &pMglSqVertexs->rb, fBmpSrcX+x, fBmpSrcY+y,	z, fBmpScaleX, fBmpScaleY, color );

	//	頂点のズラし
	//MglMoveVertexs( pMglSqVertexs, TEXTURE_FLOAT_ADJ, TEXTURE_FLOAT_ADJ );
}
*/

//	頂点情報の設定
void CMglMesh::SetupVertexes(float x, float y, float z, RECT* srcRect, float fTexScaleX, float fTexScaleY, D3DCOLOR color)
{
	GetBmpVertexs3D( &m_vertexs, fTexScaleX, fTexScaleY );
	MglMoveVertexs( &m_vertexs, x, y, z );
	MglVertexsFillColor( &m_vertexs, color );
}

//	描画
void CMglMesh::Draw(float x, float y, float z, RECT* srcRect, float fTexScaleX, float fTexScaleY, D3DCOLOR color)
{
	SetupVertexes(x,y,z,srcRect,fTexScaleX,fTexScaleY,color);

	SetD3dStageTexture();
	m_myudg->SetupMyuVertex();
	
	// マトリックス生成
	//g_WorldFrame.rotate.y += 0.01f;			// Ｙ軸回りに回転
	//g_WorldFrame.SetMat();											// 座標変換用マトリックス作成
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &g_WorldFrame.mat);	// ワールドマトリックスセット

	// 頂点バッファを使用せず直接データを渡して描画する
	m_myudg->DrawPrimitiveUpMyuVertexSquare( &m_vertexs );
}


