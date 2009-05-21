//////////////////////////////////////////////////////////
//
//	AugustText2
//
//////////////////////////////////////////////////////////

#ifndef __AugustText2_H__
#define __AugustText2_H__

#include "agh.h"
#include "AugustGraphicsManager.h"

#pragma warning( disable : 4660 ) 
//class DLL_EXP agh::CImageBase;

class CMglImage;

//class _AGST_DLL_EXP agh::CImageBase;

//	クラス宣言  /////////////////////////////////////////////////////////
class _AGST_DLL_EXP CAugustText2 : public agh::CImageBase
{
private:
	typedef agh::CImageBase _BASE;

protected:
	CMglImage* m_pImg;
	std::string m_strFilePath;

_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnDraw();

public:
	//	コンストラクタ
	//CAugustText2();
	//virtual ~CAugustText2();
	CAugustText2(){
		m_pImg = NULL;
	}
	virtual ~CAugustText2(){}

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);
};

/*
typedef CAugustText2 CAugustText2Ctrl;
typedef CAugustText2 CAugustText2;
*/
#endif//__AugustText2_H__
