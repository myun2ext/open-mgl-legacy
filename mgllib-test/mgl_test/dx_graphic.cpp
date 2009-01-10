////////////////////////////////////////////////////////////////////////////
//	�t�@�C����	�F	dx_graphic.cpp
//	�t�@�C���T�v�F	�_�C���N�g�O���t�B�b�N�֘A�̏������s���B
//	�쐬		�F	M.Minami
////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "dx_graphic.h"

////////////////////////////////////////////////////////////////////////////
//                        �O���[�o���ϐ��̐錾
////////////////////////////////////////////////////////////////////////////
// �_�C���N�g�w�O���t�B�b�N�n
LPDIRECT3DDEVICE8			g_pD3DDevice  = NULL;	// �_�C���N�g�R�c�f�o�C�X

// ���W�ϊ��}�g���b�N�X ----------------------------------------------------
static D3DXMATRIX			g_ProjMat;				// �����ϊ��}�g���b�N�X
static D3DXMATRIX			g_ViewMat;				// �J�����}�g���b�N�X

// ���C�g ------------------------------------------------------------------
static D3DMATERIAL8			g_Material;
static D3DLIGHT8			g_Light;

////////////////////////////////////////////////////////////////////////////
//                     �t�@�C���ԃC���^�[�t�F�[�X�֐�
////////////////////////////////////////////////////////////////////////////
LPDIRECT3DDEVICE8  GetD3DDevice(void) { return g_pD3DDevice; }

void GrpSetProjMat(float clip_near, float clip_far);
void GrpSetViewMat(D3DXVECTOR3 eye, D3DXVECTOR3 pos);
void GrpSetRotTransMat(D3DXMATRIX &wmat, D3DXVECTOR3 &s, D3DXVECTOR3 &t, D3DXVECTOR3 &r);
void GrpSetLiht(D3DLIGHT_MODE mode);
inline void GrpTLVertexSet(D3DTLVERTEX *v, float x, float y, float z, float tu, float tv, D3DCOLOR rgba);
inline void GrpLVertexSet(D3DLVERTEX *v, float x, float y, float z, float tu, float tv, D3DCOLOR rgba);
inline void GrpVertexSet(D3DVERTEX *v, float x, float y, float z, float nx, float ny, float nz, float tu, float tv);

void GrpSetProjMat(float clip_near, float clip_far)
{
	// �����ϊ��s��쐬�i����n�j
	D3DXMatrixPerspectiveFovLH(&g_ProjMat,							// �쐬�v���W�F�N�V�����}�g���b�N�X�ւ̃|�C���^
					D3DXToRadian(45.0),								// ����p
					640.0f / 480.0f,								// �A�X�y�N�g��i�c�A���䗦�j
					clip_near,										// Near �N���b�v
					clip_far);										// Far  �N���b�v
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &g_ProjMat);		// �����ϊ��s���ݒ�
}

void GrpSetViewMat(D3DXVECTOR3 eye, D3DXVECTOR3 pos)
{
	// �J�����s��쐬�i����n�j	
	D3DXMatrixLookAtLH(&g_ViewMat,									// �쐬�r���[�}�g���b�N�X�̃|�C���^
					   &pos,										// �J�����ʒu
					   &eye,										// �J�����Î��_
					   &D3DXVECTOR3(0,1,0));						// ���[���h��Ԃŏ�������R�����x�N�g���w��	

	// �J�����s���ݒ�
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &g_ViewMat);
}

inline void GrpLVertexSet(D3DLVERTEX *v, float x, float y, float z, float tu, float tv, D3DCOLOR rgba)
{
	v->x		= x;	
	v->y		= y;	
	v->z		= z;
	v->color	= rgba;
	v->specular	= 0;
	v->tu0		= tu;	
	v->tv0		= tv;
}

void GrpSetLight(D3DLIGHT_MODE mode)
{
	if (mode == D3DLIGHT_INIT) {
		// ���C�g������ ----------------------------------------------------
		// �}�e���A���̐ݒ�
		g_Material.Diffuse.r  = 1;									// �f�B�t���[�Y�F�ݒ�
		g_Material.Diffuse.g  = 1;
		g_Material.Diffuse.b  = 1;
		g_Material.Ambient.r  = 0.5f;								// �A���r�G���g�F�ݒ�
		g_Material.Ambient.g  = 0.5f;
		g_Material.Ambient.b  = 0.5f;
		g_Material.Emissive.r = 0;									// �G�~�b�V�����F�ݒ�
		g_Material.Emissive.g = 0;
		g_Material.Emissive.b = 0;

		// �����̍쐬
		ZeroMemory(&g_Light,sizeof(D3DLIGHT8));
		g_Light.Type		= D3DLIGHT_DIRECTIONAL;					// �f�B���N�V���i�����C�g
		g_Light.Diffuse.r = 1;										// �f�B�t�[�Y�F�ݒ�
		g_Light.Diffuse.g = 1;
		g_Light.Diffuse.b = 1;
		g_Light.Ambient.r = 0.5f;									// �A���r�G���g�F�ݒ�
		g_Light.Ambient.g = 0.5f;
		g_Light.Ambient.b = 0.5f;
		g_Light.Direction = D3DXVECTOR3(0,0,1);						// �����Ǝ˕���
		g_Light.Position  = D3DXVECTOR3(0,0,0);						// �����ʒu�i�f�B���N�V�������͉e�������j

		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);			// ���C�e�B���O����
		g_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);// �O���[�V�F�[�f�B���O���s��
		g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE,FALSE);	// �X�y�L�������g�p���Ȃ�
		g_pD3DDevice->SetLight(0,&g_Light);							// ���C�g���V�X�e���ɐݒ�

		g_pD3DDevice->SetMaterial(&g_Material);						// �}�e���A�����V�X�e���ɐݒ�
		g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);	// ���_�@���̎������K����L���ɂ���
		g_pD3DDevice->LightEnable(0, TRUE);							// ���C�g�n�m
	} else if (mode == D3DLIGHT_ON) {
		// ���C�g�n�m ------------------------------------------------------
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);			// ���C�e�B���O�n�m	
	} else {
		// ���C�g�n�e�e ----------------------------------------------------
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);			// ���C�e�B���O�n�e�e	
	}
}

void GrpSetRotTransMat(D3DXMATRIX &wmat, D3DXVECTOR3 &s, D3DXVECTOR3 &t, D3DXVECTOR3 &r)
{
	D3DXMATRIX smat, tmat, rmat;

	D3DXMatrixScaling(&smat, s.x, s.y, s.z);					// �X�P�[���}�g���b�N�X����
	D3DXMatrixTranslation(&tmat, t.x, t.y, t.z);				// �ړ��}�g���b�N�X����
	D3DXMatrixRotationYawPitchRoll(&rmat, r.y, r.x, r.z);		// ��]�}�g���b�N�X����

	// �X�P�[���}�g���b�N�X �� �X�P�[���}�g���b�N�X �~ ��]�}�g���b�N�X
	D3DXMatrixMultiply(&smat, &smat, &rmat);
	// ���[�N�}�g���b�N�X   �� ��L�v�Z����         �~ �ړ��}�g���b�N�X
	D3DXMatrixMultiply(&wmat, &smat, &tmat); 
}

