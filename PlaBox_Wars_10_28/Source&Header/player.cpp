#include <stdio.h>
#define TURN_CAMERA_V	0.05f
#define	PLAYER_SPEED	0.4f
#define _MOUSE_VOL_

#include "player.h"
#include "camera.h"
#include "input.h"
#include "Audio.h"
#include "HitCheck.h"

bool plInitFlag;
float cameraTest = 0;
bool LongLeftClick = false;

//	初期化
void CL_PLAYER::CharaInit ( int iCharaArrey )
{
	LoadThingFile ( &player, "Texture\\Xfile\\tank.X", &D3DXVECTOR3( -40.f, 0.f, -40.f ),
					&D3DXVECTOR3( 1.f, 1.f, 1.f), &D3DXVECTOR3 (0.f,0.f,0.f) );	

	fShotRecoil		= 0.f;	
	fShotInterval	= 0.f;	
	fShotCount		= 0.f;		
	bFireFlag		= false;
	hitCount		= 0;

	
	//	追加日	12/16
	bJumpFlag		= false;
	iPlPoint		= 0;
	//----------------------------------

	//	追加日	12/18
	this -> mainWeapon.iBulletType		= W_RIFLE;
	this -> subWeapon.iBulletType		= W_GATLING;
	
#ifdef _DEBUG_
	this -> mainWeapon.iAmmo			= 3;
#else
	this -> mainWeapon.iAmmo			= PL_AR_MAX_AMMO;
#endif

	this ->	subWeapon.iAmmo				= PL_AR_MAX_AMMO;
	this -> mainWeapon.bUseFlag			= true;
	this -> subWeapon.bUseFlag			= false;

	mainWeapon.fFireFlag = false;
	mainWeapon.fShotCount = mainWeapon.fShotInterval = mainWeapon.fShotRecoil = 0.f;

	subWeapon.fFireFlag = false;
	subWeapon.fShotCount = subWeapon.fShotInterval = subWeapon.fShotRecoil = 0.f;

	this -> bDownFlag					= false;
	//------------------------------------------

	possessionBottle= 0;

	player.clBullet -> InitBullet( player.clBullet, PLAYER_B_MAX );

	deadFlag = false;

	plInitFlag = false;
	for( int ii = 0 ; ii < 20 ; ii ++ )
	{
		holepos[ii] = D3DXVECTOR2(0.f,0.f);
	}
}

