#pragma once
#include "Lib.h"
#include "scene.h"

// ゲームタイトル
#define TITLE	TEXT("プラ箱戦記")



extern LPDIRECTINPUT8		pDinput;		//インプット -> 入力処理
extern LPDIRECTINPUTDEVICE8	pKeyDevice;		 //キーデバイス -> 外部キー入力
extern LPDIRECTINPUTDEVICE8	pMouseDevice;	//マウスデバイス -> 外部マウス入力


void FreeDx ();