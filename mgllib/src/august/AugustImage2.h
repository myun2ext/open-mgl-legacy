//////////////////////////////////////////////////////////
//
//	AugustImage2
//
//////////////////////////////////////////////////////////

#ifndef __AugustImage2_H__
#define __AugustImage2_H__

#include "agh.h"
#include "AugustGraphicsManager.h"

#pragma warning( disable : 4660 ) 

class CMglImage;

//class _AGST_DLL_EXP agh::CImageBase;	//	なんでこうしてるんだっけ？忘れないように・・・？
class _AGST_DLL_EXP agh::CImageBase;

//	クラス宣言  /////////////////////////////////////////////////////////
//class _AGST_DLL_EXP CAugustImage2 : public virtual agh::CImageBase, public virtual CAugustControlBase
class _AGST_DLL_EXP CAugustImage2 : public CAugustControlBaseT<agh::CImageBase>
{
private:
	//typedef agh::CImageBase _BASE;
	typedef CAugustControlBaseT<agh::CImageBase> _BASE;

protected:
	CMglImage* m_pImg;
	std::string m_strFilePath;

_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnDraw();

public:
	//	コンストラクタ
	//CAugustImage2();
	//virtual ~CAugustImage2();
	CAugustImage2()
		: _BASE ("CAugustImage2")
	{
		m_pImg = NULL;
	}
	virtual ~CAugustImage2(){}

	/*
	//	2009/09/12  CAugustControlBaseを使用するようにした結果、なんかコンパイラから作れと言われるようになったので対応・・・
	CAugustImage2(const CAugustImage2 &in_img)
		: CAugustControlBase("CAugustImage2")
	{
		m_pImg = in_img.m_pImg;
		m_strFilePath = in_img.m_strFilePath;
	}
	*/

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath){ return LoadEx(szImageFilePath); }
	bool LoadEx(const char* szImageFilePath, agh::COLOR transparentColor=0);
	
	//void SetTransparentColor(AGHCOLOR color);
};

/*
typedef CAugustImage2 CAugustImage2Ctrl;
typedef CAugustImage2 CAugustImage2;
*/
#endif//__AugustImage2_H__
