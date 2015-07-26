//	shot.h	弾丸の主な処理


#define PLAYER_B_MAX 30
#define ENEMY_B_MAX	10
#define BSP		 1
#define SHOTTIME 5

#define	RIFLE_OF_FIRE	3
#define BAZOOKA_ON_FIRE 1
#define MG_OF_FIRE 5

#define RECOIL_OF_RIFLE		0.3f
#define RECOIL_OF_MG		0.2f
#define RECOIL_OF_BAZOOKA 0.f

#define INTERVAL_OF_RIFLE	0.12f
#define INTERVAL_OF_MG 	0.1f
#define INTERVAL_OF_BAZOOKA 2.f

#define IMPACT_MAX_	10.0f

#include "graphic.h"


enum	eWEAPON
{
	W_NONE,

	W_RIFLE,

	W_MG,

	W_BAZOOKA,

	W_GATLING,

	W_MAX
};

enum	eWEAPON_RECOIL
{
	W_NONE_RECOIL,

	W_RIFLE_RECOIL = 60,

	W_MG_RECOIL,

	W_BAZOOKA_RECOIL,

	W_GATLING_RECOIL,

	W_MAX_RECOIL
};

enum	eWEAPON_MAX_AMMO
{
	PL_AR_MAX_AMMO		= 120,
	PL_MG_MAX_AMMO		= 150,
	PL_BAZ_MAX_AMMO		= 10,
	PL_GAT_MAX_AMMO		= 180,

	ENE_AR_MAX_AMMO		= 120,
	ENE_MG_MAX_AMMO		= 100,
	ENE_BAZ_MAX_AMMO	= 10,
	ENE_GAT_MAX_AMMO	= 120
};

class CL_BULLET:public CL_THING
{
public:
	bool	Shot_flag;		//	発射フラグ
	int		iBulletType;	//	弾の種類
	int		iCharaType;		//	発射主の種類

	float	gx,gy,gz;		//	弾の着弾点
	float	spx,spy,spz;	//	fr間の弾の移動量
	float	shot_time;		//	弾の消失までの時間

	CL_BULLET()	{	ZeroMemory( this, sizeof(CL_BULLET) );	}

	void	InitBullet( CL_BULLET* , int = ENEMY_B_MAX );		//初期化

	//	引数1：銃弾クラスの配列の先頭ポインタ、2：発射位置、3：着弾点、
	//	4：武器の種類、5：発射主、6：1の配列の要素数
	bool	MadeBullet( CL_BULLET* , D3DXVECTOR3 *vecPos, D3DXVECTOR3 *ImpactPos,
			int, int, eWEAPON ,int = ENEMY_B_MAX );	//精製
	
	void	ShotBullet( CL_BULLET* , int iArrayNum = ENEMY_B_MAX );		//実行
	void FreeMesh(){}
	void FreeMesh(CL_BULLET *clCharaBullet, int iArrayNum);

	//ダメージ
	int GetDamage(){ return m_Damage; }

private:
	int m_Damage;
};

extern int g_shot;
