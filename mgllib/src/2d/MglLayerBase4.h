//////////////////////////////////////////////////////////
//
//	MglLayersBase4 - ÉåÉCÉÑÅ[
//
//////////////////////////////////////////////////////////

#ifndef __MglLayersBase4_H__
#define __MglLayersBase4_H__

class DLL_EXP CMglLayerBase4
{
public:
	virtual void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )=0;
};

#endif//__MglLayersBase4_H__