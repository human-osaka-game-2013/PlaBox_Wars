#pragma once
#include "scene.h"

//	オプションのクラス
class CL_OPTION:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	オプションの初期化
	void Control ();	//	オプションの処理
	void Render ();		//　オプションの3D描画
	void Draw ();		//	オプションの2D描画
	void Release();
private:

};