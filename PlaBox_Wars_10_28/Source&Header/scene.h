#pragma once
#ifndef	_SCENE_H_
#define	_SCENE_H_


void SceneChangeFlagFalse();
//	�V�[������̃N���X�|�C���^�̍폜
#define	_CL_DELETE(p)	{ if(p) { delete (p); (p) = NULL;} }

#endif
//	�V�[���̎��
enum eSCENE
{
	S_NONE,		//	�V�[���Ȃ�

	//alpha
	S_TITLE,	//	�^�C�g��
	S_GAME,		//	�Q�[��
	S_RESULT,	//	���U���g

	//beta
	S_LOGO,		//	���S
	S_MENU,		//	���j���[
	S_OPTION,	//	�I�v�V����
	S_GALLERY,	//	�M�������[

	//mode
	S_S_MODE,	//�@�V���O���v���C���[�h
	S_M_MODE,	//	�}���`�v���C���[�h
	S_TA_MODE,	//	�^�C���A�^�b�N���[�h
	S_VS_MODE,	//	�ΐ탂�[�h

	//end
	S_END,		//	�Q�[���I��

	S_GAMEOVER,	//�@�Q�[���I�[�o�[

	S_MAX		//	�V�[���̐�
};


//=================	�N���X	=======================

//	�e�V�[�����Ƃ̋��ʂ̌p�����̃N���X
class	CL_MANAGE_SCENE
{
public:
	virtual void Init ()	= 0;		//	������
	virtual void Control ()	= 0;	//	��{����
	virtual void Render ()	= 0;	//	3D�`��
	virtual void Draw ()	= 0;	//	2D�`��
	virtual void Release() = 0;
	//	�V�[���؂�ւ�
	//	�؂�ւ������V�[���������ɓ����
	static void ChangeScene ( int nextScene );
};

#ifdef	_SCENE_CL_
//	�V�[������N���X
class	CL_SCENE:public	CL_MANAGE_SCENE
{
public:
	CL_SCENE();		//	private���̃V�[���̕ϐ��������ŏ�����

	void Init ();		//	������
	void Control ();	//	��{����
	void Render ();		//	3D�`��
	void Draw ();		//	2D�`��
	void Release();
private:

};

#endif

extern CL_MANAGE_SCENE*	pCl_scene;