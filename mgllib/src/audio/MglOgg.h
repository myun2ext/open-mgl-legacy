//////////////////////////////////////////////////////////
//
//	CMglOgg
//		- �G���[�����t��
//
//////////////////////////////////////////////////////////

#ifndef __MglOgg_H__
#define __MglOgg_H__

#include "MglBgmBase.h"
#include "Vox.h"

#define VOX_DLL_NAME		"Vox.dll"
#define VOX_LOOP_MAX		(0x7fffffff)
#define VOX_DEFAULT_VOLUME	(1.0f)

//	�N���X�錾
class DLL_EXP CMglOgg : public CMglBgmBase
{
private:
	HINSTANCE m_hDll;
	Vox* m_pDriver;
	BOOL m_loadFlg;
	BOOL m_useFlg;
	float m_fNowVolume;

	//	�������`�F�b�N
	void InitCheck() {
		if ( m_pDriver == NULL )
			Init();
	}	
	void LoadCheck() {
		if ( m_loadFlg != TRUE )
			MyuThrow( 0, "CMglOgg  Load()���Ɏ��s���Ă��������B" );
	}	

public:
	CMglOgg();
	virtual ~CMglOgg();

	//	������/�I�[�n
	void Init();
	void Release();
	void Load( const char* szOggFile );
	void UnLoad();
	void Unload(){ UnLoad(); }

	//	�Đ�����n
	void Play( int nLoopCnt );
	void Play(){ Play(VOX_LOOP_MAX); }
	void LoopPlay( int nLoopCnt=VOX_LOOP_MAX ){
		Play(nLoopCnt);
	}
	void StopLoop();
	void Pause();
	void SetVolume( float fVolume );
	void Fade( float fTargetVolume, int nFadeTimeMs );
	void FadeIn( int nFadeTimeMs ) { SetVolume(0); Fade( 1.0f, nFadeTimeMs ); }
	void FadeOut( int nFadeTimeMs ) { Fade( 0, nFadeTimeMs ); }


	void Stop(){ Pause(); }
	void SetLastLoop(){ StopLoop(); }
	void SetVolume( int nVolume=MGL_VOLUME_MAX ){ SetVolume(nVolume/100.0f); }
	void SetBalance( int nBalance=MGL_PAN_CENTER ){}


	void Enable() { m_useFlg = TRUE; }
	void Disable() { m_useFlg = FALSE; }
	Vox* GetVoxPtr() { return m_pDriver; }
};

//typedef CMglOgg CMglOgg;
//class CMglOgg : public CMglOgg{};
//typedef CMglOgg CMglMusic;

#endif//__MglOgg_H__
