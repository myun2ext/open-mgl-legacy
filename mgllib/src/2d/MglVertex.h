#ifndef __MglVertex_H__
#define __MglVertex_H__

#include "MglGraphicUtil.h"

//#define _MGLVERTEX_USE_RHW

//	���_�\����
#ifdef _MGLVERTEX_USE_RHW
	#define	FVF_MYU_VERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1 )
#else
	#define	FVF_MYU_VERTEX ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1 )
#endif
typedef struct
{
	float		x,y,z;				//�ʒu���
	//D3DXVECTOR3 pos;		// ���������̕����F�X�֐����Ă���ۂ��ėǂ������ˁE�E�E
#ifdef _MGLVERTEX_USE_RHW
	float		rhw;				//���_�ϊ��l
#endif
	//float		nx, ny, nz;			// �@���x�N�g��
	D3DCOLOR	color;				//�|���S���J���[
	DWORD		specular;			// �X�y�L�����F
	float		tu,tv;				//�e�N�X�`�����W - D3DXVECTOR2
}MYU_VERTEX;
typedef MYU_VERTEX	MGL_VERTEX;

//////////////////////////////////////////////////////

class CMglVertexBase {
private:
	//DWORD m_dwFvf;
public:
	//CMglVertexBase(DWORD dwFvf)
	//virtual DWORD GetFVF() = 0;
};

typedef class CMyuVertex : public MGL_VERTEX, CMglVertexBase {
public:
	CMyuVertex(){
		x = y = z = 0.0f;
#ifdef _MGLVERTEX_USE_RHW
		float = 1.0f;
#endif
		color = 0;
		specular = 0;
		tu = tv = 0.0f;
	}

	static DWORD GetFVF(){ return FVF_MYU_VERTEX; }
} MGLX_VERTEX, MYUX_VERTEX;

/*
//+++++++++++++++++++++++++++++++++++++++++++++
//	���_�\����2 (2009/01/10
//+++++++++++++++++++++++++++++++++++++++++++++
#define	FVF_MYU_VERTEX2 ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1 )
typedef struct
{
	float		x,y,z;				//�ʒu���
	//D3DXVECTOR3 pos;		// ���������̕����F�X�֐����Ă���ۂ��ėǂ������ˁE�E�E
	D3DCOLOR	color;				//�|���S���J���[
	DWORD		specular;			// �X�y�L�����F
	float		tu,tv;				//�e�N�X�`�����W
}MYU_VERTEX2;
typedef MYU_VERTEX2	MGL_VERTEX2;
typedef MYU_VERTEX2	MGL_VERTEX_3D;
*/


//	���g���Ă˂����E�E�E
/*typedef struct
{
	float		drawX,drawY,drawZ;	//�ʒu���
	float		rhw;				//���_�ϊ��l
	D3DCOLOR	color;				//�|���S���J���[
	float		textureX,textureY;
}MYU_VERTEX2;*/

//typedef MYU_VERTEX2	MGL_VERTEX2;

//	�l�p�`�̒��_
typedef struct
{
	MGL_VERTEX lt;	//	0 - Left Top: ����
	MGL_VERTEX rt;	//	1 - Right Top: �E��
	MGL_VERTEX rb;	//	2 - Right Bottom: �E��
	MGL_VERTEX lb;	//	3 - Left Bottom: ����
}
MGL_SQUARE_VERTEXS;
typedef MGL_SQUARE_VERTEXS MGL_SQ_VERTEXS;

/*
//	�l�p�`�̒��_
typedef struct
{
	MGL_VERTEX2 lt;	//	0
	MGL_VERTEX2 rt;	//	1
	MGL_VERTEX2 rb;	//	2
	MGL_VERTEX2 lb;	//	3
}
MGL_SQUARE_VERTEXS2;
typedef MGL_SQUARE_VERTEXS2 MGL_SQ_VERTEXS2;
*/

#ifdef _MGLVERTEX_USE_RHW
	DLL_EXP void MglVertexGen( MGL_VERTEX *pVertexOut, float x, float y, float z, float tu, float tv,
							  D3DCOLOR color=D3DCOLOR_WHITE, float rhw=1.0f );
#else
	DLL_EXP void MglVertexGen( MGL_VERTEX *pVertexOut, float x, float y, float z, float tu, float tv,
							  D3DCOLOR color=D3DCOLOR_WHITE );
#endif

#define MGL_VERTEX_SIZE		(sizeof(MYU_VERTEX))
#define MGL_VERTEXES_SIZE	(sizeof(MYU_VERTEX)*4)

//	�����Ɏg���Ă镔��������̂Ŏc���Ă���
#define MGL_VERTEXNO_LT		(0)
#define MGL_VERTEXNO_RT		(1)
#define MGL_VERTEXNO_LB		(3)
#define MGL_VERTEXNO_RB		(2)

//	���_�F
typedef struct
{
	D3DCOLOR leftTop;
	D3DCOLOR leftBottom;
	D3DCOLOR rightTop;
	D3DCOLOR rightBottom;
}
MGL_VERTEX_COLORS;

//// Methods //////////////////////////////////////////////////////////////////////////////

//DLL_EXP void MglMoveVertexs( MGL_VERTEX *pVertexs, float x, float y, int vertexCount );
DLL_EXP void MglMoveVertexs( MGL_VERTEX *pVertexs, float x, float y, float z, int vertexCount );
DLL_EXP void MglVertexsFillColor( MGL_VERTEX *pVertexs, D3DCOLOR color, int vertexCount );

inline void MglMoveVertexs( MGL_SQUARE_VERTEXS *pVertexs, float x, float y, float z=0 ){
	MglMoveVertexs( (MGL_VERTEX*)pVertexs, x, y, z, 4 ); }
inline void MglVertexsFillColor( MGL_SQUARE_VERTEXS *pVertexs, D3DCOLOR color ){
	MglVertexsFillColor( (MGL_VERTEX*)pVertexs, color, 4 ); }

#endif//__MglVertex_H__
