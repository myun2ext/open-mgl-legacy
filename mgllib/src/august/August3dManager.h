//////////////////////////////////////////////////////////
//
//	August3dManager
//
//////////////////////////////////////////////////////////

#ifndef __August3dManager_H__
#define __August3dManager_H__

#include "agh.h"
#include "AugustCommon.h"
#include "Mgl3dManager.h"

//#pragma warning( disable : 4275 ) 


//	クラス宣言  /////////////////////////////////////////////////////////
//class DLL_EXP CAugust3dManager : public CAugustVisualControlBase
class DLL_EXP CAugust3dManager : public CAugustSemiVisualControlBase
//class DLL_EXP CAugust3dManager : public agh::CControlBase
{
private:
	typedef CAugustSemiVisualControlBase _BASE;

protected:
	//CMglGraphicManager *m_pGrp;

	/*virtual void OnRegist(CAugustGlobalCommon *pGlobal){
		_BASE::OnRegist(pGlobal);
	}*/

public:
	//	コンストラクタ
	CAugust3dManager(){
		//m_pGrp = NULL;
	}
};

///////////////////////////////////////////////////////////////////

#include "MglMesh.h"

//	メッシュ
class DLL_EXP CAugustMesh : public CAugust3dVisualControlBase
{
protected:
	CMglMesh m_mesh;
	//CMglWorldMatrixManager m_matrix;

	//	イベント
_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnDraw(){
		CMglWorldMatrixManager m_matrix;
		m_matrix.SetWorld(
			m_rotate.x, m_rotate.y, m_rotate.z,
			m_x, m_y, m_z );

		m_mesh.Draw();
	}

public:

	void Load(const char* szMeshFilePath){ m_mesh.Load(szMeshFilePath); }

	///////////////////////////////////////////////////////////////

	CMglMesh& Get(){ return m_mesh; }
};

#endif//__August3dManager_H__
