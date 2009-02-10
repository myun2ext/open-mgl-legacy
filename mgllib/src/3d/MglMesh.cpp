#include "stdafx.h"
#include "MglMesh.h"

//	�R���X�g���N�^
CMglMesh::CMglMesh()
{
	m_pMesh          = NULL;
	m_pMeshMaterials = NULL;
	m_pMeshTextures  = NULL;
	m_dwMaterialCount = 0L;
}

//	X�t�@�C���ǂݍ���
void CMglMesh::Load(const char* szMeshFilePath)
{
	InitCheck();
	CreatedCheck();

	//	�t�@�C�����{���ɂ��邩�ǂ����H
	if ( !msl::IsExistFile(szMeshFilePath) )
		MyuThrow(MGLMSGNO_MESH(2), "CMglMesh::Load()  ���b�V���t�@�C�� \"%s\" �͌�����܂���B", szMeshFilePath);

	////////////////////////////////////////////

	//	X �t�@�C���̃��[�h
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	MyuAssert2( D3DXLoadMeshFromX( (char*)szMeshFilePath, D3DXMESH_SYSTEMMEM, 
								   m_d3d, NULL, 
								   &pD3DXMtrlBuffer, &m_dwMaterialCount, 
								   &m_pMesh ), D3D_OK,
		MGLMSGNO_MESH(4), "CMglMesh::Load()  D3DXLoadMeshFromX()�Ɏ��s" );

	// pD3DXMtrlBuffer ����A������e�N�X�`���[�̏���ǂݎ��
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMeshMaterials = new _D3DMATERIALx[m_dwMaterialCount];
	m_pMeshTextures  = new _IDirect3DTextureX* [m_dwMaterialCount];
	ZeroMemory(m_pMeshTextures, sizeof(LPVOID*)*m_dwMaterialCount);

	for( DWORD i=0; i < m_dwMaterialCount; i++ )
	{
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;// �����̃R�s�[
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;// �}�e���A���̊��F��ݒ肷��
	 
		const char* szTextureFile = d3dxMaterials[i].pTextureFilename;
		if ( szTextureFile != NULL )
		{
			MyuAssert2( D3DXCreateTextureFromFile( m_d3d, 
											szTextureFile, 
											&m_pMeshTextures[i] ), D3D_OK,
				MGLMSGNO_MESH(5), "CMglMesh::Load()  D3DXCreateTextureFromFile(\"%s\")�Ɏ��s",
				szTextureFile);
		}
	}

	SAFE_RELEASE(pD3DXMtrlBuffer);

	//////////////////////////////////////////////////////
	
	/*
	lpD3DDEV->SetRenderState( D3DRS_ZENABLE, TRUE);
	
	D3DXVECTOR3 vecDir;
	D3DLIGHT8 light;
	ZeroMemory( &light, sizeof(D3DLIGHT8) );
	light.Type	   = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r  = 1.0f;
	light.Diffuse.g  = 0.3f;
	light.Diffuse.b  = 0.3f;
	vecDir = D3DXVECTOR3(-1.0f, -1.0f, -0.1f);
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
	light.Range	   = 1000.0f;
	lpD3DDEV->SetLight( 0, &light );
	lpD3DDEV->LightEnable( 0, TRUE );
	lpD3DDEV->SetRenderState( D3DRS_LIGHTING, TRUE );
	lpD3DDEV->SetRenderState( D3DRS_AMBIENT, 0x00202020 );
	*/
}

void CMglMesh::Release()
{
	//InitCheck(); <- �ʂɂ���Ȃ����BSAFE_RELEASE()����NULL�`�F�b�N���Ă�񂾂��B
	//EzMsgBox("Release()");

	//	���b�V���}�e���A���̉��
	SAFE_DELETE_ARY(m_pMeshMaterials);

	//	�e�N�X�`���̉��
	if( m_pMeshTextures )
	{
		for( DWORD i=0; i < m_dwMaterialCount; i++ )
			SAFE_RELEASE( m_pMeshTextures[i] );
	
		SAFE_DELETE_ARRAY( m_pMeshTextures );
	}

	//	���b�V���̊J��
	SAFE_RELEASE( m_pMesh );
}

