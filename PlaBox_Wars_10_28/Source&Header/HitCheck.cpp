#include "HitCheck.h"
#include "graphic.h"
#include "main.h"
#include <cstdio>
#include <vector>
#include <math.h>

//	HRESULT InitBBox(LPDIRECT3DDEVICE9 pDevice,THING* pThing)
//	当たり判定用のボックスを作る
HRESULT InitBBox ( CL_THING* pThing )
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	VOID* pVertices = NULL;
	D3DXVECTOR3 vecMax, vecMin;


	//	メッシュの頂点バッファーをロック
	if ( FAILED ( pThing -> pMesh -> GetVertexBuffer ( &pVB ) ) )
	{
		return E_FAIL;
	}
	if ( FAILED ( pVB -> Lock ( 0, 0, &pVertices, 0 ) ) )
	{
		SAFE_RELEASE ( pVB );
		return E_FAIL;
	}

	//	メッシュの外接円の中心と半径を計算してくれる
	hr = D3DXComputeBoundingBox ( (D3DXVECTOR3*) pVertices, pThing -> pMesh -> GetNumVertices(),
								D3DXGetFVFVertexSize ( pThing -> pMesh ->GetFVF ()), &vecMin, &vecMax );
	pVB -> Unlock();
	SAFE_RELEASE ( pVB );

	if ( FAILED ( hr ))
	{
		return hr;
	}
	pThing -> BBox.vecMax = vecMax;
	pThing -> BBox.vecMin = vecMin;

	//	↑で出た中心と半径からメッシュとしてのボックスを作ろう
	hr = D3DXCreateBox ( pD3Device, vecMax.x * 2, vecMax.y * 2, vecMax.z * 2, &pThing -> BBox.pBBoxMesh, NULL );
	
	if ( FAILED ( hr ) )
	{
		return hr;
	}
	//ボックスメッシュのマテリアル　白色、半透明、光沢強
	pThing -> BBox.pBBoxMeshMaterials = new D3DMATERIAL9;
	pThing -> BBox.pBBoxMeshMaterials -> Diffuse.r = 1.0f;
	pThing -> BBox.pBBoxMeshMaterials -> Diffuse.g = 1.0f;
	pThing -> BBox.pBBoxMeshMaterials -> Diffuse.b = 1.0f;	
	pThing -> BBox.pBBoxMeshMaterials -> Diffuse.a = 0.5f;
	pThing -> BBox.pBBoxMeshMaterials -> Ambient = pThing -> BBox.pBBoxMeshMaterials -> Diffuse;	
	pThing -> BBox.pBBoxMeshMaterials -> Specular.r = 1.0f;
	pThing -> BBox.pBBoxMeshMaterials -> Specular.g = 1.0f;
	pThing -> BBox.pBBoxMeshMaterials -> Specular.b = 1.0f;
	pThing -> BBox.pBBoxMeshMaterials -> Emissive.r = 0.1f;
	pThing -> BBox.pBBoxMeshMaterials -> Emissive.g = 0.1f;
	pThing -> BBox.pBBoxMeshMaterials -> Emissive.b = 0.1f;
	pThing -> BBox.pBBoxMeshMaterials -> Power = 120.0f;	

	return S_OK;
}

//	BOOL Impact ( THING* pBullet, THING* pTarget )
//	衝突判定≒当たり判定
BOOL Impact ( CL_THING* pBullet, CL_THING* pTarget )
{
	//	ターゲット(敵or自機)用に2つの頂点を用意して初期化
	D3DXVECTOR3 vecMaxTage, vecMinTage;
	vecMaxTage = pTarget -> BBox.vecMax	+ pTarget -> vecPosition;
	vecMinTage = pTarget -> BBox.vecMin + pTarget -> vecPosition;

	//	銃弾の中心点が、ターゲットのボリューム内か調べてる

	if ( pBullet->vecPosition.x >= vecMinTage.x && pBullet->vecPosition.x <= vecMaxTage.x )
	{
		if( pBullet->vecPosition.y >= vecMinTage.y && pBullet->vecPosition.y <= vecMaxTage.y )
		{
			if( pBullet->vecPosition.z >= vecMinTage.z && pBullet->vecPosition.z <= vecMaxTage.z )
			{
				return TRUE;
			}
		}
	}
		return FALSE;
	
}

