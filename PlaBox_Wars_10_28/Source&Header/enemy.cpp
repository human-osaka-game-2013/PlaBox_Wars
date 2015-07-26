#include "enemy.h"
#include "camera.h"
#include "player.h"
#include "HitCheck.h"

#define MOVETEST_

int bossmove = 0;
void CL_ENEMY::CharaInit ( int iCharaArrey )
{
	switch ( iCharaArrey )
	{
	case TANK:
		LoadThingFile ( &enemy[TANK], "Texture\\Xfile\\tank.X", &TANK_BASE,
					&D3DXVECTOR3( 1.f, 1.f, 1.f), &D3DXVECTOR3(0.f,0.f,0.f) );	
		enemy[TANK].fShotRecoil		= 0.f;	
		enemy[TANK].fShotInterval	= 0.f;	
		enemy[TANK].fShotCount		= 0.f;
		enemy[TANK].mainWeapon.iBulletType = 1;
		enemy[TANK].mainWeapon.iAmmo = 120;
		enemy[TANK].mainWeapon.bUseFlag = true;
		enemy[TANK].HP = TANK_HP;
		enemy[TANK].basepos = TANK_BASE;
		enemy[TANK].movecount = 60;
		enemy[TANK].moveflag = false;
		enemy[TANK].hatecount = 0;
		break;

	case TANK2:
		LoadThingFile ( &enemy[TANK2], "Texture\\Xfile\\tank.X", &TANK2_BASE,
					&D3DXVECTOR3( 1.f, 1.f, 1.f), &D3DXVECTOR3(0.f,0.f,0.f) );	

		enemy[TANK2].fShotRecoil		= 0.f;	
		enemy[TANK2].fShotInterval	= 0.f;	
		enemy[TANK2].fShotCount		= 0.f;
		enemy[TANK2].mainWeapon.iBulletType = 1;
		enemy[TANK2].mainWeapon.iAmmo = 120;
		enemy[TANK2].mainWeapon.bUseFlag = true;
		enemy[TANK2].HP = TANK2_HP;
		enemy[TANK2].basepos = TANK2_BASE;
		enemy[TANK2].movecount = 90;
		enemy[TANK2].moveflag = false;
		enemy[TANK2].hatecount = 0;
		break;

	case FIGHTER:
		LoadThingFile ( &enemy[FIGHTER], "Texture\\Xfile\\raptor.X", &FIGHTER_BASE,
					&D3DXVECTOR3( 1.f, 1.f, 1.f), &D3DXVECTOR3(0.f,0.f,0.f) );	
		enemy[FIGHTER].fShotRecoil		= 0.f;	
		enemy[FIGHTER].fShotInterval	= 0.f;	
		enemy[FIGHTER].fShotCount		= 0.f;
		enemy[FIGHTER].mainWeapon.iBulletType = 1;
		enemy[FIGHTER].mainWeapon.iAmmo = 120;
		enemy[FIGHTER].mainWeapon.bUseFlag = true;
		enemy[FIGHTER].HP = FIGHTER_HP;
		enemy[FIGHTER].basepos = FIGHTER_BASE;
		enemy[FIGHTER].movecount = 40;
		enemy[FIGHTER].moveflag = false;
		enemy[FIGHTER].hatecount = 0;
		break;

	case FIGHTER2:
		LoadThingFile ( &enemy[FIGHTER2], "Texture\\Xfile\\raptor.X", &FIGHTER2_BASE,
					&D3DXVECTOR3( 1.f, 1.f, 1.f), &D3DXVECTOR3(0.f,0.f,0.f) );	
		enemy[FIGHTER2].fShotRecoil		= 0.f;	
		enemy[FIGHTER2].fShotInterval	= 0.f;	
		enemy[FIGHTER2].fShotCount		= 0.f;
		enemy[FIGHTER2].mainWeapon.iBulletType = 1;
		enemy[FIGHTER2].mainWeapon.iAmmo = 120;
		enemy[FIGHTER2].mainWeapon.bUseFlag = true;
		enemy[FIGHTER2].HP = FIGHTER2_HP;
		enemy[FIGHTER2].basepos = FIGHTER2_BASE;
		enemy[FIGHTER2].movecount = 150;
		enemy[FIGHTER2].moveflag = false;
		enemy[FIGHTER2].hatecount = 0;
		break;

	case SOLDIER:
		LoadThingFile ( &enemy[SOLDIER], "Texture\\Xfile\\soldier.X", &SOLDIER_BASE,
					&D3DXVECTOR3( 1.f, 1.f, 1.f), &D3DXVECTOR3(0.f,0.f,0.f) );	
		enemy[SOLDIER].fShotRecoil		= 0.f;	
		enemy[SOLDIER].fShotInterval	= 0.f;	
		enemy[SOLDIER].fShotCount		= 0.f;
		enemy[SOLDIER].mainWeapon.iBulletType = 1;
		enemy[SOLDIER].mainWeapon.iAmmo = 120;
		enemy[SOLDIER].mainWeapon.bUseFlag = true;
		enemy[SOLDIER].HP = SOLDIER_HP;
		enemy[SOLDIER].basepos = SOLDIER_BASE;
		enemy[SOLDIER].movecount = 200;
		enemy[SOLDIER].moveflag = false;
		enemy[SOLDIER].hatecount = 0;
		break;

	case SOLDIER2:
		LoadThingFile ( &enemy[SOLDIER2], "Texture\\Xfile\\soldier.X", &SOLDIER2_BASE,
					&D3DXVECTOR3( 1.f, 1.f, 1.f), &D3DXVECTOR3(0.f,0.f,0.f) );	
		enemy[SOLDIER2].fShotRecoil		= 0.f;	
		enemy[SOLDIER2].fShotInterval	= 0.f;	
		enemy[SOLDIER2].fShotCount		= 0.f;
		enemy[SOLDIER2].mainWeapon.iBulletType = 1;
		enemy[SOLDIER2].mainWeapon.iAmmo = 120;
		enemy[SOLDIER2].mainWeapon.bUseFlag = true;
		enemy[SOLDIER2].HP = SOLDIER2_HP;
		enemy[SOLDIER2].basepos = SOLDIER2_BASE;
		enemy[SOLDIER2].movecount = 10;
		enemy[SOLDIER2].moveflag = false;
		enemy[SOLDIER2].hatecount = 0;
		break;

		case BOSS:
		LoadThingFile ( &enemy[BOSS], "Texture\\Xfile\\soldier.X", &D3DXVECTOR3(10000.f,100.f,0.f),
					&D3DXVECTOR3( 1.f, 1.f, 1.f), &D3DXVECTOR3(0.f,0.f,0.f) );	
		enemy[BOSS].fShotRecoil		= 0.f;	
		enemy[BOSS].fShotInterval	= 0.f;	
		enemy[BOSS].fShotCount		= 0.f;
		enemy[BOSS].mainWeapon.iBulletType = 1;
		enemy[BOSS].mainWeapon.iAmmo = 120;
		enemy[BOSS].mainWeapon.bUseFlag = true;
		enemy[BOSS].HP = BOSS_HP;
		enemy[BOSS].basepos = TANK_BASE;
		enemy[BOSS].movecount = 60;
		enemy[BOSS].moveflag = false;
		enemy[BOSS].hatecount = 0;
		break;
	}	
	vecImpactPoint	= GetEyePos();

	this->hitCount = 0;


	enemy[iCharaArrey].clBullet -> InitBullet( enemy[iCharaArrey].clBullet , ENEMY_B_MAX );

	for ( int i = 0; i < PLAYER_B_MAX; i++ )
	{
		enemy[iCharaArrey].clHitHole[i].LoadThingFile( &clHitHole[i], "Texture\\Xfile\\dankon.x",  &D3DXVECTOR3( 0.f, -5.f, -2.f ),
					&D3DXVECTOR3(1.f,1.f,1.f), &D3DXVECTOR3 (0.f,0.f,0.f) );
		enemy[iCharaArrey].clHitHole[i].deadFlag = true;
		enemy[iCharaArrey].clHitHole[i].fEnemyRotateY = 0.f;
	}
	this -> iEnCount = 0;

	this -> deadFlag = false;
	
	//	追加日	2/11	亀田
	
	this -> fRotateVolOfChange = 0.f;
}	 
	 
