//////////////////////////////////////////////////////////
//
//	CMglMesh - ���b�V��
//
//////////////////////////////////////////////////////////

#ifndef __MglMesh_H__
#define __MglMesh_H__

#include "mglafx.h"
#include "MglGraphicManager.h"

//	�N���X�錾
class DLL_EXP CMglMesh : public CMglDgBase
{
protected:
	ID3DXMesh*				m_pMesh;			// ���b�V��
	_D3DMATERIALx*			m_pMeshMaterials;	// ���b�V���̎���
	_IDirect3DTextureX**	m_pMeshTextures;	// ���b�V���̃e�N�X�`���Q
	DWORD					m_dwNumMaterials;	// �}�e���A���̐�

public:
	CMglMesh();
	void Release();

	void Load(const char* szMeshFilePath);
	void LoadXFile(const char* szXFilePath){ Load(szXFilePath); }
	void Create(const char* szMeshFilePath){ Load(szMeshFilePath); }
};

typedef CMglMesh CMgl3dMesh;

#endif//__MglMesh_H__
