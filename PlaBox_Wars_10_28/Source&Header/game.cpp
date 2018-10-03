#include "input.h"
#include "HitCheck.h"
#include "game.h"
#include "camera.h"
#include "Audio.h"
#include "result.h"
#include "UI.h"

#define PLAYER_HP_MAX 750	//	EASY��2000	NORMAL��750	HARD��100
#define PLAYER_SP_MAX 0

#define TARGET_SCALE 0.25f

int		gameScene;
CL_PLAYER	player;
CL_ENEMY	enemy [ENEMY_MAX];
CL_WALL		object [OBJECT_MAX];
CL_HOLE		storm;
CL_RESULT	result;

bool ResultFlag = false;

int		iBomCount;
int		timer;
//	���C���Q�[���̏�����
void CL_GAME::Init ()
{
	timer = 0;
#ifndef _DEBUG_
	InitMouse ( g_hWnd );
#else
	InitMouse ( g_hWnd, true );
#endif
	LoadTexture ( "Texture\\Image\\testUI.png", TEX_PLAYER_UI1, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_PLAYER_UI1, 0, 0, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\Image\\makar.png", TEX_TARGET , 0, 0, 0 );
	SetVertex ( NORMAL, TEX_TARGET, 0, 0, NULL, NULL, NULL, NULL );
	float tsx = GetTexWidth( TEX_TARGET ) * TARGET_SCALE;
	float tsy = GetTexHeight( TEX_TARGET ) * TARGET_SCALE;
	SetTexSize( TEX_TARGET , tsx , tsy );

	//2/12�@�ΐ�ǉ�--------------------------------------------------------------------
	//HP
	LoadTexture ( "Texture\\Image\\Hp_Meter.png", TEX_PLAYER_HP, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_PLAYER_HP, 0, 520, NULL, NULL, NULL, NULL );
	//SetAlpha( TEX_PLAYER_HP,100 );


	LoadTexture ( "Texture\\Image\\dankon.png", TEX_DANKON, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_DANKON, -100, -100, NULL, NULL, NULL, NULL );

	//MP
	LoadTexture ( "Texture\\Image\\Sp_Meter.png", TEX_PLAYER_SP, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_PLAYER_SP, 0, 620, NULL, NULL, NULL, NULL );

	//HP�Q�[�W
	LoadTexture ( "Texture\\Image\\Hp_Gage.png", TEX_PLAYER_HP_GAGE, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_PLAYER_HP_GAGE, 76.30f, 540, NULL, NULL, NULL, NULL );

	//SP�Q�[�W
	LoadTexture ( "Texture\\Image\\Sp_Gage.png", TEX_PLAYER_SP_GAGE, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_PLAYER_SP_GAGE, 77.19f, 640, NULL, NULL, NULL, NULL );

	//�e�̎��
	LoadTexture ( "Texture\\Image\\UiteKina.png", TEX_PLAYER_UITE_KIND, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_PLAYER_UITE_KIND, 790, 450, NULL, NULL, NULL, NULL );
	SetAlpha( TEX_PLAYER_UITE_KIND,100 );

	//�e�̃}�K�W��
	LoadTexture ( "Texture\\Image\\bottle2.png", TEX_PLAYER_UITE_BOTTLE, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_PLAYER_UITE_BOTTLE, 1218.f, 510, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\Image\\number.png", TEX_NUM_SET, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_NUM_SET, -1000, -1000, NULL, NULL, NULL, NULL );

	storm.LoadThingFile ( &storm, "Texture\\Xfile\\bomber.x",  &D3DXVECTOR3( 1.f, -5.f, 1.f ),
					&D3DXVECTOR3(6.f,8.f,1.f), &D3DXVECTOR3 (0.f,0.f,0.f) );	
	
	//�e�A�C�R��
	LoadTexture ( "Texture\\icon\\Rifle.png", ICON_RIFLE, 0, 255, 0 );
	SetVertex ( NORMAL, ICON_RIFLE, 0, 0, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\icon\\MG.png", ICON_MG, 0, 255, 0 );
	SetVertex ( NORMAL, ICON_MG, 0, 0, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\icon\\Bazooka.png", ICON_BAZOOKA, 0, 255, 0 );
	SetVertex ( NORMAL, ICON_BAZOOKA, 0, 0, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\icon\\Gatling.png", ICON_GATLING, 0, 255, 0 );
	SetVertex ( NORMAL, ICON_GATLING, 0, 0, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\icon\\NONE.png", ICON_NONE, 0, 255, 0 );
	SetVertex ( NORMAL, ICON_NONE, 0, 0, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture/Image/particle.png", TEX_EFF_DEBRIS , 255, 255, 255 );

	//��
	LoadSoundFile("Sound\\BGM\\pl_Bt.wav", BGM_02);
	LoadSoundFile("Sound\\SE\\HundGun.wav", SE_HNG);

	LoadSoundFile("Sound\\SE\\kachi04.wav", SE_TRIGGER);
	LoadSoundFile("Sound\\SE\\power18.wav", SE_GET);
	LoadSoundFile("Sound\\SE\\bom13_b.wav", SE_BOM);

	LoadSoundFile("Sound\\BGM\\win.wav", BGM_03);

	gameScene	= SELECT_MODE;

	player.CharaInit();

	player.GetMeshVertex();

	InitBBox ( &player );

	SoundPlay( BGM_02, true);
	
	for ( int i = 0 ; i < ENEMY_MAX; i++ )
	{
		enemy[i].CharaInit( i );
		enemy[i].GetMeshVertex();
		InitBBox ( &enemy[i] );
	}

	object->CharaInit();
	for ( int i = 0 ; i < OBJECT_MAX; i++ )
	{
		InitBBox ( &object[i] );
	}

	storm.CharaInit();
	iDeadCount = 0;
	iGameCount = 0;

	iBomCount = 0;
	//���U���g
	result.Init();
	ResultFlag = false;

	//	�`�掞�ϊ��s��X�V�t���O�̏�����
	bRenderMatrixUpdateFlag = true;
}

//	���C���Q�[���̏���
void CL_GAME::Control ()
{
	if ( !ResultFlag )
	{
		timer++;
	}
	
	if ( ResultFlag )	
	{
		result.Control();
	}

	CameraPosCheck();

	//	�Q�[�����[�h�I��
	switch ( gameScene )
	{
	case SELECT_MODE:
		gameScene = SelectMode ();

		break;
	case SINGLE:

		break;
	case MULTI:
		break;
	case TIME_T:
		break;
	case VERSUS:
		break;
	}

	//	�Q�[�����[�h�I�����������Ă��Ȃ��ƁA
	//	���@�A�G�A�I�u�W�F�N�g�̏����ɂ͈ڂ�Ȃ��B	
	if ( gameScene != SELECT_MODE && !ResultFlag )
	{
		if ( !storm.deadFlag )
		{
			if ( iBomCount < 1 )
			{
				SoundPlay ( SE_BOM, false);
			}
			iBomCount++;
		}
		if ( iBomCount > 3 )
		{
			storm.deadFlag = true;
			iBomCount = 0;
		}

		iGameCount++;
		if ( player.GetDeadFlag() == false )
		{
			player.CharaControl();
			SetCameraPos ( player.vecPosition, player.vecRotate );			
		}
		
		//	�G�̐����̏���
		for ( int i = 0 ; i < ENEMY_MAX; i++ )
		{
			if ( enemy[i].GetDeadFlag() == false )
			{
				//	�v���C���[�̒e�������[�v
				for ( int j = 0; j < PLAYER_B_MAX; j++ )
				{
					//	�e��������Ă���
					if ( player.clBullet[j].Shot_flag )
					{

						//	�v���C���[�̒e�ƓG�Ƃ̓����蔻��
						if ( SegmentHitcheck( &enemy[i], &player.clBullet[j],
							&enemy[i].clHitHole[enemy[i].hitCount].vecPosOfTarget,
							&enemy[i].clHitHole[enemy[i].hitCount].vecSita,
							&enemy[i].clHitHole[enemy[i].hitCount].fSetSita ))
						{
							PasteBulletHoles ( &enemy[i]);
							player.clBullet[j].Shot_flag = false;
							//	���e�ʂ���G�t�F�N�g�̐���
							particle.PlayEffect( 
								enemy[i].clHitHole[ enemy[i].hitCount ].vecPosition,
								enemy[i].clHitHole[ enemy[i].hitCount ].vecSita,
								CEffectManager::TYPE_DEBRIS );
							enemy[i].hitCount++;
							enemy[i].HP -= player.clBullet[j].GetDamage();
							enemy[i].hatecount = 1000;
							
						}
						//	�v���C���[�̒e�ƃt�B�[���h�Ƃ̓����蔻��
						if( !BoxImpact( &object[SKY] , &player.clBullet[j] , 1) )
						{
							player.clBullet[j].Shot_flag = false;
							player.clBullet[j].vecPosition.y = -10.0f;
							player.clBullet[j].vecBeforePos.y	= enemy[i].clBullet[j].vecPosition.y;
						}
					}
				}
				enemy[i].CharaControl(i);
				//--------------------------enemy�̒e�̃q�b�g�`�F�b�N
				for( int j = 0 ; j < ENEMY_B_MAX ; j++ )
				{
					if( enemy[i].clBullet[j].Shot_flag )
					{
						if ( BoxImpact ( &enemy[i].clBullet[j] , &player , 0 ) )
						{
							enemy[i].clBullet[j].Shot_flag = false;
							player.hitCount += enemy[i].clBullet[j].GetDamage();
						}
						if( !BoxImpact( &object[SKY] , &enemy[i].clBullet[j] , 1) )
						{
							enemy[i].clBullet[j].Shot_flag = false;
							enemy[i].clBullet[j].vecPosition.y = -10.0f;
							enemy[i].clBullet[j].vecBeforePos.y	= enemy[i].clBullet[j].vecPosition.y;
						}
					}
				}

				//---------------------------------------------------
				if(enemy[i].HP <= 0 )
				{
					enemy[i].deadFlag = true;
					enemy[i].hitCount = 0;
					iDeadCount++;
					player.iPlPoint++;
					storm.vecPosition.x = enemy[i].vecPosition.x;
					storm.vecPosition.z = enemy[i].vecPosition.z - ( enemy[i].BBox.vecMax.z - enemy[i].BBox.vecMin.z)/1.7f;
					storm.vecPosition.y = enemy[i].vecPosition.y;
					storm.deadFlag = false;
				}
			}
		}
		
		if ( player.hitCount >= PLAYER_HP_MAX )
		{
			player.deadFlag = true;
			ResultFlag = true;
			ChangeScene ( S_GAMEOVER );
		}
		if ( iDeadCount >= BOSS )
		{
			if(enemy[BOSS].vecPosition.y > 30)
			{
				enemy[BOSS].vecPosition = D3DXVECTOR3(40.f,3.f,40.f);
			}
		}
		if ( iDeadCount >= ENEMY_MAX )
		{
			if(ResultFlag == false)
			{
				SoundStop(BGM_02);
				SoundPlay( BGM_03, false);
			}
			ResultFlag = true;
		}

		for ( int i = 0 ; i < OBJECT_MAX; i++ )
		{
			if ( object[i].GetDeadFlag() == false )
			{
				object[i].CharaControl( );
	
				if ( BoxImpact ( &player, &object[ITEM] , 0 ) && i == ITEM )
				{
					object[ITEM].deadFlag = true;
					if ( player.ChargeBpttle( true ) )	//	�{�g����[����
					{
						SoundPlay(SE_GET, false);
					}
					else	//	�{�g����[���s
					{
						
					}
				}
			}
		}
		
	}

	//	�p�[�e�B�N��������
	particle.Control();
}

//�@���C���Q�[����3D�`��
void CL_GAME::Render ()
{
	if ( gameScene != SELECT_MODE )
	{

		if ( player.GetDeadFlag() == false )
		{
			player.CharaRender();
			player.BulletRender ( player.clBullet, PLAYER_B_MAX );
		}
		for ( int i = 0 ; i < OBJECT_MAX; i++ )
		{
			if ( object[i].GetDeadFlag() == false )
			{
				object[i].CharaRender( i );
			}
		}
		storm.CharaRender();

		for ( int i = 0 ; i < ENEMY_MAX; i++ )
		{
			if ( enemy[i].GetDeadFlag() == false )
			{
				
				enemy[i].CharaRender( i );
				enemy[i].BulletRender ( enemy[i].clBullet , ENEMY_B_MAX );
				for ( int j = 0; j < PLAYER_B_MAX; j++ )
				{
					if ( enemy[i].clHitHole[j].GetDeadFlag() == false )
					{
						enemy[i].Transform ( &enemy[i].clHitHole[j]);
					}
				}
				
			}
		}		
		
		
	}
	
	particle.Render( &bRenderMatrixUpdateFlag);
	
	//	�`�掞�ϊ��s��X�V�t���O�̏�����
	bRenderMatrixUpdateFlag = true;
}

//	�L�����̒e�`��
void CL_CHARA::BulletRender ( CL_BULLET* clBullet, int iArrayNum )
{
	for ( int i = 0; i < iArrayNum; i++ )
	{
		if ( clBullet[i].Shot_flag == true )
		{
			clBullet[i].Transform ( &clBullet[i] );
		}
	}
}

//�A�C�R���`��p
eTEXTURE GetWepon( int _m ){
	if( _m == 0 ){
		switch( player.GetMainWeapon()->iBulletType ){
			case W_RIFLE:		return ICON_RIFLE;   break;
			case W_MG:		return ICON_MG;	   break;
			case W_BAZOOKA:	return ICON_BAZOOKA; break;
			case W_GATLING:	return ICON_GATLING; break;
			case W_NONE:		return ICON_NONE;    break;
		}
	}
	if( _m == 1 ){
		switch( player.GetSubWeapon()->iBulletType ){
			case W_RIFLE:		return ICON_RIFLE;   break;
			case W_MG:		return ICON_MG;	   break;
			case W_BAZOOKA:	return ICON_BAZOOKA; break;
			case W_GATLING:	return ICON_GATLING; break;
			case W_NONE:		return ICON_NONE;    break;
		}
	}
	return ICON_NONE;
}

#define GAGE_SIZE 290.f

//�@���C���Q�[����2D�`��
void CL_GAME::Draw ()
{
	if( !ResultFlag ){
		PlayerHoleDraw();	//	�v���C���[��ʂ̒e���\��

		SetTexSize(TEX_PLAYER_HP_GAGE ,
			GAGE_SIZE * (float)( PLAYER_HP_MAX - player.hitCount) / (float)PLAYER_HP_MAX ,
			GetTexHeight(TEX_PLAYER_HP_GAGE) );
		SetVertex ( NORMAL, TEX_PLAYER_HP_GAGE, 76.30f, 540, NULL, NULL, NULL, NULL );
		TextureDraw ( TEX_PLAYER_HP_GAGE );		//	HP�Q�[�W
		
		TextureDraw ( TEX_PLAYER_HP );			//�@�v���C���[HP

		SetVertex ( NORMAL, TEX_PLAYER_SP_GAGE, 77.19f, 640, NULL, NULL, NULL, NULL );
		TextureDraw ( TEX_PLAYER_SP_GAGE );		//	SP�Q�[�W
		TextureDraw ( TEX_PLAYER_SP );			//�@�v���C���[MP
		
		TextureDraw ( TEX_PLAYER_UITE_KIND );	//�@����̎��
		TextureDraw ( TEX_PLAYER_UITE_BOTTLE ); //�@�e�̃}�K�W��
		TextureDraw ( TEX_RADAR );				//�@���[�_�[?
		TextureDraw ( TEX_TARGET );				//�@�e�̏Ə�
		DrawAmmoStock( );						//�@�e�̒e��

		//�e�A�C�R���`��
		//790, 450
		// 90 14
		eTEXTURE _main = GetWepon(0);
		SetVertex ( NORMAL, _main, 880, 464, NULL, NULL, NULL, NULL );
		TextureDraw( _main );
		// 90 144
		eTEXTURE _sub = GetWepon(1);
		SetVertex ( NORMAL, _sub, 880, 594, NULL, NULL, NULL, NULL );
		TextureDraw( _sub );
	}
	else
	{
		result.Draw();
	}
}

//	�Q�[�����[�h�̑I��
int	CL_GAME::SelectMode ()
{
	//	�V���O�����[�h
	//if ( StCheck ( K_SINGL_MODE, PUSH ) )	
	//{
	//	MessageBox(0,"�V���O�����[�h�ŊJ�n���܂��B","",MB_OK);
		return	SINGLE;
	//}
	////	�}���`���[�h
	//if ( StCheck ( K_MULTI_MODE, PUSH ) )	
	//{
	//	MessageBox(0,"�}���`���[�h�ŊJ�n���܂��B","",MB_OK);
	//	return	MULTI;
	//}
	////	�^�C���g���C�A�����[�h
	//if ( StCheck ( K_TIME_T_MODE, PUSH ) )	
	//{
	//	MessageBox(0,"�^�C���g���C�A�����[�h�ŊJ�n���܂��B","",MB_OK);
	//	return	TIME_T;
	//}
	////	�o�[�T�X���[�h
	//if ( StCheck ( K_VS_MODE, PUSH ) )	
	//{
	//	MessageBox(0,"�o�[�T�X���[�h�ŊJ�n���܂��B","",MB_OK);
	//	return	VERSUS;
	//}
	//return 0;
}

void CL_GAME::Release()
{
	player.FreeMesh();
	for ( int i = 0; i < ENEMY_MAX; i++ ) enemy[i].FreeMesh() ;
	for ( int i = 0; i < OBJECT_MAX; i++ )object[i].FreeMesh() ;
	storm.FreeMesh();

	particle.Free();

	ReleaseAllTexture();

	ReleaseAllSoundFile();
}

void CL_CHARA::MoveZ ( D3DXVECTOR3* vecPos, D3DXVECTOR3* vecRot, float fSpeed )	//�L�[����E�O��ړ�
{
	vecPos -> x += fSpeed * sin( vecRot -> y );
	vecPos -> z += fSpeed * cos( vecRot -> y );
}

void CL_CHARA::MoveX ( D3DXVECTOR3* vecPos, D3DXVECTOR3* vecRot, float fSpeed )	//�v���C���[X�����E�ړ�
{
	vecPos -> x += fSpeed * cos( vecRot -> y );
	vecPos -> z -= fSpeed * sin( vecRot -> y );
}

void CL_CHARA::Jump ( bool* pJumpFlag, float* fPosY )
{
	if ( pJumpFlag )
	{
		y_temp = *fPosY;
		*fPosY += ( *fPosY - y_prev ) - 0.05f;
		y_prev = y_temp;	
	}
	if ( *fPosY <= 0.f ){
		*fPosY = 0.f;
		*pJumpFlag = false;
	}
	if ( *fPosY <= object[SKY].vecPosition.y +0.5f )
		*pJumpFlag = false;
}


/*
	�e���̓\��t��
	����	�G�N���X�|�C���^
*/
void PasteBulletHoles ( CL_ENEMY* pEne )
{
	//	���W�ϊ��Œe���𒅒e�_�ֈړ�
	pEne->clHitHole[ pEne->hitCount ].vecPosition = pEne->vecPosition + pEne->clHitHole[ pEne->hitCount ].vecPosOfTarget;
	pEne->clHitHole[ pEne->hitCount ].vecRotate.y =  pEne->clHitHole[ pEne->hitCount ].fSetSita;


	pEne -> clHitHole [ pEne->hitCount ].deadFlag = false;
}

//	�e���̓\��t��
void PasteBulletHoles ( CL_ENEMY* clEnemy, CL_BULLET* pBullet )
{
	D3DXVECTOR3	vecTemp = pBullet -> vecBeforePos - clEnemy -> vecPosition;

	pBullet -> vecRotate.y = clEnemy -> vecRotate.y;

	pBullet -> vecBeforePos = clEnemy -> vecPosition + RotateYMatrix ( &vecTemp, pBullet -> vecRotate.y );
	
	float	_x = clEnemy -> vecPosition.x - pBullet -> vecBeforePos.x;	//	�e�ƒe���Ƃ̋���
	float	_z = clEnemy -> vecPosition.z - pBullet -> vecBeforePos.z;	//	�e�ƒe���Ƃ̋���
	
	float	_r = 0;

	if ( clEnemy -> hitCount > PLAYER_B_MAX )
	{
		clEnemy -> hitCount = 0;
		for ( int i = 0; i < PLAYER_B_MAX; i++ )	clEnemy -> clHitHole [ clEnemy -> hitCount ].deadFlag = true;
	}

	_r = atan2f ( _z, _x );
	

	clEnemy -> clHitHole [ clEnemy -> hitCount ].vecPosition = pBullet -> vecBeforePos;
	
	//	�O��
	if ( _r > HIT_RAD_FRONT_MIN && _r < HIT_RAD_FRONT_MAX )
	{
		clEnemy->clHitHole [ clEnemy -> hitCount ].vecPosition.z = clEnemy -> vecPosition.z - ( clEnemy -> BBox.vecMax.z - clEnemy -> BBox.vecMin.z) / ADJUSTMENT_OF_HOLE_PASTE;
		clEnemy -> clHitHole [ clEnemy -> hitCount ].vecRotate.y = clEnemy -> vecRotate.y;
		clEnemy -> clHitHole [ clEnemy -> hitCount ].fSetSita = clEnemy -> vecRotate.y;
	}
	//	�w��
	else if ( _r > HIT_RAD_BACK_MIN && _r < HIT_RAD_BACK_MAX )
	{
		clEnemy -> clHitHole [ clEnemy -> hitCount ].vecPosition.z = clEnemy -> vecPosition.z + ( clEnemy -> BBox.vecMax.z - clEnemy -> BBox.vecMin.z) / ADJUSTMENT_OF_HOLE_PASTE;
		clEnemy -> clHitHole [ clEnemy -> hitCount ].vecRotate.y = clEnemy -> vecRotate.y + D3DX_PI;
		clEnemy -> clHitHole [ clEnemy -> hitCount ].fSetSita = clEnemy -> vecRotate.y + D3DX_PI;
	}
	//	�E����
	else if ( _r > HIT_RAD_RIGHT_MIN && _r < HIT_RAD_RIGHT_MAX )
	{
		clEnemy -> clHitHole [ clEnemy -> hitCount ].vecPosition.x = clEnemy -> vecPosition.x - ( clEnemy -> BBox.vecMax.x - clEnemy -> BBox.vecMin.x) / 2.1f;
		clEnemy -> clHitHole [ clEnemy -> hitCount ].vecRotate.y = clEnemy -> vecRotate.y + D3DX_PI / 2;
		clEnemy -> clHitHole [ clEnemy -> hitCount ].fSetSita = clEnemy -> vecRotate.y + D3DX_PI / 2;
	}
	//	������
	else if ( _r > HIT_RAD_LEFT_MAX || _r < HIT_RAD_LEFT_MIN )
	{
		clEnemy -> clHitHole [ clEnemy -> hitCount ].vecPosition.x = clEnemy -> vecPosition.x + ( clEnemy -> BBox.vecMax.x - clEnemy -> BBox.vecMin.x) / ADJUSTMENT_OF_HOLE_PASTE;
		clEnemy -> clHitHole [ clEnemy -> hitCount ].vecRotate.y = clEnemy -> vecRotate.y + ( ( D3DX_PI / 2 ) + D3DX_PI ) ;
		clEnemy -> clHitHole [ clEnemy -> hitCount ].fSetSita = clEnemy -> vecRotate.y + ( ( D3DX_PI / 2 ) + D3DX_PI ) ;
	}
	else
	{
		clEnemy->clHitHole[clEnemy->hitCount].deadFlag = true;
	}

	pBullet -> vecBeforePos = clEnemy -> vecPosition;

//	RotateYMatrix ( &clEnemy -> clHitHole [ clEnemy -> hitCount ].vecPosition,  clEnemy -> vecRotate.y );

	clEnemy -> clHitHole [ clEnemy -> hitCount ].vecPosOfTarget = clEnemy -> clHitHole [ clEnemy -> hitCount ].vecPosition - clEnemy -> vecPosition;
	clEnemy -> clHitHole [ clEnemy -> hitCount ].fEnemyRotateY = clEnemy -> vecRotate.y;
	
	clEnemy->clHitHole[clEnemy->hitCount].deadFlag = false;
}
//-------------------------------------------------------
int Gettime()
{
	return timer;
}

//�x�N�g������
float DotProduct(D3DXVECTOR3 _vl, D3DXVECTOR3 _vr) {
	return _vl.x * _vr.x + _vl.y * _vr.y + _vl.z * _vr.z;
}
