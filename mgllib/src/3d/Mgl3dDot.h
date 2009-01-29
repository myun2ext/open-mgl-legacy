//////////////////////////////////////////////////////////
//
//	Mgl3dDot - ���G��N���X
//
//////////////////////////////////////////////////////////

#ifndef __Mgl3dDot_H__
#define __Mgl3dDot_H__

#include "MglGraphicManager.h"
#include "MglVertexManager.h"

////////////////////////////////////

//	FVF Define
#define	FVF_MGL_DOT ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE )

//	Vertex Struct
class MGL_DOT_VERTEX
{
public:
	float		x,y,z;
	D3DCOLOR	color;
	float		point;	//	�_�̑傫��
	// ---------------------------------------------
	MGL_DOT_VERTEX(){
		x = y = z = 0.0f;
		color = 0;
		point = 1.0f;
	}
	static DWORD GetFVF(){ return FVF_MGL_DOT; }
};

//	DLL Exports (inhibit for C4275)
DLL_TMPL_EXP CMglVertexManagerT<MGL_DOT_VERTEX>;
DLL_TMPL_EXP CMglVertexManagerXT<MGL_DOT_VERTEX>;

/////////////////////////////////////////////////////////////////////

//	�N���X�錾
class DLL_EXP CMgl3dDots : public CMglVertexManagerXT<MGL_DOT_VERTEX>
{
protected:
	CMglGraphicManager* m_myudg;	//	DG�N���X�ւ̃|�C���^���i�[
	IDirect3DDevice8* m_d3d;			//	D3DDevice�ւ̃|�C���^

	//	�������\�b�h�i�`�F�b�N�p�j
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMgl3dDots();
	virtual ~CMgl3dDots(){}

	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
};

#endif//__Mgl3dDot_H__
