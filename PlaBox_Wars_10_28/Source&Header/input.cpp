#define _MOUSE_VOL_


#define _THING_CLASS_

#include <stdio.h>
#include <Windows.h>
#include "graphic.h"
#include "input.h"
#include "camera.h"

LPDIRECTINPUT8			pDinput			= NULL; //�C���v�b�g -> ���͏���
LPDIRECTINPUTDEVICE8	pKeyDevice		= NULL; //�L�[�f�o�C�X -> �O���L�[����
LPDIRECTINPUTDEVICE8	pMouseDevice	= NULL; //�}�E�X�f�o�C�X -> �O���}�E�X����

// �L�[�̏�Ԃ���ޕʂɊi�[����ϐ�
int		Key[KEYMAX];
// �L�[�̎�ޕʂɉ�����Ă��邩�̃t���O
bool	PreKey[KEYMAX] = {false};

//	�}�E�X�̏�Ԃ���ޕʂɊi�[����ϐ�
int		Mouse[MOUSEMAX];
//	�}�E�X�̎�ޕʂɉ�����Ă��邩�̃t���O
bool	PreMouse[MOUSEMAX] = {false};

//	�}�E�X�̈ړ���
MOUSE_VOL	stMouseVol;

//	�}�E�X���W���i�[����\����
POINT	poCurrentCursor;	//	���݂̃}�E�X���W	
POINT	poBeforeCursor;		//	�O�̃}�E�X���W

//	���[���h���W���̃}�E�X���W
D3DXVECTOR3	vecCursorPos;

