#ifndef __MglClassBuilder_H__
#define __MglClassBuilder_H__

#include "MglBgmBase.h"

#define MGL_CLASS_ID_BGM		"CMglBgm"
#define MGL_CLASS_ID_BGM_OGG	"CMglOgg"
#define MGL_CLASS_ID_BGM_DSHOW	"CMglMp3Dshow"

//	ÉNÉâÉXêÈåæ
class DLL_EXP CMglClassBuilder
{
public:
	static IMglBgm* BuildBgmInstance(const char* szClassId=MGL_CLASS_ID_BGM);
};

#endif//__MglClassBuilder_H__
