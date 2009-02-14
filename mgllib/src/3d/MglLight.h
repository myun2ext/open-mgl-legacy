#ifndef __MglLight_H__
#define __MglLight_H__

#include "mglafx.h"
#include "MglGraphicManager.h"

//	ライトの減衰率 
typedef struct _MGL_LIGHT_ATTENUATION {
	float fLinear;		//	直線減衰
	float fCurve;		//	カーブ（二次関数）
	float fPowCurve;	//	二乗カーブ

	_MGL_LIGHT_ATTENUATION(){}
	_MGL_LIGHT_ATTENUATION(float fLinear_in, float fCurve_in, float fPowCurve_in ){
		fLinear = fLinear_in;
		fCurve = fCurve_in;
		fPowCurve = fPowCurve_in;
	}

	_MGL_LIGHT_ATTENUATION operator *(float fVal){
		_MGL_LIGHT_ATTENUATION t;
		t.fLinear = fLinear * fVal;
		t.fCurve = fCurve * fVal;
		t.fPowCurve = fPowCurve * fVal;
		return t;
	}

	_MGL_LIGHT_ATTENUATION operator /(float fVal){
		_MGL_LIGHT_ATTENUATION t;
		t.fLinear = fLinear / fVal;
		t.fCurve = fCurve / fVal;
		t.fPowCurve = fPowCurve / fVal;
		return t;
	}

	_MGL_LIGHT_ATTENUATION operator +(float fVal){
		_MGL_LIGHT_ATTENUATION t;
		t.fLinear = fLinear + fVal;
		t.fCurve = fCurve + fVal;
		t.fPowCurve = fPowCurve + fVal;
		return t;
	}

	_MGL_LIGHT_ATTENUATION operator -(float fVal){
		_MGL_LIGHT_ATTENUATION t;
		t.fLinear = fLinear - fVal;
		t.fCurve = fCurve - fVal;
		t.fPowCurve = fPowCurve - fVal;
		return t;
	}
} MGL_LIGHT_ATTENUATION, MGL_LIGHT_ATTEN, MGL_LIGHT_ATTE, MGL_LIGHT_ATT, MGL_LIGHT_ATN;
/*
intensity = dvAttenuation0 +
    dvAttenuation1 * distance +
    dvAttenuation2 * distance squared 
*/

#define MGL_LIGHT_ATN_NON			(MGL_LIGHT_ATN(0,0,0))
#define MGL_LIGHT_ATN_LINEAR1		(MGL_LIGHT_ATN(1,0,0))
#define MGL_LIGHT_ATN_CURVE1		(MGL_LIGHT_ATN(0,1,0))	//	0.015f
#define MGL_LIGHT_ATN_POWCURVE1		(MGL_LIGHT_ATN(0,0,1))	//	0.04f
#define MGL_LIGHT_ATN_ECLIPSE1		(MGL_LIGHT_ATN(-0.14f,0.05f,0))

#define MGL_LIGHT_ATN_STD1			(MGL_LIGHT_ATN(0.6f,0.05f,0))
#define MGL_LIGHT_ATN_STD2			(MGL_LIGHT_ATN(0.5f,0.2f,0))

//	クラス宣言
class DLL_EXP CMglLight : public CMglDgBase
{
private:
	void _CMglLight(); // 内部コンストラクタ

protected:
	_D3DLIGHTx m_light;
	DWORD m_dwLightIndex;

public:
	//	コンストラクタ・デストラクタ
	CMglLight(){ _CMglLight(); }
	CMglLight(DWORD dwLightIndex){
		_CMglLight();
		m_dwLightIndex = dwLightIndex;
	}
	virtual ~CMglLight(){ Release(); }
	virtual void Release();

	//	初期化/開放
	//void Init( CMglGraphicManager* in_myudg=GetDefaultGd() ){ CMglDgBase::Init(in_myudg); }
	/*void Init( D3DLIGHTTYPE lightType,
		CMglGraphicManager* in_myudg=GetDefaultGd() );*/

	void Setup( _D3DLIGHTx &lightSetting );
	void Setup( D3DLIGHTTYPE lightType,
		float fPosX, float fPosY, float fPosZ, float fDirectionX, float fDirectionY, float fDirectionZ, MGL_LIGHT_ATTENUATION &attenuation,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK, D3DXCOLOR specular=D3DCOLOR_WHITE, float fRange=1000.0f );

	//	ディレクショナルライト
	void SetupDirectionalLight( float fDirectionX, float fDirectionY, float fDirectionZ,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK, D3DXCOLOR specular=D3DCOLOR_WHITE, float fRange=1000.0f )
	{
		Setup(D3DLIGHT_DIRECTIONAL, 0,0,0, fDirectionX, fDirectionY, fDirectionZ, MGL_LIGHT_ATN_NON, color, ambient, specular, fRange);
	}

	//	ポイントライト
	void SetupPointLight( float fPosX, float fPosY, float fPosZ, MGL_LIGHT_ATTENUATION &attenuation,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK, D3DXCOLOR specular=D3DCOLOR_WHITE, float fRange=1000.0f ){
		Setup(D3DLIGHT_POINT, fPosX, fPosY, fPosZ, 0,0,0, attenuation, color, ambient, specular, fRange);}
	void SetupPointingLight( float fPosX, float fPosY, float fPosZ, MGL_LIGHT_ATTENUATION &attenuation,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK, D3DXCOLOR specular=D3DCOLOR_WHITE, float fRange=1000.0f ){
		SetupPointLight(fPosX, fPosY, fPosZ, attenuation, color, ambient, specular, fRange);}

	///////////////////////////////////////////////////////////////////////////

	void SetLightIndex(DWORD dwLightIndex){ m_dwLightIndex = dwLightIndex; }
	void Enable();
	void Disable();
	void AllLightDisable();
	void DisableAllLight(){ AllLightDisable(); }
	void DisableLighting(){ AllLightDisable(); }
	//--------------------------------------------------------

	_D3DLIGHTx* GetD3dLightPtr(){ return &m_light; }
	void CommitD3dLight();
	void Commit(){ CommitD3dLight(); }
	void CommitLight(){ CommitD3dLight(); }
};

#endif//__MglLight_H__
