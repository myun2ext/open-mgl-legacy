//////////////////////////////////////////////////////////
//
//	MglBitmapData - テクスチャ管理クラス

#ifndef __MglBitmapData_H__
#define __MglBitmapData_H__

//	クラス宣言
class DLL_EXP CMglBitmapData
{
protected:
	D3DLOCKED_RECT m_lockedRect;

public:
	//	コンストラクタ・デストラクタ
	CMglBitmapData(D3DLOCKED_RECT lockedRect){
		m_lockedRect = lockedRect;
	}
	virtual ~CMglBitmapData(){}

};

#endif//__MglBitmapData_H__
