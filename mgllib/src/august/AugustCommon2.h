#ifndef __AugustCommon2_H__
#define __AugustCommon2_H__

//#define __MWLAGH_NOT_USE_SLIB
#include "agh.h"
#include "mwlagh.h"

#include "MyuCommonException.h"
#include "mglmsg.h"


#ifdef MGLLIB_EXPORTS
	#define _AGST_DLL_EXP __declspec(dllexport)
	#define _AGST_DLL_TMPL_EXP template class _AGST_DLL_EXP			//	C4275対応
	//#define DLL_TMPL_EXTERN
	//#define DLL_TMPL_EXTERN template
#else
	#define _AGST_DLL_EXP __declspec(dllimport)
	#define _AGST_DLL_TMPL_EXP /*extern*/ template class _AGST_DLL_EXP	//	C4275対応
	//#define DLL_TMPL_EXTERN extern
	//#define DLL_TMPL_EXTERN extern template

	//	2009/04/16 Add.
	#pragma comment(lib, "mgllib.lib")

#endif

class _AGST_DLL_EXP agh::CControlBase;


#define AUGUST_VALKEY_					(AGH_VALKEY_USER_FIRST+0x18A60000)	//	被らなさそうに適当な数字。18A6

#define AUGUST_VALKEY_SCREEN			(AUGUST_VALKEY_ + 0x0200)

#define AUGUST_VALKEY_GRP				(AUGUST_VALKEY_ + 0x0359)
#define AUGUST_VALKEY_PGRP				(AUGUST_VALKEY_GRP)		//	Alias
#define AUGUST_VALKEY_P_GRP				(AUGUST_VALKEY_GRP)		//	Alias

#define AUGUST_VALKEY_AGRPM				(AUGUST_VALKEY_ + 0x0381)

#define AUGUST_VALKEY_IMG_LOADER		(AUGUST_VALKEY_ + 0x0382)
#define AUGUST_VALKEY_IMAGE_LOADER		(AUGUST_VALKEY_IMG_LOADER)

#define AUGUST_VALKEY_AGRPM				(AUGUST_VALKEY_ + 0x0381)

#define AUGUST_VALKEY_MOUSE				(AUGUST_VALKEY_ + 0x0500)
#define AUGUST_VALKEY_PMOUSE			(AUGUST_VALKEY_MOUSE)	//	Alias
#define AUGUST_VALKEY_P_MOUSE			(AUGUST_VALKEY_MOUSE)	//	Alias

#define AUGUST_VALKEY_SOUNDMGR			(AUGUST_VALKEY_ + 0x0600)
#define AUGUST_VALKEY_PSOUND			(AUGUST_VALKEY_SOUNDMGR)
#define AUGUST_VALKEY_PSOUNDMGR			(AUGUST_VALKEY_SOUNDMGR)
#define AUGUST_VALKEY_P_SOUND			(AUGUST_VALKEY_SOUNDMGR)
#define AUGUST_VALKEY_P_SOUNDMGR		(AUGUST_VALKEY_SOUNDMGR)


////////////////////////////////////////////////////////////////////////////////

//#define AugustThrow	MyuThrow


//	例外型
#define _AUGUST_EXCEPTION_MSG_MAX		(1024)
typedef struct
{
	unsigned long nCode;
	//str::string strMsg;
	char szMsg[_AUGUST_EXCEPTION_MSG_MAX+1];
}
AugustException;


//	例外を投げる
void _AGST_DLL_EXP AugustThrow( unsigned long nCode, const char* szMsgFormat, ... );


/////////////////////

#define AUGUST_MSGNO_COMMON__(no)			MGLMSGNO_AUGUST(0x1000000+no)
#define AUGUST_MSGNO_CONTROL_BASE_(no)		AUGUST_MSGNO_COMMON__(0x1030)

#define AUGUST_MSGNO_NO_PARENT				AUGUST_MSGNO_CONTROL_BASE_(1)	/*	親コントロールがありません	*/

/***********************************************************************************/


