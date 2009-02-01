#include "stdafx.h"
#include "MglMesh.h"

//	コンストラクタ
CMglMesh::CMglMesh()
{
	m_pMesh          = NULL;
	m_pMeshMaterials = NULL;
	m_pMeshTextures  = NULL;
	m_dwNumMaterials = 0L;
}

//	Xファイル読み込み
void CMglMesh::Load(const char* szMeshFilePath)
{
	InitCheck();

	if ( m_pMesh != NULL )
		MyuThrow(678025, "CMglMesh::Load()  既に読み込み済みです。"
			"再び読み込む場合には一度 Release() を呼び出した後読み込んでください。");

	////////////////////////////////////////////

	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	//	X ファイルのロード
	MyuAssert( D3DXLoadMeshFromX( (char*)szMeshFilePath, D3DXMESH_SYSTEMMEM, 
								   m_d3d, NULL, 
								   &pD3DXMtrlBuffer, &m_dwNumMaterials, 
								   &m_pMesh ), D3D_OK,
		"CMglMesh::Load()  D3DXLoadMeshFromX()に失敗" );

	// pD3DXMtrlBuffer から、質感やテクスチャーの情報を読み取る
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMeshMaterials = new _D3DMATERIALx[m_dwNumMaterials];
	m_pMeshTextures  = new _IDirect3DTextureX* [m_dwNumMaterials];

	for( DWORD i=0; i < m_dwNumMaterials; i++ ){
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;// 質感のコピー
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;// マテリアルの環境色を設定する
	 
		MyuAssert( D3DXCreateTextureFromFile( m_d3d, 
										d3dxMaterials[i].pTextureFilename, 
										&m_pMeshTextures[i] ), D3D_OK,
			"CMglMesh::Load()  D3DXCreateTextureFromFile()に失敗" );
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
	EzMsgBox("Release()");

	//	メッシュマテリアルの解放
	SAFE_DELETE_ARY(m_pMeshMaterials);

	//	テクスチャの解放
	if( m_pMeshTextures )
	{
		for( DWORD i=0; i < m_dwNumMaterials; i++ )
			SAFE_RELEASE( m_pMeshTextures[i] );
	
		SAFE_DELETE_ARRAY( m_pMeshTextures );
	}

	//	メッシュの開放
	SAFE_RELEASE( m_pMesh );
}

