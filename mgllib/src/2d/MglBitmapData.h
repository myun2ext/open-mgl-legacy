//////////////////////////////////////////////////////////
//
//	MglBitmapData - �e�N�X�`���Ǘ��N���X

#ifndef __MglBitmapData_H__
#define __MglBitmapData_H__

//	�N���X�錾
class DLL_EXP CMglBitmapData
{
protected:
	D3DLOCKED_RECT m_lockedRect;

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglBitmapData(D3DLOCKED_RECT lockedRect){
		m_lockedRect = lockedRect;
	}
	virtual ~CMglBitmapData(){}

};

#endif//__MglBitmapData_H__
