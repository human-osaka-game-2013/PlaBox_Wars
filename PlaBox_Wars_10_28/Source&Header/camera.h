#pragma once

#define EYEPOS_Y_NORMAL		2.5f	//	立ち状態のカメラ位置
#define LOOKPOS_Y_NORMAL	2.5f	//	立ち状態の注視点

#define EYEPOS_Y_DOWN		0.65f	//	伏せ状態のカメラ位置
#define LOOKPOS_Y_DOWN		0.8f	//	伏せ状態の注視点

#define	PI	3.1415926f

void InitCamera();			//カメラ関数・・・初期化

void Camera( float );		//カメラ視点移動管理

void Camera();				//カメラ処理関数

void Jump ( bool *jflag );	

void Down ();

void CameraPosCheck();		// カメラ座標チェック

D3DXVECTOR3 GetEyePos();	//	カメラ位置の取得
D3DXVECTOR3 GetLookPos();	//	注視点の取得
float		GetRad();		//	角度(ラジアン)の取得

void SetCameraPos ( D3DXVECTOR3 vecPos, D3DXVECTOR3 vecRot );	//	カメラ位置をキャラの座標に

#ifdef	CLASS
class CL_CAMERA
{
public:
	CL_CAMERA();	//	カメラ位置、注視点、角度(ラジアン)を初期化

	D3DXVECTOR3 GetEyePos();	//	カメラ位置の取得
	D3DXVECTOR3 GetLookPos();	//	注視点の取得
	float		GetRad();		//	角度(ラジアン)の取得
private:
	static	D3DXVECTOR3 g_eyePos;	// 視点座標xyz
	static	D3DXVECTOR3 g_lookPos;	// 注視点座標xyz
	static	float		g_radian;	// 視点回転補正
};
#endif

extern D3DXVECTOR3 g_eyePos;	// 視点座標xyz
extern D3DXVECTOR3 g_lookPos;	// 注視点座標xyz
