#pragma once
#include "scene.h"

#define SUZI 5

//	リザルトのクラス
class CL_RESULT:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	リザルトの初期化
	void Control ();	//	リザルトの処理
	void Render ();		//	リザルトの3D描画
	void Draw ();		//	リザルトの2D描画
	void Release();
private:
	int Alpha;
	int TIME_Alpha;
	int SCORE_Alpha;
	int RANK_Alpha;
	int OSSAN_Alpha;

	bool timeflag;
	bool resultflag;
	int times; //タイム格納用変数
	int scores; //スコア格納用変数

	int tmp;
	int get;

	int dat[5];

	int resultCount;
	void settimes( float x, float y );
	

	struct TAIMU
	{
		float x;	
		float y;	
		float Scall;
	};
	TAIMU time[SUZI];

	struct SCORE
	{
		float x;	
		float y;	
		float Scall;
	};
	SCORE score[SUZI];

};