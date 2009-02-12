#include "stdafx.h"
#include "MglPixelShader.h"

//	�R���X�g���N�^
CMglPixelShader::CMglPixelShader()
{
	m_pShader = NULL;
}

//	�J��
void CMglPixelShader::Release()
{
#if _MGL_DXVER == 9	//	DirectX�ł́h�����̃n���h���h�ł��̂ŁE�E�E
	SAFE_RELEASE(m_pShader);
#endif
}

//	�A�Z���u���t�@�C���ǂݍ���
void CMglPixelShader::Load(const char* szShaderScriptFile)
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.Load(szShaderScriptFile);

	LoadCommon(loader.GetBuffer());
}

//	�����񂩂�ǂݍ���
void CMglPixelShader::LoadFromString( const char* szAssembleString )
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.LoadFromString(szAssembleString);

	LoadCommon(loader.GetBuffer());
}

//	Load����
void CMglPixelShader::LoadCommon(CONST DWORD* pFunction)
{
	//	�쐬�[
	MyuAssert2( m_d3d->CreatePixelShader( pFunction, &m_pShader ), D3D_OK,
		MGLMSGNO_SHADER(13), "CMglPixelShader::LoadCommon()  m_d3d->CreatePixelShader()�Ɏ��s" );
}

//	�V�F�[�_��ݒ�
void CMglPixelShader::SetShader()
{
	InitCheck();
	CreateCheck();

	MyuAssert2( m_d3d->SetPixelShader(m_pShader), D3D_OK, 
		MGLMSGNO_SHADER(20), "CMglPixelShader::SetShader()  m_d3d->SetPixelShader()�Ɏ��s" );
}

//	���[�U�V�F�[�_������
void CMglPixelShader::UnsetShader()
{
	if ( m_d3d != NULL && m_pShader != NULL )
		MyuAssert2( m_d3d->SetPixelShader(NULL), D3D_OK, 
			MGLMSGNO_SHADER(21), "CMglPixelShader::UnsetShader()  m_d3d->SetPixelShader()�Ɏ��s" );
}

//	�p�����[�^�ݒ�
void CMglPixelShader::SetShaderParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount)
{
	InitCheck();
	CreateCheck();

	MyuAssert2( m_d3d->SetPixelShaderConstant( dwStartRegisterNo, (VOID*)lpData, dwDataBlockCount), D3D_OK,
		MGLMSGNO_SHADER(32), "CMglPixelShader::SetShaderParam()  m_d3d->SetPixelShaderConstant()�Ɏ��s" );
}

//	�p�����[�^�ݒ�
void CMglPixelShader::SetShaderParam(DWORD dwStartRegisterNo, CMglShaderParam &param) {
	SetShaderParam( dwStartRegisterNo, param.GetHeadPtr(), param.GetCount() );
}
