#include "stdafx.h"
#include "mgl3d.h"
#include "dx_graphic.h"

LPDIRECT3DVERTEXBUFFER8 pVB = NULL; // 頂点バッファに使うオブジェクト
#define PI (3.1415926535f)

void GameMain(CMglTexture *pTexture);
void GameMain2(CMglTexture *pTexture);

// ----------------------------------------------------------------------------
// 頂点の定義
struct CUSTOMVERTEX
{
    FLOAT x, y, z;		// 位置
    DWORD color;			// 色
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

// ----------------------------------------------------------------------------
// Name: Render()
// Desc: ポリゴンの初期化
//-----------------------------------------------------------------------------
HRESULT InitRender(LPDIRECT3DDEVICE8 lpD3DDEV)
{
    CUSTOMVERTEX vertices[] =
    {
		//     x,      y,    z,  color
		{   0.0f,   0.0f, 0.0f, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff), },
        {   1.0f,   0.0f, 0.0f, D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), },
        {   0.0f,   1.0f, 0.0f, D3DCOLOR_RGBA(0x00, 0xff, 0x00, 0xff), },
        {   0.0f,   0.0f, 1.0f, D3DCOLOR_RGBA(0x00, 0x00, 0xff, 0xff), },
        {   1.0f,   0.0f, 0.0f, D3DCOLOR_RGBA(0xff, 0x00, 0x00, 0xff), },
    };
	HRESULT hr;
	
	hr = lpD3DDEV->CreateVertexBuffer( 5*sizeof(CUSTOMVERTEX),0,
					D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &pVB);
    if(FAILED(hr)) return E_FAIL;

    VOID* pVertices;
	hr = pVB->Lock( 0, sizeof(vertices), (BYTE**)&pVertices, 0);
    if(FAILED(hr)) return E_FAIL;
    memcpy( pVertices, vertices, sizeof(vertices) );
    pVB->Unlock();

	lpD3DDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	lpD3DDEV->SetRenderState(D3DRS_LIGHTING, FALSE);

	/*   D3DXVECTOR3 vecDir;
    D3DLIGHT8 light;
    ZeroMemory( &light, sizeof(D3DLIGHT8) );
    light.Type       = D3DLIGHT_DIRECTIONAL;
    light.Diffuse.r  = 1.0f;
    light.Diffuse.g  = 0.3f;
    light.Diffuse.b  = 0.3f;
    vecDir = D3DXVECTOR3(-1.0f, -1.0f, -0.1f);
    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
    light.Range       = 1000.0f;
    lpD3DDEV->SetLight( 0, &light );
    lpD3DDEV->LightEnable( 0, TRUE );
    lpD3DDEV->SetRenderState( D3DRS_LIGHTING, TRUE );
    lpD3DDEV->SetRenderState( D3DRS_AMBIENT, 0x00ffffff );*/

    return S_OK;
}


LPD3DXMESH				pMesh          = NULL;		// メッシュ
D3DMATERIAL8			*pMeshMaterials = NULL;		// メッシュの質感
LPDIRECT3DTEXTURE8		*pMeshTextures  = NULL;		// メッシュのテクスチャー
DWORD					dwNumMaterials = 0L;		// マテリアルの数

// ----------------------------------------------------------------------------
// Name: Render()
// Desc: ポリゴンの初期化
//-----------------------------------------------------------------------------
HRESULT InitRender2(LPDIRECT3DDEVICE8 lpD3DDEV)
{
	HRESULT hr;
    LPD3DXBUFFER pD3DXMtrlBuffer;

    // X ファイルのロード
	hr = D3DXLoadMeshFromX( "car.x", D3DXMESH_SYSTEMMEM, 
                                   lpD3DDEV, NULL, 
                                   &pD3DXMtrlBuffer, &dwNumMaterials, 
                                   &pMesh );
    if(FAILED(hr)) return E_FAIL;

    // pD3DXMtrlBuffer から、質感やテクスチャーの情報を読み取る
    D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    pMeshMaterials = new D3DMATERIAL8[dwNumMaterials];
    pMeshTextures  = new LPDIRECT3DTEXTURE8[dwNumMaterials];

    for( DWORD i=0; i < dwNumMaterials; i++ ){
        pMeshMaterials[i] = d3dxMaterials[i].MatD3D;// 質感のコピー
        pMeshMaterials[i].Ambient = pMeshMaterials[i].Diffuse;// マテリアルの環境色を設定する
     
        hr = D3DXCreateTextureFromFile( lpD3DDEV, 
                                        d3dxMaterials[i].pTextureFilename, 
                                        &pMeshTextures[i] );
	    if(FAILED(hr)) pMeshTextures[i] = NULL;
    }

    SAFE_RELEASE(pD3DXMtrlBuffer);
	
    lpD3DDEV->SetRenderState( D3DRS_ZENABLE, TRUE);
    
   D3DXVECTOR3 vecDir;
    D3DLIGHT8 light;
    ZeroMemory( &light, sizeof(D3DLIGHT8) );
    light.Type       = D3DLIGHT_DIRECTIONAL;
    light.Diffuse.r  = 1.0f;
    light.Diffuse.g  = 0.3f;
    light.Diffuse.b  = 0.3f;
    vecDir = D3DXVECTOR3(-1.0f, -1.0f, -0.1f);
    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
    light.Range       = 1000.0f;
    lpD3DDEV->SetLight( 0, &light );
    lpD3DDEV->LightEnable( 0, TRUE );
    lpD3DDEV->SetRenderState( D3DRS_LIGHTING, TRUE );
    lpD3DDEV->SetRenderState( D3DRS_AMBIENT, 0x00202020 );
	
	return S_OK;
}

