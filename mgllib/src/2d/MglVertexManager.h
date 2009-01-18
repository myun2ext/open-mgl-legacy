#ifndef __MglVertexManager_H__
#define __MglVertexManager_H__

#include "MglGraphicManager.h"

//	�N���X�錾
template <typename _VERTEX = MYUX_VERTEX>
class CMglVertexManagerManagerXT : public CMglVertexManagerManagerT<_VERTEX>
{
protected:
	CMglGraphicManager* m_myudg;	//	DG�N���X�ւ̃|�C���^���i�[
	_MGL_IDirect3DDevice* d3d;		//	D3DDevice�ւ̃|�C���^

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglVertexManagerManagerXT(){
		m_myudg = NULL;
		d3d = NULL;
	}
	virtual ~CMglVertexManagerManagerXT(){ Release(); }

	//	�������ƊJ��
	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd ){
		m_myudg = in_myudg;
		d3d = m_myudg->GetD3dDevPtr();
	}
	void Release(){

	}

};

#endif//__MglVertexManager_H__
