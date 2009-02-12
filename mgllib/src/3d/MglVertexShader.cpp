#include "stdafx.h"
#include "MglVertexShader.h"

class CMglVertexShaderDeclaration
{
protected:
	std::vector<DWORD> m_list;
public:
	//	コンストラクタ
	CMglVertexShaderDeclaration(){
		Clear();
	}
	void Clear(){
		m_list.clear();
		Add(D3DVSD_STREAM(0));
	}

	void Add(DWORD dw){ m_list.push_back(dw); }
	void InsertEnd(){
		Add(D3DVSD_END());
	}

	void CreateFromFVF(DWORD dwFvf){
		if ( dwFvf & D3DFVF_POSITION_MASK != 0 )
			Add( D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_FLOAT3 ) );

		/*if ( dwFvf & D3DFVF_XYZRHW != 0 )
			Add( D3DVSD_REG(D3DVSDE_POSITION2, D3DDECLTYPE_FLOAT4 ) );

		else if ( dwFvf & D3DFVF_XYZ != 0 )
			Add( D3DVSD_REG(D3DVSDE_POSITION, D3DDECLTYPE_FLOAT3 ) );*/

		if ( dwFvf & D3DFVF_NORMAL != 0 )
			Add( D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_FLOAT3 ) );

		if ( dwFvf & D3DFVF_PSIZE != 0 )
			Add( D3DVSD_REG(D3DVSDE_PSIZE, D3DVSDT_FLOAT1 ) );

		if ( dwFvf & D3DFVF_DIFFUSE != 0 )
			Add( D3DVSD_REG(D3DVSDE_DIFFUSE, D3DVSDT_D3DCOLOR ) );

		if ( dwFvf & D3DFVF_SPECULAR != 0 )
			Add( D3DVSD_REG(D3DVSDE_SPECULAR, D3DVSDT_D3DCOLOR ) );

		///////////////////////////////////////////////////////////

		switch(dwFvf & D3DFVF_TEXCOUNT_MASK)
		{
		case D3DFVF_TEX0:
			Add( D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_FLOAT2 ) );
			break;
		case D3DFVF_TEX1:
			Add( D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_FLOAT2 ) );
			break;
		case D3DFVF_TEX2:
			Add( D3DVSD_REG(D3DVSDE_TEXCOORD2, D3DVSDT_FLOAT2 ) );
			break;
		case D3DFVF_TEX3:
			Add( D3DVSD_REG(D3DVSDE_TEXCOORD3, D3DVSDT_FLOAT2 ) );
			break;
		case D3DFVF_TEX4:
			Add( D3DVSD_REG(D3DVSDE_TEXCOORD4, D3DVSDT_FLOAT2 ) );
			break;
		case D3DFVF_TEX5:
			Add( D3DVSD_REG(D3DVSDE_TEXCOORD5, D3DVSDT_FLOAT2 ) );
			break;
		case D3DFVF_TEX6:
			Add( D3DVSD_REG(D3DVSDE_TEXCOORD6, D3DVSDT_FLOAT2 ) );
			break;
		case D3DFVF_TEX7:
			Add( D3DVSD_REG(D3DVSDE_TEXCOORD7, D3DVSDT_FLOAT2 ) );
			break;
		}
	}

	DWORD* Get(){ return &m_list[0]; }
};

/*

#define D3DVSDE_BLENDWEIGHT     1
#define D3DVSDE_BLENDINDICES    2
#define D3DVSDE_POSITION2       15
#define D3DVSDE_NORMAL2         16



D3DFVF_XYZ	D3DDECLTYPE_FLOAT3	D3DDECLUSAGE_POSITION	0
D3DFVF_XYZRHW	D3DDECLTYPE_FLOAT4	D3DDECLUSAGE_POSITIONT	0
D3DFVF_XYZW	D3DDECLTYPE_FLOAT4	D3DDECLUSAGE_POSITIONT	0
D3DFVF_XYZB5 および D3DFVF_LASTBETA_UBYTE4	D3DVSDT_FLOAT3、D3DVSDT_FLOAT4、D3DVSDT_UBYTE4	D3DDECLUSAGE_POSITION、D3DDECLUSAGE_BLENDWEIGHT、D3DDECLUSAGE_BLENDINDICES	0
D3DFVF_XYZB5	D3DDECLTYPE_FLOAT3、D3DDECLTYPE_FLOAT4、D3DDECLTYPE_FLOAT1	D3DDECLUSAGE_POSITION、D3DDECLUSAGE_BLENDWEIGHT、D3DDECLUSAGE_BLENDINDICES	0
D3DFVF_XYZBn (n=1..4)	D3DDECLTYPE_FLOAT3、D3DDECLTYPE_FLOATn	D3DDECLUSAGE_POSITION、D3DDECLUSAGE_BLENDWEIGHT	0
D3DFVF_XYZBn (n=1..4) および D3DFVF_LASTBETA_UBYTE4	D3DDECLTYPE_FLOAT3、D3DDECLTYPE_FLOAT(n-1)、D3DDECLTYPE_UBYTE4	D3DDECLUSAGE_POSITION、D3DDECLUSAGE_BLENDWEIGHT、D3DDECLUSAGE_BLENDINDICES	0
D3DFVF_NORMAL	D3DDECLTYPE_FLOAT3	D3DDECLUSAGE_NORMAL	0
D3DFVF_PSIZE	D3DDECLTYPE_FLOAT1	D3DDECLUSAGE_PSIZE	0
D3DFVF_DIFFUSE	D3DDECLTYPE_D3DCOLOR	D3DDECLUSAGE_COLOR	0
D3DFVF_SPECULAR	D3DDECLTYPE_D3DCOLOR	D3DDECLUSAGE_COLOR	1
D3DFVF_TEXCOORDSIZEm(n)	D3DDECLTYPE_FLOATm	D3DDECLUSAGE_TEXCOORD

D3DDECLUSAGE_POSITION	0 	D3DVSDE_POSITION
D3DDECLUSAGE_POSITION	1 	D3DVSDE_POSITION2
D3DDECLUSAGE_BLENDWEIGHT	0 	D3DVSDE_BLENDWEIGHT
D3DDECLUSAGE_BLENDINDICES	0 	D3DVSDE_BLENDINDICES
D3DDECLUSAGE_NORMAL	0 	D3DVSDE_NORMAL
D3DDECLUSAGE_NORMAL	1 	D3DVSDE_NORMAL2
D3DDECLUSAGE_PSIZE	0 	D3DVSDE_PSIZE
D3DDECLUSAGE_COLOR	0 	D3DVSDE_DIFFUSE
D3DDECLUSAGE_COLOR	1 	D3DVSDE_SPECULAR
D3DDECLUSAGE_TEXCOORD	n	D3DVSDE_TEXTUREn, n <= 7
*/


