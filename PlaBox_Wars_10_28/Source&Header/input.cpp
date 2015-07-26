#define _MOUSE_VOL_


#define _THING_CLASS_

#include <stdio.h>
#include <Windows.h>
#include "graphic.h"
#include "input.h"
#include "camera.h"

LPDIRECTINPUT8			pDinput			= NULL; //インプット -> 入力処理
LPDIRECTINPUTDEVICE8	pKeyDevice		= NULL; //キーデバイス -> 外部キー入力
LPDIRECTINPUTDEVICE8	pMouseDevice	= NULL; //マウスデバイス -> 外部マウス入力

// キーの状態を種類別に格納する変数
int		Key[KEYMAX];
// キーの種類別に押されているかのフラグ
bool	PreKey[KEYMAX] = {false};

//	マウスの状態を種類別に格納する変数
int		Mouse[MOUSEMAX];
//	マウスの種類別に押されているかのフラグ
bool	PreMouse[MOUSEMAX] = {false};

//	マウスの移動量
MOUSE_VOL	stMouseVol;

//	マウス座標を格納する構造体
POINT	poCurrentCursor;	//	現在のマウス座標	
POINT	poBeforeCursor;		//	前のマウス座標

//	ワールド座標内のマウス座標
D3DXVECTOR3	vecCursorPos;

//==================================================================
//
//	ダイレクトインプットの初期化
//
//=================================================================
//ダイレクトインプットの初期化関数
HRESULT InitDinput(HWND hWnd )
{
	HRESULT hr;
	
	//｢DirectInput｣オブジェクトの作成
	if(FAILED (hr = DirectInput8Create (
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&pDinput,
		NULL
		) ) )
	{
		return hr;
	}
	//if(FAILED ( hr = pDinput->EnumDevices(
	//		DI8DEVCLASS_GAMECTRL,
	//		lpCallback,
	//		pvRef,
	//		DIEDFL_ATTACHEDONLY
	//	)))
	//{
	//	return hr;
	//}
	if (FAILED ( InitKey ( hWnd )))
	{
		return hr;
	}
	if (FAILED ( InitMouse ( hWnd, true )))
	{
		return hr;
	}
	
	return S_OK;
}

//------------------------------------------------------------------
//
//	キーの設定
//	
//-----------------------------------------------------------------
HRESULT	InitKey ( HWND hWnd )
{
	HRESULT hr;

	//｢DirectInputデバイス｣オブジェクトの作成(キーボード)
	if(FAILED (hr = pDinput->CreateDevice (
	GUID_SysKeyboard,
	&pKeyDevice,
	NULL

	) ) )
	{
		return hr;
	}
	//デバイスをキーボードに設定
	if(FAILED (hr = pKeyDevice->SetDataFormat (&c_dfDIKeyboard) ) )
	{
		return hr;
	}
	//協調レベルの設定		*当該アプリケーション(ゲーム)と、windowsOS自体のキーボードデバイスの占有率設定
	if(FAILED (hr = pKeyDevice->SetCooperativeLevel(
		hWnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND		// * 非排他でバック・グラウンド
		) ) )
	{
		return hr;
	}
	//デバイスを｢取得｣する
	pKeyDevice->Acquire();							// * 作成したデバイスへのアクセス権取得
	return S_OK;
}

//------------------------------------------------------------------
//
//	マウスの設定
//	
//-----------------------------------------------------------------
HRESULT	InitMouse ( HWND hWnd, bool bForeGroundMode )
{
	HRESULT hr;
	LPDIENUMDEVICESCALLBACK lpCallback	= NULL;
	LPVOID	pvRef	= NULL;		
	HGLOBAL	hGlobal	= NULL;	//	グローバルハンドル	
	
	//｢DirectInputデバイス｣オブジェクトの作成(マウス)
	if(FAILED (hr = pDinput->CreateDevice (
		GUID_SysMouseEm,
		&pMouseDevice,
		NULL
		) ) )
	{
		return hr;
	}

	//デバイスをマウスに設定
	if(FAILED (hr = pMouseDevice->SetDataFormat (&c_dfDIMouse) ) )
	{
		return hr;
	}

	if ( bForeGroundMode )	// フォアグラウンドでマウスを使うなら
	{
		//	マウスの動作の設定
		if(FAILED (hr = pMouseDevice->SetCooperativeLevel(
			hWnd,
			DISCL_EXCLUSIVE | DISCL_FOREGROUND
			)))
		{
			return hr;
		}
	}
	else
	{
		//	マウスの動作の設定
		if(FAILED (hr = pMouseDevice->SetCooperativeLevel(
			hWnd,
			DISCL_EXCLUSIVE | DISCL_BACKGROUND
			)))
		{
			return hr;
		}
	}

	//	イベント通知を使ってマウスの動作を検出する方法と、
	//	マウスからのバッファリング入力を読み取る
	hGlobal = CreateEvent(NULL, FALSE, FALSE, NULL);

	if( hGlobal == NULL )
	{
		return FALSE;
	}
	//	デバイス状態が変化したときに設定されるイベントを指定する
	if (FAILED ( hr = pMouseDevice->SetEventNotification ( hGlobal )))
	{
		return hr;
	}

	DIPROPDWORD dipdw;
    // the header
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    // the data
    dipdw.dwData            = DIPROPAXISMODE_REL;

	//	デバイスの動作を定義するプロパティを設定する
	if (FAILED ( hr = pMouseDevice->SetProperty(
		DIPROP_BUFFERSIZE,
		&dipdw.diph
		)))
	{
		return hr;
	}

	//デバイスを｢取得｣する
	pMouseDevice->Acquire();	// * 作成したデバイスへのアクセス権取得
	return S_OK;
}

