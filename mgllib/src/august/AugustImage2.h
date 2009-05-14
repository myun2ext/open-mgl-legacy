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

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CAugustImage2 : public agh::CImageBase
{
private:
	//typedef CAugustVisualControlBaseT<agh::CImageBase> _BASE;
	typedef CAugustVisualControlBase2 _BASE;

protected:
	CMglImageCacher *m_pCacher;
	CMglImage* m_pImg;
	std::string m_strFilePath;

_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnDraw();

public:
	//	コンストラクタ
	CAugustImage2(){
		m_pCacher = NULL;
		m_pImg = NULL;
	}
	virtual ~CAugustImage2(){} // 作っておかないと恐らくCImageBaseからのデストラクタが上手く動かない気がする・・・

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);
};

/*
typedef CAugustImage2 CAugustImage2Ctrl;
typedef CAugustImage2 CAugustImage2;
*/
#endif//__AugustImage2_H__