//	BOOL Impact ( THING* pBullet, THING* pTarget )
//　箱同士の衝突判定
BOOL BoxImpact ( CL_THING* pA, CL_THING* pB ,int _check)
{
	//物体A用に２つの頂点を用意し初期化する
	D3DXVECTOR3 vecMaxA,vecMinA;
	vecMaxA = pA -> BBox.vecMax + pA -> vecPosition;
	vecMinA = pA -> BBox.vecMin + pA -> vecPosition;
	//物体B用に８つの頂点を用意し初期化する
	
	D3DXVECTOR3 vecB[8];
	vecB[0].x = pB -> BBox.vecMin.x;
	vecB[0].y = pB -> BBox.vecMin.y;
	vecB[0].z = pB -> BBox.vecMin.z;
	vecB[1].x = pB -> BBox.vecMax.x;
	vecB[1].y = pB -> BBox.vecMin.y;
	vecB[1].z = pB -> BBox.vecMin.z;
	vecB[2].x = pB -> BBox.vecMin.x;
	vecB[2].y = pB -> BBox.vecMax.y;
	vecB[2].z = pB -> BBox.vecMin.z;
	vecB[3].x = pB -> BBox.vecMin.x;
	vecB[3].y = pB -> BBox.vecMin.y;
	vecB[3].z = pB -> BBox.vecMax.z;
	vecB[4].x = pB -> BBox.vecMax.x;
	vecB[4].y = pB -> BBox.vecMax.y;
	vecB[4].z = pB -> BBox.vecMin.z;
	vecB[5].x = pB -> BBox.vecMax.x;
	vecB[5].y = pB -> BBox.vecMin.y;
	vecB[5].z = pB -> BBox.vecMax.z;
	vecB[6].x = pB -> BBox.vecMin.x;
	vecB[6].y = pB -> BBox.vecMax.y;
	vecB[6].z = pB -> BBox.vecMax.z;
	vecB[7].x = pB -> BBox.vecMax.x;
	vecB[7].y = pB -> BBox.vecMax.y;
	vecB[7].z = pB -> BBox.vecMax.z;

	// 物体Bの８つの頂点全てについて、物体Aのボリューム内であるかどうか調べる
	for(DWORD i=0;i<8;i++)
	{
		vecB[i] += pB -> vecPosition;
		if(vecB[i].x >= vecMinA.x && vecB[i].x <= vecMaxA.x)
		{
			if(vecB[i].y >= vecMinA.y && vecB[i].y <= vecMaxA.y)
			{
				if(vecB[i].z >= vecMinA.z && vecB[i].z <= vecMaxA.z)
				{
					return TRUE;
				}
			}
		}
	}


	if( _check == 0 )
		return BoxImpact(pB,pA,1);
	else if( _check == 1 )
		return FALSE;
	else 
		return FALSE;
}


