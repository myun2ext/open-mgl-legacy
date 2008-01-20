//////////////////////////////////////////////////////////
//
//	MglBitmapData - D3DLOCKED_RECT�Ǘ��N���X

#ifndef __MglBitmapData_H__
#define __MglBitmapData_H__

//	�N���X�錾
class DLL_EXP CMglBitmapData
{
protected:
	//D3DLOCKED_RECT m_lockedRect;
	int m_nPitch;
	BYTE* m_pBits;
	int m_nHeight;

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglBitmapData(D3DLOCKED_RECT lockedRect, int nHeight){
		//m_lockedRect = lockedRect;
		m_nPitch = lockedRect.Pitch;
		m_pBits = (BYTE*)lockedRect.pBits;
		m_nHeight = nHeight;
	}
	virtual ~CMglBitmapData(){}

	D3DCOLOR* GetHorizontalLine(int y){
		if ( y >= m_nHeight )
			return NULL;
		return (D3DCOLOR*)(m_pBits + m_nPitch*y);
	}
	D3DCOLOR* GetLine(int y){ return GetHorizontalLine(y); }
	D3DCOLOR Get(int x,int y){
		D3DCOLOR* p = GetHorizontalLine(y);
		if ( p == NULL )
			return NULL;
		if ( x >= m_nPitch )
			return NULL;
		return p[x];
	}

	int GetWidth(){ return m_nPitch; }
	int GetHeight(){ return m_nHeight; }
};

#endif//__MglBitmapData_H__
