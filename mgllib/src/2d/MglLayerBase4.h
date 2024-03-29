//////////////////////////////////////////////////////////
//
//	MglLayersBase4 - レイヤー
//
//////////////////////////////////////////////////////////

#ifndef __MglLayersBase4_H__
#define __MglLayersBase4_H__

#include "mgl_common.h"

#define MGL_LAYER_CMSGCODE_ON_FRAME		(0x00010080)

///////////////////////////////////////////////////////////////////

//	レイヤー既定クラス宣言
class DLL_EXP CMglLayerBase4 : public CMglClassMsg
{
protected:
	bool m_isShouldDeletePtr;
public:
	CMglLayerBase4(){
		m_isShouldDeletePtr = false;
	}
	//CMglLayerBase4(bool isShouldDeletePtr):m_isShouldDeletePtr(isShouldDeletePtr){}
	/*virtual void Release(){
		if ( m_isReleasePtr
	}*/
	virtual void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )=0;
	//bool isShouldDeletePtr(){ return m_isShouldDeletePtr; }
	virtual void Release(){}
	virtual BOOL DoFrame(){return TRUE;}
	virtual RECT GetRect(){RECT rect; ZeroMemory(&rect,sizeof(rect)); return rect;}
};

///////////////////////////////////////////////////////////////////

//	エフェクトレイヤーの既定クラス
template <typename TBase> class CMgEffectLayerBase : public TBase
{
private:
	BOOL m_isTerminated;
public:
	CMgEffectLayerBase(){ m_isTerminated=FALSE; }
	//virtual BOOL DoFrame()=0;
	//virtual BOOL IsTerminated()=0;

	int SendMessage(int nMsgCode, string strMsgParams=""){
		switch(nMsgCode){
		case MGL_LAYER_CMSGCODE_ON_FRAME:
			return DoFrame(); break;
		}
		return CMglClassMsg::SendMessage(nMsgCode,strMsgParams);
	}

};

#endif//__MglLayersBase4_H__
