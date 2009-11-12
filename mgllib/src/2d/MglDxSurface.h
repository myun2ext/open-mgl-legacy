//////////////////////////////////////////////////////////
//
//	MglDxSurface - DirectX�̃T�[�t�F�X�Ǘ��N���X
//

#ifndef __MglDxSurface_H__
#define __MglDxSurface_H__

#include "MglGraphicManager.h"

//	�G�N�X�|�[�g
DLL_TMPL_EXP CMglDgIBase< _MGL_IDirect3DSurface >;

//	�N���X�錾
class DLL_EXP CMglDxSurface : public CMglDgIBase< _MGL_IDirect3DSurface >
{
protected:
	//CMglGraphicManager* m_myudg;	//	DG�N���X�ւ̃|�C���^���i�[

	//	Direct3D�n
	//_MGL_IDirect3DDevice* d3d;			//	D3DDevice�ւ̃|�C���^
	//_MGL_IDirect3DSurface* m_pSurface;	//	�T�[�t�F�X

	void CreateCheck() {
		InitCheck();	//	2008/06/28 ��������Ȃ��ƑʖڂłȂ��E�E�E�H
		//if ( createFlg == FALSE ){
		if ( m_pI == NULL )
			MyuThrow( 0, "CMglDxSurface ���쐬�ł���ɂ��ւ�炸������s�����Ƃ��܂����BCreate()�n���\�b�h���Ă�ł��������B" );
	}

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglDxSurface();
	virtual ~CMglDxSurface();

	//	�������ƊJ��
	
	void SetSurface( _MGL_IDirect3DSurface *pSurface ){
		m_pI = pSurface;
		m_pI->AddRef();
	}
	
	////////////////////////////////////////////////////////////////////////////
};


#endif//__MglDxSurface_H__