//	�`��
void CMglMesh::Draw()
{
	InitCheck();
	if ( m_pMesh == NULL )
		MyuThrow(MGLMSGNO_MESH(3), "CMglMesh::Draw()  ���b�V�����ǂݍ��݁A�܂��͍쐬����Ă��܂���B");

	for( DWORD i=0; i < m_dwMaterialCount; i++ )
	{
		if ( m_pMeshMaterials != NULL )
			MyuAssert2( m_pD3dDev->SetMaterial( &m_pMeshMaterials[i] ), D3D_OK,
				MGLMSGNO_MESH(129), "CMglMesh::Draw()  m_pD3dDev->SetMaterial()�Ɏ��s" );

		if ( m_pMeshTextures != NULL && m_pMeshTextures[i] != NULL )
			MyuAssert2( m_pD3dDev->SetTexture( 0, m_pMeshTextures[i] ), D3D_OK,
				MGLMSGNO_MESH(130), "CMglMesh::Draw()  m_pD3dDev->SetTexture()�Ɏ��s" );

		MyuAssert2( m_pMesh->DrawSubset( i ), D3D_OK,
			MGLMSGNO_MESH(128), "CMglMesh::Draw()  m_pMesh->DrawSubset()�Ɏ��s" );
	}
}

/////////////////////////////////////////////////

//	���p�`���b�V���쐬
/*void CMglMesh::CreatePolygon(float fSideSize, float fHeight, float fDepth,
		D3DXCOLOR color, D3DXCOLOR ambient, D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower)
{
	InitCheck();
	CreatedCheck();

	MyuAssert2( D3DXCreatePolygon( m_d3d, fSideSize, fHeight, fDepth, &m_pMesh, NULL), D3D_OK,
		MGLMSGNO_MESH(32), "CMglMesh::CreateBox()  D3DXCreateBox()�Ɏ��s" );

        LPDIRECT3DDEVICE8   pDevice,
        FLOAT               Length, 
        UINT                Sides, 
        LPD3DXMESH*         ppMesh,
        LPD3DXBUFFER*       ppAdjacency);

	///////////////////////////////////////////////////////////////

	CreateMaterials(1);

	_D3DMATERIALx* pMat = this->GetMaterial(0);
	pMat->Diffuse = color;
	pMat->Ambient = ambient;
	pMat->Specular = specular;
	pMat->Emissive = emissive;
	pMat->Power = fSpecularPower;
}*/

//	�����b�V���쐬
void CMglMesh::CreateBox(float fWidth, float fHeight, float fDepth,
		D3DXCOLOR color, D3DXCOLOR ambient, D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower)
{
	InitCheck();
	CreatedCheck();

	MyuAssert2( D3DXCreateBox( m_d3d, fWidth, fHeight, fDepth, &m_pMesh, NULL), D3D_OK,
		MGLMSGNO_MESH(32), "CMglMesh::CreateBox()  D3DXCreateBox()�Ɏ��s" );

	///////////////////////////////////////////////////////////////

	//m_dwMaterialCount = 1;
	CreateMaterials(1);

	_D3DMATERIALx* pMat = this->GetMaterial(0);
	/*pMat->Ambient = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pMat->Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pMat->Specular = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pMat->Power = 20.0f;*/
	/*pMat->Diffuse = D3DXCOLOR(color);
	pMat->Ambient = D3DXCOLOR(ambient);
	pMat->Specular = D3DXCOLOR(specular);*/
	pMat->Diffuse = color;
	pMat->Ambient = ambient;
	pMat->Specular = specular;
	pMat->Emissive = emissive;
	pMat->Power = fSpecularPower;
}