//==================================================================
//
//	�_�C���N�g�C���v�b�g�̏�����
//
//=================================================================
//�_�C���N�g�C���v�b�g�̏������֐�
HRESULT InitDinput(HWND hWnd )
{
	HRESULT hr;
	
	//�DirectInput��I�u�W�F�N�g�̍쐬
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
//	�L�[�̐ݒ�
//	
//-----------------------------------------------------------------
HRESULT	InitKey ( HWND hWnd )
{
	HRESULT hr;

	//�DirectInput�f�o�C�X��I�u�W�F�N�g�̍쐬(�L�[�{�[�h)
	if(FAILED (hr = pDinput->CreateDevice (
	GUID_SysKeyboard,
	&pKeyDevice,
	NULL

	) ) )
	{
		return hr;
	}
	//�f�o�C�X���L�[�{�[�h�ɐݒ�
	if(FAILED (hr = pKeyDevice->SetDataFormat (&c_dfDIKeyboard) ) )
	{
		return hr;
	}
	//�������x���̐ݒ�		*���Y�A�v���P�[�V����(�Q�[��)�ƁAwindowsOS���̂̃L�[�{�[�h�f�o�C�X�̐�L���ݒ�
	if(FAILED (hr = pKeyDevice->SetCooperativeLevel(
		hWnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND		// * ��r���Ńo�b�N�E�O���E���h
		) ) )
	{
		return hr;
	}
	//�f�o�C�X��擾�����
	pKeyDevice->Acquire();							// * �쐬�����f�o�C�X�ւ̃A�N�Z�X���擾
	return S_OK;
}

//------------------------------------------------------------------
//
//	�}�E�X�̐ݒ�
//	
//-----------------------------------------------------------------
HRESULT	InitMouse ( HWND hWnd, bool bForeGroundMode )
{
	HRESULT hr;
	LPDIENUMDEVICESCALLBACK lpCallback	= NULL;
	LPVOID	pvRef	= NULL;		
	HGLOBAL	hGlobal	= NULL;	//	�O���[�o���n���h��	
	
	//�DirectInput�f�o�C�X��I�u�W�F�N�g�̍쐬(�}�E�X)
	if(FAILED (hr = pDinput->CreateDevice (
		GUID_SysMouseEm,
		&pMouseDevice,
		NULL
		) ) )
	{
		return hr;
	}

	//�f�o�C�X���}�E�X�ɐݒ�
	if(FAILED (hr = pMouseDevice->SetDataFormat (&c_dfDIMouse) ) )
	{
		return hr;
	}

	if ( bForeGroundMode )	// �t�H�A�O���E���h�Ń}�E�X���g���Ȃ�
	{
		//	�}�E�X�̓���̐ݒ�
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
		//	�}�E�X�̓���̐ݒ�
		if(FAILED (hr = pMouseDevice->SetCooperativeLevel(
			hWnd,
			DISCL_EXCLUSIVE | DISCL_BACKGROUND
			)))
		{
			return hr;
		}
	}

	//	�C�x���g�ʒm���g���ă}�E�X�̓�������o������@�ƁA
	//	�}�E�X����̃o�b�t�@�����O���͂�ǂݎ��
	hGlobal = CreateEvent(NULL, FALSE, FALSE, NULL);

	if( hGlobal == NULL )
	{
		return FALSE;
	}
	//	�f�o�C�X��Ԃ��ω������Ƃ��ɐݒ肳���C�x���g���w�肷��
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

	//	�f�o�C�X�̓�����`����v���p�e�B��ݒ肷��
	if (FAILED ( hr = pMouseDevice->SetProperty(
		DIPROP_BUFFERSIZE,
		&dipdw.diph
		)))
	{
		return hr;
	}

	//�f�o�C�X��擾�����
	pMouseDevice->Acquire();	// * �쐬�����f�o�C�X�ւ̃A�N�Z�X���擾
	return S_OK;
}

//==================================================================
//
//	�L�[��ԃ`�F�b�N
//
//=================================================================
//	��1����( �L�[�̒萔 )�A��2����( �L�[�̎�� )
void KeyCheck ( int DIK, int st )
{
	HRESULT hr = pKeyDevice->Acquire();		//�f�o�C�X�ւ̃A�N�Z�X���̍Ď擾
	
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

//	�L�[�ʏ�Ԕ���
//	��1����( �L�[�̎�� )�A��2����( �L�[�̏�� )
bool StCheck(int st, int Keyst) 
{
	return ( Key[st] == Keyst );
}

//==================================================================
//
//	�}�E�X��ԃ`�F�b�N
//
//=================================================================
//	�}�E�X��ԃ`�F�b�N
//	����1�F�{�^���̎��
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

//	�}�E�X���W�̎擾�ƈړ��ʂ����߂�B
//	����1�F�E�C���h�E�n���h��
void CursorSet(HWND hWnd)
{
	GetCursorPos( &poCurrentCursor );

	ScreenToClient( hWnd, &poCurrentCursor );

	stMouseVol.lMVolX = poCurrentCursor.x - poBeforeCursor.x;
	stMouseVol.lMVolY = poCurrentCursor.y - poBeforeCursor.y;
	poBeforeCursor = poCurrentCursor;	

}

//	�}�E�X�{�^���ʏ�Ԕ���
//	��1����( �{�^���̎�� )�A��2����( �{�^���̏�� )
bool MouseStCheck ( int st, int MouseSt )
{
	return	 Mouse[st] == MouseSt ? true : false ;
}

//	�g���L�[�S���̃`�F�b�N
void CheckAllKey ()
{
	KeyCheck ( DIK_Q,		TURN_L	);
	KeyCheck ( DIK_E,		TURN_R	);
	KeyCheck ( DIK_W,		UP		);
	KeyCheck ( DIK_S,		DOWN	);
	KeyCheck ( DIK_A,		LEFT	);
	KeyCheck ( DIK_D,		RIGHT	);
	
	//	�ǉ���	12/16
	KeyCheck ( DIK_SPACE,	JUMP	);
	KeyCheck ( DIK_R,		RELOAD	);

	// ����`�F���W
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
//	�X�N���[�����W���̃}�E�X���W�����[���h���W�ɕϊ�
//	�����	12/12	
//-------------------------------------------------------------------
void MousePosTransform ()
{
	D3DXMATRIXA16	matView;
	D3DXMATRIXA16	matProj;

	D3DXVECTOR3	vecEyePt	( GetEyePos() );	//�J����(���_)�ʒu
	D3DXVECTOR3	vecLookatPt	( GetLookPos() );	//�����ʒu
	D3DXVECTOR3	vecUpVec	(0.0f, 1.0f, 0.0f);	//����ʒu

	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.6f, 0.9f, 100.0f);

	CalcScreenToWorld ( &vecCursorPos, poCurrentCursor.x, poCurrentCursor.y, 
						0.5f, WIN_WIDTH, WIN_HEIGHT, &matView, &matProj );

	//char msg[256];
	//ZeroMemory(msg, sizeof(msg));
	//sprintf_s(msg, "vecCursorPos x = %f, y = %f, z = %f\n", vecCursorPos.x, vecCursorPos.y, vecCursorPos.z);
	//OutputDebugStringA(msg);
}