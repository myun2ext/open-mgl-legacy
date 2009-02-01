//////////////////////////////////////////////////////////
//
//	CMglMesh - メッシュ
//
//////////////////////////////////////////////////////////

#ifndef __MglMesh_H__
#define __MglMesh_H__

#include "mglafx.h"
#include "MglGraphicManager.h"

//	クラス宣言
class DLL_EXP CMglMesh : public CMglDgBase
{
protected:
	ID3DXMesh*				m_pMesh;			// メッシュ
	_D3DMATERIALx*			m_pMeshMaterials;	// メッシュの質感
	_IDirect3DTextureX**	m_pMeshTextures;	// メッシュのテクスチャ群
	DWORD					m_dwNumMaterials;	// マテリアルの数

public:
	CMglMesh();
	void Release();

	void Load(const char* szMeshFilePath);
	void LoadXFile(const char* szXFilePath){ Load(szXFilePath); }
	void Create(const char* szMeshFilePath){ Load(szMeshFilePath); }
};

typedef CMglMesh CMgl3dMesh;

#endif//__MglMesh_H__
