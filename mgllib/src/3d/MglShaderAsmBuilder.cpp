#include "stdafx.h"
#include "MglShaderAsmBuilder.h"

//	�R���X�g���N�^
CMglShaderAsmBuilder::CMglShaderAsmBuilder()
{
	m_pShader = NULL;
	m_dwFvf = 0;
}

//	�J��
void CMglShaderAsmBuilder::Release()
{
#if _MGL_DXVER == 9	//	DirectX�ł́h�����̃n���h���h�ł��̂ŁE�E�E
	SAFE_RELEASE(m_pShader);
#endif
	ReleaseShader();
}

//	�A�Z���u���t�@�C���ǂݍ���
void CMglShaderAsmBuilder::Load(const char* szShaderScriptFile)
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.Load(szShaderScriptFile);

	LoadCommon(loader.GetBuffer());
}

//	�����񂩂�ǂݍ���
void CMglShaderAsmBuilder::LoadFromString( const char* szAssembleString )
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.LoadFromString(szAssembleString);

	LoadCommon(loader.GetBuffer());
}

//	Load����
void CMglShaderAsmBuilder::LoadCommon(CONST DWORD* pFunction)
{
#if _MGL_DXVER == 9	//	DirectX�ł́h�����̃n���h���h�ł��̂ŁE�E�E
	MyuAssert2( m_d3d->CreateVertexShader( pFunction, &m_pShader ), D3D_OK,
		MGLMSGNO_SHADER(96), "CMglShaderAsmBuilder::Load()  m_d3d->CreateVertexShader()�Ɏ��s" );
#else
	if ( m_dwFvf == 0 )
		MyuThrow( MGLMSGNO_SHADER(102), "CMglShaderAsmBuilder::Load()  SetFVF() �ɂĒ��_�t�H�[�}�b�g���w�肵�Ă��������B" );

    // �o�[�e�b�N�X�V�F�[�_�[���쐬����
    DWORD dwDecl[] =
    {
        D3DVSD_STREAM(0),
        D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_FLOAT3 ),            //D3DVSDE_POSITION,  0  
        D3DVSD_REG(D3DVSDE_TEXCOORD0,D3DVSDT_FLOAT2 ),            //D3DVSDE_TEXCOORD0, 7  
        D3DVSD_REG(D3DVSDE_TEXCOORD7,D3DVSDT_FLOAT2 ),            //D3DVSDE_TEXCOORD0, 7  
        D3DVSD_END()
    };

	CMglShaderAsmBuilderDeclaration decl;
	decl.CreateFromFVF(m_dwFvf);
	/*decl.Add( D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_FLOAT3 ) );
	decl.Add( D3DVSD_REG(D3DVSDE_DIFFUSE, D3DVSDT_D3DCOLOR ) );
	decl.Add( D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_FLOAT3 ) );
	decl.Add( D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_FLOAT2 ) );
	decl.Add( D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_FLOAT2 ) );
	decl.Add( D3DVSD_REG(D3DVSDE_TEXCOORD2, D3DVSDT_FLOAT2 ) );
	decl.Add( D3DVSD_REG(D3DVSDE_TEXCOORD3, D3DVSDT_FLOAT2 ) );
	decl.Add( D3DVSD_REG(D3DVSDE_TEXCOORD4, D3DVSDT_FLOAT2 ) );
	decl.Add( D3DVSD_REG(D3DVSDE_TEXCOORD6, D3DVSDT_FLOAT2 ) );
	decl.Add( D3DVSD_REG(D3DVSDE_TEXCOORD7, D3DVSDT_FLOAT2 ) );
	decl.InsertEnd();*/

	MyuAssert2( m_d3d->CreateVertexShader( decl.Get(), pFunction, &m_pShader, 0 ), D3D_OK,
	//MyuAssert2( m_d3d->CreateVertexShader( dwDecl, pFunction, &m_pShader, 0 ), D3D_OK,
		MGLMSGNO_SHADER(96), "CMglShaderAsmBuilder::Load()  m_d3d->CreateVertexShader()�Ɏ��s" );
#endif
}

//	�V�F�[�_��ݒ�
void CMglShaderAsmBuilder::SetShader()
{
	InitCheck();
	CreateCheck();

	MyuAssert2( m_d3d->SetVertexShader(m_pShader), D3D_OK, 
		MGLMSGNO_SHADER(97), "CMglShaderAsmBuilder::SetShader()  m_d3d->SetVertexShader()�Ɏ��s" );
}

//	���[�U�V�F�[�_������
void CMglShaderAsmBuilder::UnsetShader()
{
	if ( m_d3d != NULL && m_pShader != NULL )
		MyuAssert2( m_d3d->SetVertexShader(NULL), D3D_OK, 
			MGLMSGNO_SHADER(97), "CMglShaderAsmBuilder::UnsetShader()  m_d3d->SetVertexShader()�Ɏ��s" );
}

//	�p�����[�^�ݒ�
void CMglShaderAsmBuilder::SetShaderParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount)
{
	InitCheck();
	CreateCheck();

	MyuAssert2( m_d3d->SetVertexShaderConstant( dwStartRegisterNo*4, (VOID*)lpData, dwDataBlockCount*4), D3D_OK,
		MGLMSGNO_SHADER(98), "CMglShaderAsmBuilder::SetShaderParam()  m_d3d->SetVertexShaderConstant()�Ɏ��s" );
}

//	�p�����[�^�ݒ�
void CMglShaderAsmBuilder::SetShaderParam(DWORD dwStartRegisterNo, CMglShaderAsmBuilderParam &param) {
	SetShaderParam( dwStartRegisterNo, param.GetHeadPtr(), param.GetCount() );
}
