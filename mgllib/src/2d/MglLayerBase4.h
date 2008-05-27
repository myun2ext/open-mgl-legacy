//////////////////////////////////////////////////////////
//
//	MglLayersBase4 - レイヤー
//
//////////////////////////////////////////////////////////

#ifndef __MglLayersBase4_H__
#define __MglLayersBase4_H__

//	クラス宣言
class DLL_EXP CMglLayerBase4
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
	virtual RECT GetRect(){RECT rect; ZeroMemory(&rect,sizeof(rect)); return rect;}
};

//	クラス宣言
template <typename TBase> class CMgEffectLayerBase : public TBase
{
private:
	BOOL m_isTerminated;
public:
	CMgEffectLayerBase(){ m_isTerminated=FALSE; }
	virtual BOOL OnFrame()=0;
	//virtual BOOL IsTerminated()=0;
};

#endif//__MglLayersBase4_H__
