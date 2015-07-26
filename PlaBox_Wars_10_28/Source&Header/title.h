#pragma once
#include "scene.h"

#include <stdlib.h> /**/
#include <time.h>   /**/

#define DANKON		15

//	タイトルのクラス
class CL_TITLE:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	タイトルの初期化
	void Control ();	//	タイトルの処理
	void Render ();		//　タイトルの3D描画
	void Draw ();		//	タイトルの2D描画
	void Release();
	
private:
	struct Tama
	{
		float x;	// 弾の位置
		float y;	// 弾の位置
		bool  Hit;	// true の時だけ表示
		float Scall;// 弾の縦横の縮尺
	};



	Tama tama[DANKON];
	int t_cnt;          //弾痕カウント
	float Rand_X[DANKON], Rand_Y[DANKON];  //乱数格納
	float h;             //母数カウント


	float tl_x;     // タイトルのX座標
	float tl_y;     // タイトルのY座標
	int   Alpha;
	float t_Scall;  // タイトルの縦横の縮尺

	float menu_x;
	float menu_y;

	int Run;       // 移動方向の乱数

	float t_bX;    // タイトル座標の格納
	float t_bY;    // タイトル座標の格納
	
};
