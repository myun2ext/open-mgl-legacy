#ifndef __MglTextLayer_H__
#define __MglTextLayer_H__

#include "MglLayerBase4.h"
#include "MglText.h"

//	クラス宣言
class DLL_EXP CMglTextLayer : public CMglLayerBase4
{
private:
	CMglText* m_pText;
	string m_strText;
	DWORD m_dwOption;

public:
	//	コンストラクタ
	CMglTextLayer(){
		m_pText = NULL;
		m_dwOption = 0;
	}
	CMglTextLayer(CMglText *pMglText, const char* szText, bool isShouldDeletePtr)
	{
		m_pText = pMglText;
		m_strText = szText;
		m_dwOption = 0;
		m_isShouldDeletePtr = isShouldDeletePtr;
	}
	CMglTextLayer(const char* szText){
		m_pText = new CMglText();
		m_strText = szText;
		m_dwOption = 0;
		m_isShouldDeletePtr = true;
	}

	//	オプション
	void SetOption(DWORD dwOption){
		m_dwOption = dwOption;
	}
	//	オプション
	void SetLeft(){ m_dwOption |= DT_LEFT; }
	void SetCenter(){ /*m_dwOption ^= DT_RIGHT;*/ m_dwOption |= DT_CENTER; }
	void SetRight(){ /*m_dwOption ^= DT_CENTER;*/ m_dwOption |= DT_RIGHT; }
	void SetTop(){ m_dwOption |= DT_TOP; }
	void SetVCenter(){ /*m_dwOption ^= DT_BOTTOM;*/ m_dwOption |= DT_VCENTER; }
	void SetBottom(){ /*m_dwOption ^= DT_VCENTER;*/ m_dwOption |= DT_BOTTOM; }
	//void SetBold(){}

	//	implement
	void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_BLACK,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )
	{
		m_pText->Draw(m_strText.c_str(),(int)x,(int)y,color,m_dwOption);
	}
	void Release(){
		if ( m_isShouldDeletePtr )
			delete m_pText;
	}
};

#endif//__MglTextLayer_H__
