//////////////////////////////////////////////////////////
//
//	Mgl3dSquare - ���G��N���X
//
//////////////////////////////////////////////////////////

#ifndef __Mgl3dSquare_H__
#define __Mgl3dSquare_H__

#include "MglGraphicManager.h"
#include "MglVertexManager.h"
//#include "MglTexture.h"

//#pragma warning( disable : 4660 )

//	Vertex Struct
class MGL_NOTEX_VERTEX
{
public:
	float		x,y,z;
	D3DCOLOR	color;
	// ---------------------------------------------
	MGL_NOTEX_VERTEX(){
		x = y = z = 0.0f;
		color = 0;
	}
	static DWORD GetFVF(){ return D3DFVF_XYZ | D3DFVF_DIFFUSE; }
};

//	�N���X�錾
//class DLL_EXP CMgl3dSquare : public CMglVertexManagerXT<MGL_NOTEX_VERTEX>
class DLL_EXP CMgl3dSquare : public CMglVertexManagerX
{
public:
	typedef CMyuVertex _VERTEX;

protected:
	CMglGraphicManager* m_myudg;	//	DG�N���X�ւ̃|�C���^���i�[
	_MGL_IDirect3DDevice* m_d3d;			//	D3DDevice�ւ̃|�C���^

	//	�������\�b�h�i�`�F�b�N�p�j
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMgl3dSquare();
	virtual ~CMgl3dSquare(){}

	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	void SimpleCreate(float fWidth, float fHeight, D3DCOLOR color);

	void Draw(){ CMglVertexManagerX::Draw(D3DPT_TRIANGLESTRIP); }		//	D3DPT_TRIANGLESTRIP���ƍŌ�̒��_�̐F���ςɂȂ�񂾂�˂��E�E�E�Ȃ�ł��낤�˂��E�E�E
	//void Draw(){ CMglVertexManagerX::Draw(D3DPT_TRIANGLEFAN); }
	//void Draw(){ CMglVertexManagerXT<MGL_NOTEX_VERTEX>::Draw(D3DPT_TRIANGLESTRIP); }
};

#endif//__Mgl3dSquare_H__