//	基本処理
void CL_PLAYER::CharaControl ( int iCharaArrey )
{
	//this -> bFireFlag = false;

	//LongLeftClick = false;

	//	左方向に視点を回転----------------------------------------------------------------------
	if ( StCheck ( TURN_L, ON	) )
	{
		vecRotate.y += -TURN_CAMERA_V;
	}
	//	右方向に視点を回転----------------------------------------------------------------------
	if ( StCheck ( TURN_R, ON	) )
	{
		vecRotate.y += TURN_CAMERA_V;
	}
	
	//	前進---------------------------------------------------------------------
	if ( StCheck ( UP, ON	) )
	{
		MoveZ ( &vecPosition, &vecRotate, PLAYER_SPEED );
		if ( !Impact( &player, &object[SKY]) )
		{
			MoveZ ( &vecPosition, &vecRotate, -PLAYER_SPEED );
		}
	}
	//	後退----------------------------------------------------------------------
	if ( StCheck ( DOWN, ON	) )
	{
		MoveZ ( &vecPosition, &vecRotate, -PLAYER_SPEED );
		if ( !Impact( &player, &object[SKY]) )
		{
			MoveZ ( &vecPosition, &vecRotate, PLAYER_SPEED );
		}
	}
	//	左移動----------------------------------------------------------------------
	if ( StCheck ( LEFT, ON	) )
	{
		MoveX ( &vecPosition, &vecRotate, -PLAYER_SPEED );
		if ( !Impact( &player, &object[SKY]) )
		{
			MoveX ( &vecPosition, &vecRotate, PLAYER_SPEED );
		}
	}
	//	右移動----------------------------------------------------------------------
	if ( StCheck ( RIGHT, ON) )
	{
		MoveX ( &vecPosition, &vecRotate, PLAYER_SPEED );
		if ( !Impact( &player, &object[SKY]) )
		{
			MoveX ( &vecPosition, &vecRotate, -PLAYER_SPEED );
		}
	}

	//	リロード----------------------------------------------------------------------
	if ( StCheck ( RELOAD, PUSH ) )
	{
		if ( mainWeapon.iAmmo < PL_AR_MAX_AMMO )
		{
			if( ChargeBpttle ( false ) )
			{
				mainWeapon.iAmmo = PL_AR_MAX_AMMO;
				SoundPlay( SE_TRIGGER, false );
			}
		}
	}

	//	射撃----------------------------------------------------------------------
	if ( !mainWeapon.fFireFlag )
	{
	//	変更しました
	//	12/20
		if ( MouseStCheck ( MOUSE_L, PUSH) )	
		{
			mainWeapon.fFireFlag = true;
			LongLeftClick = true;
			SoundPlay( SE_TRIGGER, false );
		}
		
		
	//------------------------------------------------------------
	}
	if ( MouseStCheck ( MOUSE_L, ON ) )	
	{
		LongLeftClick = true;
	}
	else if ( MouseStCheck ( MOUSE_L, RELEASE ) )	
	{
		LongLeftClick = false;
	}

	//	発射の制御
	if( mainWeapon.fFireFlag )
		ShotControl( mainWeapon.fShotRecoil, mainWeapon.fShotInterval, mainWeapon.fShotCount, &mainWeapon );	
	if( subWeapon.fFireFlag )
		ShotControl( subWeapon.fShotRecoil, subWeapon.fShotInterval, subWeapon.fShotCount, &subWeapon );	

//	追加日	12/16
	//	ジャンプ--------------------------------------------------------------------
	if ( !this -> bJumpFlag )
	{
		if ( StCheck ( JUMP, PUSH ) )	
		{
			this -> bJumpFlag = true;	
			this -> y_prev = this -> vecPosition.y;
			this -> vecPosition.y += JUMP_VOL;
		}
	}
	else
	{
		Jump ( &this -> bJumpFlag , &this -> vecPosition.y );
	}

	//	伏せ------------------------------------------------------------------------
	if ( MouseStCheck ( MOUSE_R, PUSH) )
	{
		if ( !bDownFlag )
		{
			player.vecRotate.x = -1.5;
			this -> bDownFlag = true;
		}
		else
		{
			player.vecRotate.x = 0;
			this -> bDownFlag = false;
		}
	}

	//武器切り替え
	if ( StCheck ( WEPON_C, PUSH ) ){
		//if( !mainWeapon.fFireFlag ){
			BULLET_INFO tmp = mainWeapon;
			mainWeapon = subWeapon;
			subWeapon = tmp;
		//}
	}

//	セカンダリ武器を強制切り替え(仮)
	if ( StCheck ( K_AR, PUSH ) )
	{
		subWeapon.iBulletType = W_RIFLE;

	}	
	if ( StCheck ( K_MG, PUSH ) )
	{
		subWeapon.iBulletType = W_MG;

	}
	if ( StCheck ( K_GT, PUSH ) )
	{
		subWeapon.iBulletType = W_GATLING;

	}
	if ( StCheck ( K_BZ, PUSH ) )
	{
		subWeapon.iBulletType = W_BAZOOKA;

	}

//---------------------------------------------------------------------------------

	clBullet[0].ShotBullet( clBullet, PLAYER_B_MAX );

	//照準　マウスカーソル位置につけてるだけ
	
	float mx = poCurrentCursor.x - GetTexWidth( TEX_TARGET ) / 2.f;
	float my = poCurrentCursor.y - GetTexHeight( TEX_TARGET ) / 2.f;
	
	SetVertex ( NORMAL, TEX_TARGET, mx, my, NULL, NULL, NULL, NULL );
}

//	メッシュの解放
void CL_PLAYER::FreeMesh()
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

	player.clBullet -> FreeMesh( player.clBullet , PLAYER_B_MAX );
}

//	3D描画
void CL_PLAYER::CharaRender ( int iCharaArrey )
{
	Transform ( &player );
	//BillboardingTransform ( &target );
}

