#ifndef __mgl3d_H__
#define __mgl3d_H__

#include "mglafx.h"

/////////////////////////////////////////////////////////////////////////

#include "MglImage.h"

class DLL_EXP CMgl3dImage : public CMglTexture
{
public:
	void Draw3d();

	void GetBmpVertexs3D( MGL_SQUARE_VERTEXS *pMglSqVertexs, float fScaleX, float fScaleY );
};

#endif//__mgl3d_H__
