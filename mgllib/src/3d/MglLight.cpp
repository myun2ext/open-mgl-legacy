#include "stdafx.h"
#include "MglLight.h"

//	コンストラクタ
CMglLight::CMglLight()
{
	ZeroMemory( &m_light, sizeof(m_light) );
}

//	開放
void CMglLight::Release()
{

}


void CMglLight::Setup( D3DLIGHTTYPE lightType, float fPosX, float fPosY, float fPosZ,
					  D3DXCOLOR color, D3DCOLOR ambient, float fRange )
{
	InitCheck();

	ZeroMemory( &m_light, sizeof(m_light) );

	m_light.Type = lightType;
	m_light.Diffuse = color;
	D3DXVECTOR3 vecDir(fPosX,fPosY,fPosZ);
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_light.Direction, &vecDir );
	m_light.Range = fRange;

	m_d3d->SetRenderState( D3DRS_LIGHTING, TRUE );
	m_d3d->SetLight( 0, &m_light );
	m_d3d->LightEnable( 0, TRUE );
	m_d3d->SetRenderState( D3DRS_AMBIENT, ambient );
}

