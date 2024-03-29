#include "stdafx.h"
#include "MglLight.h"

//	コンストラクタ
void CMglLight::_CMglLight()
{
	ZeroMemory( &m_light, sizeof(m_light) );
	m_dwLightIndex = 0;
}

//	開放
void CMglLight::Release()
{
	if ( m_d3d != NULL )
		CMglLight::Disable();
}


void CMglLight::Setup( _D3DLIGHTx &lightSetting )
{
	InitCheck();

	//	前回のライト構造体を初期化
	ZeroMemory( &m_light, sizeof(m_light) );

	//	ライトの有効化は最初にしといた方がいいんでないかい
	m_d3d->SetRenderState( D3DRS_LIGHTING, TRUE );

	////////////////////////////////////////////////

	m_light = lightSetting;

	CommitD3dLight();
	CMglLight::Enable();
	//m_d3d->SetLight( m_dwLightIndex, &m_light );
	//m_d3d->LightEnable( m_dwLightIndex, TRUE );

	m_d3d->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
	m_d3d->SetRenderState( D3DRS_AMBIENT, D3DXCOLOR(m_light.Ambient) );

	/*
	m_d3d->SetRenderState( D3DRS_ALPHABLENDENABLE,	FALSE );		// αブレンディング無効
	m_d3d->SetRenderState( D3DRS_ALPHATESTENABLE,	FALSE );		// αテストを無効に

	m_d3d->SetRenderState( D3DRS_ZWRITEENABLE,		TRUE );			// Zバッファへの書き込み許可

	m_d3d->SetRenderState( D3DRS_AMBIENT, 0x00808080 );				// 環境光

	m_d3d->SetRenderState( D3DRS_SRCBLEND,	D3DBLEND_ONE );			// ソース側の色の比率
	m_d3d->SetRenderState( D3DRS_DESTBLEND,	D3DBLEND_ZERO );		// 書き込み側の色の比率

	m_d3d->LightEnable( 0, TRUE );									// ライトを有効に

	m_d3d->SetTextureStageState( 0 , D3DTSS_ALPHAOP,	D3DTOP_DISABLE );		//αチャネルは無効に
	*/

	/*
	g_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);// グローシェーディングを行う
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);	// スペキュラを使用しない
	g_pD3DDevice->SetMaterial(&g_Material);						// マテリアルをシステムに設定
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);	// 頂点法線の自動正規化を有効にする
	*/
}

void CMglLight::Setup( D3DLIGHTTYPE lightType,
					  float fPosX, float fPosY, float fPosZ,
					  float fDirectionX, float fDirectionY, float fDirectionZ,
					  MGL_LIGHT_ATTENUATION &attenuation,
					  D3DXCOLOR color, D3DXCOLOR ambient, D3DXCOLOR specular, float fRange )
{
	_D3DLIGHTx light;
	ZeroMemory( &light, sizeof(light) );

	light.Type = lightType;
	light.Diffuse = color;
	light.Ambient = ambient;
	light.Specular = specular;
	light.Range = fRange;
	
	light.Attenuation0 = attenuation.fLinear;
	light.Attenuation1 = attenuation.fCurve;
	light.Attenuation2 = attenuation.fPowCurve;

	if ( light.Attenuation0 == 0 && light.Attenuation1 == 0 && light.Attenuation2 == 0 )
		light.Attenuation0 = 0.000001f;

	/*light.Attenuation0 = -0.14f;
	light.Attenuation1 = 0.05f;
	light.Attenuation2 = 0.0f;*/

	/*light.Attenuation0 = 0.6f;
	light.Attenuation1 = 0.05f;
	light.Attenuation2 = 0.0f;*/
	/*light.Attenuation0 = 0.5f;
	light.Attenuation1 = 0.1f;
	light.Attenuation2 = 0.0f;*/

	D3DXVECTOR3 direction(fDirectionX,fDirectionY,fDirectionZ);
	D3DXVECTOR3 position(fPosX,fPosY,fPosZ);
	//position *= 10.0f;
	light.Position = position;
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &direction );
	//D3DXVec3Normalize( (D3DXVECTOR3*)&light.Position, &position );

	Setup(light);
}

//typedef struct _D3DLIGHT8 {
//    D3DLIGHTTYPE    Type;            /* Type of light source */
//    D3DCOLORVALUE   Diffuse;         /* Diffuse color of light */
//    D3DCOLORVALUE   Specular;        /* Specular color of light */
//    D3DCOLORVALUE   Ambient;         /* Ambient color of light */
//    D3DVECTOR       Position;         /* Position in world space */
//    D3DVECTOR       Direction;        /* Direction in world space */
//    float           Range;            /* Cutoff range */
//    float           Falloff;          /* Falloff */
//    float           Attenuation0;     /* Constant attenuation */
//    float           Attenuation1;     /* Linear attenuation */
//    float           Attenuation2;     /* Quadratic attenuation */
//    float           Theta;            /* Inner angle of spotlight cone */
//    float           Phi;              /* Outer angle of spotlight cone */
//} D3DLIGHT8;

void CMglLight::Enable(){
	InitCheck();
	MyuAssert2( m_d3d->LightEnable( m_dwLightIndex, TRUE ), D3D_OK,
		MGLMSGNO_LIGHT(20), "CMglLight::Enable()  m_d3d->LightEnable()に失敗" );
}
void CMglLight::Disable(){
	InitCheck();
	m_d3d->LightEnable( m_dwLightIndex, FALSE );
}
void CMglLight::AllLightDisable(){
	InitCheck();
	m_d3d->SetRenderState( D3DRS_LIGHTING, FALSE );
}

void CMglLight::CommitD3dLight(){
	InitCheck();
	MyuAssert2( m_d3d->SetLight( m_dwLightIndex, &m_light ), D3D_OK,
		MGLMSGNO_LIGHT(10), "CMglLight::CommitD3dLight()  m_d3d->SetLight()に失敗" );
}
