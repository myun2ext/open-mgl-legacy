//////////////////////////////////////////////////////////
//
//	MglDrawLine
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglDrawLine.h"

//CMglTexture* CMglDrawLine::m_pLineTex;

//	コンストラクタ
CMglDrawLine::CMglDrawLine(){
	/*
	//	初回一回だけ
	if ( m_pLineTex == NULL ){
		m_pLineTex = new CMglTexture();

		//m_pLineTex->Create(1,1,FALSE);
		m_pLineTex->Create(2,2,FALSE);
	}
	*/

	m_myudg = NULL;
	m_d3d = NULL;
}

//	初期化
void CMglDrawLine::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	m_d3d = m_myudg->GetD3dDevPtr();
}

//	描画
void CMglDrawLine::Draw(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR startColor, D3DCOLOR endColor, float width)
{
	InitCheck();

	MYU_VERTEX vertices[4];		//	頂点
	ZeroMemory( vertices, sizeof(vertices) );

	//	転送元設定
	vertices[VERTEXNO_LT].tu = vertices[VERTEXNO_LB].tu = 0.0f;
	vertices[VERTEXNO_LT].tv = vertices[VERTEXNO_RT].tv = 0.0f;
	vertices[VERTEXNO_RB].tu = vertices[VERTEXNO_RT].tu = 1.0f;
	vertices[VERTEXNO_RB].tv = vertices[VERTEXNO_LB].tv = 1.0f;

	//	始点
	vertices[VERTEXNO_LT].x = fStartX;
	vertices[VERTEXNO_LT].y = fStartY;
#ifdef _MGLVERTEX_USE_RHW
	vertices[VERTEXNO_LT].rhw = 1.0f;
#endif
	vertices[VERTEXNO_LT].color = startColor;
	vertices[VERTEXNO_RT].x = fStartX+width;
	vertices[VERTEXNO_RT].y = fStartY-width;
#ifdef _MGLVERTEX_USE_RHW
	vertices[VERTEXNO_RT].rhw = 1.0f;
#endif
	vertices[VERTEXNO_RT].color = startColor;
	
	//	終点
	vertices[VERTEXNO_LB].x = fEndX;
	vertices[VERTEXNO_LB].y = fEndY;
#ifdef _MGLVERTEX_USE_RHW
	vertices[VERTEXNO_LB].rhw = 1.0f;
#endif
	vertices[VERTEXNO_LB].color = endColor;
	vertices[VERTEXNO_RB].x = fEndX+width;
	vertices[VERTEXNO_RB].y = fEndY-width;
#ifdef _MGLVERTEX_USE_RHW
	vertices[VERTEXNO_RB].rhw = 1.0f;
#endif
	vertices[VERTEXNO_RB].color = endColor;


	//////////////////////////////////////////////////////


	//	頂点バッファ生成
	LPDIRECT3DVERTEXBUFFER8 pVertexBuffer = NULL;
	if( FAILED( m_d3d->CreateVertexBuffer( sizeof(vertices),
                                                  //0, D3DFVF_CUSTOMVERTEX,
                                                  0, FVF_MYU_VERTEX,
                                                  D3DPOOL_DEFAULT, &pVertexBuffer ) ) )
    {
        MyuThrow( MGLMSGNO_DRAW_LINE_DRAW_FAILED,
			"CMglDrawLine::Draw()  m_d3d->CreateVertexBuffer()に失敗" );
    }

    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
    // gain access to the vertices. This mechanism is required becuase vertex
    // buffers may be in device memory.
    BYTE* pVertices = NULL;
    if( FAILED( pVertexBuffer->Lock( 0, MGL_VERTEXES_SIZE, &pVertices, 0 ) ) )
        MyuThrow( MGLMSGNO_DRAW_LINE_DRAW_FAILED,
			"CMglDrawLine::Draw()  pVertexBuffer->Lock()に失敗" );

	if ( pVertices == NULL )
        MyuThrow( MGLMSGNO_DRAW_LINE_DRAW_FAILED,
			"CMglDrawLine::Draw()  pVertices is NULL." );

    memcpy( pVertices, vertices, MGL_VERTEXES_SIZE );
    pVertexBuffer->Unlock();

	m_d3d->SetVertexShader(FVF_MYU_VERTEX);
	m_d3d->SetStreamSource(0, pVertexBuffer , sizeof(MYU_VERTEX));
	m_d3d->DrawPrimitive(D3DPT_TRIANGLESTRIP , 0 , 2);

    //m_d3d->SetStreamSource( 0, pVertexBuffer, 0, sizeof(MYU_VERTEX) );
    //m_d3d->SetStreamSource( 0, pVertexBuffer, sizeof(MYU_VERTEX) );
    //m_d3d->SetFVF( FVF_MYU_VERTEX );
    //m_d3d->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );

	/*
	//	絵画
	MyuAssert( m_d3d->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 1, vertices, sizeof(MYU_VERTEX) ), D3D_OK,
		"CMglDrawLine::Draw()  DrawPrimitiveUP()に失敗" );
	*/

	/*
	//	アルファオプション
	//m_myudg->SetAlphaMode( MGL_ALPHA_OPT_DEFAULT );

	//	描画
	m_pLineTex->Draw( vertices );
	*/
}