void CL_ENEMY::CharaControl ( int iCharaArrey )
{

	switch ( iCharaArrey )
	{
	case TANK:
		vecImpactPoint	= GetEyePos();

#ifndef	MOVETEST

		enemy[TANK].clBullet[0].ShotBullet( clBullet, ENEMY_B_MAX );				//弾を制御
		if((sqrt((player.vecPosition.x - enemy[TANK].vecPosition.x)*(player.vecPosition.x - enemy[TANK].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[TANK].vecPosition.z)*(player.vecPosition.z - enemy[TANK].vecPosition.z))) > FINDLENGS)
		{
			if(enemy[TANK].movecount <= 0)
			{
				enemy[TANK].movecount = 300;
				enemy[TANK].movegoalpos.x = enemy[TANK].basepos.x + (float)(rand()%7)-3.f;
				enemy[TANK].movegoalpos.y = 0.f;
				enemy[TANK].movegoalpos.z = enemy[TANK].basepos.z + (float)(rand()%7)-3.f;
				enemy[TANK].vecRotate.y = atan2(enemy[TANK].movegoalpos.x-enemy[TANK].vecPosition.x,enemy[TANK].movegoalpos.z-enemy[TANK].vecPosition.z)+D3DX_PI; 
				enemy[TANK].moveflag = true;
			}
			if(moveflag == true)
			{
				enemy[TANK].MoveZ(&enemy[TANK].vecPosition,&enemy[TANK].vecRotate,-0.1f);
				if(movecount < 150)
				{
					if((sqrt((enemy[TANK].movegoalpos.x - enemy[TANK].vecPosition.x)*(enemy[TANK].movegoalpos.x - enemy[TANK].vecPosition.x)) + sqrt((enemy[TANK].movegoalpos.z - enemy[TANK].vecPosition.z)*(enemy[TANK].movegoalpos.z - enemy[TANK].vecPosition.z))) > 6.f)
					{
						moveflag = false;
					}
				}
				
			}
			enemy[TANK].movecount --;
		}


#else	
		if ( this -> iEnCount < 120 )
		{	
			MoveX( &enemy[TANK].vecPosition, &enemy[TANK].vecRotate, 0.1f );
		
			if( !BoxImpact( &object[SKY] , &enemy[TANK] , 1 ) ){
				MoveX( &enemy[TANK].vecPosition, &enemy[TANK].vecRotate, -0.1f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveX( &enemy[TANK].clHitHole[i].vecPosition, &enemy[TANK].vecRotate, -0.1f ); }
			}
		}
		else
		{
			MoveX( &enemy[TANK].vecPosition, &enemy[TANK].vecRotate, -0.1f );
			
			if( !BoxImpact( &object[SKY] , &enemy[TANK] , 1 ) ){
				MoveX( &enemy[TANK].vecPosition, &enemy[TANK].vecRotate, 0.1f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveX( &enemy[TANK].clHitHole[i].vecPosition, &enemy[TANK].vecRotate, 0.1f ); }
			}
		}
#endif
		break;

	case TANK2:
		vecImpactPoint	= GetEyePos();

#ifndef	MOVETEST

		enemy[TANK2].clBullet[0].ShotBullet( clBullet, ENEMY_B_MAX );
		
		if((sqrt((player.vecPosition.x - enemy[TANK2].vecPosition.x)*(player.vecPosition.x - enemy[TANK2].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[TANK2].vecPosition.z)*(player.vecPosition.z - enemy[TANK2].vecPosition.z))) > FINDLENGS)
		{
			if(enemy[TANK2].movecount <= 0)
			{
				enemy[TANK2].movecount = 300;
				enemy[TANK2].movegoalpos.x = enemy[TANK2].basepos.x + (float)(rand()%7)-3.f;
				enemy[TANK2].movegoalpos.y = 0.f;
				enemy[TANK2].movegoalpos.z = enemy[TANK2].basepos.z + (float)(rand()%7)-3.f;
				enemy[TANK2].vecRotate.y = atan2(enemy[TANK2].movegoalpos.x-enemy[TANK2].vecPosition.x,enemy[TANK2].movegoalpos.z-enemy[TANK2].vecPosition.z)+D3DX_PI; 
				enemy[TANK2].moveflag = true;
			}
			if(moveflag == true)
			{
				enemy[TANK2].MoveZ(&enemy[TANK2].vecPosition,&enemy[TANK2].vecRotate,-0.1f);
				if(movecount < 150)
				{
					if((sqrt((enemy[TANK2].movegoalpos.x - enemy[TANK2].vecPosition.x)*(enemy[TANK2].movegoalpos.x - enemy[TANK2].vecPosition.x)) + sqrt((enemy[TANK2].movegoalpos.z - enemy[TANK2].vecPosition.z)*(enemy[TANK2].movegoalpos.z - enemy[TANK2].vecPosition.z))) > 6.f)
					{
						moveflag = false;
					}
				}
				
			}
			enemy[TANK2].movecount --;
		}
#else				
		if ( this -> iEnCount < 120 )
		{
			MoveX( &enemy[TANK2].vecPosition, &enemy[TANK2].vecRotate, -0.1f );
		
			if( !BoxImpact( &object[SKY] , &enemy[TANK2] , 1 ) ){
				MoveX( &enemy[TANK2].vecPosition, &enemy[TANK2].vecRotate, 0.1f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveX( &enemy[TANK2].clHitHole[i].vecPosition, &enemy[TANK2].vecRotate, 0.1f ); }
			}
		}
		else
		{
			MoveX( &enemy[TANK2].vecPosition, &enemy[TANK2].vecRotate, 0.1f );
			
			if( !BoxImpact( &object[SKY] , &enemy[TANK2] , 1 ) ){
				MoveX( &enemy[TANK2].vecPosition, &enemy[TANK2].vecRotate, -0.1f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveX( &enemy[TANK2].clHitHole[i].vecPosition, &enemy[TANK2].vecRotate, -0.1f ); }
			}
		}
		
#endif		break;

	case FIGHTER:
		vecImpactPoint	= GetEyePos();

#ifndef	MOVETEST

		enemy[FIGHTER].clBullet[0].ShotBullet( clBullet, ENEMY_B_MAX );
		
		if((sqrt((player.vecPosition.x - enemy[FIGHTER].vecPosition.x)*(player.vecPosition.x - enemy[FIGHTER].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[FIGHTER].vecPosition.z)*(player.vecPosition.z - enemy[FIGHTER].vecPosition.z))) > FINDLENGS)
		{
			if(enemy[FIGHTER].movecount <= 0)
			{
				enemy[FIGHTER].movecount = 300;
				enemy[FIGHTER].movegoalpos.x = enemy[FIGHTER].basepos.x + (float)(rand()%7)-3.f;
				enemy[FIGHTER].movegoalpos.y = 0.f;
				enemy[FIGHTER].movegoalpos.z = enemy[FIGHTER].basepos.z + (float)(rand()%7)-3.f;
				enemy[FIGHTER].vecRotate.y = atan2(enemy[FIGHTER].movegoalpos.x-enemy[FIGHTER].vecPosition.x,enemy[FIGHTER].movegoalpos.z-enemy[FIGHTER].vecPosition.z)+D3DX_PI; 
				enemy[FIGHTER].moveflag = true;
			}
			if(moveflag == true)
			{
				enemy[FIGHTER].MoveZ(&enemy[FIGHTER].vecPosition,&enemy[FIGHTER].vecRotate,-0.15f);
				if(movecount < 150)
				{
					if((sqrt((enemy[FIGHTER].movegoalpos.x - enemy[FIGHTER].vecPosition.x)*(enemy[FIGHTER].movegoalpos.x - enemy[FIGHTER].vecPosition.x)) + sqrt((enemy[FIGHTER].movegoalpos.z - enemy[FIGHTER].vecPosition.z)*(enemy[FIGHTER].movegoalpos.z - enemy[FIGHTER].vecPosition.z))) > 6.f)
					{
						moveflag = false;
					}
				}
				
			}
			enemy[FIGHTER].movecount --;
		}
		
#else	
		if ( this -> iEnCount < 60 )
		{
			MoveZ( &enemy[FIGHTER].vecPosition, &enemy[FIGHTER].vecRotate, -0.22f );
		
			if( !BoxImpact( &object[SKY] , &enemy[FIGHTER] , 1 ) ){
				MoveZ( &enemy[FIGHTER].vecPosition, &enemy[FIGHTER].vecRotate, 0.22f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveZ( &enemy[FIGHTER].clHitHole[i].vecPosition, &enemy[FIGHTER].vecRotate, 0.22f ); }
			}
		}
		else if ( this -> iEnCount < 120 )
		{
			MoveX( &enemy[FIGHTER].vecPosition, &enemy[FIGHTER].vecRotate, 0.1f );
		
			if( !BoxImpact( &object[SKY] , &enemy[FIGHTER] , 1 ) ){
				MoveX( &enemy[FIGHTER].vecPosition, &enemy[FIGHTER].vecRotate, -0.1f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveX( &enemy[FIGHTER].clHitHole[i].vecPosition, &enemy[FIGHTER].vecRotate, -0.1f ); }
			}
		}
		else if ( this -> iEnCount < 180 )
		{
			MoveZ( &enemy[FIGHTER].vecPosition, &enemy[FIGHTER].vecRotate, 0.22f );
		
			if( !BoxImpact( &object[SKY] , &enemy[FIGHTER] , 1 ) ){
				MoveZ( &enemy[FIGHTER].vecPosition, &enemy[FIGHTER].vecRotate, -0.22f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveZ( &enemy[FIGHTER].clHitHole[i].vecPosition, &enemy[FIGHTER].vecRotate, -0.22f ); }
			}
		}
		else
		{
			MoveX( &enemy[FIGHTER].vecPosition, &enemy[FIGHTER].vecRotate, -0.1f );
	
			if( !BoxImpact( &object[SKY] , &enemy[FIGHTER] , 1 ) ){
				MoveX( &enemy[FIGHTER].vecPosition, &enemy[FIGHTER].vecRotate, 0.1f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveX( &enemy[FIGHTER].clHitHole[i].vecPosition, &enemy[FIGHTER].vecRotate, 0.1f ); }
			}
		}
#endif
		break;

	case FIGHTER2:
		vecImpactPoint	= GetEyePos();

#ifndef	MOVETEST

		enemy[FIGHTER2].clBullet[0].ShotBullet( clBullet, ENEMY_B_MAX );
	
		if((sqrt((player.vecPosition.x - enemy[FIGHTER2].vecPosition.x)*(player.vecPosition.x - enemy[FIGHTER2].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[FIGHTER2].vecPosition.z)*(player.vecPosition.z - enemy[FIGHTER2].vecPosition.z))) > FINDLENGS)
		{
			if(enemy[FIGHTER2].movecount <= 0)
			{
				enemy[FIGHTER2].movecount = 300;
				enemy[FIGHTER2].movegoalpos.x = enemy[FIGHTER2].basepos.x + (float)(rand()%7)-3.f;
				enemy[FIGHTER2].movegoalpos.y = 0.f;
				enemy[FIGHTER2].movegoalpos.z = enemy[FIGHTER2].basepos.z + (float)(rand()%7)-3.f;
				enemy[FIGHTER2].vecRotate.y = atan2(enemy[FIGHTER2].movegoalpos.x-enemy[FIGHTER2].vecPosition.x,enemy[FIGHTER2].movegoalpos.z-enemy[FIGHTER2].vecPosition.z)+D3DX_PI; 
				enemy[FIGHTER2].moveflag = true;
			}
			if(moveflag == true)
			{
				enemy[FIGHTER2].MoveZ(&enemy[FIGHTER2].vecPosition,&enemy[FIGHTER2].vecRotate,-0.15f);
				if(movecount < 150)
				{
					if((sqrt((enemy[FIGHTER2].movegoalpos.x - enemy[FIGHTER2].vecPosition.x)*(enemy[FIGHTER2].movegoalpos.x - enemy[FIGHTER2].vecPosition.x)) + sqrt((enemy[FIGHTER2].movegoalpos.z - enemy[FIGHTER2].vecPosition.z)*(enemy[FIGHTER2].movegoalpos.z - enemy[FIGHTER2].vecPosition.z))) > 6.f)
					{
						moveflag = false;
					}
				}
				
			}
			enemy[FIGHTER2].movecount --;
		}
	
#else
		if ( this -> iEnCount < 60 )
		{
			MoveZ( &enemy[FIGHTER2].vecPosition, &enemy[FIGHTER2].vecRotate, 0.22f );
	
			if( !BoxImpact( &object[SKY] , &enemy[FIGHTER2] , 1 ) ){
				MoveZ( &enemy[FIGHTER2].vecPosition, &enemy[FIGHTER2].vecRotate, -0.22f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveZ( &enemy[FIGHTER2].clHitHole[i].vecPosition, &enemy[FIGHTER2].vecRotate, -0.22f ); }
			}
		}
		else if ( this -> iEnCount < 120 )
		{
			MoveX( &enemy[FIGHTER2].vecPosition, &enemy[FIGHTER2].vecRotate, -0.1f );

			if( !BoxImpact( &object[SKY] , &enemy[FIGHTER2] , 1 ) ){
				MoveX( &enemy[FIGHTER2].vecPosition, &enemy[FIGHTER2].vecRotate, 0.1f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveX( &enemy[FIGHTER2].clHitHole[i].vecPosition, &enemy[FIGHTER2].vecRotate, 0.1f ); }
			}
		}
		else if ( this -> iEnCount < 180 )
		{
			MoveZ( &enemy[FIGHTER2].vecPosition, &enemy[FIGHTER2].vecRotate, -0.22f );
		}
		else
		{
			MoveX( &enemy[FIGHTER2].vecPosition, &enemy[FIGHTER2].vecRotate, 0.1f );
		}
#endif

		break;

	case SOLDIER:
		vecImpactPoint	= GetEyePos();

#ifndef	MOVETEST

		enemy[SOLDIER].clBullet[0].ShotBullet( clBullet, ENEMY_B_MAX );
		
		if((sqrt((player.vecPosition.x - enemy[SOLDIER].vecPosition.x)*(player.vecPosition.x - enemy[SOLDIER].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[SOLDIER].vecPosition.z)*(player.vecPosition.z - enemy[SOLDIER].vecPosition.z))) > FINDLENGS)
		{
			if(enemy[SOLDIER].movecount <= 0)
			{
				enemy[SOLDIER].movecount = 300;
				enemy[SOLDIER].movegoalpos.x = enemy[SOLDIER].basepos.x + (float)(rand()%7)-3.f;
				enemy[SOLDIER].movegoalpos.y = 0.f;
				enemy[SOLDIER].movegoalpos.z = enemy[SOLDIER].basepos.z + (float)(rand()%7)-3.f;
				enemy[SOLDIER].vecRotate.y = atan2(enemy[SOLDIER].movegoalpos.x-enemy[SOLDIER].vecPosition.x,enemy[SOLDIER].movegoalpos.z-enemy[SOLDIER].vecPosition.z)+D3DX_PI; 
				enemy[SOLDIER].moveflag = true;
			}
			if(moveflag == true)
			{
				enemy[SOLDIER].MoveZ(&enemy[SOLDIER].vecPosition,&enemy[SOLDIER].vecRotate,-0.1f);
				if(movecount < 150)
				{
					if((sqrt((enemy[SOLDIER].movegoalpos.x - enemy[SOLDIER].vecPosition.x)*(enemy[SOLDIER].movegoalpos.x - enemy[SOLDIER].vecPosition.x)) + sqrt((enemy[SOLDIER].movegoalpos.z - enemy[SOLDIER].vecPosition.z)*(enemy[SOLDIER].movegoalpos.z - enemy[SOLDIER].vecPosition.z))) > 6.f)
					{
						moveflag = false;
					}
				}
				
			}
			enemy[SOLDIER].movecount --;
		}
	
#else
		if ( this -> iEnCount < 120 )
		{
			MoveZ( &enemy[SOLDIER].vecPosition, &enemy[SOLDIER].vecRotate, -0.17f );
	
			if( !BoxImpact( &object[SKY] , &enemy[SOLDIER] , 1 ) ){
				MoveZ( &enemy[SOLDIER].vecPosition, &enemy[SOLDIER].vecRotate, 0.17f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveZ( &enemy[SOLDIER].clHitHole[i].vecPosition, &enemy[SOLDIER].vecRotate, 0.17f ); }
			}
		}
		else
		{
			MoveZ( &enemy[SOLDIER].vecPosition, &enemy[SOLDIER].vecRotate, 0.17f );
	
			if( !BoxImpact( &object[SKY] , &enemy[SOLDIER] , 1 ) ){
				MoveZ( &enemy[SOLDIER].vecPosition, &enemy[SOLDIER].vecRotate, -0.17f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveZ( &enemy[SOLDIER].clHitHole[i].vecPosition, &enemy[SOLDIER].vecRotate, -0.17f ); }
			}
		}
#endif
		break;

	case SOLDIER2:
		vecImpactPoint	= GetEyePos();
		
#ifndef	MOVETEST

		enemy[SOLDIER2].clBullet[0].ShotBullet( clBullet, ENEMY_B_MAX );
		
		if((sqrt((player.vecPosition.x - enemy[SOLDIER].vecPosition.x)*(player.vecPosition.x - enemy[SOLDIER].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[SOLDIER].vecPosition.z)*(player.vecPosition.z - enemy[SOLDIER].vecPosition.z))) > FINDLENGS)
		{
			if(enemy[SOLDIER2].movecount <= 0)
			{
				enemy[SOLDIER2].movecount = 300;
				enemy[SOLDIER2].movegoalpos.x = enemy[SOLDIER2].basepos.x + (float)(rand()%7)-3.f;
				enemy[SOLDIER2].movegoalpos.y = 0.f;
				enemy[SOLDIER2].movegoalpos.z = enemy[SOLDIER2].basepos.z + (float)(rand()%7)-3.f;
				enemy[SOLDIER2].vecRotate.y = atan2(enemy[SOLDIER2].movegoalpos.x-enemy[SOLDIER2].vecPosition.x,enemy[SOLDIER2].movegoalpos.z-enemy[SOLDIER2].vecPosition.z)+D3DX_PI; 
				enemy[SOLDIER2].moveflag = true;
			}
			if(moveflag == true)
			{
				enemy[SOLDIER2].MoveZ(&enemy[SOLDIER2].vecPosition,&enemy[SOLDIER2].vecRotate,-0.1f);
				if(movecount < 150)
				{
					if((sqrt((enemy[SOLDIER2].movegoalpos.x - enemy[SOLDIER2].vecPosition.x)*(enemy[SOLDIER2].movegoalpos.x - enemy[SOLDIER2].vecPosition.x)) + sqrt((enemy[SOLDIER2].movegoalpos.z - enemy[SOLDIER2].vecPosition.z)*(enemy[SOLDIER2].movegoalpos.z - enemy[SOLDIER2].vecPosition.z))) > 6.f)
					{
						moveflag = false;
					}
				}
				
			}
			enemy[SOLDIER2].movecount --;
		}
		
#else
		if ( this -> iEnCount < 120 )
		{
			MoveZ( &enemy[SOLDIER2].vecPosition, &enemy[SOLDIER2].vecRotate, 0.17f );
		
			if( !BoxImpact( &object[SKY] , &enemy[SOLDIER2] , 1 ) ){
				MoveZ( &enemy[SOLDIER2].vecPosition, &enemy[SOLDIER2].vecRotate, -0.17f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveZ( &enemy[SOLDIER2].clHitHole[i].vecPosition, &enemy[SOLDIER2].vecRotate, -0.17f ); }
			}
		}
		else
		{
			MoveZ( &enemy[SOLDIER2].vecPosition, &enemy[SOLDIER2].vecRotate, -0.17f );
		
			if( !BoxImpact( &object[SKY] , &enemy[SOLDIER2] , 1 ) ){
				MoveZ( &enemy[SOLDIER2].vecPosition, &enemy[SOLDIER2].vecRotate, 0.17f );
				for ( int i = 0; i < PLAYER_B_MAX; i++ ){ 
					MoveZ( &enemy[SOLDIER2].clHitHole[i].vecPosition, &enemy[SOLDIER2].vecRotate, 0.17f ); }
			}
		}
#endif
		break;

		case BOSS:
		vecImpactPoint	= GetEyePos();
		enemy[BOSS].clBullet[0].ShotBullet( clBullet, ENEMY_B_MAX );
		enemy[BOSS].ShotControl(fShotRecoil,fShotInterval,fShotCount,&mainWeapon);
		enemy[BOSS].vecRotate.y = atan2(player.vecPosition.x-enemy[BOSS].vecPosition.x,player.vecPosition.z-enemy[BOSS].vecPosition.z)+D3DX_PI; //プレイヤーのほうに左右に向く
		if((sqrt((player.vecPosition.x - enemy[BOSS].vecPosition.x)*(player.vecPosition.x - enemy[BOSS].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[BOSS].vecPosition.z)*(player.vecPosition.z - enemy[BOSS].vecPosition.z))) > 50.f)
		{
			if(enemy[BOSS].movecount <= 0)
			{	
				bossmove = rand()%2;
				
				enemy[BOSS].movecount = 60;
				enemy[BOSS].moveflag = true;		
			}
			if(bossmove == 0)enemy[BOSS].MoveX(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,BOSS_MOVE_VOL_2);
			if(bossmove == 1)enemy[BOSS].MoveX(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,-BOSS_MOVE_VOL_2);
			enemy[BOSS].MoveZ(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,-BOSS_MOVE_VOL_2);
			enemy[BOSS].movecount --;
		}
		else if((sqrt((player.vecPosition.x - enemy[BOSS].vecPosition.x)*(player.vecPosition.x - enemy[BOSS].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[BOSS].vecPosition.z)*(player.vecPosition.z - enemy[BOSS].vecPosition.z))) < 20.f)
		{
			if(enemy[BOSS].movecount <= 0)
			{	
				bossmove = rand()%2;
				
				enemy[BOSS].movecount = 60;
				enemy[BOSS].moveflag = true;		
			}
			if(bossmove == 0)enemy[BOSS].MoveX(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,BOSS_MOVE_VOL_2);
			if(bossmove == 1)enemy[BOSS].MoveX(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,-BOSS_MOVE_VOL_2);
			enemy[BOSS].MoveZ(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,+BOSS_MOVE_VOL_2);
			enemy[BOSS].movecount --;
		}
		else
		{
			if(enemy[BOSS].movecount <= 0)
			{	
				bossmove = rand()%4;
				
				enemy[BOSS].movecount = 60;
				enemy[BOSS].moveflag = true;		
			}
			if(bossmove == 0)
			{
				enemy[BOSS].MoveX(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,BOSS_MOVE_VOL_2);
				enemy[BOSS].MoveZ(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,+BOSS_MOVE_VOL_1);
			}
			if(bossmove == 1)
			{
				enemy[BOSS].MoveX(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,-BOSS_MOVE_VOL_2);
				enemy[BOSS].MoveZ(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,+BOSS_MOVE_VOL_1);
			}
			if(bossmove == 2)
			{
				enemy[BOSS].MoveX(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,BOSS_MOVE_VOL_2);
				enemy[BOSS].MoveZ(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,-BOSS_MOVE_VOL_1);
			}
			if(bossmove == 3)
			{
				enemy[BOSS].MoveX(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,-BOSS_MOVE_VOL_2);
				enemy[BOSS].MoveZ(&enemy[BOSS].vecPosition,&enemy[BOSS].vecRotate,-BOSS_MOVE_VOL_1);
			}

			
			enemy[BOSS].movecount --;
		}
		if(enemy[BOSS].vecPosition.x > 40.f)enemy[BOSS].vecPosition.x = 40.f;
		if(enemy[BOSS].vecPosition.x < -40.f)enemy[BOSS].vecPosition.x = -40.f;
		if(enemy[BOSS].vecPosition.z > 40.f)enemy[BOSS].vecPosition.z = 40.f;
		if(enemy[BOSS].vecPosition.z < -40.f)enemy[BOSS].vecPosition.z = -40.f;
	}
	for(int iii = 0 ; iii < BOSS ; iii ++)
	{
		if(enemy[iii].hatecount > 0)
		{
			enemy[iii].hatecount --;
		}
		if(((sqrt((player.vecPosition.x - enemy[iii].vecPosition.x)*(player.vecPosition.x - enemy[iii].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[iii].vecPosition.z)*(player.vecPosition.z - enemy[iii].vecPosition.z))) < FINDLENGS)||enemy[iii].hatecount > 0)
		{
			if( rand()%20 == 0 )	///<	1/10で発射の制限(仮)
			{
				enemy[iii].ShotControl(fShotRecoil,fShotInterval,fShotCount,&mainWeapon); //弾を発射
				enemy[iii].vecRotate.y = atan2(player.vecPosition.x-enemy[iii].vecPosition.x,player.vecPosition.z-enemy[iii].vecPosition.z)+D3DX_PI; //プレイヤーのほうに左右に向く
			}
		}
		if(((sqrt((player.vecPosition.x - enemy[iii].vecPosition.x)*(player.vecPosition.x - enemy[iii].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[iii].vecPosition.z)*(player.vecPosition.z - enemy[iii].vecPosition.z))) < FINDLENGS
			&& (sqrt((player.vecPosition.x - enemy[iii].vecPosition.x)*(player.vecPosition.x - enemy[iii].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[iii].vecPosition.z)*(player.vecPosition.z - enemy[iii].vecPosition.z))) > FARLENGS)||
			(enemy[iii].hatecount > 0 &&(sqrt((player.vecPosition.x - enemy[iii].vecPosition.x)*(player.vecPosition.x - enemy[iii].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[iii].vecPosition.z)*(player.vecPosition.z - enemy[iii].vecPosition.z))) < NEARLENGS))
		{

			if( iii == FIGHTER  || iii == FIGHTER2 )
			{
				enemy[iii].MoveZ(&enemy[iii].vecPosition,&enemy[iii].vecRotate,-0.015f);
			}
			else
			{
				enemy[iii].MoveZ(&enemy[iii].vecPosition,&enemy[iii].vecRotate,-0.01f);
			}
		}
		if(((sqrt((player.vecPosition.x - enemy[iii].vecPosition.x)*(player.vecPosition.x - enemy[iii].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[iii].vecPosition.z)*(player.vecPosition.z - enemy[iii].vecPosition.z))) < FINDLENGS
			&& (sqrt((player.vecPosition.x - enemy[iii].vecPosition.x)*(player.vecPosition.x - enemy[iii].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[iii].vecPosition.z)*(player.vecPosition.z - enemy[iii].vecPosition.z))) < NEARLENGS)||
			(enemy[iii].hatecount > 0 &&(sqrt((player.vecPosition.x - enemy[iii].vecPosition.x)*(player.vecPosition.x - enemy[iii].vecPosition.x)) + sqrt((player.vecPosition.z - enemy[iii].vecPosition.z)*(player.vecPosition.z - enemy[iii].vecPosition.z))) < NEARLENGS))
		{
			if( iii == FIGHTER  || iii == FIGHTER2 )
			{
				enemy[iii].MoveZ(&enemy[iii].vecPosition,&enemy[iii].vecRotate,0.013f);
			}
			else
			{
				enemy[iii].MoveZ(&enemy[iii].vecPosition,&enemy[iii].vecRotate,0.01f);
			}
		}
	}
	/*if(enemy[BOSS].hatecount > 0)
	{
		enemy[BOSS].hatecount --;
	}*/
	this -> iEnCount++;
	if ( this -> iEnCount > 240 )
	{
		this -> iEnCount = 0;
	}
	
	//	敵に張り付いた弾痕の座標更新
	for ( int i = 0; i < PLAYER_B_MAX; i++)
	{
		if ( this -> clHitHole[i].deadFlag == false )
		{
		
			clHitHole[i].vecRotate.y = clHitHole[i].fSetSita + vecRotate.y - clHitHole[i].fSetSita;
			float x = clHitHole[i].vecPosOfTarget.x * cos( clHitHole[i].vecRotate.y ) + clHitHole[i].vecPosOfTarget.z  * sin(clHitHole[i].vecRotate.y );
			float y = clHitHole[i].vecPosOfTarget.y;
			float z = clHitHole[i].vecPosOfTarget.x * -sin( clHitHole[i].vecRotate.y ) + clHitHole[i].vecPosOfTarget.z * cos( clHitHole[i].vecRotate.y );

			clHitHole[i].vecPosition = vecPosition + D3DXVECTOR3( x , y , z );
		}
	}
	//---------------------------------------------
}	 
	 
