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

//	�e�L�X�g�\���N���X
#include "TexString.h"

extern	HWND	g_hWnd;	//	�Q�[�����[�h�Ńt�H�A�O���E���h�Ń}�E�X���g�����߂�
						//	�}�E�X�������̂��߂̈���

//---------------------------------------------------------------------------------------
//
//	���C���Q�[���Ŏg���v�f�̗�
//
//----------------------------------------------------------------------------------------
//	�Q�[�����[�h�̎��
enum	eGAME_SCENE
{
	SELECT_MODE,

	SINGLE,

	MULTI,

	TIME_T,

	VERSUS,

	MODE_MAX
};

//	�I�u�W�F�N�g�̎��
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

//	�G�̎��
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

	float	fShotRecoil;	//�A�ˌ�̔����̃J�E���^
	float	fShotInterval;	//�ˌ���1��1���̊Ԋu�̃J�E���^
	float	fShotCount;		//�A�ː��J�E���^
	bool		fFireFlag;

}BULLET_INFO;

#ifndef	_GAME_CL_
//----------------------------------------------------------------------------------------
//
//	���C���Q�[���Ŏg���N���X
//
//----------------------------------------------------------------------------------------
//	���C���Q�[���̃N���X
class CL_GAME:public CL_MANAGE_SCENE
{
public:
	void	Init ();		//	���C���Q�[���̏�����
	void	Control ();		//	���C���Q�[���̏���
	void	Render ();		//	���C���Q�[����3D�`��
	void	Draw ();		//	���C���Q�[����2D�`��
	void	Release();

	int		SelectMode();
	int		iDeadCount;
	int		iGameCount;
	
	CEffectManager particle;	//	�p�[�e�B�N���N���X�I�u�W�F�N�g
	bool	bRenderMatrixUpdateFlag;	///<	�p�[�e�B�N���`��p�ɗp�ӂ��Ă���A�`��s��̍X�V�t���O�i���j
};
#endif

#ifndef	_CHARA_CL_

//	�v���C���[�ƓG�̋��ʏ����̃N���X
class CL_OBJECT:public CL_THING
{
public:
	bool	deadFlag;	//	�`��n�y�сA�Q�[�����Ŏg�����S�t���O
	int		hitCount;	//	�e�e�ɓ��������J�E���g
	int		HP;
	virtual	void	CharaInit ( int = 0 )	 = 0;	//	������
	virtual	void	CharaControl ( int = 0 ) = 0;	//	��{����
	virtual	void	CharaRender ( int = 0 )	 = 0;	//	3D�`��

	bool	GetDeadFlag()	{ return	deadFlag; }		//	���S�t���O�̎擾
};

//------------------------------------------------------------------
//
//	�L�����N���X
//
//------------------------------------------------------------------

class	CL_CHARA
{
public:
	D3DXVECTOR3	vecImpactPoint;		//	���e�_x,y,z
	bool		bFireFlag;			//	���˃t���O
	
	//	�ǉ���	12/16
	bool	bJumpFlag;
	bool	bDownFlag;
	float	y_prev,	y_temp;	//	�W�����v���̈ʒu�ۑ��p
	//---------------------------------------------

	//	����1�F�ˌ���1��1���̊Ԋu�A2�F�A�ˌ�̔����A3�F�A�ː��A4�F������
	virtual void	ShotControl ( float &, float &, float &, BULLET_INFO * ) = 0;	//	���˂̐���
	
	//	�ǉ���	12/19
	//
	virtual	void	Reload ( CL_CHARA* ) = 0;
	
	void	MoveZ( D3DXVECTOR3* , D3DXVECTOR3* , float );	//	�v���C���[Z���O��ړ�
	void	MoveX( D3DXVECTOR3* , D3DXVECTOR3* , float );	//	�v���C���[X�����E�ړ�
	
	//	�ǉ���	12/16
	void	Jump ( bool *, float *);
	//----------------------------------

	void	BulletRender ( CL_BULLET* , int = ENEMY_B_MAX );

	float	fRotateVolOfChange;
};

class CL_HOLE:public CL_OBJECT
{
public:
	void	CharaInit ( int = 0 );		//	������
	void	CharaControl ( int = 0 );	//	��{����
	void	CharaRender ( int = 0 );	//	3D�`��
	void	FreeMesh();

