#include <stdio.h>



#define	PI	3.1415926f

#include "graphic.h"
#include "camera.h"

D3DXVECTOR3 g_eyePos;	// 視点座標xyz
D3DXVECTOR3 g_lookPos;	// 注視点座標xyz

float g_radian;		// 視点回転補正

void InitCamera()
{
	//視点の初期化
	g_eyePos.x =	0.0f;
	g_eyePos.y =	EYEPOS_Y_NORMAL;
	g_eyePos.z =	0.0f;

	//注視点の初期化
	g_lookPos.x = 0.0f;
	g_lookPos.y = LOOKPOS_Y_NORMAL;
	g_lookPos.z = 10.0f;

	//回転に使用
	g_radian = 0.0f;
}

D3DXVECTOR3 GetEyePos() { return g_eyePos; }
D3DXVECTOR3 GetLookPos(){ return g_lookPos; }
float		GetRad()	{ return g_radian; }


void Down ()
{
	g_eyePos.y = EYEPOS_Y_DOWN;
	g_lookPos.y = LOOKPOS_Y_DOWN;
}

void CameraPosCheck()
{
	
}

void SetCameraPos ( D3DXVECTOR3 vecPos, D3DXVECTOR3 vecRot )	//	カメラ位置をキャラの座標に
{
	g_eyePos.x	= vecPos.x;
	g_eyePos.z	= vecPos.z;
	
	//	追加日	12/16
	g_lookPos.y = g_eyePos.y = vecPos.y + EYEPOS_Y_NORMAL;
	//--------------------------------------------

	g_radian	= vecRot.y;

	g_lookPos.x	= g_eyePos.x + sin( g_radian );
	g_lookPos.z	= g_eyePos.z + cos( g_radian );
}