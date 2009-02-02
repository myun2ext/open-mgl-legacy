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
	DWORD					m_dwMaterialCount;	// �}�e���A���̐�

	//-------------------------------------------------------------

	void CreatedCheck(){
		if ( m_pMesh != NULL )
			MyuThrow(MGLMSGNO_MESH(0), "CMglMesh::Load()  ���ɓǂݍ��ݍς݂ł��B"
				"�Ăѓǂݍ��ޏꍇ�ɂ͈�x Release() ���Ăяo������ǂݍ���ł��������B");
	}
	void CreateMaterials(){ CreateMaterials(m_dwMaterialCount); }
	void CreateMaterials(int nCount){
		m_pMeshMaterials = new _D3DMATERIALx[nCount];
		m_dwMaterialCount = nCount;
	}
	void CreateTextures(){ CreateTextures(m_dwMaterialCount); }
	void CreateTextures(int nCount){
		m_pMeshTextures = new _IDirect3DTextureX* [nCount];
		ZeroMemory(m_pMeshTextures, sizeof(LPVOID*)*nCount);
		m_dwMaterialCount = nCount;
	}

public:
	CMglMesh();
	virtual ~CMglMesh(){ Release(); }
	void Release();

	void Load(const char* szMeshFilePath);
	void LoadXFile(const char* szXFilePath){ Load(szXFilePath); }
	void Create(const char* szMeshFilePath){ Load(szMeshFilePath); }

	void Draw();

	//	�������b�V��
	void CreateBox(float fWidth, float fHeight, float fDepth,
		D3DCOLOR color=D3DCOLOR_WHITE, D3DCOLOR ambient=D3DCOLOR_WHITE,
		D3DCOLOR specular=D3DCOLOR_WHITE, float fPower=1.0f);

	//-------------------------------------------

	ID3DXMesh* GetMeshPtr(){ return m_pMesh; }
	ID3DXMesh* GetID3DXMeshPtr(){ return m_pMesh; }
	_D3DMATERIALx* GetMaterialArrayPtr(){ return m_pMeshMaterials; }
	_IDirect3DTextureX** GetTextureArrayPtr(){ return m_pMeshTextures; }
	DWORD GetMaterialCount(){ return m_dwMaterialCount; }

	_D3DMATERIALx* GetMaterial(int index){ return &m_pMeshMaterials[index]; }
};

typedef CMglMesh CMgl3dMesh;

#endif//__MglMesh_H__
