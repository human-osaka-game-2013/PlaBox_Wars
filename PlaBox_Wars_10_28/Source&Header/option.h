#pragma once
#include "scene.h"

//	�I�v�V�����̃N���X
class CL_OPTION:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	�I�v�V�����̏�����
	void Control ();	//	�I�v�V�����̏���
	void Render ();		//�@�I�v�V������3D�`��
	void Draw ();		//	�I�v�V������2D�`��
	void Release();
private:

};