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
	DWORD					m_dwMaterialCount;	// マテリアルの数

	//-------------------------------------------------------------

	void CreatedCheck(){
		if ( m_pMesh != NULL )
			/*MyuThrow(MGLMSGNO_MESH(0), "CMglMesh::Load()  既に読み込み済みです。"
				"再び読み込む場合には一度 Release() を呼び出した後読み込んでください。");*/
			MyuThrow(MGLMSGNO_MESH(0), "CMglMesh  既にメッシュは作成済です。");
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

	void CreateSingleMaterial(
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=2.0f);

public:
	//	コンストラクタ・デストラクタ
	CMglMesh();
	virtual ~CMglMesh(){ Release(); }
	void Release();

	void Load(const char* szMeshFilePath);
	void LoadXFile(const char* szXFilePath){ Load(szXFilePath); }
	void Create(const char* szMeshFilePath){ Load(szMeshFilePath); }

	void Draw();

	//////////////////////////////////////////////////////////////////////////

	//	箱, 直方体
	void CreateBox(float fWidth, float fHeight, float fDepth,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=2.0f);

	//	立方体
	void CreateCube(float fSize,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=2.0f)
	{ CreateBox(fSize,fSize,fSize,color,ambient,specular,emissive,fSpecularPower); }

	//	円柱
	void CreateCylinder(float fWidth, float fHeight,	
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=2.0f)
	{
		CreateCylinderEx(fWidth,fWidth,fHeight,color,ambient,specular,emissive,fSpecularPower);
	}
	void CreateCylinderEx(float fWidthNear, float fWidthFar, float fHeight,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=2.0f)
	{
		CreateCylinderEx(fWidthNear,fWidthFar,fHeight,color,ambient,specular,emissive,fSpecularPower,16);
	}
	void CreateCylinderEx(float fWidthNear, float fWidthFar, float fHeight,
		D3DXCOLOR color, D3DXCOLOR ambient,
		D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower,
		UINT nSideCount, UINT nVertical=1);

	//	円錐
	void CreateCone(float fWidth, float fHeight,	
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=2.0f)
	{
		CreateCylinderEx(fWidth,0,fHeight,color,ambient,specular,emissive,fSpecularPower);
	}
	void CreateConeEx(float fWidth, float fHeight,
		D3DXCOLOR color, D3DXCOLOR ambient,
		D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower,
		UINT nSideCount, UINT nVertical=1)
	{
		CreateCylinderEx(fWidth,0,fHeight,color,ambient,specular,emissive,fSpecularPower,nSideCount,nVertical);
	}

	////////////////////////////////////////////////////////////////

	//	specular -> mirror / reflect
	//	emissive -> emit
	//	fSpecularPower -> fMirrorRatio / fReflectRatio

	////////////////////////////////////////////////////////////////

	ID3DXMesh* GetMeshPtr(){ return m_pMesh; }
	ID3DXMesh* GetID3DXMeshPtr(){ return m_pMesh; }
	_D3DMATERIALx* GetMaterialArrayPtr(){ return m_pMeshMaterials; }
	_IDirect3DTextureX** GetTextureArrayPtr(){ return m_pMeshTextures; }
	DWORD GetMaterialCount(){ return m_dwMaterialCount; }

	_D3DMATERIALx* GetMaterial(int index){ return &m_pMeshMaterials[index]; }
};

typedef CMglMesh CMgl3dMesh;
typedef CMglMesh CMgl3dModel;
typedef CMglMesh CMgl3dShape;

//	CMgl3dBox - 直方体
class DLL_EXP CMgl3dBox : public CMglMesh
{
public:
	void Create(float fWidth, float fHeight, float fDepth,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=2.0f)
	{
		CMglMesh::CreateBox(fWidth,fHeight,fDepth,color,ambient,specular,emissive,fSpecularPower);
	}
};

//	CMgl3dCube - 立方体
class DLL_EXP CMgl3dCube : public CMglMesh
{
public:
	void Create(float fSize,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=2.0f)
	{
		CMglMesh::CreateCube(fSize,color,ambient,specular,emissive,fSpecularPower);
	}
};

//	CMgl3dCylinder - 円柱
class DLL_EXP CMgl3dCylinder : public CMglMesh
{
public:
	void Create(float fWidth, float fHeight,	
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=2.0f)
	{
		CMglMesh::CreateCylinder(fWidth,fHeight,color,ambient,specular,emissive,fSpecularPower);
	}
	void CreateEx(float fWidthNear, float fWidthFar, float fHeight,	
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=2.0f)
	{
		CMglMesh::CreateCylinderEx(fWidthNear,fWidthFar,fHeight,color,ambient,specular,emissive,fSpecularPower);
	}
	void CreateCylinderEx(float fWidthNear, float fWidthFar, float fHeight,
		D3DXCOLOR color, D3DXCOLOR ambient,
		D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower,
		UINT nSideCount, UINT nVertical=1)
	{
		CMglMesh::CreateCylinderEx(fWidthNear,fWidthFar,fHeight,color,ambient,specular,emissive,fSpecularPower,nSideCount,nVertical);
	}
};

//	CMgl3dCone - 円錐
class DLL_EXP CMgl3dCone : public CMglMesh
{
public:
	void Create(float fWidth, float fHeight,	
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=2.0f)
	{
		CMglMesh::CreateCylinderEx(fWidth,0,fHeight,color,ambient,specular,emissive,fSpecularPower);
	}
	void CreateEx(float fWidth, float fHeight,
		D3DXCOLOR color, D3DXCOLOR ambient,
		D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower,
		UINT nSideCount, UINT nVertical=1)
	{
		CMglMesh::CreateCylinderEx(fWidth,0,fHeight,color,ambient,specular,emissive,fSpecularPower,nSideCount,nVertical);
	}
};

#endif//__MglMesh_H__
