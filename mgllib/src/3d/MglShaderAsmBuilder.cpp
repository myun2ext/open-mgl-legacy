#include "stdafx.h"
#include "MglShaderAsmBuilder.h"

//	コンストラクタ
CMglShaderAsmBuilder::CMglShaderAsmBuilder()
{
	m_pShader = NULL;
	m_dwFvf = 0;
}

//	開放
void CMglShaderAsmBuilder::Release()
{
#if _MGL_DXVER == 9	//	DirectXでは”ただのハンドル”ですので・・・
	SAFE_RELEASE(m_pShader);
#endif
	ReleaseShader();
}

//	アセンブルファイル読み込み
void CMglShaderAsmBuilder::Load(const char* szShaderScriptFile)
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.Load(szShaderScriptFile);

	LoadCommon(loader.GetBuffer());
}

//	文字列から読み込み
void CMglShaderAsmBuilder::LoadFromString( const char* szAssembleString )
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.LoadFromString(szAssembleString);

	LoadCommon(loader.GetBuffer());
}

//	Load共通
void CMglShaderAsmBuilder::LoadCommon(CONST DWORD* pFunction)
{
#if _MGL_DXVER == 9	//	DirectXでは”ただのハンドル”ですので・・・
	MyuAssert2( m_d3d->CreateVertexShader( pFunction, &m_pShader ), D3D_OK,
		MGLMSGNO_SHADER(96), "CMglShaderAsmBuilder::Load()  m_d3d->CreateVertexShader()に失敗" );
#else
	if ( m_dwFvf == 0 )
		MyuThrow( MGLMSGNO_SHADER(102), "CMglShaderAsmBuilder::Load()  SetFVF() にて頂点フォーマットを指定してください。" );

    // バーテックスシェーダーを作成する
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
		MGLMSGNO_SHADER(96), "CMglShaderAsmBuilder::Load()  m_d3d->CreateVertexShader()に失敗" );
#endif
}

//	シェーダを設定
void CMglShaderAsmBuilder::SetShader()
{
	InitCheck();
	CreateCheck();

	MyuAssert2( m_d3d->SetVertexShader(m_pShader), D3D_OK, 
		MGLMSGNO_SHADER(97), "CMglShaderAsmBuilder::SetShader()  m_d3d->SetVertexShader()に失敗" );
}

//	ユーザシェーダを解除
void CMglShaderAsmBuilder::UnsetShader()
{
	if ( m_d3d != NULL && m_pShader != NULL )
		MyuAssert2( m_d3d->SetVertexShader(NULL), D3D_OK, 
			MGLMSGNO_SHADER(97), "CMglShaderAsmBuilder::UnsetShader()  m_d3d->SetVertexShader()に失敗" );
}

//	パラメータ設定
void CMglShaderAsmBuilder::SetShaderParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount)
{
	InitCheck();
	CreateCheck();

	MyuAssert2( m_d3d->SetVertexShaderConstant( dwStartRegisterNo*4, (VOID*)lpData, dwDataBlockCount*4), D3D_OK,
		MGLMSGNO_SHADER(98), "CMglShaderAsmBuilder::SetShaderParam()  m_d3d->SetVertexShaderConstant()に失敗" );
}

//	パラメータ設定
void CMglShaderAsmBuilder::SetShaderParam(DWORD dwStartRegisterNo, CMglShaderAsmBuilderParam &param) {
	SetShaderParam( dwStartRegisterNo, param.GetHeadPtr(), param.GetCount() );
}
