//////////////////////////////////////////////////////////
//
//	AugustWindow2
//
//////////////////////////////////////////////////////////

#ifndef __AugustWindow2_H__
#define __AugustWindow2_H__

#include "AugustCommon2.h"

class /*_AGST_DLL_EXP*/ CMwlAghWindow;
class /*_AGST_DLL_EXP*/ CMyuThreadBase;

class /*_AGST_DLL_EXP*/ CAugustWindow2 : public CMwlAghWindow
{
private:
	typedef CMwlAghWindow _BASE;
public:
	//	コンストラクタ・デストラクタ
	CAugustWindow2(){}
	virtual ~CAugustWindow2(){}

	/*int Start( const char* szWindowTitle, const char* szWinClassName,
		int nWinWidthSize, int nWinHeightSize, int nWinXPos=MYU_WINPOS_AUTO, int nWinYPos=MYU_WINPOS_AUTO,
		DWORD dwWinStyle=MYU_WINDOW_DEFAULT_STYLE, int nWindowShow=SW_SHOWDEFAULT );*/
	virtual void _AGST_DLL_EXP Start();
	//virtual void OnCreatedWindow(){}
};

#endif//__AugustWindow2_H__