// ----------------------------------------------------------------------------
// Name: Render()
// Desc: ポリゴンの描画
//-----------------------------------------------------------------------------
void Render(LPDIRECT3DDEVICE8 lpD3DDEV)
{
	static int i=0;
	i++;

    D3DXMATRIX mWorld, mRotX, mRotY, mTrans;
	float time = (float)timeGetTime();
	//TODO: D3DXMatrixRotationY(&mRotY, time/600.0f);
	//D3DXMatrixRotationY(&mRotY, 600.0f);
	D3DXMatrixRotationY(&mRotY, 60.0f);
//	D3DXMatrixRotationX(&mRotX, time/300.0f);
	D3DXMatrixRotationX(&mRotX, 0.0f);
	D3DXMatrixTranslation(&mTrans, 0,0,0.0f);
	mWorld = mRotX * mRotY * mTrans;
	D3DXMATRIX mView, mProj;
	D3DXMatrixLookAtLH(&mView
					,&D3DXVECTOR3(0-(i/100.0f),2.0f,2.0f-(i/100.0f))	// カメラ位置
					,&D3DXVECTOR3(0+(i/1000.0f),0,0)		// カメラの注目点
					,&D3DXVECTOR3(0,1,0)		// 上の向き
					);
	D3DXMatrixPerspectiveFovLH(&mProj
		,60.0f*PI/180.0f						// 視野角
		,1.0f									// アスペクト比
		,0.01f									// 最近接距離
		,100.0f									// 最遠方距離
		);
	lpD3DDEV->SetTransform(D3DTS_WORLD, &mWorld);
	lpD3DDEV->SetTransform(D3DTS_VIEW,  &mView);
	lpD3DDEV->SetTransform(D3DTS_PROJECTION, &mProj);

	lpD3DDEV->SetStreamSource( 0, pVB, sizeof(CUSTOMVERTEX) );
    lpD3DDEV->SetVertexShader( D3DFVF_CUSTOMVERTEX );
    lpD3DDEV->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 3 );
}
void Render2(LPDIRECT3DDEVICE8 lpD3DDEV)
{
    D3DXMATRIX mWorld;
    D3DXMatrixRotationY( &mWorld, timeGetTime()/1000.0f );
	D3DXMATRIX mView, mProj;
    D3DXMatrixLookAtLH( &mView, &D3DXVECTOR3( 0.0f, 3.0f, 4.0f ), 
                                &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), 
                                &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	D3DXMatrixPerspectiveFovLH(&mProj
		,60.0f*PI/180.0f						// 視野角
		,1.0f									// アスペクト比
		,0.01f									// 最近接距離
		,100.0f									// 最遠方距離
		);
	
	lpD3DDEV->SetTransform(D3DTS_WORLD, &mWorld);
	lpD3DDEV->SetTransform(D3DTS_VIEW,  &mView);
	lpD3DDEV->SetTransform(D3DTS_PROJECTION, &mProj);


    for( DWORD i=0; i < dwNumMaterials; i++ ){
        lpD3DDEV->SetMaterial( &pMeshMaterials[i] );
        lpD3DDEV->SetTexture( 0, pMeshTextures[i] );
        pMesh->DrawSubset( i );
    }
}
///////////////////////////////////////////////////////////////////

