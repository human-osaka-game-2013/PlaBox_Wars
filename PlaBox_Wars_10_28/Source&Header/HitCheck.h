//	HitCheck.h
//	当たり判定の為のボックスを作って当たり判定を取る。

#pragma once

#include "Lib.h"
#include "graphic.h"

//	追加日	2/10	亀田
#define ADJUSTMENT_OF_HOLE_PASTE 1.85f	//	弾痕貼り付け時の微調整

//	弾痕貼り付け時の各面の角度制限
#define	HIT_RAD_FRONT_MIN	0.5f	//	前面	
#define	HIT_RAD_FRONT_MAX	2.5f	//	前面
#define	HIT_RAD_BACK_MIN	-2.5f	//	背面
#define	HIT_RAD_BACK_MAX	-0.5f	//	背面
#define	HIT_RAD_RIGHT_MIN	-0.2f	//	右側面
#define	HIT_RAD_RIGHT_MAX	0.2f	//	右側面
#define	HIT_RAD_LEFT_MIN	-2.8f	//	左側面
#define	HIT_RAD_LEFT_MAX	2.8f	//	左側面

//	関数SegmentHitcheckにて使用
#define CHECK_HIT_POINT	2	//	着弾点の判定上限
#define NUM_PRISM_VERTEX 8	//	四角柱の頂点数（引数pA用）
#define NUM_PRISM_FACE 6	//	四角柱の面数（引数pA用）

//	HRESULT InitBBox(LPDIRECT3DDEVICE9 pDevice,THING* pThing)
//	当たり判定用のボックスを作る
HRESULT InitBBox ( CL_THING* );

//	BOOL Impact ( THING* pTarget, THING* pBullet )
//	衝突判定≒当たり判定
BOOL Impact ( CL_THING* , CL_THING* );

//	BOOL Impact ( THING* pBullet, THING* pTarget )
//　箱同士の衝突判定
BOOL BoxImpact ( CL_THING* , CL_THING* ,int );

//	当たり判定用の四角形の情報
/*
	a－b
	|　|
	d－c
*/
struct HitRect
{
public:
	D3DXVECTOR3 a, b, c, d;
};

//	線分pqが三角形abcと交点しているかどうかを渡す
//	交差している場合、交差点の重心座標(u,v,w)も返すt
bool IntersectSegmentTriangle( D3DXVECTOR3 p, D3DXVECTOR3 q,
	D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c,
	float &u, float &v, float &w, float &t );

/*	ベクトルvに対して頂点abcポリゴンが表裏どちらを向くか求める
	abcには必ず反時計回りの並びで入れる事
	関数SegmentHitcheck内のtmpRectでは「abc」又は「acd」の順で代入すること
	戻り値	0：裏	1：表	-1：エラー
*/
int PolygonSideCheck( D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c, D3DXVECTOR3 v );

//	頂点abcからなるポリゴンの法線を計算
D3DXVECTOR3 GetPolygonNormal( D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c );

/**	
*	@brief	線分と四角柱モデルとの当たり判定
*	@param[in]	pA	物体A
*	@param[in]	pB	物体B	
*	@param[in]	pHitVec		着弾点からpAの基準点の距離の格納用	
*	@param[in]	pHitNomal	着弾面の法線ベクトル
*	@param[in]	pHitFaceSita	着弾面の法線ベクトルと(0,0,1)ベクトルの間の角度
*	@retval	true	当たっていて、且つpBとpAの最初の接触点がpAポリゴンの表面であった場合
*	@retval	false	当たっていない、又はpBとpAの最初の接触点がpAポリゴンの裏面であった場合
*	@details 補足
	物体A（この場合四角柱型）と	物体Bの（前フレームと現フレームの座標）2点で出来た線分との
	当たり判定をとり物体Aのどのポリゴンに表面から当たったかを調べる関数。@n
	player.xの面指定	例：□0123（数字はvector型のlocalVecに格納されている頂点番号）@n
	底面			□0231@n
	上面			□4675@n
	側面（狭い方）	□0462	□1375@n	
	側面（広い方）	□0154	□2673	（※各面の並びは反時計回り基準にしています）@n
*	@todo	pHitFaceSitaを求める数の為の法線ベクトルと比較対象のベクトルの値が理論的なものじゃない。@n
			考えなおす必要あり
*/
bool SegmentHitcheck( CL_THING* pA, CL_THING* pB, 
	D3DXVECTOR3* pHitVec, D3DXVECTOR3* pHitNomal, float* pHitFaceSita );