//	August Framework クラスの基底
template <typename T>
class CAugustControlBaseT : public T
{
public:
	/*	agh::CControlBase で定義されている事を期待しているメソッド（て言うかまぁあるんだけど）  */
	//virtual bool IsRegisted()=0;

protected:
	std::string m_strClassName;

	void SetClassName(const char* szClassName){ m_strClassName = szClassName; }

	void RegistCheck(){
		if ( IsRegisted() == false )
			//AugustThrow( 9999, "%s  親のコントロールが存在しません。RegistControl()にて親コントロールへの登録を行ってください。", m_strClassName.c_str() );
			AugustThrow( AUGUST_MSGNO_NO_PARENT, "%s に対し操作を行うには親コントロールとの関連付けが必要です。\r\n[親コントロール].RegistControl() にて親コントロールへの関連付けを行ってください。", m_strClassName.c_str() );
	}
	void RegistedCheck(){ RegistCheck(); }

public:
	//	コンストラクタ・デストラクタ
	//CAugustControlBase(){}
	CAugustControlBaseT(const char* szClassName){ SetClassName(szClassName); }
	virtual ~CAugustControlBaseT(){}
};

typedef CAugustControlBaseT<agh::CControlBase> CAugustControlBase;



/***********************************************************************************/


////////////////////////////////////////////////////
//
//	CAugustVisualControlBaseT
//


//	内部メソッド
void _AGST_DLL_EXP _AugustPaintRect(AGHCOLOR color, agh::CRect rect);

class CAugustGraphicsManager;
class CMglGraphicManager;

//	クラス宣言
template <typename T> /* T=CAugustControlBaseT、ないしCAugustControlBaseTを継承したクラスである事が前提	*/
class CAugustVisualControlBaseT : public T
{
protected:
	CAugustGraphicsManager* m_pAGrpMgr;
	CMglGraphicManager *m_pGrp;

_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnRegist(){
		m_pAGrpMgr = (CAugustGraphicsManager*)MyuAssertNull(_BASE::GetValPtr(AUGUST_VALKEY_AGRPM),
			"%s:  AUGUST_VALKEY_IMAGE_LOADER の取得に失敗。", m_strClassName.c_str() );
	}

public:
	//	コンストラクタ・デストラクタ
	//CAugustControlBase(){}
	CAugustVisualControlBaseT(const char* szClassName) : T(szClassName) { m_pAGrpMgr = NULL; }
	virtual ~CAugustVisualControlBaseT(){}

	//////////////////////////////////////////

	virtual void PaintBackground(AGHCOLOR color){ _AugustPaintRect(color, m_rect); }
	//virtual void PaintBackground(AGHCOLOR color);
};



/***********************************************************************************/



//	Load()を実装するメソッドの基底クラス
class CAugustLoadable
{
public:
	//	コンストラクタ・デストラクタ
	CAugustLoadable(){}
	virtual ~CAugustLoadable(){}

	virtual bool Load(const char* szFileName)=0;
};

#endif//__AugustCommon2_H__





#if 1 == 0
//	August Framework クラスの基底
class _AGST_DLL_EXP CAugustControlBase : public virtual agh::CControlBase
{
public:
	/*	agh::CControlBase で定義されている事を期待しているメソッド（て言うかまぁあるんだけど）  */
	//virtual bool IsRegisted()=0;

protected:
	std::string m_strClassName;

	void SetClassName(const char* szClassName){ m_strClassName = szClassName; }

	void RegistCheck(){
		if ( IsRegisted() == false )
			//AugustThrow( 9999, "%s  親のコントロールが存在しません。RegistControl()にて親コントロールへの登録を行ってください。", m_strClassName.c_str() );
			AugustThrow( MGLMSGNO_AUGUST(0x01001031), "%s には親コントロールが必要です。 [親コントロール].RegistControl() にて親コントロールへの登録を行ってください。", m_strClassName.c_str() );
	}
	void RegistedCheck(){ RegistCheck(); }

public:
	//	コンストラクタ・デストラクタ
	//CAugustControlBase(){}
	CAugustControlBase(const char* szClassName){ SetClassName(szClassName); }
	virtual ~CAugustControlBase(){}
};
#endif


/***********************************************************************************/