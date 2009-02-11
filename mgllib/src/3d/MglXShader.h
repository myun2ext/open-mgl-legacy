//////////////////////////////////////////////////////////
//
//	CMglXShader - ���b�V��
//
//////////////////////////////////////////////////////////

#ifndef __MglXShader_H__
#define __MglXShader_H__

#include "mglafx.h"
#include "MglGraphicManager.h"

//	�N���X�錾
class DLL_EXP CMglXShader : public CMglDgBase
{
protected:
	ID3DXBuffer *m_pBufShader;
	ID3DXBuffer *m_pBufErrorInfo;

	void CreatedCheck(){
		if ( m_pBufShader != NULL )
			MyuThrow(MGLMSGNO_SHADER(1), "CMglXShader  ���ɃV�F�[�_�͍쐬�ςł��B");
	}
	void CreateCheck(){
		if ( m_pBufShader == NULL )
			MyuThrow(MGLMSGNO_SHADER(2), "CMglXShader  �V�F�[�_���쐬����Ă��܂���B");
	}

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglXShader();
	virtual ~CMglXShader(){ Release(); }
	void Release();

	void Load(const char* szShaderScriptFile);
	void LoadScript(const char* szShaderScriptFile){ Load(szShaderScriptFile); }
	void Create(const char* szShaderScriptFile){ Load(szShaderScriptFile); }

	const char* GetCompileErrorMsg();
};
//typedef CMglXShader CMglShaderBase;
typedef CMglXShader CMglShaderLoader;

#endif//__MglXShader_H__