	//	�ǉ���	2/10	�T�c
	D3DXVECTOR3	vecPosOfTarget;	//	�G�Ƃ̈ʒu�֌W(����)
	D3DXVECTOR3	vecSita;		//	���e�ʂ̖@���x�N�g��
	float	fSetSita;
	float	fEnemyRotateY;	//	�O�t���[����vecRotate.y

};

//------------------------------------------------------------------------------
//
//	�v���C���[�N���X
//
//------------------------------------------------------------------------------
class CL_PLAYER:public CL_OBJECT, public CL_CHARA
{
public:
	float	fShotRecoil;	//	�A�ˌ�̔����̃J�E���^
	float	fShotInterval;	//	�ˌ���1��1���̊Ԋu�̃J�E���^
	float	fShotCount;		//	�A�ː��J�E���^
	
	//	�ǉ���	12/16
	int		iPlPoint;		//	�l���|�C���g
	//---------------------------------------

	//CL_PLAYER ()	{	ZeroMemory ( this, sizeof(CL_PLAYER) );	}
	void	CharaInit ( int = 0 );		//	������
	void	CharaControl ( int = 0 );	//	��{����
	void	CharaRender ( int = 0 );	//	3D�`��

	//	�ύX���܂����B12/18
	//
	BULLET_INFO*	GetMainWeapon()	{ return	&mainWeapon; }
	BULLET_INFO*	GetSubWeapon()	{ return	&subWeapon; }

	//	����1�F�ˌ���1��1���̊Ԋu�A2�F�A�ˌ�̔����A3�F�A�ː��A4�F������
	void	ShotControl ( float &, float &, float &, BULLET_INFO * );	//	���˂̐���

	CL_BULLET	clBullet [PLAYER_B_MAX];	//	�v���C���[�̏e�e�̐�

	//	�{�g���̎g�p�֐�
	//	�����Ftrue�Ń{�g����[�Afalse�Ń{�g������
	//	�Ԃ�l�F��[�A����ł����ꍇ��true�A�ł��Ȃ������ꍇ��false
	bool	ChargeBpttle ( bool bCharge );

	void	Reload ( CL_CHARA* );
	//�k��@Ammo�������n���֐���ǉ� 01/27
	int		GetAmmoStock ( );
	D3DXVECTOR2 holepos[HOLE_MAX];
	int		GetBottleNum ( ) { return possessionBottle;};
	//----------------------------------------------------------------
	void FreeMesh();

private:
	//	�ύX���܂����B12/18
	//
	BULLET_INFO		mainWeapon;			//	���C��������
	BULLET_INFO		subWeapon;			//	�T�u������
	//------------------------------------------------------
	int		possessionBottle;	//	�ێ����Ă���{�g����
};

//------------------------------------------------------------------------------
//
//	�G�N���X
//
//------------------------------------------------------------------------------
class CL_ENEMY:public CL_OBJECT, public CL_CHARA
{
public:
	float	fShotRecoil;	//	�A�ˌ�̔����̃J�E���^
	float	fShotInterval;	//	�ˌ���1��1���̊Ԋu�̃J�E���^
	float	fShotCount;		//	�A�ː��J�E���^
	void	CharaInit ( int = 0 );		//	������
	void	CharaControl ( int = 0 );	//	��{����
	void	CharaRender ( int = 0 );	//	3D�`��

	//	����1�F�ˌ���1��1���̊Ԋu�A2�F�A�ˌ�̔����A3�F�A�ː��A4�F������
	void	ShotControl ( float &, float &, float &, BULLET_INFO * );	//	���˂̐���
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
	//	�ύX���܂����B12/18
	//
	BULLET_INFO		mainWeapon;
	//----------------------------
	int		dropItem;
};
//------------------------------------------------------------------------------
//
//	��Q���N���X
//
//------------------------------------------------------------------------------
class CL_WALL:public CL_OBJECT
{
public:
	void	CharaInit ( int = 0 );		//	������
	void	CharaControl ( int = 0 );	//	��{����
	void	CharaRender ( int = 0 );	//	3D�`��
	void FreeMesh();
protected:
	int		dropItem;
};

/*
	�e���̓\��t��
	����	�G�N���X�|�C���^
*/
void PasteBulletHoles ( CL_ENEMY* pEen );	//	�G���݂̂œ\��t�����ꍇ
//	���o�[�W����
void PasteBulletHoles ( CL_ENEMY* clEnemy, CL_BULLET* pBullet );	

int Gettime(); //�^�C�}�[�擾
#endif

