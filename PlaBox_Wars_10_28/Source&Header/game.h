#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#define	ONE_FR	60.f
#define JUMP_VOL	1.0f

#include "graphic.h"
#include "scene.h"
#include "shot.h"
#include "UI.h"
#include "effectMagager.h"

//	テキスト表示クラス
#include "TexString.h"

extern	HWND	g_hWnd;	//	ゲームモードでフォアグラウンドでマウスを使うための
						//	マウス初期化のための引数

//---------------------------------------------------------------------------------------
//
//	メインゲームで使う要素の列挙
//
//----------------------------------------------------------------------------------------
//	ゲームモードの種類
enum	eGAME_SCENE
{
	SELECT_MODE,

	SINGLE,

	MULTI,

	TIME_T,

	VERSUS,

	MODE_MAX
};

//	オブジェクトの種類
enum	eOBJECT
{
	SKY,

	ITEM,

	//WALL1,

	//TBC,

	OBJECT_MAX
};

enum	ePLAYER
{
	PLAYER1 = 1,

	PLAYER2,

	ENEMY,

	PLAYER_MAX
};

//	敵の種類
enum	eENEMY
{
	TANK,

	TANK2,

	FIGHTER,

	FIGHTER2,

	SOLDIER,

	SOLDIER2,

	BOSS,

	ENEMY_MAX
};
#endif

typedef struct
{
	int		iBulletType;
	int		iAmmo;

	bool	bUseFlag;

	float	fShotRecoil;	//連射後の反動のカウンタ
	float	fShotInterval;	//射撃時1発1発の間隔のカウンタ
	float	fShotCount;		//連射数カウンタ
	bool		fFireFlag;

}BULLET_INFO;

#ifndef	_GAME_CL_
//----------------------------------------------------------------------------------------
//
//	メインゲームで使うクラス
//
//----------------------------------------------------------------------------------------
//	メインゲームのクラス
class CL_GAME:public CL_MANAGE_SCENE
{
public:
	void	Init ();		//	メインゲームの初期化
	void	Control ();		//	メインゲームの処理
	void	Render ();		//	メインゲームの3D描画
	void	Draw ();		//	メインゲームの2D描画
	void	Release();

	int		SelectMode();
	int		iDeadCount;
	int		iGameCount;
	
	CEffectManager particle;	//	パーティクルクラスオブジェクト
	bool	bRenderMatrixUpdateFlag;	///<	パーティクル描画用に用意している、描画行列の更新フラグ（仮）
};
#endif

#ifndef	_CHARA_CL_

//	プレイヤーと敵の共通処理のクラス
class CL_OBJECT:public CL_THING
{
public:
	bool	deadFlag;	//	描画系及び、ゲーム内で使う死亡フラグ
	int		hitCount;	//	銃弾に当たったカウント
	int		HP;
	virtual	void	CharaInit ( int = 0 )	 = 0;	//	初期化
	virtual	void	CharaControl ( int = 0 ) = 0;	//	基本処理
	virtual	void	CharaRender ( int = 0 )	 = 0;	//	3D描画

	bool	GetDeadFlag()	{ return	deadFlag; }		//	死亡フラグの取得
};

//------------------------------------------------------------------
//
//	キャラクラス
//
//------------------------------------------------------------------

class	CL_CHARA
{
public:
	D3DXVECTOR3	vecImpactPoint;		//	着弾点x,y,z
	bool		bFireFlag;			//	発射フラグ
	
	//	追加日	12/16
	bool	bJumpFlag;
	bool	bDownFlag;
	float	y_prev,	y_temp;	//	ジャンプ時の位置保存用
	//---------------------------------------------

	//	引数1：射撃時1発1発の間隔、2：連射後の反動、3：連射数、4：武器種類
	virtual void	ShotControl ( float &, float &, float &, BULLET_INFO * ) = 0;	//	発射の制御
	
	//	追加日	12/19
	//
	virtual	void	Reload ( CL_CHARA* ) = 0;
	
	void	MoveZ( D3DXVECTOR3* , D3DXVECTOR3* , float );	//	プレイヤーZ軸前後移動
	void	MoveX( D3DXVECTOR3* , D3DXVECTOR3* , float );	//	プレイヤーX軸左右移動
	
	//	追加日	12/16
	void	Jump ( bool *, float *);
	//----------------------------------

	void	BulletRender ( CL_BULLET* , int = ENEMY_B_MAX );

	float	fRotateVolOfChange;
};

class CL_HOLE:public CL_OBJECT
{
public:
	void	CharaInit ( int = 0 );		//	初期化
	void	CharaControl ( int = 0 );	//	基本処理
	void	CharaRender ( int = 0 );	//	3D描画
	void	FreeMesh();

