#include "stdafx.h"
void Mp3Test();

//	メインフレームクラス
class CMglTestFrame : public CMglguiWindow
{
private:
	CMglAghImage m_img;
public:
	void OnInit(){
		m_img.Load("test.jpg");
		CMglguiWindow::RegistControl(&m_img);

		Mp3Test();

		m_audio.Load("hoge.wav");
		m_audio.Load("hoge2.wav");

		//	キーボードイベントハンドラ登録
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_Z,
			(MGL_KB_EVT_HANDLER_CALLBACK)PlaySoundZ);

		//	キーボードイベントハンドラ登録
		RegistKbHandler(
			MGL_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN,
			DIK_X,
			(MGL_KB_EVT_HANDLER_CALLBACK)PlaySoundX);
	}
	bool PlaySoundZ(){
		m_audio.Play("hoge.wav");
		return true;
	}

	bool PlaySoundX(){
		m_audio.Play("hoge2.wav");
		return true;
	}
};
CMglTestFrame g_frame;

//	WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{

	g_frame.Start();
	return 0;
}


void Mp3Test(){

		// DirectShowのインスタンス宣言
	IGraphBuilder *p_graph=NULL;
	IMediaControl *p_control=NULL;
	IMediaEvent   *p_event=NULL;

	HRESULT hr;   // 処理結果

	long event_code;   // イベントコード

	// フィルタグラフのインスタンスを生成
	hr=CoCreateInstance(
			CLSID_FilterGraph,	  // フィルタグラフのクラスID
			NULL,				// 非アグリゲートオブジェクト
			CLSCTX_INPROC_SERVER,   // 呼び出し側と同じプロセスで実行
			IID_IGraphBuilder,	  // グラフビルダでオブジェクト間通信する
			(void **)&p_graph);	 // インスタンスを入れるポインタ

	// フィルタグラフからIMediaControlを取得する
	hr=p_graph->QueryInterface(
			IID_IMediaControl,	  //IMediaControlのインターフェース指定
			(void **)&p_control);   //IMediaControlを入れるポインタ

	// フィルタグラフからIMediaEventを取得する
	hr=p_graph->QueryInterface(
			IID_IMediaEvent,		//IMediaEventのインターフェース指定
			(void **)&p_event);	 //IMediaEventを入れるポインタ

	// 再生するファイルを指定する
	hr=p_graph->RenderFile(
			L"kanon_lstrgt_org.mp3",  // メディアファイル名
			NULL);								// 予約(NULL固定)

	// ファイルのレンダリングに成功したらグラフを実行する
	if(SUCCEEDED(hr))
	{
	  // グラフを実行する
	  hr=p_control->Run();

	 if( hr == S_OK )
	  {
		// グラフの実行に成功したら完了するまでイベントを待つ
		p_event->WaitForCompletion(
			INFINITE,				 // イベントタイマー(無期限)
			&event_code);			 // イベント結果コード
	  }
	 else
		 MessageBox(NULL,"sdfsdfd",NULL,NULL);
	}

	// IMediaControlを開放する
	p_control->Release();

	// IMediaEventを開放する
	p_event->Release();

	// フィルタグラフを開放する
	p_graph->Release();
}