#ifndef __Mgl3dImage_H__
#define __Mgl3dImage_H__

#include "mglafx.h"

/////////////////////////////////////////////////////////////////////////

#include "MglImage.h"

class DLL_EXP CMgl3dImage : public CMglTexture
{
public:
	void Draw(float x=0.0f, float y=0.0f, float z=0.0f, RECT* srcRect=NULL, float fScaleX=1.0f, float fScaleY=1.0f,
		D3DCOLOR color=D3DCOLOR_WHITE);

	void GetBmpVertexs3D( MGL_SQUARE_VERTEXS *pMglSqVertexs, float fScaleX=1.0f, float fScaleY=1.0f );
};

#endif//__Mgl3dImage_H__
