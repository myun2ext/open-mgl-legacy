//////////////////////////////////////////////////////////
//
//	CMglHlsl - �V�F�[�_�[
//
//////////////////////////////////////////////////////////

#ifndef __MglHlsl_H__
#define __MglHlsl_H__

#include "mglafx.h"
#include "MglGraphicManager.h"

//typedef ID3DXBuffer _MGL_ID3DXEffect_;
typedef ID3DXEffect _MGL_ID3DXEffect_;

typedef LPCSTR _MGL_D3DXHANDLE;	

//	�N���X�錾
class DLL_EXP CMglEffectCore : public CMglDgBase
{
protected:
	_MGL_ID3DXEffect_ *m_pEffect;
	ID3DXBuffer *m_pBufErrorInfo;

	void CreatedCheck(){
		InitCheck();
		if ( m_pEffect != NULL )
			MyuThrow(MGLMSGNO_SHADER(201), "CMglHlsl  ���ɓǂݍ��ݍςł��B");
	}
	void CreateCheck(){
		InitCheck();
		if ( m_pEffect == NULL )
			MyuThrow(MGLMSGNO_SHADER(202), "CMglHlsl  Load()����Ă��܂���B");
	}

	////////////////////////////////////

	UINT m_nPassCount;
	bool m_bPassBegun;

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglEffectCore();
	virtual ~CMglEffectCore(){ Release(); }
	void Release();

	void Load(const char* szShaderScriptFile);
	void LoadScript(const char* szShaderScriptFile){ Load(szShaderScriptFile); }
	void Create(const char* szShaderScriptFile){ Load(szShaderScriptFile); }

	void LoadFromString( const char* szAssembleString );
	void CreateFromString( const char* szAssembleString ){ LoadFromString(szAssembleString); }

	/*void LoadFromResource( const char* szAssembleString ); <- DirectX8 ���T�|�[�g�E�E�E
	void CreateFromResource( const char* szAssembleString ){ LoadFromString(szAssembleString); }*/

	///////////////////////////////////////////////////////////

	void SetTechnique( const char* szTechniqueName );
	//void SetTexture( const char* szTechniqueName );

	UINT Begin( bool bRestoreCurrentRenderStates );
	UINT Begin();
	void End();
	void Pass(UINT nPassNo=0){ BeginPass(nPassNo); }
	void BeginPass(UINT nPassNo=0);
	void EndPass();
	UINT GetPassCount(){ return m_nPassCount; }

	///////////////////////////////////////////////////////////

	const char* GetCompileErrorMsg();

	//	�G�t�F�N�g�̃|�C���^�擾
	_MGL_ID3DXEffect_* GetEffectPtr(){
		InitCheck();
		CreateCheck();
		return m_pEffect;
	}
};

////////////////////////////////////////

class CMglHlsl : public CMglEffectCore
{

};

typedef CMglHlsl CMglHLSL, CMglEffect;

#endif//__MglHlsl_H__
