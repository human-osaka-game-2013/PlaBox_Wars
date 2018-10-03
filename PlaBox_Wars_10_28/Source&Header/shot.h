//	shot.h	�e�ۂ̎�ȏ���


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
	bool	Shot_flag;		//	���˃t���O
	int		iBulletType;	//	�e�̎��
	int		iCharaType;		//	���ˎ�̎��

	float	gx,gy,gz;		//	�e�̒��e�_
	float	spx,spy,spz;	//	fr�Ԃ̒e�̈ړ���
	float	shot_time;		//	�e�̏����܂ł̎���

	CL_BULLET()	{	ZeroMemory( this, sizeof(CL_BULLET) );	}

	void	InitBullet( CL_BULLET* , int = ENEMY_B_MAX );		//������

	//	����1�F�e�e�N���X�̔z��̐擪�|�C���^�A2�F���ˈʒu�A3�F���e�_�A
	//	4�F����̎�ށA5�F���ˎ�A6�F1�̔z��̗v�f��
	bool	MadeBullet( CL_BULLET* , D3DXVECTOR3 *vecPos, D3DXVECTOR3 *ImpactPos,
			int, int, eWEAPON ,int = ENEMY_B_MAX );	//����
	
	void	ShotBullet( CL_BULLET* , int iArrayNum = ENEMY_B_MAX );		//���s
	void FreeMesh(){}
	void FreeMesh(CL_BULLET *clCharaBullet, int iArrayNum);

	//�_���[�W
	int GetDamage(){ return m_Damage; }

private:
	int m_Damage;
};

extern int g_shot;
