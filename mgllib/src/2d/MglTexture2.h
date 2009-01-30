//////////////////////////////////////////////////////////
//
//	MglTexture2 - �e�N�X�`���Ǘ��N���X
//
//	�Ȃ��ACreateTextureFromFile() �ō쐬���ꂽ�e�N�X�`����
//	�O�p�`��񖇑g�ݍ��킹���l�p�`�ł���̂ł��̎��ɒ��ӂ��ꂽ���I

#ifndef __MglTexture2_H__
#define __MglTexture2_H__

#include "MglD3dTexture.h"
#include "MglVertexManager.h"


//	�N���X�錾
class DLL_EXP CMglTexture2// : public CMyuReleaseBase
{
protected:
	CMglGraphicManager* m_myudg;	//	DG�N���X�ւ̃|�C���^���i�[

	//	Direct3D�n
	_MGL_IDirect3DDevice* d3d;			//	D3DDevice�ւ̃|�C���^

	//	�������\�b�h�i�`�F�b�N�p�j
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglTexture2();
	virtual ~CMglTexture2(){ Release(); }

	//	�������ƊJ��
	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	void Release();

};

#endif//__MglTexture2_H__
