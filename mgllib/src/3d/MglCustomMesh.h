//////////////////////////////////////////////////////////
//
//	CMglCustomMesh - メッシュ
//
//////////////////////////////////////////////////////////

#ifndef __MglCustomMesh_H__
#define __MglCustomMesh_H__

#include "mglafx.h"
#include "MglGraphicManager.h"

#define MGL_SPECULAR_POWER_DEFAULT	(2.0f)
#define MGL_MESH_DETAIL_DEFAULT		(16)
#define _MGL_SPD	(MGL_SPECULAR_POWER_DEFAULT)
#define _MGL_MDD	(MGL_MESH_DETAIL_DEFAULT)

//	クラス宣言
class DLL_EXP CMglCustomMesh : public CMglDgBase
{
protected:
	ID3DXMesh*				m_pMesh;			// メッシュ
	_D3DMATERIALx*			m_pMeshMaterials;	// メッシュの質感
	_IDirect3DTextureX**	m_pMeshTextures;	// メッシュのテクスチャ群
	DWORD					m_dwMaterialCount;	// マテリアルの数

	//-------------------------------------------------------------

	void CreatedCheck(){
		if ( m_pMesh != NULL )
			/*MyuThrow(MGLMSGNO_MESH(0), "CMglCustomMesh::Load()  既に読み込み済みです。"
				"再び読み込む場合には一度 Release() を呼び出した後読み込んでください。");*/
			MyuThrow(MGLMSGNO_MESH(0), "CMglCustomMesh  既にメッシュは作成済です。");
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
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD);

public:
	//	コンストラクタ・デストラクタ
	CMglCustomMesh();
	virtual ~CMglCustomMesh(){ Release(); }
	void Release();

	void Load(const char* szMeshFilePath);
	void LoadXFile(const char* szXFilePath){ Load(szXFilePath); }
	void Create(const char* szMeshFilePath){ Load(szMeshFilePath); }

	void Draw();

	//////////////////////////////////////////////////////////////////////////

	//	箱, 直方体メッシュ
	void CreateBox(float fWidth, float fHeight, float fDepth,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD);

	//	立方体メッシュ
	void CreateCube(float fSize,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD)
	{	CreateBox(fSize,fSize,fSize,color,ambient,specular,emissive,fSpecularPower); }

	//	円柱メッシュ
	void CreateCylinder(float fWidth, float fHeight,	
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD)
	{
		CreateCylinderEx(fWidth,fWidth,fHeight,color,ambient,specular,emissive,fSpecularPower);
	}
	void CreateCylinderEx(float fWidthNear, float fWidthFar, float fHeight,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD)
	{
		CreateCylinderEx(fWidthNear,fWidthFar,fHeight,color,ambient,specular,emissive,fSpecularPower,_MGL_MDD);
	}
	void CreateCylinderEx(float fWidthNear, float fWidthFar, float fHeight,
		D3DXCOLOR color, D3DXCOLOR ambient,
		D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower,
		UINT nDetailCount, UINT nVertical=1);

	//	円錐メッシュ
	void CreateCone(float fWidth, float fHeight,	
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD)
	{
		CreateCylinderEx(fWidth,0,fHeight,color,ambient,specular,emissive,fSpecularPower);
	}
	void CreateConeEx(float fWidth, float fHeight,
		D3DXCOLOR color, D3DXCOLOR ambient,
		D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower,
		UINT nDetailCount, UINT nVertical=1)
	{
		CreateCylinderEx(fWidth,0,fHeight,color,ambient,specular,emissive,fSpecularPower,nDetailCount,nVertical);
	}

	//	ドーナツメッシュ
	void CreateDonut(float fSize, float fRingDiameter,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD)
	{
		CreateDonutEx(fSize,fRingDiameter,_MGL_MDD,_MGL_MDD,color,ambient,specular,emissive,fSpecularPower);
	}
	void CreateDonutEx(float fSize, float fRingDiameter, UINT nCircleDetail, UINT nCylinderDetail,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD);

	//	球体メッシュ
	void CreateSphere(float fSize,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD)
	{
		CreateSphereEx(fSize,_MGL_MDD,_MGL_MDD,color,ambient,specular,emissive,fSpecularPower);
	}
	void CreateSphereEx(float fSize, UINT nHorizontalDetail, UINT nVerticalDetail,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD);

