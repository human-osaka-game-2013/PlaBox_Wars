#include "HitCheck.h"
//#include "shot.h"
#include "camera.h"
#include "game.h"
int g_shot = SHOTTIME;

//弾速
#define RIFLR_SPEED 0.85f
#define MG_SPEED 1.2f
#define BAZOOKA_SPEED 0.7f
#define GATLING_SPEED 2.f

//弾ダメージ
#define RIFLR_DAMAGE 3
#define MG_DAMAGE 2
#define BAZOOKA_DAMAGE 10
#define GATLING_DAMAGE 1


//	銃弾の初期化
void CL_BULLET::InitBullet( CL_BULLET *clCharaBullet, int iArrayNum )
{
	for ( int i = 0; i < iArrayNum; i++, clCharaBullet++ )
	{
		LoadThingFile ( clCharaBullet, "Texture\\Xfile\\R_Bullet.x", &D3DXVECTOR3( -1.f, -8.f, -1.f ), &D3DXVECTOR3( 0.5f, 0.5f, 0.5f ), &D3DXVECTOR3(0.f,0.f,0.f) );
		clCharaBullet -> vecPosition.x	= 0;
		clCharaBullet -> vecPosition.y	= -5.f;
		clCharaBullet -> vecPosition.z	= 0;

		clCharaBullet -> vecBeforePos.x	= 0;
		clCharaBullet -> vecBeforePos.y	= -5.f;
		clCharaBullet -> vecBeforePos.z	= 0;

		clCharaBullet -> gx	= 0;
		clCharaBullet -> gy	= 0;
		clCharaBullet -> gz	= 0;
		clCharaBullet -> Shot_flag = false;
		clCharaBullet -> shot_time = 0;
		clCharaBullet -> spx	= 0;
		clCharaBullet -> spy	= 0;
		clCharaBullet -> spz	= 0;
		
		InitBBox( clCharaBullet );
	}
}

//	銃弾の生成
bool CL_BULLET::MadeBullet( CL_BULLET *clCharaBullet,  D3DXVECTOR3 *vecPos, 
							D3DXVECTOR3 *ImpactPos, int iWeaponType, int iFireChara ,eWEAPON type , int iArrayNum)
{
	for( int i = 0; i < iArrayNum; i++, clCharaBullet++ )
	{
		if(clCharaBullet -> Shot_flag == false)
		{
			clCharaBullet -> vecPosition.x = vecPos -> x;
			clCharaBullet -> vecPosition.y = vecPos -> y;
			clCharaBullet -> vecPosition.z = vecPos -> z;

			clCharaBullet -> vecBeforePos.x = vecPos -> x;
			clCharaBullet -> vecBeforePos.y	= vecPos -> y;
			clCharaBullet -> vecBeforePos.z	= vecPos -> z;

			clCharaBullet -> gx = ImpactPos -> x;
			clCharaBullet -> gy = ImpactPos -> y;
			clCharaBullet -> gz = ImpactPos -> z;

			clCharaBullet -> Shot_flag = true;
			clCharaBullet -> shot_time = 0.f;
			
			//距離求める
			float Length = GetVectorLength( D3DXVECTOR3( clCharaBullet->gx - clCharaBullet->vecPosition.x ,
														clCharaBullet->gy - clCharaBullet->vecPosition.y ,
														clCharaBullet->gz - clCharaBullet->vecPosition.z ) );
			//距離で割ることで単位ベクトル化
			clCharaBullet -> spx	= ( clCharaBullet->gx - clCharaBullet->vecPosition.x ) / Length;
			clCharaBullet -> spy	= ( clCharaBullet->gy - clCharaBullet->vecPosition.y ) / Length;
			clCharaBullet -> spz	= ( clCharaBullet->gz - clCharaBullet->vecPosition.z ) / Length;

			clCharaBullet -> iBulletType = type;
			clCharaBullet -> iCharaType = iFireChara;

			clCharaBullet -> vecScall = D3DXVECTOR3( 1.f , 1.f , 1.f );

			switch( type ){ 
				case W_RIFLE:	
					clCharaBullet -> m_Damage = RIFLR_DAMAGE;
					if( iFireChara != PLAYER1 ){
						for( UINT ii = 0 ; ii < clCharaBullet -> dwNumMaterials ; ii++ ){
							clCharaBullet -> pMeshMaterials -> Ambient = D3DXCOLOR( 255 , 0 , 0 , 255 );
						}
					}
					break;
				case W_MG:
					clCharaBullet -> m_Damage = MG_DAMAGE; 
					if( iFireChara != PLAYER1 ){
						for( UINT ii = 0 ; ii < clCharaBullet -> dwNumMaterials ; ii++ ){
							clCharaBullet -> pMeshMaterials -> Ambient = D3DXCOLOR( 255 , 0 , 0 , 255 );
						}
					}
					break;
				case W_BAZOOKA:
					clCharaBullet -> m_Damage = BAZOOKA_DAMAGE; 
					clCharaBullet -> SetScall( D3DXVECTOR3( 3.f , 3.f , 3.f ) );
					if( iFireChara != PLAYER1 ){
						for( UINT ii = 0 ; ii < clCharaBullet -> dwNumMaterials ; ii++ ){
							clCharaBullet -> pMeshMaterials -> Ambient = D3DXCOLOR( 255 , 0 , 0 , 255 );
						}
					}
					break;
				case W_GATLING:
					clCharaBullet -> m_Damage = GATLING_DAMAGE; 
					if( iFireChara != PLAYER1 ){
						for( UINT ii = 0 ; ii < clCharaBullet -> dwNumMaterials ; ii++ ){
							clCharaBullet -> pMeshMaterials -> Ambient = D3DXCOLOR( 255 , 0 , 0 , 255 );
						}
					}
					break;
			}
			return true;			
		}
	}
	return false;
}

