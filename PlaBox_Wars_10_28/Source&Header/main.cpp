
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include <crtdbg.h>
#define	_SCENE_CL_

#include "input.h"
#include "graphic.h"
#include "main.h"
#include "scene.h"
#include "camera.h"
#include "Audio.h"
#include "game.h"
#include "object.h"

BOOL	g_bActive;
HWND	g_hWnd;

extern CL_PLAYER	player;
extern CL_ENEMY		enemy [ENEMY_MAX];
extern CL_WALL		object [OBJECT_MAX];


//==================================================================================
//
//	メッセージ処理
//
//=================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	//case WM_ACTIVATE:
	//	if (wp == WA_INACTIVE)
	//	    g_bActive = FALSE;
	//	else
	//	    g_bActive = TRUE;

	//	// Set exclusive mode access to the mouse based on active state
	//	SetAcquire();
	//	return 0;

	case WM_KEYDOWN:
		if(wp==VK_ESCAPE){
			PostQuitMessage (0);
			return 0;
		}

		break;
	case WM_DESTROY:

		PostQuitMessage (0);
		
		return 0;
	}
	return DefWindowProc (hWnd, msg, wp, lp);
}

//----------------------------------------------------------------------
//
//	メインルーチン
//
//----------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR IpCmdLine, int nCmdShow )
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(350);


	MSG msg;
	HWND hWnd;
	WNDCLASS winc;

	// Windows情報の設定
	winc.style			= CS_HREDRAW | CS_VREDRAW; //ウインドのサイズが変わった時再描画する処理
	winc.lpfnWndProc	= WndProc;	// 送られてきたメッセージを元に様々な処理を行う関数
	winc.cbClsExtra		= winc.cbWndExtra = 0;
	winc.hInstance		= hInstance;
	winc.hIcon			= LoadIcon( NULL, IDI_APPLICATION);
	winc.hCursor		= LoadCursor( NULL, IDC_ARROW);
	winc.hbrBackground	= (HBRUSH) GetStockObject (WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("TITLE");

	// Windowsの登録
	if ( !RegisterClass (&winc))	return 0;

	// Windowsの生成
	int dH = GetSystemMetrics (SM_CYCAPTION) + GetSystemMetrics (SM_CYFRAME) * 2;
	int dW = GetSystemMetrics (SM_CXFRAME) * 2;

	hWnd = CreateWindow(
		TEXT("TITLE"),
		TITLE,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,		// x
		CW_USEDEFAULT,		// y
		WIN_WIDTH + dW,			// Width
		WIN_HEIGHT + dH,			// Height
		NULL, NULL, hInstance, NULL
	);

	if ( !hWnd ) return 0;

	// Direct3D周りの初期化処理
	if ( !InitRender(hWnd) ) return 0;

	// ダイレクトインプットの初期化
	InitDinput(hWnd);

	// サウンドの初期化
	InitXAudio2();

	// シーンクラスの呼び出し
	CL_SCENE	Cl_manageScene;

	//	カメラの初期化
	InitCamera();

	g_hWnd = hWnd;

	srand(( unsigned )time( NULL ));

	DWORD SyncOld = timeGetTime();
	DWORD SyncNow;

	timeBeginPeriod(1);

	ZeroMemory (&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		Sleep(1);

		if ( PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}

		else
		{
			SyncNow = timeGetTime();

			if (SyncNow - SyncOld >= 1000 / 60)
			{
				SceneChangeFlagFalse();

				// 初期化
				Cl_manageScene.Init();

				//	マウス座標の取得
				CursorSet ( hWnd );

				// 処理
				Cl_manageScene.Control();
				
				// 描画前処理
				BeginRender();

				// 描画
				Cl_manageScene.Render();
				
				// 描画後処理
				EndRender();

				// 描画前処理
				BeginDraw ();
				
				Cl_manageScene.Draw ();

				// 描画後処理
				EndRender();

				// 表示
				pD3Device -> Present ( NULL, NULL, NULL, NULL );

				SyncOld = SyncNow;

			}
		}
	}

	timeEndPeriod(1);

	pCl_scene->Release();
	_CL_DELETE(pCl_scene);

	FreeDx ();

	return (int)msg.wParam;
}

//作成したDirectXオブジェクトの解放
//メモリ解放処理
void FreeDx()
{
	if(pKeyDevice)
	{
		pKeyDevice -> Unacquire();
	}
	if(pMouseDevice)
	{
		pMouseDevice -> Unacquire();
	}

	SAFE_RELEASE (pKeyDevice);
	SAFE_RELEASE (pMouseDevice);
	SAFE_RELEASE (pDinput);

	ReleaseXAudio2();

	ReleaseRender();
}
