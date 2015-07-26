#pragma once
#ifndef	_SCENE_H_
#define	_SCENE_H_


void SceneChangeFlagFalse();
//	シーン制御のクラスポインタの削除
#define	_CL_DELETE(p)	{ if(p) { delete (p); (p) = NULL;} }

#endif
//	シーンの種類
enum eSCENE
{
	S_NONE,		//	シーンなし

	//alpha
	S_TITLE,	//	タイトル
	S_GAME,		//	ゲーム
	S_RESULT,	//	リザルト

	//beta
	S_LOGO,		//	ロゴ
	S_MENU,		//	メニュー
	S_OPTION,	//	オプション
	S_GALLERY,	//	ギャラリー

	//mode
	S_S_MODE,	//　シングルプレイモード
	S_M_MODE,	//	マルチプレイモード
	S_TA_MODE,	//	タイムアタックモード
	S_VS_MODE,	//	対戦モード

	//end
	S_END,		//	ゲーム終了

	S_GAMEOVER,	//　ゲームオーバー

	S_MAX		//	シーンの数
};


//=================	クラス	=======================

//	各シーンごとの共通の継承元のクラス
class	CL_MANAGE_SCENE
{
public:
	virtual void Init ()	= 0;		//	初期化
	virtual void Control ()	= 0;	//	基本処理
	virtual void Render ()	= 0;	//	3D描画
	virtual void Draw ()	= 0;	//	2D描画
	virtual void Release() = 0;
	//	シーン切り替え
	//	切り替えたいシーンを引数に入れる
	static void ChangeScene ( int nextScene );
};

#ifdef	_SCENE_CL_
//	シーン制御クラス
class	CL_SCENE:public	CL_MANAGE_SCENE
{
public:
	CL_SCENE();		//	private内のシーンの変数をここで初期化

	void Init ();		//	初期化
	void Control ();	//	基本処理
	void Render ();		//	3D描画
	void Draw ();		//	2D描画
	void Release();
private:

};

#endif

extern CL_MANAGE_SCENE*	pCl_scene;