/**	
*	@brief	線分と四角柱モデルとの当たり判定
*/
bool SegmentHitcheck( CL_THING* pA, CL_THING* pB, 
	D3DXVECTOR3* pHitVec, D3DXVECTOR3* pHitNomal, float* pHitFaceSita )
{
	int hitCount = 0;		//	当たった面の数
	D3DXVECTOR3 HitPoint[CHECK_HIT_POINT];//	着弾点
	D3DXVECTOR3	tmpVec[NUM_PRISM_VERTEX];	//	pA用の頂点変数
	float t = 0.f;			//	当たり判定関数用に必要な引数
	
	//	pAのlocalVecをワールド座標変換して、tmpVecに代入
	for( int i = 0; i < NUM_PRISM_VERTEX; i++ )
	{
		tmpVec[i] = pA->LocalToWarldTransform( pA->vecRotate.x, pA->vecRotate.y, pA->vecRotate.z,
										pA->vecScall.x, pA->vecScall.y, pA->vecScall.z,
										pA->vecPosition.x, pA->vecPosition.y, pA->vecPosition.z,
										pA->localVec[i].x, pA->localVec[i].y, pA->localVec[i].z);
		
	}

	HitRect tmpRect[NUM_PRISM_FACE];		//	tmpVecを元に四角柱情報を生成	
	HitRect* pHitRect[CHECK_HIT_POINT] = {NULL}; //	当たった判定があった配列のポインタを入れておく
	
	//	底面
	tmpRect[0].a = tmpVec[0]; 
	tmpRect[0].b = tmpVec[2]; 
	tmpRect[0].c = tmpVec[3]; 
	tmpRect[0].d = tmpVec[1];
	//	上面
	tmpRect[1].a = tmpVec[4]; 
	tmpRect[1].b = tmpVec[6]; 
	tmpRect[1].c = tmpVec[7]; 
	tmpRect[1].d = tmpVec[5];
	//	側面（狭い方）
	tmpRect[2].a = tmpVec[0]; 
	tmpRect[2].b = tmpVec[4]; 
	tmpRect[2].c = tmpVec[6]; 
	tmpRect[2].d = tmpVec[2];

	tmpRect[3].a = tmpVec[1];
	tmpRect[3].b = tmpVec[3];
	tmpRect[3].c = tmpVec[7];
	tmpRect[3].d = tmpVec[5];
	//	側面（広い方）
	tmpRect[4].a = tmpVec[0]; 
	tmpRect[4].b = tmpVec[1]; 
	tmpRect[4].c = tmpVec[5]; 
	tmpRect[4].d = tmpVec[4];

	tmpRect[5].a = tmpVec[2];
	tmpRect[5].b = tmpVec[6];
	tmpRect[5].c = tmpVec[7];
	tmpRect[5].d = tmpVec[3];
	
	//	6面（△を12面）全てチェック
	//（※各面の並びは反時計回り基準にabcdに代入しているのでループでも問題なし）
	for( int i = 0; i < NUM_PRISM_FACE; i++ )
	{
		//	□abcdを△2つに分けて判定を取る
		//	pBの2点と△abcの判定
		if( IntersectSegmentTriangle( pB->vecPosition, pB->vecBeforePos, 
			tmpRect[i].a, tmpRect[i].b, tmpRect[i].c,
			HitPoint[hitCount].x, HitPoint[hitCount].y, HitPoint[hitCount].z, t) )
		{
			pHitRect[hitCount] = &tmpRect[i];	//	当たった面の行列ポインタを確保
			hitCount++;	//	判定カウンタ++
		}
		//	pBの2点と△acdの判定
		else if( IntersectSegmentTriangle( pB->vecPosition, pB->vecBeforePos,
			tmpRect[i].a, tmpRect[i].c, tmpRect[i].d,
			HitPoint[hitCount].x, HitPoint[hitCount].y, HitPoint[hitCount].z, t) )
		{
			pHitRect[hitCount] = &tmpRect[i]; 
			hitCount++;
		}
		

		if( hitCount >= CHECK_HIT_POINT )	//	2点以上交差する事はほぼ無いのでループを抜ける
			break;
	}

	//	当たっていなかったのでfalse
	if( hitCount == 0 )
	{
		return false;
	}

	//	表面に当たっていたので、pHitVecとpHitFaceSitaに必要な情報を入れる
	*pHitVec = HitPoint[0] - pA->vecPosition;
	D3DXVECTOR3 vecNomal(GetPolygonNormal( pHitRect[0]->a, pHitRect[0]->b, pHitRect[0]->c ));
	D3DXVECTOR3 _vecTemp(0,0,1);
	*pHitNomal = vecNomal;
	float lengthN = GetVectorLength(vecNomal);
	float lengthT = GetVectorLength(_vecTemp);
	float _dot = D3DXVec3Dot(&_vecTemp, &vecNomal);
	float cosSita = _dot/( lengthN * lengthT );
	if(vecNomal.x >= 0)
		*pHitFaceSita = acos(cosSita);
	else
		*pHitFaceSita = -acos(cosSita);
	return true;	
}
/*
	線分pqが三角形abcと交点しているかどうかを渡す
	交差している場合、交差点の座標(u,v,w)を返す
*/
bool IntersectSegmentTriangle( D3DXVECTOR3 p, D3DXVECTOR3 q,
	D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c,
	float &u, float &v, float &w, float &t )
{
	D3DXVECTOR3 ab = b-a;	//	三角形の辺のベクトルを求める
	D3DXVECTOR3 ac = c-a;
	D3DXVECTOR3 qp = p-q;	//	線分のベクトルを求める

	//	三角形の法線を計算。同じ三角形に対して複数の線分が交差する場合は
	//	予め計算しておくか、あるいはキャッシュを残しておくことも可能
	D3DXVECTOR3 n;	//	外接の計算結果
	D3DXVec3Cross( &n, &ab, &ac );

	//	分母dを計算。d<=0の場合、線分は三角形に平行であるか、
	//	あるいは三角形から離れていく方向を指しているので、早期に終了
	float d = D3DXVec3Dot( &qp, &n );
	if( d <= 0.0f )	return false;

	//	pqと三角形の平面の交差の値tを計算
	//	0<=t の場合は光線に交差。線分は 0<=t<=1 の場合に交差。
	//	交差が三角形を貫通することが分かるまでdによる除算を遅延
	D3DXVECTOR3 ap = p-a;
	t = D3DXVec3Dot( &ap, &n );
	if( t < 0.0f )	return false;
	if( t > d )	return false;	//	線分に対して。
							//	光線に対する判定ではコードのこの行は除外

	//	重心座標の成分を計算し範囲内にあるかどうか判定
	D3DXVECTOR3 e;
	D3DXVec3Cross( &e, &qp, &ap );
	v = D3DXVec3Dot( &ac, &e );
	if( v < 0.0f || v > d )	return false;
	w = -D3DXVec3Dot( &ab, &e );
	if( w < 0.0f || v + w > d )	return false;

	//	線分/光線は三角形と交差。遅延した除算を実行し
	//	最後に重心座標の成分を計算
	float ood = 1.0f / d;
	t *= ood;
	v *= ood;		//	bの座標値
	w *= ood;		//	cの座標値
	u = 1.0f-v-w;	//	aの座標値

	D3DXVECTOR3 tmpBarycentric(0,0,0);	//	交点の計算用
	tmpBarycentric = (a*u)+(b*v)+(c*w);	//	重心値を元に交点を計算
	//	計算結果を代入
	u = tmpBarycentric.x;	v = tmpBarycentric.y;	w = tmpBarycentric.z;
	return true;
}

