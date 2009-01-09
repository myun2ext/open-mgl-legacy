#ifndef __Mgl3dImage_H__
#define __Mgl3dImage_H__

#include "mglafx.h"

/////////////////////////////////////////////////////////////////////////

#include "MglImage.h"

class DLL_EXP CMgl3dImage : public CMglTexture
{
public:
	void Draw();

	void GetBmpVertexs3D( MGL_SQUARE_VERTEXS *pMglSqVertexs, float fScaleX, float fScaleY );
};

#endif//__Mgl3dImage_H__
