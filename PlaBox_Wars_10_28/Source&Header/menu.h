#pragma once
#include "scene.h"

//	メニューのクラス
class CL_MENU:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	メニューの初期化
	void Control ();	//	メニューの処理
	void Render ();		//　メニューの描画
	void Release();
private:

};