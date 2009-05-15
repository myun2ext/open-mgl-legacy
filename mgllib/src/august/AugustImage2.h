//////////////////////////////////////////////////////////
//
//	AugustImage2
//
//////////////////////////////////////////////////////////

#ifndef __AugustImage2_H__
#define __AugustImage2_H__

#include "agh.h"

#pragma warning( disable : 4660 ) 
//class DLL_EXP agh::CImageBase;

class CMglImage;

//	クラス宣言  /////////////////////////////////////////////////////////
class CAugustImage2 : public agh::CImageBase
{
private:
	typedef agh::CImageBase _BASE;

protected:
	CMglImage* m_pImg;
	std::string m_strFilePath;

_AGH_EVENT_ACCESS_MODIFIER:
	virtual void DLL_EXP OnDraw();

public:
	//	コンストラクタ
	CAugustImage2(){
		m_pImg = NULL;
	}
	virtual ~CAugustImage2(){}

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool DLL_EXP Load(const char* szImageFilePath);
};

/*
typedef CAugustImage2 CAugustImage2Ctrl;
typedef CAugustImage2 CAugustImage2;
*/
#endif//__AugustImage2_H__