//	�~�����b�V���쐬
void CMglMesh::CreateCylinderEx(float fWidthNear, float fWidthFar, float fHeight,
		D3DXCOLOR color, D3DXCOLOR ambient, D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower,
		UINT nDetailCount, UINT nVerticalVertexCount)
{
	InitCheck();
	CreatedCheck();

	float fRadiusNear = fWidthNear/2;
	float fRadiusFar = fWidthFar/2;

	if ( nDetailCount < 3 )
		nDetailCount = 3;

	if ( nVerticalVertexCount < 1 )
		nVerticalVertexCount = 1;

	//	�~���쐬
	MyuAssert2( D3DXCreateCylinder( m_d3d, fRadiusNear, fRadiusFar, fHeight,
		nDetailCount, nVerticalVertexCount, &m_pMesh, NULL), D3D_OK,
		MGLMSGNO_MESH(40), "CMglMesh::CreateCylinderEx()  D3DXCreateCylinder()�Ɏ��s" );

	//	�}�e���A���쐬
	CreateSingleMaterial(color,ambient,specular,emissive,fSpecularPower);
}

//	Teapot���b�V���쐬
void CMglMesh::CreateTeapot(
		D3DXCOLOR color, D3DXCOLOR ambient, D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower)
{
	InitCheck();
	CreatedCheck();

	MyuAssert2( D3DXCreateTeapot( m_d3d, &m_pMesh, NULL), D3D_OK,
		MGLMSGNO_MESH(72), "CMglMesh::CreateTeapot()  D3DXCreateTeapot()�Ɏ��s" );

	CreateSingleMaterial(color,ambient,specular,emissive,fSpecularPower);
}

//	�h�[�i�c���b�V���쐬
void CMglMesh::CreateDonutEx(float fSize, float fRingDiameter, UINT nCircleDetail, UINT nCylinderDetail,
		D3DXCOLOR color, D3DXCOLOR ambient, D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower)
{
	InitCheck();
	CreatedCheck();

	if ( fRingDiameter > fSize )
		MyuThrow( MGLMSGNO_MESH(81), "fRingDiameter �� fSize �𒴂��邱�Ƃ͏o���܂���B");

	float fInnerRadius = fRingDiameter/2;
	float fOuterRadius = fSize/2-fInnerRadius;

	if ( nCircleDetail < 3 )
		nCircleDetail = 3;
	if ( nCylinderDetail < 3 )
		nCylinderDetail = 3;

	//	�h�[�i�c����
	MyuAssert2( D3DXCreateTorus( m_d3d, fInnerRadius, fOuterRadius,
		nCylinderDetail, nCircleDetail, &m_pMesh, NULL), D3D_OK,
		MGLMSGNO_MESH(80), "CMglMesh::CreateDonut()  D3DXCreateTorus()�Ɏ��s" );

	CreateSingleMaterial(color,ambient,specular,emissive,fSpecularPower);
}

//	���̃��b�V���쐬
void CMglMesh::CreateSphereEx(float fSize, UINT nHorizontalDetail, UINT nVerticalDetail,
		D3DXCOLOR color, D3DXCOLOR ambient, D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower)
{
	InitCheck();
	CreatedCheck();

	float fRadius = fSize/2;

	if ( nHorizontalDetail < 2 )
		nHorizontalDetail = 2;
	if ( nVerticalDetail < 2 )
		nVerticalDetail = 2;

	//	���b�V������
	MyuAssert2( D3DXCreateSphere( m_d3d, fRadius,
		nHorizontalDetail, nVerticalDetail, &m_pMesh, NULL), D3D_OK,
		MGLMSGNO_MESH(80), "CMglMesh::CreateSphereEx()  D3DXCreateSphere()�Ɏ��s" );

	CreateSingleMaterial(color,ambient,specular,emissive,fSpecularPower);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	�ЂƂ[�����̃}�e���A���[�i��
void CMglMesh::CreateSingleMaterial(
	D3DXCOLOR color, D3DXCOLOR ambient, D3DXCOLOR specular, D3DXCOLOR emissive, float fSpecularPower)
{
	//m_dwMaterialCount = 1;
	CreateMaterials(1);

	_D3DMATERIALx* pMat = this->GetMaterial(0);
	pMat->Diffuse = color;
	pMat->Ambient = ambient;
	pMat->Specular = specular;
	pMat->Emissive = emissive;
	pMat->Power = fSpecularPower;
}