//==================================================================
//
//	キー状態チェック
//
//=================================================================
//	第1引数( キーの定数 )、第2引数( キーの種類 )
void KeyCheck ( int DIK, int st )
{
	HRESULT hr = pKeyDevice->Acquire();		//デバイスへのアクセス権の再取得
	
	if( (hr==DI_OK) || (hr==S_FALSE) )	
	{
		BYTE diks[256];
		pKeyDevice->GetDeviceState(sizeof (diks), &diks);

		if ( diks[DIK] & 0x80 )
		{
			if ( !PreKey[st] )
			{
				Key[st] = PUSH;
			}
			else
			{
				Key[st] = ON;
			}
			PreKey[st] = true;
		}

		else
		{
			if ( !PreKey[st] )
			{
				Key[st] = OFF;
			}
			else
			{
				Key[st] = RELEASE;
			}
			PreKey[st] = false;
		}
	}
}

//	キー別状態判定
//	第1引数( キーの種類 )、第2引数( キーの状態 )
bool StCheck(int st, int Keyst) 
{
	return ( Key[st] == Keyst );
}

//==================================================================
//
//	マウス状態チェック
//
//=================================================================
//	マウス状態チェック
//	引数1：ボタンの種類
void MouseCheck ( int st )
{
	HRESULT	hr = pMouseDevice->Acquire();

	DIMOUSESTATE dims;

	hr = pMouseDevice->GetDeviceState(sizeof (dims), &dims);

	if ( hr== S_OK || (hr== S_FALSE) )
	{
		if ( dims.rgbButtons[st] & 0x80 )
		{
			if ( !PreMouse[st] )
			{
				Mouse[st] = PUSH;
			}
			else
			{
				Mouse[st] = ON;
			}
			PreMouse[st] = true;
		}

		else
		{
			if ( !PreMouse[st] )
			{
				Mouse[st] = OFF;
			}
			else
			{
				Mouse[st] = RELEASE;
			}
			PreMouse[st] = false;
		}
	}
}

//	マウス座標の取得と移動量を決める。
//	引数1：ウインドウハンドル
void CursorSet(HWND hWnd)
{
	GetCursorPos( &poCurrentCursor );

	ScreenToClient( hWnd, &poCurrentCursor );

	stMouseVol.lMVolX = poCurrentCursor.x - poBeforeCursor.x;
	stMouseVol.lMVolY = poCurrentCursor.y - poBeforeCursor.y;
	poBeforeCursor = poCurrentCursor;	

}

//	マウスボタン別状態判定
//	第1引数( ボタンの種類 )、第2引数( ボタンの状態 )
bool MouseStCheck ( int st, int MouseSt )
{
	return	 Mouse[st] == MouseSt ? true : false ;
}

//	使うキー全部のチェック
void CheckAllKey ()
{
	KeyCheck ( DIK_Q,		TURN_L	);
	KeyCheck ( DIK_E,		TURN_R	);
	KeyCheck ( DIK_W,		UP		);
	KeyCheck ( DIK_S,		DOWN	);
	KeyCheck ( DIK_A,		LEFT	);
	KeyCheck ( DIK_D,		RIGHT	);
	
	//	追加日	12/16
	KeyCheck ( DIK_SPACE,	JUMP	);
	KeyCheck ( DIK_R,		RELOAD	);

	// 武器チェンジ
	KeyCheck ( DIK_Z,		WEPON_C	);

	//--------------------------------------------

	KeyCheck ( DIK_G, K_GALLERY		);
	KeyCheck ( DIK_F, K_MAIN_GAME	);
	KeyCheck ( DIK_O, K_OPTION		);
	KeyCheck ( DIK_T, K_TITLE		);

	KeyCheck ( DIK_1, K_AR );
	KeyCheck ( DIK_2, K_MG );
	KeyCheck ( DIK_3, K_GT );
	KeyCheck ( DIK_4, K_BZ );

	MouseCheck ( MOUSE_L );
	MouseCheck ( MOUSE_R );
	MouseCheck ( MOUSE_C );
}

//-------------------------------------------------------------------
//	スクリーン座標内のマウス座標をワールド座標に変換
//	制作日	12/12	
//-------------------------------------------------------------------
void MousePosTransform ()
{
	D3DXMATRIXA16	matView;
	D3DXMATRIXA16	matProj;

	D3DXVECTOR3	vecEyePt	( GetEyePos() );	//カメラ(視点)位置
	D3DXVECTOR3	vecLookatPt	( GetLookPos() );	//注視位置
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);	//上方位置

	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 100.0f);

	CalcScreenToWorld ( &vecCursorPos, poCurrentCursor.x, poCurrentCursor.y, 
						0.5f, WIN_WIDTH, WIN_HEIGHT, &matView, &matProj );

	//char msg[256];
	//ZeroMemory(msg, sizeof(msg));
	//sprintf_s(msg, "vecCursorPos x = %f, y = %f, z = %f\n", vecCursorPos.x, vecCursorPos.y, vecCursorPos.z);
	//OutputDebugStringA(msg);
}