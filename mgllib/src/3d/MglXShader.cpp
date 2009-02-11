#include "stdafx.h"
#include "MglXShader.h"

//	�R���X�g���N�^
CMglXShader::CMglXShader()
{
	m_pBufShader = NULL;
	m_pBufErrorInfo = NULL;
}

//	�J��
void CMglXShader::Release()
{
	SAFE_RELEASE(m_pBufShader);
	SAFE_RELEASE(m_pBufErrorInfo);
}

//	X�t�@�C���ǂݍ���
void CMglXShader::Load(const char* szShaderScriptFile)
{
	InitCheck();
	CreatedCheck();

	//	�t�@�C�����{���ɂ��邩�ǂ����H
	if ( !msl::IsExistFile(szShaderScriptFile) )
		MyuThrow(MGLMSGNO_SHADER(2), "CMglXShader::Load()  �t�@�C�� \"%s\" �͌�����܂���B", szShaderScriptFile);

	//	�A�Z���u���t�@�C���ǂݍ��݁[
	MyuAssert2( D3DXAssembleShaderFromFile( szShaderScriptFile, 0, NULL, &m_pBufShader, &m_pBufErrorInfo ), D3D_OK,
		MGLMSGNO_SHADER(12), "CMglXShader::Load()  D3DXAssembleShaderFromFile()�Ɏ��s\r\n\r\n%s", GetCompileErrorMsg() );
}

//	X�t�@�C���ǂݍ���
void CMglXShader::LoadFromString(const char* szAssembleString)
{
	InitCheck();
	CreatedCheck();

	//	�A�Z���u���t�@�C���ǂݍ��݁[
	MyuAssert2( D3DXAssembleShader( szAssembleString, strlen(szAssembleString),
		0, NULL, &m_pBufShader, &m_pBufErrorInfo ), D3D_OK,
		MGLMSGNO_SHADER(13), "CMglXShader::LoadFromString()  D3DXAssembleShader()�Ɏ��s\r\n\r\n%s", GetCompileErrorMsg() );
}

//	�G���[���b�Z�[�W�擾
const char* CMglXShader::GetCompileErrorMsg()
{
	if ( m_pBufErrorInfo == NULL )
		return "";

	return (const char*) m_pBufErrorInfo->GetBufferPointer();
}

//	�o�b�t�@�擾
CONST DWORD* CMglXShader::GetBuffer()
{
	InitCheck();
	CreateCheck();

	return (CONST DWORD*) m_pBufShader->GetBufferPointer();
}

