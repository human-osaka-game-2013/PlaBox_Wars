#pragma once
#include "scene.h"

//	�M�������[�̃N���X
class CL_GALLERY:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	�M�������[�̏�����
	void Control ();	//	�M�������[�̏���
	void Render ();		//�@�M�������[��3D�`��
	void Draw ();		//	�M�������[��2D�`��
	void Release();
private:

};