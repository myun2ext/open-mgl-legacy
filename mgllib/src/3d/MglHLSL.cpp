#include "stdafx.h"
#include "MglHLSL.h"

//	�R���X�g���N�^
CMglHlsl::CMglHlsl()
{
	m_pBufShader = NULL;
	m_pBufErrorInfo = NULL;
}

//	�J��
void CMglHlsl::Release()
{
	SAFE_RELEASE(m_pBufShader);
	SAFE_RELEASE(m_pBufErrorInfo);
}

//	X�t�@�C���ǂݍ���
void CMglHlsl::Load(const char* szShaderScriptFile)
{
	InitCheck();
	CreatedCheck();

	//	�t�@�C�����{���ɂ��邩�ǂ����H
	if ( !msl::IsExistFile(szShaderScriptFile) )
		MyuThrow(MGLMSGNO_SHADER(2), "CMglHlsl::Load()  �t�@�C�� \"%s\" �͌�����܂���B", szShaderScriptFile);

	//	�A�Z���u���t�@�C���ǂݍ��݁[
	/*MyuAssert2( D3DXAssembleShaderFromFile( szShaderScriptFile, 0, NULL, &m_pBufShader, &m_pBufErrorInfo ), D3D_OK, <- �Ȃ�GetCompileErrorMsg()����Ɏ��s����Ă��܂��炵���E�E�E�܂��œK���Ƃ��ł��ˁE�E�E
		MGLMSGNO_SHADER(12), "CMglHlsl::Load()  D3DXAssembleShaderFromFile()�Ɏ��s\r\n\r\n%s", GetCompileErrorMsg() );*/
	HRESULT hr = D3DXAssembleShaderFromFile( szShaderScriptFile, 0, NULL, &m_pBufShader, &m_pBufErrorInfo );
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(13), "CMglHlsl::LoadFromString()  ���̃G���[�̂��� D3DXAssembleShader() �͎��s���܂����B\r\n\r\n%s", GetCompileErrorMsg() );
}

//	X�t�@�C���ǂݍ���
void CMglHlsl::LoadFromString(const char* szAssembleString)
{
	InitCheck();
	CreatedCheck();

	//	�A�Z���u���t�@�C���ǂݍ��݁[
	/*MyuAssert2( D3DXAssembleShader( szAssembleString, strlen(szAssembleString), <- �Ȃ�GetCompileErrorMsg()����Ɏ��s����Ă��܂��炵���E�E�E�܂��œK���Ƃ��ł��ˁE�E�E
		0, NULL, &m_pBufShader, &m_pBufErrorInfo ), D3D_OK,
		MGLMSGNO_SHADER(13), "CMglHlsl::LoadFromString()  D3DXAssembleShader()�Ɏ��s\r\n\r\n%s", GetCompileErrorMsg() );*/
	//	�A�Z���u���t�@�C���ǂݍ��݁[
	HRESULT hr = D3DXAssembleShader( szAssembleString, strlen(szAssembleString),
		0, NULL, &m_pBufShader, &m_pBufErrorInfo );
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(13), "CMglHlsl::LoadFromString()  ���̃G���[�̂��� D3DXAssembleShader() �͎��s���܂����B\r\n\r\n%s", GetCompileErrorMsg() );
}

//	�G���[���b�Z�[�W�擾
const char* CMglHlsl::GetCompileErrorMsg()
{
	if ( m_pBufErrorInfo == NULL )
		return "(No Error Buffer.)";

	return (const char*) m_pBufErrorInfo->GetBufferPointer();
}

//	�o�b�t�@�擾
CONST DWORD* CMglHlsl::GetBuffer()
{
	InitCheck();
	CreateCheck();

	return (CONST DWORD*) m_pBufShader->GetBufferPointer();
}

