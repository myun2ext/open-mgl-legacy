#ifndef __MglLight_H__
#define __MglLight_H__

#include "mglafx.h"
#include "MglGraphicManager.h"

//	ƒNƒ‰ƒXéŒ¾
class DLL_EXP CMglLight : public CMglDgBase
{
protected:
	_D3DLIGHTx m_light;

public:
	CMglLight();
	virtual ~CMglLight(){ Release(); }
	virtual void Release();

	//	‰Šú‰»/ŠJ•ú
	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() ){ CMglDgBase::Init(in_myudg); }
	void Init( D3DLIGHTTYPE lightType,
		CMglGraphicManager* in_myudg=GetDefaultGd() );

	void Setup( D3DLIGHTTYPE lightType,
		float fPosX, float fPosY, float fPosZ,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DCOLOR ambient=D3DCOLOR_WHITE, float fRange=1000.0f );
};

#endif//__MglLight_H__
