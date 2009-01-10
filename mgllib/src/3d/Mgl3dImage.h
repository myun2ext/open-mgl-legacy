#ifndef __Mgl3dImage_H__
#define __Mgl3dImage_H__

#include "mglafx.h"

/////////////////////////////////////////////////////////////////////////

#include "MglImage.h"

class DLL_EXP CMgl3dImage : public CMglTexture
{
protected:
	MGL_SQUARE_VERTEXS m_vertexs;

	void GetBmpVertexs3D( MGL_SQUARE_VERTEXS *pMglSqVertexs, float fScaleX=1.0f, float fScaleY=1.0f );

public:
	void Draw(float x=0.0f, float y=0.0f, float z=0.0f, RECT* srcRect=NULL,
		float fTexScaleX=1.0f, float fTexScaleY=1.0f, D3DCOLOR color=D3DCOLOR_WHITE);

	void SetupVertexes(float x=0.0f, float y=0.0f, float z=0.0f, RECT* srcRect=NULL,
		float fTexScaleX=1.0f, float fTexScaleY=1.0f, D3DCOLOR color=D3DCOLOR_WHITE);
};

#endif//__Mgl3dImage_H__
