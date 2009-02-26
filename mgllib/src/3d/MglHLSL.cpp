#include "stdafx.h"
#include "MglHLSL.h"

//	�R���X�g���N�^
CMglHlsl::CMglHlsl()
{
	m_pEffect = NULL;
	m_pBufErrorInfo = NULL;

	m_nPassCount = 0;
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
	CreatedCheck();

	//	�t�@�C�����{���ɂ��邩�ǂ����H
	if ( !msl::IsExistFile(szShaderScriptFile) )
		MyuThrow(MGLMSGNO_SHADER(202), "CMglHlsl::Load()  �t�@�C�� \"%s\" �͌�����܂���B", szShaderScriptFile);

	//	�G�t�F�N�g�t�@�C���ǂݍ��݁[
	/*MyuAssert2( D3DXAssembleShaderFromFile( szShaderScriptFile, 0, NULL, &m_pEffect, &m_pBufErrorInfo ), D3D_OK, <- �Ȃ�GetCompileErrorMsg()����Ɏ��s����Ă��܂��炵���E�E�E�܂��œK���Ƃ��ł��ˁE�E�E
		MGLMSGNO_SHADER(12), "CMglHlsl::Load()  D3DXAssembleShaderFromFile()�Ɏ��s\r\n\r\n%s", GetCompileErrorMsg() );*/
	HRESULT hr = D3DXCreateEffectFromFile( m_d3d, szShaderScriptFile, &m_pEffect, &m_pBufErrorInfo );
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(213), "CMglHlsl::Load()  ���̃G���[�̂��� D3DXCreateEffectFromFile() �͎��s���܂����B\r\n\r\n%s", GetCompileErrorMsg() );
}

//	�����񂩂�ǂݍ���
void CMglHlsl::LoadFromString(const char* szAssembleString)
{
	CreatedCheck();

	//	�G�t�F�N�g�ǂݍ��݁[
	/*MyuAssert2( D3DXAssembleShader( szAssembleString, strlen(szAssembleString), <- �Ȃ�GetCompileErrorMsg()����Ɏ��s����Ă��܂��炵���E�E�E�܂��œK���Ƃ��ł��ˁE�E�E
		0, NULL, &m_pEffect, &m_pBufErrorInfo ), D3D_OK,
		MGLMSGNO_SHADER(13), "CMglHlsl::LoadFromString()  D3DXAssembleShader()�Ɏ��s\r\n\r\n%s", GetCompileErrorMsg() );*/
	HRESULT hr = D3DXCreateEffect( m_d3d, szAssembleString, strlen(szAssembleString), &m_pEffect, &m_pBufErrorInfo );
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(214), "CMglHlsl::LoadFromString()  ���̃G���[�̂��� D3DXCreateEffect() �͎��s���܂����B\r\n\r\n%s", GetCompileErrorMsg() );
}

//	�G���[���b�Z�[�W�擾
const char* CMglHlsl::GetCompileErrorMsg()
{
	if ( m_pBufErrorInfo == NULL )
		return "(No Error Buffer.)";

	return (const char*) m_pBufErrorInfo->GetBufferPointer();
}

//	�e�N�j�b�N��ݒ�
void CMglHlsl::SetTechnique( _MGL_D3DXHANDLE szTechniqueName )
{
	CreateCheck();

	//	�A�Z���u���t�@�C���ǂݍ��݁[
	MyuAssert2( m_pEffect->SetTechnique( szTechniqueName ), D3D_OK,
		MGLMSGNO_SHADER(240), "CMglHlsl::SetTechnique()  m_pEffect->SetTechnique()�Ɏ��s" );
}

////////////////////////////////////////////////////////////////

//	Begin()
UINT CMglHlsl::Begin( bool bRestoreCurrentRenderStates )
{
	CreateCheck();

	DWORD dwFlags = 0;
	if ( !bRestoreCurrentRenderStates )
		dwFlags = /*D3DXFX_DONOTSAVESHADERSTATE |*/ D3DXFX_DONOTSAVESTATE ;

	//	Begin
	MyuAssert2( m_pEffect->Begin( &m_nPassCount, dwFlags ), D3D_OK,
		MGLMSGNO_SHADER(280), "CMglHlsl::Begin()  m_pEffect->Begin()�Ɏ��s" );

	return m_nPassCount;
}
UINT CMglHlsl::Begin() {
	return Begin(true);
}

//	End()
void CMglHlsl::End()
{
	CreateCheck();
	MyuAssert2( m_pEffect->End(), D3D_OK,
		MGLMSGNO_SHADER(281), "CMglHlsl::End()  m_pEffect->End()�Ɏ��s" );

	m_nPassCount = 0;
}

//	Pass()
void CMglHlsl::Pass(UINT nPassNo)
{
	CreateCheck();
	MyuAssert2( m_pEffect->Pass(nPassNo), D3D_OK,
		MGLMSGNO_SHADER(284), "CMglHlsl::Pass()  m_pEffect->Pass(%s)�Ɏ��s", nPassNo );
}

//	�o�b�t�@�擾
/*_MGL_ID3DXEffect_* CMglHlsl::GetEffectPtr()
{
	InitCheck();
	CreateCheck();

	return m_pEffect;
}
*/
