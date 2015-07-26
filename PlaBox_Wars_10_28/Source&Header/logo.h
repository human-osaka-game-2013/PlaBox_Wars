#pragma once
#include "scene.h"


//	ロゴのクラス
class CL_LOGO:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	ロゴの初期化
	void Control ();	//	ロゴの処理
	void Render ();	//	ロゴの3D描画
	void Draw ();		//	ロゴの2D描画
	void Release();
private:
	int Alpha;
};
