#include "stdafx.h"
#include "MglClassBuilder.h"

///////////////////////////////////////////////////////////////////////

#include "MglBgm.h"

///////////////////////////////////////////////////////////////////////

IMglBgm* CMglClassBuilder::BuildBgmInstance(const char* szClassId)
{
	//return new CMglOgg();
	return new CMglMp3Dshow();
}

