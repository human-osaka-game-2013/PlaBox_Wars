#pragma once

#define DIRECTINPUT_VERSION 0x0800

//�v���v���֘A�w�b�_�[�t�@�C��
#include <Windows.h>	//window��b�t�@�C��
#include <dinput.h>		//�L�[����
#include <MMSystem.h>	//wav�Đ�
#include <XAudio2.h>	//mp3,wma�Đ�

//���C�u�����Ǎ�
#pragma comment	(lib, "d3dx9d.lib")
#pragma comment	(lib, "d3dxof.lib")
#pragma comment	(lib, "dinput8.lib")	
#pragma comment	(lib, "dsound.lib")	//wav�Đ�
#pragma comment	(lib, "dxguid.lib")
#pragma comment	(lib, "winmm.lib")

#define SAFE_RELEASE(p) { if(p) { (p) -> Release(); (p) = NULL; } }
#define NULL_DELETE(p) { if(p) { delete (p); (p) = NULL; } }
#define NULL_ARRAY_DELETE(p) { if(p) { delete[] (p); (p) = NULL; } }