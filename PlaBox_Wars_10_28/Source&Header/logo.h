#pragma once
#include "scene.h"


//	���S�̃N���X
class CL_LOGO:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	���S�̏�����
	void Control ();	//	���S�̏���
	void Render ();	//	���S��3D�`��
	void Draw ();		//	���S��2D�`��
	void Release();
private:
	int Alpha;
};
