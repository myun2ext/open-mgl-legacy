//////////////////////////////////////////////////////////
//
//	MglDirectMusicBase  v0.10.51 05/01/29
//		- DirectMusicクラス
//
//	v0.10.50 04/12/26
//	・色々改良
//
//	v0.10.51 05/01/29
//	・ループ再生のロジックをちーとばかし改良
//
//////////////////////////////////////////////////////////

#ifndef __MglDirectMusicBase_H__
#define __MglDirectMusicBase_H__

//	DirectShow
#include <DShow.h>/*
#ifdef _DEBUG
	#pragma comment(lib, "Strmbasd.lib")
#else
	#pragma comment(lib, "Strmbase.lib")
#endif//_DEBUG*/

//#include "MyuStringNameMap.h"

#include "MyuReleaseBase.h"

//	クラス宣言
//class DLL_EXP CMglDirectMusicBase
class DLL_EXP CMglDirectMusicBase : public CMglReleaseBase	//	2009/09/05
{
private:
	IDirectMusicLoader8* m_pLoader;
	IDirectMusicPerformance8* m_pPerformance;
	//IDirectMusicSegment8 *segments[256];

	typedef map<string,IDirectMusicSegment8*> SEG_TYPE;
	typedef SEG_TYPE::iterator SEG_ITR;
	SEG_TYPE m_segments;

	BOOL m_flgEnable; // <-- コイツはbaseにあるべきじゃない気が…
	
	//CMyuStringNameMap m_segments;

	//	存在チェック
	void InitCheck() {
		if ( m_pLoader == NULL || m_pPerformance == NULL )
			Init();
	}
	BOOL IsExist( const char* szSegmentName )
	{
		SEG_ITR itr = m_segments.find( szSegmentName );
		if ( itr == m_segments.end() )
			return FALSE;
		else
			return TRUE;
	}
	void ExistChk( const char* szSegmentName )
	{
		if ( IsExist(szSegmentName) == FALSE )
			MyuThrow( 0, "CMglDirectMusicBase  m_segments[%s]は存在しない、または正しく初期化されていません。", szSegmentName );
	}

public:
	CMglDirectMusicBase();
	virtual ~CMglDirectMusicBase();
	void InitEx( HWND hWnd, const char *szBaseDirectory, DWORD dwDefaultPathType, DWORD dwPerformanceChannelCount, DWORD dwFlags=DMUS_AUDIOF_ALL );
	void Init( HWND hWnd, const char *szBaseDirectory="" ){
		InitEx( hWnd, szBaseDirectory, DMUS_APATH_DYNAMIC_STEREO, 64 );}
	void Init( const char *szBaseDirectory="" ){ Init( NULL, szBaseDirectory ); }
	void Release();

	void Load( const char* szAudioFile, const char* szAlias=NULL );
	void PlaySegment( const char* szSegmentName );
	void Play( const char* szSegmentName ){PlaySegment(szSegmentName);}
	void LoopPlay( const char* szSegmentName, DWORD dwLoopCount=DMUS_SEG_REPEAT_INFINITE ){
		LoopPlaySegment(szSegmentName,dwLoopCount); }
	void LoopPlaySegment( const char* szSegmentName, DWORD dwLoopCount=DMUS_SEG_REPEAT_INFINITE );
	void StopSegment( const char* szSegmentName );
	void StopSegment( IDirectMusicSegment* pSegment );
	void Stop( const char* szSegmentName );
	void StopAll();

	void SetVolume( int nVolume=0 );

	void Disable(){
		/*
			全ての再生を停止。
			ただし、再生されていないセグメントをStopSegment()するとどうなるかは不明。
		*/
		StopAll();

		m_flgEnable = FALSE;
	}
	void Enable(){ m_flgEnable = TRUE; }

	//	未実装
	//void PauseSegment( const char* szSegmentName ){}-

	IDirectMusicSegment8* GetSegmentPtr( const char* szSegmentName );
};

#endif//__MglDirectMusicBase_H__