	//	お茶POTメッシュ
	void CreateTeapot(	
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD);


	void AppendTexture(const char* szTextureFile)
	{
		m_pMeshTextures  = new _IDirect3DTextureX* [1];
		ZeroMemory(m_pMeshTextures, sizeof(LPVOID*)*1);

		MyuAssert2( D3DXCreateTextureFromFile( m_d3d, 
										szTextureFile, 
										&m_pMeshTextures[0] ), D3D_OK,
				MGLMSGNO_MESH(5), "CMglCustomMesh::Load()  D3DXCreateTextureFromFile(\"%s\")に失敗",
				szTextureFile);
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

typedef CMglCustomMesh CMgl3dMesh;
typedef CMglCustomMesh CMgl3dModel;
typedef CMglCustomMesh CMgl3dShape;


/**************************************************************************************************/


//	CMgl3dBox - 直方体
class DLL_EXP CMgl3dBox : public CMglCustomMesh
{
public:
	void Create(float fWidth, float fHeight, float fDepth,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD)
	{
		CMglCustomMesh::CreateBox(fWidth,fHeight,fDepth,color,ambient,specular,emissive,fSpecularPower);
	}
};

//	CMgl3dCube - 立方体
class DLL_EXP CMgl3dCube : public CMglCustomMesh
{
public:
	void Create(float fSize,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD)
	{
		CMglCustomMesh::CreateCube(fSize,color,ambient,specular,emissive,fSpecularPower);
	}
};
typedef CMgl3dCube CMglCube, CMglCubeMesh;


//	CMgl3dCylinder - 円柱
class DLL_EXP CMgl3dCylinder : public CMglCustomMesh
{
public:
	void Create(float fWidth, float fHeight,	
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD)
	{
		CMglCustomMesh::CreateCylinder(fWidth,fHeight,color,ambient,specular,emissive,fSpecularPower);
	}
	void CreateEx(float fWidthNear, float fWidthFar, float fHeight,	
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD)
	{
		CMglCustomMesh::CreateCylinderEx(fWidthNear,fWidthFar,fHeight,color,ambient,specular,emissive,fSpecularPower);
	}
	void CreateCylinderEx(float fWidthNear, float fWidthFar, float fHeight,
		D3DXCOLOR color, D3DXCOLOR ambient,
		D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower,
		UINT nDetailCount, UINT nVertical=1)
	{
		CMglCustomMesh::CreateCylinderEx(fWidthNear,fWidthFar,fHeight,color,ambient,specular,emissive,fSpecularPower,nDetailCount,nVertical);
	}
};
typedef CMgl3dCylinder CMglCylinder, CMglCylinderMesh;


//	CMgl3dCone - 円錐
class DLL_EXP CMgl3dCone : public CMglCustomMesh
{
public:
	void Create(float fWidth, float fHeight,	
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD)
	{
		CMglCustomMesh::CreateCylinderEx(fWidth,0,fHeight,color,ambient,specular,emissive,fSpecularPower);
	}
	void CreateEx(float fWidth, float fHeight,
		D3DXCOLOR color, D3DXCOLOR ambient,
		D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower,
		UINT nDetailCount, UINT nVertical=1)
	{
		CMglCustomMesh::CreateCylinderEx(fWidth,0,fHeight,color,ambient,specular,emissive,fSpecularPower,nDetailCount,nVertical);
	}
};
typedef CMgl3dCone CMglCone, CMglConeMesh;


//	CMgl3dTeapot - お茶POT
class DLL_EXP CMgl3dTeapot : public CMglCustomMesh
{
public:
	void Create(
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK,
		D3DXCOLOR specular=D3DCOLOR_BLACK, D3DXCOLOR emissive=D3DCOLOR_BLACK, float fSpecularPower=_MGL_SPD)
	{
		CMglCustomMesh::CreateTeapot(color,ambient,specular,emissive,fSpecularPower);
	}
};
typedef CMgl3dTeapot CMglTeapot, CMglTeapotMesh;

#undef _MGL_SPD
#undef _MGL_MDD

#endif//__MglCustomMesh_H__
