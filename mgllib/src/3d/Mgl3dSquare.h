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

#pragma warning( disable : 4660 ) 

//	�N���X�錾
class DLL_EXP CMgl3dSquare : public CMglVertexManagerX
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
	CMgl3dSquare();
	virtual ~CMgl3dSquare(){}

	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
};

#endif//__Mgl3dSquare_H__
