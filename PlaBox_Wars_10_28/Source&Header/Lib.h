#pragma once

#define DIRECTINPUT_VERSION 0x0800

//プリプロ関連ヘッダーファイル
#include <Windows.h>	//window基礎ファイル
#include <dinput.h>		//キー入力
#include <MMSystem.h>	//wav再生
#include <XAudio2.h>	//mp3,wma再生

//ライブラリ読込
#pragma comment	(lib, "d3dx9d.lib")
#pragma comment	(lib, "d3dxof.lib")
#pragma comment	(lib, "dinput8.lib")	
#pragma comment	(lib, "dsound.lib")	//wav再生
#pragma comment	(lib, "dxguid.lib")
#pragma comment	(lib, "winmm.lib")

#define SAFE_RELEASE(p) { if(p) { (p) -> Release(); (p) = NULL; } }
#define NULL_DELETE(p) { if(p) { delete (p); (p) = NULL; } }
#define NULL_ARRAY_DELETE(p) { if(p) { delete[] (p); (p) = NULL; } }