#pragma once
#include "Lib.h"

#define SAMPLE_BUFFER_SIZE  16

//	�}�E�X���W���i�[����\����
extern	POINT	poCurrentCursor;	//	���݂̃}�E�X���W	

#ifdef	_MOUSE_VOL_

struct	MOUSE_VOL
{
	long	lMVolX, lMVolY, lMVolZ;
};

//	�}�E�X�̈ړ��ʂ��i�[����
extern	MOUSE_VOL	stMouseVol;

//	���[���h���W���̃}�E�X���W
extern	D3DXVECTOR3	vecCursorPos;

#endif

// �L�[�̏�Ԃ̎��
enum KEYSTATE 
{
	PUSH,
	RELEASE,
	ON,
	OFF,
	KEYSTATE_MAX
};

// �g�p����L�[�̎��
// KeyCheck�Ƌ��Ɏg���L�[��������΃R�R�Ɏ�ނ�ǉ����Ă���
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

HRESULT InitDinput(HWND);	//Direct�C���v�b�g�̏�����

HRESULT	InitKey ( HWND hWnd );	//	�L�[�̏�����

HRESULT	InitMouse ( HWND hWnd, bool bForeGroundMode = false  );	//	�}�E�X�̏�����

//	�L�[��ԃ`�F�b�N
//	��1����( �L�[�̒萔 )�A��2����( �L�[�̎�� )
void KeyCheck ( int DIK, int st );

//	�L�[�ʏ�Ԕ���
//	��1����( �L�[�̎�� )�A��2����( �L�[�̏�� )
bool StCheck(int st, int Keyst);

//	�}�E�X��ԃ`�F�b�N
//	����1�F�{�^���̎��
void MouseCheck ( int st );

//	�}�E�X���W�̎擾
//	����1�F�E�C���h�E�n���h��
void CursorSet(HWND hWnd);

//	�}�E�X�{�^���ʏ�Ԕ���
//	��1����( �{�^���̎�� )�A��2����( �{�^���̏�� )
bool MouseStCheck ( int st, int MouseSt );

//	�g���L�[�S���̃`�F�b�N
void CheckAllKey ();

//-------------------------------------------------------------------
//	�X�N���[�����W���̃}�E�X���W�����[���h���W�ɕϊ�
//	�����	12/12	
//-------------------------------------------------------------------
void MousePosTransform ();