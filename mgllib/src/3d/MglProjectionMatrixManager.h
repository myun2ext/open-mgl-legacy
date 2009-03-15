///////////////////////////////////////////////////////////////////////
//
//	MglProjectionMatrixManager
//
///////////////////////////////////////////////////////////////////////

#ifndef __MglProjectionMatrixManager_H__
#define __MglProjectionMatrixManager_H__

#include "MglGraphicManager.h"

#define _MGL3D_COORDINATE_LEFT_HAND		(0)	//	左手座標系
#define _MGL3D_COORDINATE_RIGHT_HAND	(1)	//	右手座標系
#define _MGL3D_COORDINATE_USE			_MGL3D_COORDINATE_LEFT_HAND

#define MGL3D_X	(0)
#define MGL3D_Y	(1)
#define MGL3D_Z	(2)

//	クラス宣言
class DLL_EXP CMglProjectionMatrixManager : public virtual CMglDgBase
{
private:

protected:
	D3DXMATRIX m_projection;

	float m_fAspectRatio;
	float m_fViewingAngle;
	float m_fClipNear;
	float m_fClipFar;
public:

	//////////////////////////
	//
	//		公開メソッド
	//

	//	コンストラクタ/デストラクタ
	CMglProjectionMatrixManager();
	virtual ~CMglProjectionMatrixManager();

	//	初期化/開放
	virtual void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	virtual void Release();

	/////////////////////////////////////////////////////////////////

	void ReTransform();

	//	Projection
	void SetupProjection( float fAspectRatio, float fViewingAngle=30.0f, float fClipNear=0.01f, float fClipFar=100.0f );
	void SetProjectionMatrix(D3DXMATRIX &matProjection);

	D3DXMATRIX& GetProjectionMatrix(){ return m_projection; }
};

typedef CMglProjectionMatrixManager CMglPerspectiveMatrixManager;

#endif//__MglProjectionMatrixManager_H__