//	銃弾の処理
void CL_BULLET::ShotBullet( CL_BULLET *clCharaBullet, int iArrayNum )		//実行
{
	for(int i = 0; i < iArrayNum; i++, clCharaBullet++ )
	{
		if(clCharaBullet -> Shot_flag == true)
		{
			float Speed = 0.f;
			switch( clCharaBullet -> iBulletType ){ 
				case W_RIFLE:		Speed = RIFLR_SPEED; break;
				case W_MG:		Speed = MG_SPEED; break;
				case W_BAZOOKA:	Speed = BAZOOKA_SPEED; break;
				case W_GATLING:	Speed = GATLING_SPEED; break;
			}
			clCharaBullet -> vecBeforePos.x = clCharaBullet -> vecPosition.x;
			clCharaBullet -> vecBeforePos.y	= clCharaBullet -> vecPosition.y;
			clCharaBullet -> vecBeforePos.z	= clCharaBullet -> vecPosition.z;

			clCharaBullet -> vecPosition.x += clCharaBullet -> spx * Speed;
			clCharaBullet -> vecPosition.y += clCharaBullet -> spy * Speed;
			clCharaBullet -> vecPosition.z += clCharaBullet -> spz * Speed;

			//バズーカなら落ちていく
			if( clCharaBullet -> iBulletType == W_BAZOOKA ) 
			{
				clCharaBullet -> vecPosition.y -= clCharaBullet -> shot_time / 20 * 0.01f;
			}

			clCharaBullet -> shot_time ++;

			/*if( clCharaBullet -> shot_time <= 0 )
			{
				clCharaBullet -> Shot_flag = false;
				clCharaBullet -> vecPosition.y = -10.0f;
				clCharaBullet -> vecBeforePos.y	= clCharaBullet -> vecPosition.y;
			}*/
			
		}
		else
		{
			clCharaBullet -> vecPosition.y = -10.0f;
		}
	}
}

//	メッシュの解放
void CL_BULLET::FreeMesh(CL_BULLET *clCharaBullet, int iArrayNum)
{
	for ( int i = 0; i < iArrayNum; i++, clCharaBullet++ )
	{
		//メッシュ解放
		SAFE_RELEASE( clCharaBullet->pMesh );
		SAFE_RELEASE( clCharaBullet->BBox.pBBoxMesh );
		
		//テクスチャ解放
		for( DWORD i=0; i<clCharaBullet->dwNumMaterials; i++ )
		{
			SAFE_RELEASE( clCharaBullet->pMeshTextures[i] );
		}
		 
		//配列解放
		NULL_ARRAY_DELETE(clCharaBullet->pMeshTextures);
		NULL_ARRAY_DELETE(clCharaBullet->pMeshMaterials);
		NULL_ARRAY_DELETE(clCharaBullet->BBox.pBBoxMeshMaterials);
	}
}
