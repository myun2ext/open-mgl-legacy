//////////////////////////////////////////////////////////
//
//	MglDirectShowBase  v0.10.51 05/01/29
//		- DirectMusic�N���X
//
//	v0.10.50 04/12/26
//	�E�F�X����
//
//	v0.10.51 05/01/29
//	�E���[�v�Đ��̃��W�b�N�����[�Ƃ΂�������
//
//////////////////////////////////////////////////////////

#ifndef __MglDirectShowBase_H__
#define __MglDirectShowBase_H__

#include "MglBgmBase.h"

//	DirectShow
#include <DShow.h>

//	�N���X�錾
class DLL_EXP CMglDirectShowBase : public IMglBgmBase, public CMyuReleaseBase
{
private:
	// DirectShow�̃C���X�^���X�錾
	IGraphBuilder *m_pGraph;
	IMediaControl *m_pControl;
	IMediaEvent *m_pEvent;
	IBaseFilter* m_pAudioRendererFilter;
	IBasicAudio* m_pBasicAudio;
	BOOL m_bRunReady;

	//	���݃`�F�b�N
	void InitCheck() {
		if ( m_pGraph == NULL || m_pControl == NULL || m_pEvent == NULL )
			Init();
	}
	void EnableAudioExControl();

public:
	CMglDirectShowBase();
	virtual ~CMglDirectShowBase();
	void Init( HWND hWnd );
	void Init(){ Init(NULL); }
	void Release();

	void Load( const char* szMediaFile );
	void Play();
	void LoopPlay(DWORD dwLoopCount=MGL_AUDIO_LOOP_MAX );
	void Stop();
	void Pause();

	void SetVolume( int nVolume=MGL_VOLUME_MAX );	//	100����
	void SetBalance( int nBalance=MGL_PAN_CENTER );	//	-100�`100

	//void EnableAudioExControl();

	//	����DirectX�ϐ��̎擾
	IGraphBuilder* GetGraphBuilderPtr(){ return m_pGraph; }
	IMediaControl* GetMediaControlPtr(){ return m_pControl; }
	IMediaEvent* GetMediaEventPtr(){ return m_pEvent; }
	/*	�ʂɗv��Ȃ���EnableAudioExControl()�ĂԂ̂��K�v�E�E�E
	IBaseFilter* GetBaseFilterPtr(){ return m_pAudioRendererFilter; }
	IBasicAudio* GetBasicAudioPtr(){ return m_pBasicAudio; }*/

	//	* NotImplemented!! *
	void LoopPlay( int nLoopCnt=MGL_AUDIO_LOOP_MAX ){}
	void SetLastLoop(){}
	void Unload(){}
};

#endif//__MglDirectShowBase_H__