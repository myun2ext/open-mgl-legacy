//////////////////////////////////////////////////////////
//
//	AugustImageImpl
//
//////////////////////////////////////////////////////////

#ifndef __AugustImageImpl_H__
#define __AugustImageImpl_H__

#include "agh.h"
#include "AugustCommon.h"
#include "MglGraphicManager.h"
#include "MglImageCacher.h"

//	Implクラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CAugustImageImpl : public agh::IImageImpl, public CAugustVisualControlBase4
{
private:
	//typedef CAugustVisualControlBaseT<agh::CImageBase> _BASE;
	typedef CAugustVisualControlBase4 _BASE_AG;

protected:
	CMglImageCacher *m_pCacher;
	CMglImage* m_pImg;
	agh::CImageBase *m_pBaseControl;
	std::string m_strFilePath; //別に親でもいいか？（いやだめか？

_AGH_EVENT_ACCESS_MODIFIER:	//	_AGH_EVENT_ACCESS_MODIFIERでないのには何か意味でもあるんだろうか
	//virtual void OnRegist();
	virtual void OnDraw();

public:
	//	コンストラクタ
	CAugustImageImpl(agh::CImageBase *pControl){
		m_pCacher = NULL;
		m_pImg = NULL;
		m_pBaseControl = pControl;
	}
	/*CAugustImageCore(){
		m_pCacher = NULL;
		m_pImg = NULL;
		m_pBaseControl = NULL;
	}*/
	virtual ~CAugustImageImpl(){}

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath);

	////////////////////////////////////////////

	/*void SetAghControlPtr(agh::CImageBase *pControl){
		m_pBaseControl = pControl;
	}*/
};
typedef CAugustImageImpl CAugustImageCore;

#endif//__AugustImageImpl_H__