//#define D3DFVF D3DFVF_XYZRHW | D3DFVF_DIFFUSE
#define D3DFVF FVF_MYU_VERTEX

/*
typedef struct {
	float x , y , z , w;
	DWORD color;
} D3DVERTEX;
*/
#define D3DVERTEX	MYU_VERTEX


void CMglDrawLine::Draw2(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR startColor, D3DCOLOR endColor, float width)
{
	InitCheck();

	static D3DVERTEX pt[4];

	//	始点
	pt[VERTEXNO_LT].x = fStartX;
	pt[VERTEXNO_LT].y = fStartY;
	pt[VERTEXNO_LT].color = startColor;
	pt[VERTEXNO_RT].x = fStartX;
	pt[VERTEXNO_RT].y = fStartY;
	pt[VERTEXNO_RT].color = startColor;
	
	//	終点
	pt[VERTEXNO_LB].x = fEndX+50;
	pt[VERTEXNO_LB].y = fEndY+90;
	pt[VERTEXNO_LB].color = endColor;
	pt[VERTEXNO_RB].x = fEndX+20;
	pt[VERTEXNO_RB].y = fEndY+20;
	pt[VERTEXNO_RB].color = endColor;

	/*
	static D3DVERTEX pt[4] = {
		{fStartX , 10 , 0 , 1 , 0xFFFF0000} ,
		{400 , 200 , 0 , 1 , 0xFF00FF00} ,
		{10 , 200 , 0 , 1 , 0xFF0000FF} ,
		{200 , 600 , 0 , 1 , 0xFF000000}
	};
	*/
	D3DXMATRIX d3dm;
	D3DVERTEX *d3dv;
	IDirect3DVertexBuffer8 *d3dvb;

	m_d3d->CreateVertexBuffer(
		sizeof (D3DVERTEX) * 4 , 0 , D3DFVF , D3DPOOL_MANAGED , &d3dvb);
	d3dvb->Lock(0 , 0 , (BYTE**)&d3dv , 0);
	memcpy(d3dv , pt , sizeof (D3DVERTEX) * 4);
	d3dvb->Unlock();

	m_d3d->SetVertexShader(D3DFVF);
	m_d3d->SetStreamSource(0 , d3dvb , sizeof (D3DVERTEX));
	//m_d3d->DrawPrimitive(D3DPT_TRIANGLESTRIP , 0 , 2);
}


/*
void CMglDrawLine::Draw2(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR startColor, D3DCOLOR endColor, float width)
{
	InitCheck();

	static D3DVERTEX pt[4];

	//	始点
	pt[VERTEXNO_LT].x = fStartX;
	pt[VERTEXNO_LT].y = fStartY;
	pt[VERTEXNO_LT].color = startColor;
	pt[VERTEXNO_RT].x = fStartX;
	pt[VERTEXNO_RT].y = fStartY;
	pt[VERTEXNO_RT].color = startColor;
	
	//	終点
	pt[VERTEXNO_LB].x = fEndX;
	pt[VERTEXNO_LB].y = fEndY;
	pt[VERTEXNO_LB].color = endColor;
	pt[VERTEXNO_RB].x = fEndX;
	pt[VERTEXNO_RB].y = fEndY;
	pt[VERTEXNO_RB].color = endColor;

	D3DXMATRIX d3dm;
	D3DVERTEX *d3dv;
	IDirect3DVertexBuffer8 *d3dvb;

	m_d3d->CreateVertexBuffer(
		sizeof (D3DVERTEX) * 4 , 0 , D3DFVF , D3DPOOL_MANAGED , &d3dvb);
	d3dvb->Lock(0 , 0 , (BYTE**)&d3dv , 0);
	memcpy(d3dv , pt , sizeof (D3DVERTEX) * 4);
	d3dvb->Unlock();
	m_d3d->SetVertexShader(D3DFVF);
	m_d3d->SetStreamSource(0 , d3dvb , sizeof (D3DVERTEX));
	m_d3d->DrawPrimitive(D3DPT_TRIANGLESTRIP , 0 , 2);
}
*/