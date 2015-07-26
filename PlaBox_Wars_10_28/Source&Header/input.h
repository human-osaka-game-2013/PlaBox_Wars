#pragma once
#include "Lib.h"

#define SAMPLE_BUFFER_SIZE  16

//	マウス座標を格納する構造体
extern	POINT	poCurrentCursor;	//	現在のマウス座標	

#ifdef	_MOUSE_VOL_

struct	MOUSE_VOL
{
	long	lMVolX, lMVolY, lMVolZ;
};

//	マウスの移動量を格納する
extern	MOUSE_VOL	stMouseVol;

//	ワールド座標内のマウス座標
extern	D3DXVECTOR3	vecCursorPos;

#endif

// キーの状態の種類
enum KEYSTATE 
{
	PUSH,
	RELEASE,
	ON,
	OFF,
	KEYSTATE_MAX
};

// 使用するキーの種類
// KeyCheckと共に使うキーが増えればココに種類を追加していく
enum KEYKIND
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	TURN_L,
	TURN_R,
	JUMP,
	RELOAD,
	WEPON_C,

	K_TITLE,
	K_GALLERY,
	K_OPTION,
	K_MAIN_GAME,
	K_MENU,

	K_AR,
	K_MG,
	K_GT,
	K_BZ,

	KEYMAX
};

enum eMOUSEKIND
{
	MOUSE_L,
	MOUSE_R,
	MOUSE_C,
	
	MOUSEMAX
};

HRESULT InitDinput(HWND);	//Directインプットの初期化

HRESULT	InitKey ( HWND hWnd );	//	キーの初期化

HRESULT	InitMouse ( HWND hWnd, bool bForeGroundMode = false  );	//	マウスの初期化

//	キー状態チェック
//	第1引数( キーの定数 )、第2引数( キーの種類 )
void KeyCheck ( int DIK, int st );

//	キー別状態判定
//	第1引数( キーの種類 )、第2引数( キーの状態 )
bool StCheck(int st, int Keyst);

//	マウス状態チェック
//	引数1：ボタンの種類
void MouseCheck ( int st );

//	マウス座標の取得
//	引数1：ウインドウハンドル
void CursorSet(HWND hWnd);

//	マウスボタン別状態判定
//	第1引数( ボタンの種類 )、第2引数( ボタンの状態 )
bool MouseStCheck ( int st, int MouseSt );

//	使うキー全部のチェック
void CheckAllKey ();

//-------------------------------------------------------------------
//	スクリーン座標内のマウス座標をワールド座標に変換
//	制作日	12/12	
//-------------------------------------------------------------------
void MousePosTransform ();