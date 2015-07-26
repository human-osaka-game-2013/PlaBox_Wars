
#define TANK_HP			25
#define TANK2_HP		25
#define FIGHTER_HP		10
#define FIGHTER2_HP		10
#define SOLDIER_HP		15
#define SOLDIER2_HP		15
#define BOSS_HP			30

//ÉvÉåÉCÉÑÅ[î≠å©ãóó£
#define SHOT_LANGE 30.f

#define FINDLENGS		40.f
#define NEARLENGS		20.f
#define FARLENGS		30.f
//ìGÇÃëÂëÃÇÃúpújà íu
#define TANK_BASE D3DXVECTOR3(0.f, 0.f, 0.f)
#define TANK2_BASE D3DXVECTOR3(-15.f, 0.f, 25.f)
#define FIGHTER_BASE D3DXVECTOR3(25.f, 8.f, 15.f)
#define FIGHTER2_BASE D3DXVECTOR3(25.f, 8.f, -15.f)
#define SOLDIER_BASE D3DXVECTOR3(15.f, 0.f, -25.f )
#define SOLDIER2_BASE D3DXVECTOR3(-25.f, 0.f, 15.f)
#include "game.h"
#include "Lib.h"
extern	CL_ENEMY enemy[ENEMY_MAX];

#define BOSS_MOVE_VOL_1	0.2f
#define BOSS_MOVE_VOL_2	0.3f

//class	CL_TANK:public CL_ENEMY
//{
//
//};
//
//class	CL_ROBOT:public CL_ENEMY
//{
//
//};
//
//class	CL_FIGHTER:public CL_ENEMY
//{
//
//};