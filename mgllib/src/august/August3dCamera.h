//////////////////////////////////////////////////////////
//
//	August3dCamera
//
//////////////////////////////////////////////////////////

#ifndef __August3dCamera_H__
#define __August3dCamera_H__

#include "agh.h"
#include "AugustGraphicsManager.h"

#pragma warning( disable : 4660 ) 

class CMglImage;

//class _AGST_DLL_EXP agh::CImageBase;	//	�Ȃ�ł������Ă�񂾂����H�Y��Ȃ��悤�ɁE�E�E�H
class _AGST_DLL_EXP agh::CImageBase;

//	�N���X�錾  /////////////////////////////////////////////////////////
//class _AGST_DLL_EXP CAugust3dCamera : public virtual agh::CImageBase, public virtual CAugustControlBase
class _AGST_DLL_EXP CAugust3dCamera : public CAugustControlBaseT<agh::CImageBase>
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
	//	�R���X�g���N�^
	//CAugust3dCamera();
	//virtual ~CAugust3dCamera();
	CAugust3dCamera()
		: _BASE ("CAugust3dCamera")
	{
		m_pImg = NULL;
	}
	virtual ~CAugust3dCamera(){}

	/*
	//	2009/09/12  CAugustControlBase���g�p����悤�ɂ������ʁA�Ȃ񂩃R���p�C��������ƌ�����悤�ɂȂ����̂őΉ��E�E�E
	CAugust3dCamera(const CAugust3dCamera &in_img)
		: CAugustControlBase("CAugust3dCamera")
	{
		m_pImg = in_img.m_pImg;
		m_strFilePath = in_img.m_strFilePath;
	}
	*/

	//bool SetImageFilePath(const char* szImageFilePath);
	virtual bool Load(const char* szImageFilePath){ return LoadEx(szImageFilePath); }
	bool LoadEx(const char* szImageFilePath, agh::COLOR transparentColor=AGHCOLOR_PINK);
	
	//void SetTransparentColor(AGHCOLOR color);
};

/*
typedef CAugust3dCamera CAugust3dCameraCtrl;
typedef CAugust3dCamera CAugust3dCamera;
*/
#endif//__August3dCamera_H__
