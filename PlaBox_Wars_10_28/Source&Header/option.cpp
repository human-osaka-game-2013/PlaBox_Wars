#include "graphic.h"
#include "input.h"
#include "option.h"
#include"Audio.h"
//	�I�v�V�����̏�����
void CL_OPTION::Init ()
{
	LoadTexture ( "Texture\\Image\\option.png", TEX_OPTION, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_OPTION, 0, 0, NULL, NULL, NULL, NULL );
}

//	�I�v�V�����̏���
void CL_OPTION::Control ()
{
	if ( StCheck ( K_TITLE, PUSH ) )	
	{
		MessageBox(0,"�^�C�g���ɖ߂�܂��B","",MB_OK);
		ChangeScene ( S_TITLE );
	}
}

//�@�I�v�V������3D�`��
void CL_OPTION::Render ()
{
	
}

//�@�I�v�V������2D�`��
void CL_OPTION::Draw ()
{
	TextureDraw ( TEX_OPTION );
}

void CL_OPTION::Release()
{
	ReleaseAllTexture();
	ReleaseAllSoundFile();
}