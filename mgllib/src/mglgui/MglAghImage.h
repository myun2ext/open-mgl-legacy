//////////////////////////////////////////////////////////
//
//	MglAghImage
//
//////////////////////////////////////////////////////////

#ifndef __MglAghImage_H__
#define __MglAghImage_H__

#include "agh.h"

class DLL_EXP agh::CImageBase;

//	ÉNÉâÉXêÈåæ  /////////////////////////////////////////////////////////
class DLL_EXP CMglAghImage : public agh::CImageBase
{
	friend class CMglguiScreen;
protected:
	std::string m_strLayerName;
	std::string m_strFilePath;
public:
	bool Load(const char* szImageFilePath);
};

#endif//__MglAghImage_H__
