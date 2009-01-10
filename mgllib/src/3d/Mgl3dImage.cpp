#include "stdafx.h"
#include "Mgl3dImage.h"

//	BMPの頂点情報取得
void CMgl3dImage::GetBmpVertexs3D( MGL_SQUARE_VERTEXS *pMglSqVertexs, float fScaleX, float fScaleY )
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
	MglVertexGen( &pMglSqVertexs->lt, 0,        0,			0.0f, 0.0f );
	MglVertexGen( &pMglSqVertexs->rt, fBmpSrcX, 0,			fBmpScaleX, 0.0f );
	MglVertexGen( &pMglSqVertexs->lb, 0,        fBmpSrcY,	0.0f, fBmpScaleY );
	MglVertexGen( &pMglSqVertexs->rb, fBmpSrcX, fBmpSrcY,	fBmpScaleX, fBmpScaleY );

	//	頂点のズラし
	//MglMoveVertexs( pMglSqVertexs, TEXTURE_FLOAT_ADJ, TEXTURE_FLOAT_ADJ );
}

//	頂点情報の設定
void CMgl3dImage::SetupVertexes(float x, float y, float z, RECT* srcRect, float fTexScaleX, float fTexScaleY, D3DCOLOR color)
{
	GetBmpVertexs3D( &m_vertexs, fTexScaleX, fTexScaleY );
	MglMoveVertexs( &m_vertexs, x, y, z );
}

//	描画
void CMgl3dImage::Draw(float x, float y, float z, RECT* srcRect, float fTexScaleX, float fTexScaleY, D3DCOLOR color)
{
	SetupVertexes(x,y,z,srcRect,fTexScaleX,fTexScaleY,color);

	/*
	//	頂点初期情報取得
	GetBmpVertexs3D( &vertexs, fScaleX, fScaleY );
	SetupVertexes( &vertexs, fScaleX, fScaleY );

	//	x, yに移動
	MglMoveVertexs( &vertexs, x, y );

	//	頂点の色
	vertexs.lt.color = color;
	vertexs.rt.color = color;
	vertexs.lb.color = color;
	vertexs.rb.color = color;
	*/

	/*
	vertexs.lt.x /= 100;
	vertexs.rt.x /= 100;
	vertexs.lb.x /= 100;
	vertexs.rb.x /= 100;
	vertexs.lt.y /= 100;
	vertexs.rt.y /= 100;
	vertexs.lb.y /= 100;
	vertexs.rb.y /= 100;
	*/

	/////////////////////////////////////////////////////

	//g_pD3DDevice->SetTexture(0, pTexture->GetDirect3dTexturePtr());	// テクスチャをセット
	SetD3dStageTexture();

	// デバイスに使用する頂点フォーマットをセットする（光源無し、座標変換有り）
	//d3d->SetVertexShader(FVF_MYU_VERTEX);
	m_myudg->SetupMyuVertex();
	
	// マトリックス生成
	//g_WorldFrame.rotate.y += 0.01f;			// Ｙ軸回りに回転
	//g_WorldFrame.SetMat();											// 座標変換用マトリックス作成
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &g_WorldFrame.mat);	// ワールドマトリックスセット

	// 頂点バッファを使用せず直接データを渡して描画する
	d3d->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, &m_vertexs, sizeof(MGL_VERTEX));
}


