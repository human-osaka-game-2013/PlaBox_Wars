#define	_SCENE_CL_
#define _CHARA_CL_

#include "scene.h"
#include "input.h"
#include "graphic.h"
#include "logo.h"
#include "title.h"
#include "game.h"
#include "menu.h"
#include "option.h"
#include "gallery.h"
#include "gameover.h"
#include "Audio.h"

CL_MANAGE_SCENE*	pCl_scene = NULL;
static bool	initSceneFlag;
static int currentScene;

bool SceneChangeFlag = false;

// �V�[��������
void CL_SCENE::Init ()
{
	
	if ( !initSceneFlag )
	{
		SoundAllStop();
		ReleaseAllSoundFile();
		initSceneFlag = true;
		switch ( currentScene )
		{
		case S_LOGO:
			_CL_DELETE(pCl_scene)
			pCl_scene = new CL_LOGO();
			pCl_scene -> Init();

			break;

		case S_TITLE:
			_CL_DELETE(pCl_scene)
			pCl_scene = new CL_TITLE();
			pCl_scene -> Init();

			break;
		
		case S_GAME:
			_CL_DELETE(pCl_scene)
			pCl_scene = new CL_GAME();
			pCl_scene -> Init();

			break;

		case S_OPTION:
			_CL_DELETE(pCl_scene)
			pCl_scene = new CL_OPTION();
			pCl_scene -> Init();

			break;
		case S_GALLERY:
			_CL_DELETE(pCl_scene)
			pCl_scene = new CL_GALLERY();
			pCl_scene -> Init();

			break;
		case S_RESULT:
			_CL_DELETE(pCl_scene)

			break;
		case S_END:
			_CL_DELETE(pCl_scene)	

			break;

		case S_GAMEOVER:
			_CL_DELETE(pCl_scene)
			pCl_scene = new CL_GAMEOVER();
			pCl_scene -> Init();

			break;
		}
	}
}

// �V�[���ʏ���
void CL_SCENE::Control ()
{
	if( !SceneChangeFlag ){
		CheckAllKey ();
		MousePosTransform ();
		pCl_scene -> Control();
	}
}

// �V�[����3D�`��
void CL_SCENE::Render ()
{
	if( !SceneChangeFlag )
		pCl_scene -> Render();
}

// �V�[����2D�`��
void CL_SCENE::Draw ()
{
	if( !SceneChangeFlag )
		pCl_scene -> Draw();
}

//	�V�[���R���X�g���N�^
CL_SCENE::CL_SCENE()
{
	SceneChangeFlag = false;
	initSceneFlag	 = false;	

	currentScene = S_LOGO;
}

//	�V�[���N���X���
void CL_SCENE::Release()
{
	ReleaseAllTexture();
	ReleaseAllSoundFile();
}

//	�V�[���ύX
void CL_MANAGE_SCENE::ChangeScene ( int nextScene )
{
	SceneChangeFlag = true;
	initSceneFlag = false;
	currentScene = nextScene;
	pCl_scene->Release();
}

//	�V�[���ύX�t���O�擾
void SceneChangeFlagFalse()
{
	SceneChangeFlag = false;
}

