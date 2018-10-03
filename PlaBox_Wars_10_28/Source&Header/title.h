#pragma once
#include "scene.h"

#include <stdlib.h> /**/
#include <time.h>   /**/

#define DANKON		15

//	�^�C�g���̃N���X
class CL_TITLE:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	�^�C�g���̏�����
	void Control ();	//	�^�C�g���̏���
	void Render ();		//�@�^�C�g����3D�`��
	void Draw ();		//	�^�C�g����2D�`��
	void Release();
	
private:
	struct Tama
	{
		float x;	// �e�̈ʒu
		float y;	// �e�̈ʒu
		bool  Hit;	// true �̎������\��
		float Scall;// �e�̏c���̏k��
	};



	Tama tama[DANKON];
	int t_cnt;          //�e���J�E���g
	float Rand_X[DANKON], Rand_Y[DANKON];  //�����i�[
	float h;             //�ꐔ�J�E���g


	float tl_x;     // �^�C�g����X���W
	float tl_y;     // �^�C�g����Y���W
	int   Alpha;
	float t_Scall;  // �^�C�g���̏c���̏k��

	float menu_x;
	float menu_y;

	int Run;       // �ړ������̗���

	float t_bX;    // �^�C�g�����W�̊i�[
	float t_bY;    // �^�C�g�����W�̊i�[
	
};
