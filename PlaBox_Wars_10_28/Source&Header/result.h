#pragma once
#include "scene.h"

#define SUZI 5

//	���U���g�̃N���X
class CL_RESULT:public CL_MANAGE_SCENE
{
public:
	void Init ();		//	���U���g�̏�����
	void Control ();	//	���U���g�̏���
	void Render ();		//	���U���g��3D�`��
	void Draw ();		//	���U���g��2D�`��
	void Release();
private:
	int Alpha;
	int TIME_Alpha;
	int SCORE_Alpha;
	int RANK_Alpha;
	int OSSAN_Alpha;

	bool timeflag;
	bool resultflag;
	int times; //�^�C���i�[�p�ϐ�
	int scores; //�X�R�A�i�[�p�ϐ�

	int tmp;
	int get;

	int dat[5];

	int resultCount;
	void settimes( float x, float y );
	

	struct TAIMU
	{
		float x;	
		float y;	
		float Scall;
	};
	TAIMU time[SUZI];

	struct SCORE
	{
		float x;	
		float y;	
		float Scall;
	};
	SCORE score[SUZI];

};