//	メインフレームクラス
class CMglTestFrame : public CAugustWindow
{
private:
	CAugustImage m_img;
	CAugustText m_text;
	CMglImage3D m_img2;
public:
	void OnInit(){
		RegistControl(&m_img);
		RegistControl(&m_text);

		m_img.Load("test.jpg");
		m_img2.CreateTextureFromFile("font_big.tga");
		m_text.SetText("hoge");
		m_text.SetFontSize(64);
		m_text.SetColor(0x77000000);

		m_audio.Load("hoge.wav");
		m_audio.Load("hoge2.wav");

		//	キーボードイベントハンドラ登録
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_Z,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)PlaySoundZ);

		//	キーボードイベントハンドラ登録
		RegistKbHandler(
			AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_X,
			(AUGUST_KB_EVT_HANDLER_CALLBACK)PlaySoundX);

		//////////////////////////////

		InitRender(grp.GetD3dDevPtr());
		//InitRender2(grp.GetD3dDevPtr());
	}
	/*bool DoFrame(){
		Render(grp.GetD3dDevPtr());

		return CAugustWindow::DoFrame();
	}*/
	void OnDraw(){
		grp.Clear(0);

		Render(grp.GetD3dDevPtr());
		//Render2(grp.GetD3dDevPtr());

	//	Vertexを設定
	MyuAssert( grp.GetD3dDevPtr()->SetVertexShader( FVF_MYU_VERTEX ), D3D_OK,
		"CMglGraphicManager::Init()  SetVertexShader()に失敗" );


		g_pD3DDevice = grp.GetD3dDevPtr();
		//GameMain(m_img2.GetDirect3dTexturePtr());
		GameMain2(&m_img2);


		//m_img2.Draw3d();
		grp.SpriteEnd();
		grp.SpriteBegin();
		//GetVCtrlPtr(0)->Draw();
	}
	bool PlaySoundZ(){
		m_audio.Play("hoge.wav");
		return true;
	}

	bool PlaySoundX(){
		m_audio.Play("hoge2.wav");
		return true;
	}
};
CMglTestFrame g_frame;

//	WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{

	g_frame.Start();
	return 0;
}






D3D_COORDINATE	g_WorldFrame(D3DXVECTOR3(1,1,1), D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0));



void GameMain(CMglTexture* pTexture)
{
	D3DCOLOR color = 0xffffffff;

	//	頂点初期情報取得
	MGL_SQUARE_VERTEXS vertexs;
	pTexture->GetBmpVertexs( &vertexs );

	//	x, yに移動
	MglMoveVertexs( &vertexs, 0, 0 );

	//	頂点の色
	vertexs.lt.color = color;
	vertexs.rt.color = color;
	vertexs.lb.color = color;
	vertexs.rb.color = color;

	/////////////////////////////////////////////////////

	g_pD3DDevice->SetTexture(0, pTexture->GetDirect3dTexturePtr());	// テクスチャをセット

	// デバイスに使用する頂点フォーマットをセットする（光源無し、座標変換有り）
	g_pD3DDevice->SetVertexShader(FVF_MYU_VERTEX);
	
	// マトリックス生成
	//g_WorldFrame.rotate.y += 0.01f;			// Ｙ軸回りに回転
	g_WorldFrame.SetMat();											// 座標変換用マトリックス作成
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &g_WorldFrame.mat);	// ワールドマトリックスセット

	// 頂点バッファを使用せず直接データを渡して描画する
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vertexs, sizeof(D3DLVERTEX));
}



inline void GrpLVertexSet2(MGL_VERTEX *v, float x, float y, float z, float tu, float tv, D3DCOLOR rgba)
{
	v->x		= x;	
	v->y		= y;	
	v->z		= z;
	v->color	= rgba;
	//v->rhw	= 1.0f;
	v->tu		= tu;	
	v->tv		= tv;
}

void GameMain2(CMglTexture* pTexture)
{
	static int i=0;
	i++;

	g_pD3DDevice->SetTexture(0, pTexture->GetDirect3dTexturePtr());	// テクスチャをセット

	// 頂点情報設定（トライアングルストリップ形式）
	// 頂点、Ｘ、Ｙ、Ｚ、テクスチャＵ、テクスチャＶ、ＲＧＢＡ
	MGL_VERTEX v[4];												// 光源無し、座標変換有り頂点
	GrpLVertexSet2(&v[0], -1, 1, 0, 0, 0, D3DCOLOR_RGBA(255, 255, 255, 255));
	GrpLVertexSet2(&v[1],  1, 1, 0, 1, 0, D3DCOLOR_RGBA(255, 255, 255, 255));
	GrpLVertexSet2(&v[2], -1,-1, 0, 0, 1, D3DCOLOR_RGBA(255, 255, 255, 255));
	GrpLVertexSet2(&v[3],  1,-1, 0, 1, 1, D3DCOLOR_RGBA(255, 255, 255, 255));

	D3DCOLOR color = 0xffffffff;

	/////////////////////////////////////////////////////

	// デバイスに使用する頂点フォーマットをセットする（光源無し、座標変換有り）
	//g_pD3DDevice->SetVertexShader(D3DFVF_LVERTEX);
	g_pD3DDevice->SetVertexShader(FVF_MYU_VERTEX);
	
	// マトリックス生成
	//g_WorldFrame.rotate.y += 0.01f;			// Ｙ軸回りに回転
	g_WorldFrame.SetMat();											// 座標変換用マトリックス作成
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &g_WorldFrame.mat);	// ワールドマトリックスセット

	// 頂点バッファを使用せず直接データを渡して描画する
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(D3DLVERTEX));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(MGL_VERTEX));
}
