#include "logo.h"
#include "graphic.h"
#include"Audio.h"
// logoCount �C���N�������g++�Ŏg�p�ɕύX
int logoCount;

#define  NONDISP   18
#define  LOGOFI    NONDISP  +24
#define  LOGODISP  LOGOFI   +36
#define  LOGOFO    LOGODISP +24

//	���S�̏�����
void CL_LOGO::Init ()
{
	Alpha = 0;

	LoadTexture ( "Texture\\Image\\logo2.png", TEX_LOGO, 0, 0, 0 );
	SetVertex ( NORMAL, TEX_LOGO, 120, 180, NULL, NULL, NULL, NULL );
	logoCount = 0;
}

//	���S�̏���
void CL_LOGO::Control ()
{
	logoCount++;


	if (logoCount < NONDISP) {
	}
	else if (logoCount  < LOGOFI) {
		Alpha += 11;
		if ( Alpha > 255 ) Alpha = 255;
		//VerTex �́@color ���@0x1000000 �ł��
		//���̒l��11�������B�����A�Q�T�T���傫�����255�ɂ���
		//���ʂ�0x1000000�{���Acolor��0x1000000�Ŋ��������܂�ɉ�����
	}
	else if (logoCount  < LOGODISP) {
	}
	else if (logoCount  < LOGOFO){
		Alpha -= 11;
		if ( Alpha < 0 ) Alpha = 0;
		//VerTex �́@color ���@0x1000000 �ł��
		//���̒l����11�������B�����A�O��菬�������0�ɂ���
		//���ʂ�0x1000000�{���Acolor��0x1000000�Ŋ��������܂�ɉ�����
	}
	else{
		ChangeScene ( S_TITLE );
	}
	
	SetAlpha ( TEX_LOGO, Alpha);

	//if ( !logoCount )	ChangeScene ( S_TITLE );
}

//�@���S��3D�`��
void CL_LOGO::Render ()
{
	
}

//�@���S��2D�`��
void CL_LOGO::Draw ()
{
	TextureDraw ( TEX_LOGO );
}

void CL_LOGO::Release()
{
	ReleaseAllTexture();
	ReleaseAllSoundFile();
}