void CL_ENEMY::CharaRender ( int iCharaArrey )
{
	Transform ( &enemy[iCharaArrey] );
}

void CL_ENEMY::ShotControl ( float &pRecoil, float &pInterval, float &pCount, BULLET_INFO * pWeapon )
{
	switch ( pWeapon->iBulletType )
	{
	case	W_RIFLE:
		if ( pRecoil <= 0 )
		{
			if ( pInterval <= 0 )
			{
				if ( pCount < RIFLE_OF_FIRE )
				{
					pCount++;
					D3DXVECTOR3 _vec(vecPosition.x , vecPosition.y + 2.5f , vecPosition.z);
					clBullet[0].MadeBullet( clBullet, &_vec, &vecImpactPoint,
											pWeapon->iBulletType, ENEMY, W_RIFLE ,ENEMY_B_MAX );

					pInterval = INTERVAL_OF_RIFLE * ONE_FR;
				}
				else
				{
					pRecoil = RECOIL_OF_RIFLE * ONE_FR;
					pCount = 0;
				}
			}
			else
			{
				pInterval--;
			}
		}
		else
		{
			pRecoil--;
		}

		break;

	case	W_MG:

		break;

	case	W_BAZOOKA:

		break;

	case	W_GATLING:

		break;

	};
}

void CL_ENEMY::Reload ( CL_CHARA* pCl )
{

}

//	メッシュの解放
void CL_ENEMY::FreeMesh()
{
	//メッシュ解放
	SAFE_RELEASE( this->pMesh );
	SAFE_RELEASE( this->BBox.pBBoxMesh );

	//テクスチャ解放
	for( DWORD i=0; i<this->dwNumMaterials; i++ )
	{
		SAFE_RELEASE( this->pMeshTextures[i] );
	}
	
	//配列解放
	NULL_ARRAY_DELETE(this->pMeshTextures);
	NULL_ARRAY_DELETE(this->pMeshMaterials);
	NULL_ARRAY_DELETE(this->BBox.pBBoxMeshMaterials);
	
	for( DWORD i=0; i< PLAYER_B_MAX; i++ )
	{
		this->clHitHole[i].FreeMesh();
	}
	//	敵の弾の解放
	clBullet -> FreeMesh( clBullet, ENEMY_B_MAX );

}