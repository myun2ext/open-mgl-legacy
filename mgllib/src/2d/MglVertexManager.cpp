#include "stdafx.h"
#include "MglVertexManager.h"

//	�}�N����
#define CMglVertexManagerXT_CPPCL(_RETTYPE) template <typename _VERTEX> _RETTYPE CMglVertexManagerXT<_VERTEX>

//	�e�N�X�`���̐ݒ�
CMglVertexManagerXT_CPPCL(void)::SetD3dStageTexture(DWORD nStage)
{
	//	�e�N�X�`���̐ݒ�
	MyuAssert( d3d->SetTexture(nStage, m_pTexture), D3D_OK,
		"CMglVertexManagerXT::SetD3dTexture()  d3d->SetTexture()�Ɏ��s" );
}

CMglVertexManager g__CMglVertexManager_test;
CMglVertexManagerXT<> g__CMglVertexManagerX_test;
