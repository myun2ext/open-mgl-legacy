////////////////////////////////////////////////////////////////////////////
//	�t�@�C����	�F	dx_graphic.h
//	�t�@�C���T�v�F	dx_graphic ���W���[���w�b�_
//	�쐬		�F	M.Minami
////////////////////////////////////////////////////////////////////////////
#ifndef __DX_GRAPHIC_H_
#define __DX_GRAPHIC_H_

////////////////////////////////////////////////////////////////////////////
//						�w�b�_�t�@�C���̃C���N���[�h
////////////////////////////////////////////////////////////////////////////
#include <d3d8.h>								// DirectXGraphics �w�b�_�t�@�C��
#include <d3dx8.h>								// D3DX �w�b�_�t�@�C��

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

////////////////////////////////////////////////////////////////////////////
//							�}�N���A�\���̒�`
////////////////////////////////////////////////////////////////////////////
// �e�N�X�`���p ------------------------------------------------------------
// �e�N�X�`���Ǘ��\����
typedef struct  {
	LPDIRECT3DTEXTURE8	Tex;					// �e�N�X�`���o�b�t�@
	unsigned int		Width;					// �e�N�X�`������
	unsigned int		Height;					// �e�N�X�`����
} TEXTURE_DATA;

// �e�N�X�`���o�b�t�@�T�C�Y
#define TEX_MAX		100

// �X�v���C�g�p ------------------------------------------------------------
// �u�����h���[�h
typedef enum {
	D3DBLEND_NORMAL,							// �ʏ�A���t�@�u�����h
	D3DBLEND_ADD								// ���Z�A���t�@�u�����h
} BLEND_MODE;

// ���_�t�H�[�}�b�g --------------------------------------------------------
// �����v�Z�����A���W�ϊ��������_�t�H�[�}�b�g
typedef struct {
	float	x, y, z;							// ���W�ϊ��ςݒ��_���W
	float	rhw;								 
	DWORD	color;								// ���_�F�i�q�f�a�`�j
	DWORD	specular;							// �X�y�L�����F
	float	tu0, tv0;							// �e�N�X�`�����W
} D3DTLVERTEX;

#define D3DFVF_TLVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE |  D3DFVF_SPECULAR | D3DFVF_TEX1)

// ���W�ϊ��L��A���C�e�B���O�������_�t�H�[�}�b�g
typedef struct {
	float x, y, z;								// ���_���W
	DWORD color;								// ���_�F�i�q�f�a�`�j
	DWORD specular;								// �X�y�L�����F
	float tu0, tv0;								// �e�N�X�`�����W
} D3DLVERTEX;

#define D3DFVF_LVERTEX 		(D3DFVF_XYZ | D3DFVF_DIFFUSE |  D3DFVF_SPECULAR | D3DFVF_TEX1)

// ���W�ϊ��L��A���C�e�B���O�L�蒸�_�t�H�[�}�b�g
typedef struct {
	float x,  y,  z;							// ���_���W
	float nx, ny, nz;							// �@���x�N�g��
	float tu0, tv0;								// �e�N�X�`�����W
} D3DVERTEX;

#define D3DFVF_VERTEX 		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

//	���C�g�p ---------------------------------------------------------------
typedef enum {
	D3DLIGHT_INIT,		// ���C�g������
	D3DLIGHT_ON,		// ���C�g�n�m
	D3DLIGHT_OFF		// ���C�g�n�e�e
} D3DLIGHT_MODE;

////////////////////////////////////////////////////////////////////////////
//                     �t�@�C���ԃC���^�[�t�F�[�X�֐�
////////////////////////////////////////////////////////////////////////////
// �e�N�X�`���o�b�t�@�擾
extern TEXTURE_DATA* GetTextureBuf(int idx);
// �R�c�f�o�C�X�擾
extern LPDIRECT3DDEVICE8  GetD3DDevice(void);
extern LPDIRECT3DDEVICE8 g_pD3DDevice;

////////////////////////////////////////////////////////////////////////////
//                             �O���Q�Ɛ錾
////////////////////////////////////////////////////////////////////////////
// �_�C���N�g�O���t�B�b�N�X�������֐�
extern BOOL GrpInit(HWND hwnd);
// �_�C���N�g�O���t�B�b�N�X�J���֐�
extern void GrpRelease(void);

// �e�N�X�`�����[�h�����֐�
extern BOOL GrpLoadTexture(int idx, char *bmp_name, D3DCOLOR rgba = 0);
// �e�N�X�`���J�������֐�
extern void GrpReleaseTexture(int idx);