	//	追加日	2/10	亀田
	D3DXVECTOR3	vecPosOfTarget;	//	敵との位置関係(距離)
	D3DXVECTOR3	vecSita;		//	着弾面の法線ベクトル
	float	fSetSita;
	float	fEnemyRotateY;	//	前フレームのvecRotate.y

};

//------------------------------------------------------------------------------
//
//	プレイヤークラス
//
//------------------------------------------------------------------------------
class CL_PLAYER:public CL_OBJECT, public CL_CHARA
{
public:
	float	fShotRecoil;	//	連射後の反動のカウンタ
	float	fShotInterval;	//	射撃時1発1発の間隔のカウンタ
	float	fShotCount;		//	連射数カウンタ
	
	//	追加日	12/16
	int		iPlPoint;		//	獲得ポイント
	//---------------------------------------

	//CL_PLAYER ()	{	ZeroMemory ( this, sizeof(CL_PLAYER) );	}
	void	CharaInit ( int = 0 );		//	初期化
	void	CharaControl ( int = 0 );	//	基本処理
	void	CharaRender ( int = 0 );	//	3D描画

	//	変更しました。12/18
	//
	BULLET_INFO*	GetMainWeapon()	{ return	&mainWeapon; }
	BULLET_INFO*	GetSubWeapon()	{ return	&subWeapon; }

	//	引数1：射撃時1発1発の間隔、2：連射後の反動、3：連射数、4：武器種類
	void	ShotControl ( float &, float &, float &, BULLET_INFO * );	//	発射の制御

	CL_BULLET	clBullet [PLAYER_B_MAX];	//	プレイヤーの銃弾の数

	//	ボトルの使用関数
	//	引数：trueでボトル補充、falseでボトル消費
	//	返り値：補充、消費できた場合はtrue、できなかった場合はfalse
	bool	ChargeBpttle ( bool bCharge );

	void	Reload ( CL_CHARA* );
	//北川　Ammoを引き渡す関数を追加 01/27
	int		GetAmmoStock ( );
	D3DXVECTOR2 holepos[HOLE_MAX];
	int		GetBottleNum ( ) { return possessionBottle;};
	//----------------------------------------------------------------
	void FreeMesh();

private:
	//	変更しました。12/18
	//
	BULLET_INFO		mainWeapon;			//	メイン武器種類
	BULLET_INFO		subWeapon;			//	サブ武器種類
	//------------------------------------------------------
	int		possessionBottle;	//	保持しているボトル数
};

//------------------------------------------------------------------------------
//
//	敵クラス
//
//------------------------------------------------------------------------------
class CL_ENEMY:public CL_OBJECT, public CL_CHARA
{
public:
	float	fShotRecoil;	//	連射後の反動のカウンタ
	float	fShotInterval;	//	射撃時1発1発の間隔のカウンタ
	float	fShotCount;		//	連射数カウンタ
	void	CharaInit ( int = 0 );		//	初期化
	void	CharaControl ( int = 0 );	//	基本処理
	void	CharaRender ( int = 0 );	//	3D描画

	//	引数1：射撃時1発1発の間隔、2：連射後の反動、3：連射数、4：武器種類
	void	ShotControl ( float &, float &, float &, BULLET_INFO * );	//	発射の制御
	D3DXVECTOR3 basepos;
	D3DXVECTOR3 movegoalpos;
	bool	moveflag;
	int		movecount;
	int		hatecount;
	CL_BULLET	clBullet [ENEMY_B_MAX];
	CL_HOLE	clHitHole [PLAYER_B_MAX];

	void	Reload ( CL_CHARA* );

	int		iEnCount;
	void FreeMesh();
protected:
	//	変更しました。12/18
	//
	BULLET_INFO		mainWeapon;
	//----------------------------
	int		dropItem;
};
//------------------------------------------------------------------------------
//
//	障害物クラス
//
//------------------------------------------------------------------------------
class CL_WALL:public CL_OBJECT
{
public:
	void	CharaInit ( int = 0 );		//	初期化
	void	CharaControl ( int = 0 );	//	基本処理
	void	CharaRender ( int = 0 );	//	3D描画
	void FreeMesh();
protected:
	int		dropItem;
};

/*
	弾痕の貼り付け
	引数	敵クラスポインタ
*/
void PasteBulletHoles ( CL_ENEMY* pEen );	//	敵情報のみで貼り付けれる場合
//	旧バージョン
void PasteBulletHoles ( CL_ENEMY* clEnemy, CL_BULLET* pBullet );	

int Gettime(); //タイマー取得
#endif

