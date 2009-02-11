//////////////////////////////////////////////////////////
//
//	CMglPixelShader - ピクセルシェーダ
//
//////////////////////////////////////////////////////////

#ifndef __MglPixelShader_H__
#define __MglPixelShader_H__

#include "mglafx.h"
#include "MglGraphicManager.h"
#include "MglXShader.h"

//	クラス宣言
class DLL_EXP CMglPixelShader : public CMglDgBase
{
protected:
#if _MGL_DXVER == 9
	_IDirect3DPixelShaderX* m_pShader;
#else
	DWORD m_pShader;
#endif

	//-------------------------------------------------------------

	void CreatedCheck(){
		if ( m_pShader != NULL )
			MyuThrow(MGLMSGNO_SHADER(1), "CMglPixelShader  既にシェーダは作成済です。");
	}
	void CreateCheck(){
		if ( m_pShader == NULL )
			MyuThrow(MGLMSGNO_SHADER(2), "CMglPixelShader  シェーダが作成されていません。");
	}
	void LoadCommon(CONST DWORD* pFunction);

public:
	//	コンストラクタ・デストラクタ
	CMglPixelShader();
	virtual ~CMglPixelShader(){ Release(); }
	void Release();

	void Load(const char* szShaderScriptFile);
	void LoadScript(const char* szShaderScriptFile){ Load(szShaderScriptFile); }
	void Create(const char* szShaderScriptFile){ Load(szShaderScriptFile); }

	void LoadFromString( const char* szAssembleString );
	void CreateFromString( const char* szAssembleString ){ LoadFromString(szAssembleString); }

	//////////////////////////////////////////////////////////////////////////

	void SetShader();

	void SetShaderParam(DWORD dwRegisterNo, const void* lpData, DWORD dwDataBlockCount);
	void SetShaderParam(DWORD dwRegisterNo, CMglShaderParam &param);
};

#endif//__MglPixelShader_H__