// �X�v���C�g������
extern void GrpSprInit(void);
// �X�v���C�g�q�f�a�`�Z�b�g
extern void GrpSprRGBASet(BLEND_MODE mode, D3DCOLOR rgba);
// �X�v���C�g��]�p�Z�b�g
extern void GrpSprAngleSet(float angle, float cx, float cy);
// �X�v���C�g�X�P�[���Z�b�g
extern void GrpSprScaleSet(float sx, float sy);
// �X�v���C�g�`��
extern void GrpSprDraw(int x, int y, int idx, int u, int v, int w, int h);

// �P�F�|���S���\��
extern void GrpPolyDraw(float x, float y, float w, float h, D3DCOLOR rgba);
// �e�o�r�\��
extern void GrpFpsDisp(int x, int y);
// �t�H���g�\���֐�
extern void GrpFontDisp(char *str, int x, int y, D3DCOLOR color);

// �����ϊ��s��̐ݒ�
extern void GrpSetProjMat(float clip_near, float clip_far);
// �J�����s��̐ݒ�
extern void GrpSetViewMat(D3DXVECTOR3 eye, D3DXVECTOR3 pos);
// �r���{�[�g�p�}�g���b�N�X�ݒ�
extern void GrpSetBillBoardMat(D3DXMATRIX &wmat, D3DXVECTOR3 &t);
// ���W�n�}�g���b�N�X�v�Z�֐�
extern void GrpSetRotTransMat(D3DXMATRIX &wmat, D3DXVECTOR3 &s, D3DXVECTOR3 &t, D3DXVECTOR3 &r);
// ���C�g�̏������A�n�m / �n�e�e�؂�ւ�
extern void GrpSetLight(D3DLIGHT_MODE mode);
// �t�H�O�̐ݒ�
extern void GrpSetFog(float st, float end, D3DCOLOR col);
// �R�c���W�@���@�Q�c���W�ϊ�
extern void GrpVecCnv2d(D3DXVECTOR3* out_vec, D3DXVECTOR3* cnv_vec, D3DXMATRIX* world);
// ���������A���W�ϊ��������_���Z�b�g
extern inline void GrpTLVertexSet(D3DTLVERTEX *v, float x, float y, float z, float tu, float tv, D3DCOLOR rgba);
// ���������A���W�ϊ��L�蒸�_���Z�b�g
extern inline void GrpLVertexSet(D3DLVERTEX *v, float x, float y, float z, float tu, float tv, D3DCOLOR rgba);
// �����L��A���W�ϊ��L�蒸�_���Z�b�g
extern inline void GrpVertexSet(D3DVERTEX *v, float x, float y, float z, float nx, float ny, float nz, float tu, float tv);

////////////////////////////////////////////////////////////////////////////
//                             �N���X�錾
////////////////////////////////////////////////////////////////////////////
// ���W�n�Ǘ��N���X
class D3D_COORDINATE {
public:
	D3DXVECTOR3		scale;							// �X�P�[��
	D3DXVECTOR3		trans;							// �ړ��x�N�g��
	D3DXVECTOR3		rotate;							// ��]�x�N�g��
	D3DXMATRIX		mat;							// ���W�n�̕ϊ��}�g���b�N�X
public:
	// �R���X�g���N�^�i�x�N�g���̏��������s���j
	D3D_COORDINATE() {}
	D3D_COORDINATE(D3DXVECTOR3 s, D3DXVECTOR3 t, D3DXVECTOR3 r) {
		SetVect(s, t, r);
	}

	void SetVect(D3DXVECTOR3 s, D3DXVECTOR3 t, D3DXVECTOR3 r) {
		scale  = s;
		trans  = t;
		rotate = r;
		SetMat();
	}
	// �X�P�[������]���ړ��ϊ��ς݃}�g���b�N�X�쐬
	void SetMat(void) {
		// GrpSetRotTransMat�́A�^�����X�P�[���x�N�g���A�ړ��x�N�g���A��]�x�N�g������
		// mat = �X�P�[��mat  �~�@�i�x��]mat�@�~�@�w��]mat�@�~�@�y��]mat�j�@�~�@�ړ�mat�@
		// �Ƃ������ϊ��}�g���b�N�X�𐶐����܂�
		// �܂�A�X�P�[�� -> ��] -> �ړ� �ƌ��������ŏ������s�����}�g���b�N�X���쐬���܂��B
		GrpSetRotTransMat(mat, scale, trans, rotate);
	}
};

#endif

