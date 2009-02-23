#include "stdafx.h"
#include "MglHLSL.h"

//	�R���X�g���N�^
CMglHlsl::CMglHlsl()
{
	m_pEffect = NULL;
	m_pBufErrorInfo = NULL;
}

//	�J��
void CMglHlsl::Release()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pBufErrorInfo);
}

//	�G�t�F�N�g�t�@�C���ǂݍ���
void CMglHlsl::Load(const char* szShaderScriptFile)
{
	InitCheck();
	CreatedCheck();

	//	�t�@�C�����{���ɂ��邩�ǂ����H
	if ( !msl::IsExistFile(szShaderScriptFile) )
		MyuThrow(MGLMSGNO_SHADER(202), "CMglHlsl::Load()  �t�@�C�� \"%s\" �͌�����܂���B", szShaderScriptFile);

	//	�A�Z���u���t�@�C���ǂݍ��݁[
	/*MyuAssert2( D3DXAssembleShaderFromFile( szShaderScriptFile, 0, NULL, &m_pEffect, &m_pBufErrorInfo ), D3D_OK, <- �Ȃ�GetCompileErrorMsg()����Ɏ��s����Ă��܂��炵���E�E�E�܂��œK���Ƃ��ł��ˁE�E�E
		MGLMSGNO_SHADER(12), "CMglHlsl::Load()  D3DXAssembleShaderFromFile()�Ɏ��s\r\n\r\n%s", GetCompileErrorMsg() );*/
	HRESULT hr = D3DXCreateEffectFromFile( m_d3d, szShaderScriptFile, &m_pEffect, &m_pBufErrorInfo );
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(213), "CMglHlsl::Load()  ���̃G���[�̂��� D3DXCreateEffectFromFile() �͎��s���܂����B\r\n\r\n%s", GetCompileErrorMsg() );
}

//	�����񂩂�ǂݍ���
void CMglHlsl::LoadFromString(const char* szAssembleString)
{
	InitCheck();
	CreatedCheck();

	//	�A�Z���u���t�@�C���ǂݍ��݁[
	/*MyuAssert2( D3DXAssembleShader( szAssembleString, strlen(szAssembleString), <- �Ȃ�GetCompileErrorMsg()����Ɏ��s����Ă��܂��炵���E�E�E�܂��œK���Ƃ��ł��ˁE�E�E
		0, NULL, &m_pEffect, &m_pBufErrorInfo ), D3D_OK,
		MGLMSGNO_SHADER(13), "CMglHlsl::LoadFromString()  D3DXAssembleShader()�Ɏ��s\r\n\r\n%s", GetCompileErrorMsg() );*/
	//	�A�Z���u���t�@�C���ǂݍ��݁[
	HRESULT hr = D3DXCreateEffect( m_d3d, szAssembleString, strlen(szAssembleString), &m_pEffect, &m_pBufErrorInfo );
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(213), "CMglHlsl::LoadFromString()  ���̃G���[�̂��� D3DXCreateEffect() �͎��s���܂����B\r\n\r\n%s", GetCompileErrorMsg() );
}

//	�G���[���b�Z�[�W�擾
const char* CMglHlsl::GetCompileErrorMsg()
{
	if ( m_pBufErrorInfo == NULL )
		return "(No Error Buffer.)";

	return (const char*) m_pBufErrorInfo->GetBufferPointer();
}

//	�o�b�t�@�擾
_MGL_ID3DXEffect_* CMglHlsl::GetBuffer()
{
	InitCheck();
	CreateCheck();

	return m_pEffect;
}