////////////////////////////////////////////////////////////////////////

//	コンストラクタ
CMglVertexShader::CMglVertexShader()
{
	m_pShader = NULL;
	m_dwFvf = 0;
}

//	開放
void CMglVertexShader::Release()
{
#if _MGL_DXVER == 9	//	DirectXでは”ただのハンドル”ですので・・・
	SAFE_RELEASE(m_pShader);
#endif
	ReleaseShader();
}

//	アセンブルファイル読み込み
void CMglVertexShader::Load(const char* szShaderScriptFile)
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.Load(szShaderScriptFile);

	LoadCommon(loader.GetBuffer());
}

//	文字列から読み込み
void CMglVertexShader::LoadFromString( const char* szAssembleString )
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.LoadFromString(szAssembleString);

	LoadCommon(loader.GetBuffer());
}

//	Load共通
void CMglVertexShader::LoadCommon(CONST DWORD* pFunction)
{
#if _MGL_DXVER == 9	//	DirectXでは”ただのハンドル”ですので・・・
	MyuAssert2( m_d3d->CreateVertexShader( pFunction, &m_pShader ), D3D_OK,
		MGLMSGNO_SHADER(96), "CMglVertexShader::Load()  m_d3d->CreateVertexShader()に失敗" );
#else
	if ( m_dwFvf == 0 )
		MyuThrow( MGLMSGNO_SHADER(102), "CMglVertexShader::Load()  SetFVF() にて頂点フォーマットを指定してください。" );

	/*
    // バーテックスシェーダーを作成する
    DWORD dwDecl[] =
    {
        D3DVSD_STREAM(0),
        D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_FLOAT3 ),            //D3DVSDE_POSITION,  0  
        D3DVSD_REG(D3DVSDE_TEXCOORD0,D3DVSDT_FLOAT2 ),            //D3DVSDE_TEXCOORD0, 7  
        D3DVSD_END()
    };
	*/

	CMglVertexShaderDeclaration decl;
	decl.CreateFromFVF(m_dwFvf);

	MyuAssert2( m_d3d->CreateVertexShader( decl.Get(), pFunction, &m_pShader, 0 ), D3D_OK,
		MGLMSGNO_SHADER(96), "CMglVertexShader::Load()  m_d3d->CreateVertexShader()に失敗" );
#endif
}

//	シェーダを設定
void CMglVertexShader::SetShader()
{
	MyuAssert2( m_d3d->SetVertexShader(m_pShader), D3D_OK, 
		MGLMSGNO_SHADER(97), "CMglVertexShader::SetShader()  m_d3d->SetVertexShader()に失敗" );
}

//	ユーザシェーダを解除
void CMglVertexShader::UnsetShader()
{
	MyuAssert2( m_d3d->SetVertexShader(NULL), D3D_OK, 
		MGLMSGNO_SHADER(97), "CMglVertexShader::UnsetShader()  m_d3d->SetVertexShader()に失敗" );
}

//	パラメータ設定
void CMglVertexShader::SetShaderParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount)
{
	MyuAssert2( m_d3d->SetVertexShaderConstant( dwStartRegisterNo, (VOID*)lpData, dwDataBlockCount), D3D_OK,
		MGLMSGNO_SHADER(98), "CMglVertexShader::SetShaderParam()  m_d3d->SetVertexShaderConstant()に失敗" );
}

//	パラメータ設定
void CMglVertexShader::SetShaderParam(DWORD dwStartRegisterNo, CMglShaderParam &param)
{
	SetShaderParam( dwStartRegisterNo, param.GetHeadPtr(), param.GetCount() );
}
