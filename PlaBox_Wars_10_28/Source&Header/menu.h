#pragma once
#include "scene.h"

//	���j���[�̃N���X
class CL_MENU:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	���j���[�̏�����
	void Control ();	//	���j���[�̏���
	void Render ();		//�@���j���[�̕`��
	void Release();
private:

};