//	変更しました。12/18
//
//	発射の制御
//	引数1：連射後の反動、2：射撃時1発1発の間隔、3：連射数、4：武器種類
void CL_PLAYER::ShotControl ( float &pRecoil, float &pInterval, float &pCount, BULLET_INFO* pWeapon )
{
	if ( pWeapon -> iAmmo > 0)
	{
		switch ( pWeapon->iBulletType )
		{
		case	W_RIFLE:
			//if( !LongLeftClick )
			if ( pRecoil <= 0 )	//	連射後の反動
			{
				if ( pInterval <= 0 )	//	射撃時1発1発の間隔
				{
					if ( pCount < RIFLE_OF_FIRE )	//	連射回数
					{
						SoundPlay ( SE_HNG, false );
						pCount++;
						//	銃弾生成
						clBullet[0].MadeBullet( clBullet, &GetEyePos(), &vecCursorPos,
												pWeapon->iBulletType, PLAYER1, W_RIFLE , PLAYER_B_MAX );
						pWeapon -> iAmmo--;	//	1発撃ったので弾数消費
						
						pInterval = INTERVAL_OF_RIFLE * ONE_FR;	// 1発撃ったのでカウンタをリセット
					}
					else
					{
						pWeapon->fFireFlag = false;	
						pCount = 0;
					}
					//	連射数撃ち終わったので反動カウンタをリセット
					if ( pCount == RIFLE_OF_FIRE  )	pRecoil = RECOIL_OF_RIFLE * ONE_FR;	
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
			//if( !LongLeftClick )
			if ( pRecoil <= 0 )
			{
				if ( pInterval <= 0 )
				{
					if ( pCount < MG_OF_FIRE )
					{
						SoundPlay ( SE_HNG, false );
						pCount++;
						//vecCursorPos.y = 0.f;
						clBullet[0].MadeBullet( clBullet, &GetEyePos(), &vecCursorPos,
												pWeapon->iBulletType, PLAYER1, W_MG,PLAYER_B_MAX );
						pWeapon -> iAmmo--;
						
						pInterval = INTERVAL_OF_MG * ONE_FR;
					}
					else
					{
						pWeapon->fFireFlag = false;	
						pCount = 0;
					}
					if ( pCount == MG_OF_FIRE  )	pRecoil = RECOIL_OF_MG * ONE_FR;
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

		case	W_BAZOOKA:
			//if( !LongLeftClick )
			if ( pRecoil <= 0 )
			{
				if ( pInterval <= 0 )
				{
					SoundPlay ( SE_HNG, false );
					pCount++;
					//vecCursorPos.y = 0.f;
					clBullet[0].MadeBullet( clBullet, &GetEyePos(), &vecCursorPos,
											pWeapon->iBulletType, PLAYER1, W_BAZOOKA , PLAYER_B_MAX );
					pWeapon -> iAmmo--;
						
					pInterval = INTERVAL_OF_BAZOOKA * ONE_FR;

					pWeapon->fFireFlag = false;	
					pCount = 0;

					pRecoil = RECOIL_OF_BAZOOKA * ONE_FR;
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

		case	W_GATLING:
			if ( LongLeftClick )
			{
				if ( pRecoil <= 0 )
				{
					if ( pInterval <= 0 )
					{
						
						SoundPlay ( SE_HNG, false );
						
						//vecCursorPos.y = 0.f;
						if( clBullet[0].MadeBullet( clBullet, &GetEyePos(), &vecCursorPos,
												pWeapon->iBulletType, PLAYER1, W_GATLING,PLAYER_B_MAX ))
							pWeapon -> iAmmo--;
							
						pInterval = INTERVAL_OF_RIFLE * ONE_FR;
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
			}
			else
			{
				pWeapon->fFireFlag = false;
			}
			break;

		};
	}
	else
	{
		pCount = RIFLE_OF_FIRE;
		pWeapon->fFireFlag = false;
	}
}

//	ボトルの使用関数
bool	CL_PLAYER::ChargeBpttle ( bool bCharge )
{
	bool	bResult = false;	//	ボトル使用結果
	if ( bCharge )
	{
		possessionBottle++;
		bResult = true;
	}
	else
	{
		if ( possessionBottle <= 0 )	//	持ってるボトルが０以下なら
		{
			bResult = false;
		}
		else
		{
			possessionBottle--;

			bResult = true;
		}
	}
	return bResult;
}

void CL_PLAYER::Reload ( CL_CHARA* pCl )
{
}

//北川　Ammoを引き渡す関数を追加 01/27
int	CL_PLAYER::GetAmmoStock ( )
{
	return mainWeapon.iAmmo; 
}