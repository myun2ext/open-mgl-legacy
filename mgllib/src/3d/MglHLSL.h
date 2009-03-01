//////////////////////////////////////////////////////////
//
//	CMglHlsl - シェーダー
//
//////////////////////////////////////////////////////////

#ifndef __MglHlsl_H__
#define __MglHlsl_H__

#include "mglafx.h"
#include "MglGraphicManager.h"

//typedef ID3DXBuffer _MGL_ID3DXEffect_;
typedef ID3DXEffect _MGL_ID3DXEffect_;

#if _MGL_DXVER == 8
	typedef LPCSTR _MGL_D3DXHANDLE;	
#else
	typedef D3DXHANDLE _MGL_D3DXHANDLE;	
#endif

//	クラス宣言
class DLL_EXP CMglEffectCore : public CMglDgBase
{
protected:
	_MGL_ID3DXEffect_ *m_pEffect;
	ID3DXBuffer *m_pBufErrorInfo;

	void CreatedCheck(){
		InitCheck();
		if ( m_pEffect != NULL )
			MyuThrow(MGLMSGNO_SHADER(201), "CMglHlsl  既に読み込み済です。");
	}
	void CreateCheck(){
		InitCheck();
		if ( m_pEffect == NULL )
			MyuThrow(MGLMSGNO_SHADER(202), "CMglHlsl  Load()されていません。");
	}

	////////////////////////////////////

	UINT m_nPassCount;
	bool m_bBegun;
	bool m_bPassBegun;

public:
	//	コンストラクタ・デストラクタ
	CMglEffectCore();
	virtual ~CMglEffectCore(){ Release(); }
	void Release();

	void Load(const char* szShaderScriptFile);
	void LoadScript(const char* szShaderScriptFile){ Load(szShaderScriptFile); }
	void Create(const char* szShaderScriptFile){ Load(szShaderScriptFile); }

	void LoadFromString( const char* szAssembleString );
	void CreateFromString( const char* szAssembleString ){ LoadFromString(szAssembleString); }

	/*void LoadFromResource( const char* szAssembleString ); <- DirectX8 未サポート・・・
	void CreateFromResource( const char* szAssembleString ){ LoadFromString(szAssembleString); }*/

	///////////////////////////////////////////////////////////

	void SetTechnique( const char* szTechniqueName );
	void FirstTechnique(){ NextTechnique(NULL); }
	void NextTechnique( _MGL_D3DXHANDLE hPrevTechnique );
	_MGL_D3DXHANDLE FindNextValidTechnique( _MGL_D3DXHANDLE hPrevTechnique=NULL );

	UINT Begin( bool bRestoreCurrentRenderStates );
	UINT Begin();
	void End();
	void Pass(UINT nPassNo=0){ BeginPass(nPassNo); }
	void BeginPass(UINT nPassNo=0);
	void EndPass();
	UINT GetPassCount(){ return m_nPassCount; }

	///////////////////////////////////////////////////////////

	const char* GetCompileErrorMsg();

	//	エフェクトのポインタ取得
	_MGL_ID3DXEffect_* GetEffectPtr(){
		InitCheck();
		CreateCheck();
		return m_pEffect;
	}
};

////////////////////////////////////////////

class CMglHlsl : public CMglEffectCore
{

};
typedef CMglHlsl CMglHLSL, CMglEffect;

////////////////////////////////////////////

//	テクニック - Technique
class CMglHlslTechnique
{
protected:
	CMglHlsl *m_pHlsl;

	void InitCheck(){
		if ( m_pHlsl == NULL )
			MyuThrow(MGLMSGNO_SHADER(601), "CMglHlslTechnique  Init()にて CMglHlsl を設定してください。");
	}

	void SetTechnique( const char* szTechniqueName ){
		InitCheck();
		m_pHlsl->SetTechnique(szTechniqueName);
	}

public:
	//	コンストラクタ
	CMglHlslTechnique(){
		m_pHlsl = NULL;
	}

	//	初期化
	void Init( CMglHlsl& hlsl, const char* szTechniqueName=NULL ){
		m_pHlsl = &hlsl;
		SetTechnique(szTechniqueName);
	}

	/////////////////////////////////////////

	//	設定
	//void SetPass(
};
typedef CMglHlslTechnique CMglHLSLTech;

//////////////////////////////////////////////

//	Pass
class CMglHlslPass : public CMglHlslTechnique
{
protected:
	UINT m_nPassNo;

public:
	//	コンストラクタ
	CMglHlslPass(){
		m_nPassNo = 0;
	}

	//	初期化
	void Init( CMglHlsl& hlsl, const char* szTechniqueName=NULL, UINT nPassNo=0 ){
		CMglHlslTechnique::Init(hlsl, szTechniqueName);
		m_nPassNo = nPassNo;
	}

	void Begin(){

	}
};
/*
protected:
	CMglHlsl *m_pHlsl;
public:
	CMglHlslPass(){
		m_pHlsl = NULL;
	}
	void Init(CMglHlsl& hlsl){
		m_pHlsl = &hlsl;
	}
*/

#endif//__MglHlsl_H__
