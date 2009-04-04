#include "stdafx.h"
#include "MglAugustFactory.h"
#include "mglaugust.h"

agh::CImageBase* CMglAugustFactory::GetImage()
{
	return new CAugustImage();
}
