//////////////////////////////////////////////////////////
//
//	Mgl3dDot - ���G��N���X
//
//////////////////////////////////////////////////////////

#ifndef __Mgl3dDot_H__
#define __Mgl3dDot_H__

#include "MglGraphicManager.h"
//#include "MglTexture.h"

//	�N���X�錾
class DLL_EXP CMgl3dDots
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
