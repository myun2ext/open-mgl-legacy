#include "stdafx.h"
#include "MglVertexShader.h"

//	�R���X�g���N�^
CMglVertexShader::CMglVertexShader()
{
	m_pShader = NULL;
}

//	�J��
void CMglVertexShader::Release()
{
#if _MGL_DXVER == 9	//	DirectX�ł́h�����̃n���h���h�ł��̂ŁE�E�E
	SAFE_RELEASE(m_pShader);
#endif
}

//	�A�Z���u���t�@�C���ǂݍ���
void CMglVertexShader::Load(const char* szShaderScriptFile)
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.Load(szShaderScriptFile);

	LoadCommon(loader.GetBuffer());
}

//	�����񂩂�ǂݍ���
void CMglVertexShader::LoadFromString( const char* szAssembleString )
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.LoadFromString(szAssembleString);

	LoadCommon(loader.GetBuffer());
}

//	Load����
void CMglVertexShader::LoadCommon(CONST DWORD* pFunction)
{
#if _MGL_DXVER == 9	//	DirectX�ł́h�����̃n���h���h�ł��̂ŁE�E�E
	MyuAssert2( m_d3d->CreateVertexShader( pFunction, &m_pShader ), D3D_OK,
		MGLMSGNO_SHADER(96), "CMglVertexShader::LoadCommon()  m_d3d->CreateVertexShader()�Ɏ��s" );
#else
	MyuAssert2( m_d3d->CreateVertexShader( pFunction, &m_pShader ), D3D_OK,
		MGLMSGNO_SHADER(96), "CMglVertexShader::LoadCommon()  m_d3d->CreateVertexShader()�Ɏ��s" );
#endif
}

//	�V�F�[�_��ݒ�
void CMglVertexShader::SetShader()
{
	MyuAssert2( m_d3d->SetVertexShader(m_pShader), D3D_OK, 
		MGLMSGNO_SHADER(97), "CMglVertexShader::SetShader()  m_d3d->SetVertexShader()�Ɏ��s" );
}

//	�p�����[�^�ݒ�
void CMglVertexShader::SetShaderParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount)
{
	MyuAssert2( m_d3d->SetVertexShaderConstant( dwStartRegisterNo, (VOID*)lpData, dwDataBlockCount), D3D_OK,
		MGLMSGNO_SHADER(98), "CMglVertexShader::SetShaderParam()  m_d3d->SetVertexShaderConstant()�Ɏ��s" );
}

//	�p�����[�^�ݒ�
void CMglVertexShader::SetShaderParam(DWORD dwStartRegisterNo, CMglShaderParam &param)
{
	SetShaderParam( dwStartRegisterNo, param.GetHeadPtr(), param.GetCount() );
}
