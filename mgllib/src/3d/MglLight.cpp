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
	CMglLight::Disable();
}


void CMglLight::Setup( D3DLIGHTTYPE lightType,
					  float fPosX, float fPosY, float fPosZ,
					  float fDirectionX, float fDirectionY, float fDirectionZ,
					  D3DXCOLOR color, D3DXCOLOR ambient, D3DXCOLOR specular, float fRange )
{
	InitCheck();

	ZeroMemory( &m_light, sizeof(m_light) );

	m_light.Type = lightType;
	m_light.Diffuse = color;
	m_light.Ambient = ambient;
	m_light.Specular = specular;
	m_light.Range = fRange;

	D3DXVECTOR3 direction(fDirectionX,fDirectionY,fDirectionZ);
	D3DXVECTOR3 position(fPosX,fPosY,fPosZ);
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_light.Direction, &direction );
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_light.Position, &position );

	m_d3d->SetRenderState( D3DRS_LIGHTING, TRUE );

	CommitD3dLight();
	CMglLight::Enable();
	//m_d3d->SetLight( m_dwLightIndex, &m_light );
	//m_d3d->LightEnable( m_dwLightIndex, TRUE );

	m_d3d->SetRenderState( D3DRS_AMBIENT, ambient );

	/*
	g_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);// グローシェーディングを行う
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);	// スペキュラを使用しない
	g_pD3DDevice->SetMaterial(&g_Material);						// マテリアルをシステムに設定
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);	// 頂点法線の自動正規化を有効にする
	*/
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
	m_d3d->LightEnable( m_dwLightIndex, TRUE );
}
void CMglLight::Disable(){
	m_d3d->LightEnable( m_dwLightIndex, FALSE );
}
void CMglLight::AllLightDisable(){
	m_d3d->SetRenderState( D3DRS_LIGHTING, FALSE );
}

void CMglLight::CommitD3dLight(){
	m_d3d->SetLight( m_dwLightIndex, &m_light );
}
