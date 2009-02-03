#include "stdafx.h"
#include "MglLight.h"

//	�R���X�g���N�^
void CMglLight::_CMglLight()
{
	ZeroMemory( &m_light, sizeof(m_light) );
	m_dwLightIndex = 0;
}

//	�J��
void CMglLight::Release()
{
	if ( m_d3d != NULL )
		CMglLight::Disable();
}


void CMglLight::Setup( D3DLIGHTTYPE lightType,
					  float fPosX, float fPosY, float fPosZ,
					  float fDirectionX, float fDirectionY, float fDirectionZ,
					  D3DXCOLOR color, D3DXCOLOR ambient, D3DXCOLOR specular, float fRange )
{
	InitCheck();

	//	�O��̃��C�g�\���̂�������
	ZeroMemory( &m_light, sizeof(m_light) );

	//	���C�g�̗L�����͍ŏ��ɂ��Ƃ�������������łȂ�����
	m_d3d->SetRenderState( D3DRS_LIGHTING, TRUE );

	////////////////////////////////////////////////

	m_light.Type = lightType;
	m_light.Diffuse = color;
	m_light.Ambient = ambient;
	m_light.Specular = specular;
	m_light.Range = fRange;

	D3DXVECTOR3 direction(fDirectionX,fDirectionY,fDirectionZ);
	D3DXVECTOR3 position(fPosX,fPosY,fPosZ);
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_light.Direction, &direction );
	D3DXVec3Normalize( (D3DXVECTOR3*)&m_light.Position, &position );


	CommitD3dLight();
	CMglLight::Enable();
	//m_d3d->SetLight( m_dwLightIndex, &m_light );
	//m_d3d->LightEnable( m_dwLightIndex, TRUE );

	m_d3d->SetRenderState( D3DRS_SPECULARENABLE, TRUE );
	m_d3d->SetRenderState( D3DRS_AMBIENT, ambient );

	/*
	m_d3d->SetRenderState( D3DRS_ALPHABLENDENABLE,	FALSE );		// ���u�����f�B���O����
	m_d3d->SetRenderState( D3DRS_ALPHATESTENABLE,	FALSE );		// ���e�X�g�𖳌���

	m_d3d->SetRenderState( D3DRS_ZWRITEENABLE,		TRUE );			// Z�o�b�t�@�ւ̏������݋���

	m_d3d->SetRenderState( D3DRS_AMBIENT, 0x00808080 );				// ����

	m_d3d->SetRenderState( D3DRS_SRCBLEND,	D3DBLEND_ONE );			// �\�[�X���̐F�̔䗦
	m_d3d->SetRenderState( D3DRS_DESTBLEND,	D3DBLEND_ZERO );		// �������ݑ��̐F�̔䗦

	m_d3d->LightEnable( 0, TRUE );									// ���C�g��L����

	m_d3d->SetTextureStageState( 0 , D3DTSS_ALPHAOP,	D3DTOP_DISABLE );		//���`���l���͖�����
*/

	/*
	g_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);// �O���[�V�F�[�f�B���O���s��
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);	// �X�y�L�������g�p���Ȃ�
	g_pD3DDevice->SetMaterial(&g_Material);						// �}�e���A�����V�X�e���ɐݒ�
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);	// ���_�@���̎������K����L���ɂ���
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
	InitCheck();
	m_d3d->LightEnable( m_dwLightIndex, TRUE );
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
	m_d3d->SetLight( m_dwLightIndex, &m_light );
}
