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

class CMglText;

//class _AGST_DLL_EXP agh::CTextBase;	<- 実態はtypedef
class _AGST_DLL_EXP agh::CVisualControlBase;
template class _AGST_DLL_EXP agh::CTextBaseT<agh::CVisualControlBase>;

//	クラス宣言  /////////////////////////////////////////////////////////
//class _AGST_DLL_EXP CAugustText2 : public agh::CTextBase
class _AGST_DLL_EXP CAugustText2 : public CAugustVisualControlBaseT<agh::CTextBase>
{
public:
	static const char* CLASS_NAME;
private:
	//typedef agh::CTextBase _BASE;
	typedef CAugustVisualControlBaseT<agh::CTextBase> _BASE;

protected:
	CMglGraphicManager *m_pGrp;
	CMglText* m_pText;
	bool m_bChanged;

	void OnChanged(){ m_bChanged = true; }
	void ReCreateFont();
	DWORD GetDrawInternalOption();

_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnDraw();

public:
	//	コンストラクタ
	CAugustText2();
	virtual ~CAugustText2();
	/*CAugustText2(){
		m_pText = NULL;
	}
	virtual ~CAugustText2(){}*/

	//	2009/09/29  コピーコンストラクタ対応（STL向け）
	CAugustText2(const CAugustText2& from);

	/////////////////////////////////////////////////////////////////////

	virtual void SetOption(agh::AGHDWORD dwOption);
	virtual void SetFontName(const char* szFontName);
	virtual void SetFontPoint(int point);
	//virtual void SetStr(const char* szStr){ m_textData = szStr; }
	//virtual const char* GetStr(){ return m_textData.c_str(); }
	virtual void SetColor(agh::COLOR color);
	//virtual void SetOption(AGHDWORD dwOption);
	//virtual AGHCOLOR GetColor(){ return m_color; }
	//virtual AGHDWORD GetOption(){ return m_dwOption; }
	//virtual void Align(int align){ m_nAlign = align; }
};

/*
typedef CAugustText2 CAugustText2Ctrl;
typedef CAugustText2 CAugustText2;
*/
#endif//__AugustText2_H__
