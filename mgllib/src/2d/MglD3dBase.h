#ifndef __MglD3dBase_H__
#define __MglD3dBase_H__

class DLL_EXP CMglD3dBase : public CMyuReleaseBase
{
protected:
	_MGL_IDirect3DDevice* d3d;		//	D3DDevice�ւ̃|�C���^
	_MGL_IDirect3DDevice* m_d3d;	//	D3DDevice�ւ̃|�C���^
	_MGL_IDirect3DDevice* m_pD3dDev;//	D3DDevice�ւ̃|�C���^

	//	�������\�b�h�i�`�F�b�N�p�j
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

public:
	CMglD3dBase(){
		m_myudg = NULL;
		d3d = NULL;
		m_d3d = NULL;
		m_pD3dDev = NULL;
	}
	virtual ~CMglD3dBase(){
		//DbBaseRelease();
		CMglD3dBase::Release();
	}

	//	������/�J��
	virtual void Init( _MGL_IDirect3DDevice* in_pD3d ){
		d3d = in_pD3d;
		m_d3d = in_pD3d;
		m_pD3dDev = in_pD3d;

		if ( m_pD3dDev == NULL )
			MyuThrow(MGLMSGNO_GRPMGR(320), "CMglD3dBase::Init()  Direct3DDevice ������������Ă��܂���B");
	}
	virtual void Release(){}
	//void DbBaseRelease(){}
};
typedef CMglD3dBase CMglD3dClassBase;

////////////////////////////////////////////////////////////

template <typename T> class CMglD3dIBase : public CMglD3dBase
{
protected:
	T* m_pI;

	void CreatedCheck(){
		InitCheck();
		if ( m_pI != NULL )
			MyuThrow(MsgNoBase()+1, "%s  ���ɓǂݍ��ݍςł��B", ClassName());
	}
	void CreateCheck(){
		InitCheck();
		if ( m_pI == NULL )
			MyuThrow(MsgNoBase()+2, "%s  �쐬����Ă��܂���B", ClassName());
	}

	virtual int MsgNoBase(){return 0;}
	virtual const char* ClassName(){return "????";}

public:
	CMglD3dIBase(){
		m_pI = NULL;
	}
	virtual ~CMglD3dIBase(){
		//	�����J���p�̃��t�@�����X���폜
		//MGLGRP_DELREF();  CMglD3dBase::Release()���牼�z�֐��ł��̃N���X��Release()���Ă΂�邱�Ƃ͕������Ă�̂ŕʂɕK�v�Ȃ�����
	}

	//	������/�J��
	virtual void Init( _MGL_IDirect3DDevice* in_pD3d ){
		CMglD3dBase::Init(in_pD3d);
	}

	virtual void Release(){
		SAFE_RELEASE(m_pI);
		CMglD3dBase::Release();
	}
};

#endif//__MglD3dBase_H__