/*	ベクトルvに対して頂点abcポリゴンが表裏どちらを向くか求める
	abcには必ず反時計回りの並びで入れる事
	関数SegmentHitcheck内のtmpRectでは「abc」又は「acd」の順で代入すること
	戻り値	0：裏	1：表	-1：エラー
*/
int PolygonSideCheck( D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c, D3DXVECTOR3 v )
{
	D3DXVECTOR3 ab = b-a;	//	三角形の辺のベクトルを求める
	D3DXVECTOR3 bc = c-a;

	D3DXVECTOR3 n(0.f,0.f,0.f);	//	外接の計算結果
	float t = 0.f;	//	内接の計算結果

	//	ab bcの外接
	D3DXVec3Cross( &n, &ab, &bc );

	//	vとの内積
	t = D3DXVec3Dot( &v, &n );

	if( t < 0.0f )	//ポリゴンはベクトルvから見て表側
	{
		return 1;
	}
	else if( t > 0.0f )	//ポリゴンはベクトルvから見て裏側
	{
		return 0;
	}

	//	d=0	並行
	return -1;
}

/*
	頂点abcからなるポリゴンの法線を計算
*/
D3DXVECTOR3 GetPolygonNormal( D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c )
{
	D3DXVECTOR3 ab = b-a;
	D3DXVECTOR3 bc = c-b;
	D3DXVECTOR3 n;	//	法線

	D3DXVec3Cross( &n, &ab, &bc );	//	ab bcの外積
	D3DXVec3Normalize( &n, &n );	//	nの単位化
	return n;
}