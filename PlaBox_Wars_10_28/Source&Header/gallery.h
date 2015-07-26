#pragma once
#include "scene.h"

//	ギャラリーのクラス
class CL_GALLERY:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	ギャラリーの初期化
	void Control ();	//	ギャラリーの処理
	void Render ();		//　ギャラリーの3D描画
	void Draw ();		//	ギャラリーの2D描画
	void Release();
private:

};