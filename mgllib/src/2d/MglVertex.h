#ifndef __MglVertex_H__
#define __MglVertex_H__

#include "MglGraphicUtil.h"

#define _MGLVERTEX_USE_SPECULAR
#define _MGLVERTEX_USE_NORMAL
#define _MGLVERTEX_USE_MULTITEX
#define _MGLVERTEX_USE_VECTOR3

#ifdef _MGLVERTEX_USE_NORMAL
	#define _MGLVERTEX_D3DFVF_NORMAL D3DFVF_NORMAL
#else
	#define _MGLVERTEX_D3DFVF_NORMAL
#endif

#ifdef _MGLVERTEX_USE_MULTITEX
	#define _MGLVERTEX_D3DFVF_TEX_EXTENDS D3DFVF_TEX8 
#else
	#define _MGLVERTEX_D3DFVF_TEX_EXTENDS D3DFVF_TEX1
#endif

//	���_�\����
#ifdef _MGLVERTEX_USE_RHW
	//#define	FVF_MYU_VERTEX ( D3DFVF_XYZRHW | _MGLVERTEX_D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1 )
	#define	FVF_MYU_VERTEX ( D3DFVF_XYZRHW | _MGLVERTEX_D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | _MGLVERTEX_D3DFVF_TEX_EXTENDS )
#else
	//#define	FVF_MYU_VERTEX ( D3DFVF_XYZ | _MGLVERTEX_D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1 )
	#define	FVF_MYU_VERTEX ( D3DFVF_XYZ | _MGLVERTEX_D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | _MGLVERTEX_D3DFVF_TEX_EXTENDS )
#endif
typedef struct
{
	//float		x,y,z;				//�ʒu���
	D3DXVECTOR3 pos;				// ���������̕����F�X�֐����Ă���ۂ��ėǂ������ˁE�E�E
#ifdef _MGLVERTEX_USE_RHW
	float		rhw;				//���_�ϊ��l
#endif
#ifdef _MGLVERTEX_USE_NORMAL
	//float		nx, ny, nz;			// �@���x�N�g��
	D3DXVECTOR3	normal;				// �@���x�N�g��
#endif
	D3DCOLOR	color;				// �|���S���J���[
#ifdef _MGLVERTEX_USE_SPECULAR
	D3DCOLOR	specular;			// �X�y�L�����F
#endif
#ifdef _MGLVERTEX_USE_MULTITEX
	D3DXVECTOR2 tPosAry[8];			//�e�N�X�`�����W�z��
#else
	float		tu,tv;				//�e�N�X�`�����W - D3DXVECTOR2
#endif
}MYU_VERTEX;
typedef MYU_VERTEX	MGL_VERTEX;


typedef struct
{
	float		x,y,z;				//�ʒu���
	float		rhw;				//���_�ϊ��l
	D3DCOLOR	color;				// �|���S���J���[
	float		tu,tv;				//�e�N�X�`�����W - D3DXVECTOR2
}MYU_VERTEX_SIMPLE1;
typedef MYU_VERTEX_SIMPLE1 MGL_VERTEX1, MGL_VERTEX_SIMPLE, MGL_VERTEX_SIMPLE1;
typedef MYU_VERTEX_SIMPLE1 MYU_VERTEX1, MYU_VERTEX_SIMPLE, MYU_VERTEX_SIMPLE1;

#define	FVF_MYU_VERTEX1		( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

/*
typedef struct
{
	float		x,y,z;				//�ʒu���
#ifdef _MGLVERTEX_USE_RHW
	float		rhw;				//���_�ϊ��l
#endif
#ifdef _MGLVERTEX_USE_NORMAL
	//float		nx, ny, nz;			// �@���x�N�g��
	D3DXVECTOR3	normal;				// �@���x�N�g��
#endif
	D3DCOLOR	color;				// �|���S���J���[
#ifdef _MGLVERTEX_USE_SPECULAR
	D3DCOLOR	specular;			// �X�y�L�����F
#endif
#ifdef _MGLVERTEX_USE_MULTITEX
	float		tu,tv;				//�e�N�X�`�����W - D3DXVECTOR2
	D3DXVECTOR2 tPosAry[7];			//�e�N�X�`�����W�z��
#else
#endif
}MYU_VERTEX1;
typedef MYU_VERTEX1	MGL_VERTEX1;
*/


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
#ifdef _MGLVERTEX_USE_VECTOR3
		//normal = D3DXVECTOR3(0,1,0); ���̕����������E�E�E
		pos.x = pos.y = pos.z = 0.0f;
#else
		x = y = z = 0.0f;
#endif
#ifdef _MGLVERTEX_USE_RHW
		float = 1.0f;
#endif
		color = D3DCOLOR_BLACK;
#ifdef _MGLVERTEX_USE_SPECULAR
		specular = 0;
#endif
#ifdef _MGLVERTEX_USE_NORMAL
  #ifdef _MGLVERTEX_USE_VECTOR3
		//normal.y = 1;
		//normal = D3DXVECTOR3(0,1,0); ���̕����������E�E�E
		normal.x = 0;
		normal.y = 1;
		normal.z = 0;
  #else
		nx = 0;
		ny = 1;
		nz = 0;
  #endif
#endif
#ifdef _MGLVERTEX_USE_MULTITEX
		ZeroMemory(&tPosAry, sizeof(tPosAry));
#else
		tu = tv = 0.0f;
#endif
	}

	static DWORD GetFVF(){ return FVF_MYU_VERTEX; }
#ifdef _MGLVERTEX_USE_MULTITEX
	void SetTuTv(MGLTUTV tutv){ SetTuTv(0, tutv); }
	void SetTuTv(int no, MGLTUTV tutv){
		tPosAry[no].x = tutv.tu;
		tPosAry[no].y = tutv.tv;
	}
#else
	void SetTuTv(MGLTUTV tutv){
		tu = tutv.tu;
		tv = tutv.tv;
	}
#endif
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

DLL_EXP void MglMoveVertexs( MGL_VERTEX *pVertexs, float x, float y, float z, int vertexCount );
DLL_EXP void MglVertexsFillColor( MGL_VERTEX *pVertexs, D3DCOLOR color, int vertexCount );

inline void MglMoveVertexs( MGL_SQUARE_VERTEXS *pVertexs, float x, float y, float z=0 ){
	MglMoveVertexs( (MGL_VERTEX*)pVertexs, x, y, z, 4 ); }
inline void MglVertexsFillColor( MGL_SQUARE_VERTEXS *pVertexs, D3DCOLOR color ){
	MglVertexsFillColor( (MGL_VERTEX*)pVertexs, color, 4 ); }

#endif//__MglVertex_H__
