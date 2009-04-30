#ifndef __MglD3dBase_H__
#define __MglD3dBase_H__

class DLL_EXP CMglD3dBase : public CMyuReleaseBase
{
protected:
	_MGL_IDirect3DDevice* d3d;		//	D3DDeviceへのポインタ
	_MGL_IDirect3DDevice* m_d3d;	//	D3DDeviceへのポインタ
	_MGL_IDirect3DDevice* m_pD3dDev;//	D3DDeviceへのポインタ

	//	内部メソッド（チェック用）
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

	//	初期化/開放
	virtual void Init( _MGL_IDirect3DDevice* in_pD3d ){
		d3d = in_pD3d;
		m_d3d = in_pD3d;
		m_pD3dDev = in_pD3d;

		if ( m_pD3dDev == NULL )
			MyuThrow(MGLMSGNO_GRPMGR(320), "CMglD3dBase::Init()  Direct3DDevice が初期化されていません。");
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
			MyuThrow(MsgNoBase()+1, "%s  既に読み込み済です。", ClassName());
	}
	void CreateCheck(){
		InitCheck();
		if ( m_pI == NULL )
			MyuThrow(MsgNoBase()+2, "%s  作成されていません。", ClassName());
	}

	virtual int MsgNoBase(){return 0;}
	virtual const char* ClassName(){return "????";}

public:
	CMglD3dIBase(){
		m_pI = NULL;
	}
	virtual ~CMglD3dIBase(){
		//	自動開放用のリファレンスを削除
		//MGLGRP_DELREF();  CMglD3dBase::Release()から仮想関数でこのクラスのRelease()が呼ばれることは分かってるので別に必要ないかも
	}

	//	初期化/開放
	virtual void Init( _MGL_IDirect3DDevice* in_pD3d ){
		CMglD3dBase::Init(in_pD3d);
	}

	virtual void Release(){
		SAFE_RELEASE(m_pI);
		CMglD3dBase::Release();
	}
};

#endif//__MglD3dBase_H__
