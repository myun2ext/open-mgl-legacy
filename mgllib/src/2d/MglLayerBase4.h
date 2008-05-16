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
	bool m_isShouldReleasePtr;
public:
	CMglLayerBase4(){
		m_isShouldReleasePtr = false;
	}
	/*virtual void Release(){
		if ( m_isReleasePtr
	}*/
	virtual void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )=0;
	bool IsShouldReleasePtr(){ return m_isShouldReleasePtr; }
};

#endif//__MglLayersBase4_H__
