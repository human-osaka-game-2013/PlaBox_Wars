#include "Lib.h"
#include "title.h"
#include "graphic.h"
#include "input.h"
#include "logo.h"
#include "Audio.h"

#define TIT_FI	      (102		+ 24)   //�^�C�g���t�F�[�h�C��

//	�ύX��	2/14	�T�c			��120��30��
#define TIT_DS        (TIT_FI     + 60)  //�^�C�g���\��
#define TIT_SH        (TIT_DS     + 60)   //���G�t�F�N�g
#define TIT_DS_BS     (TIT_SH     + 60)   //���G�t�F�N�g�\��
#define TIT_SM        (TIT_DS_BS  + 50)   //�k��
#define TIT_RISE      (TIT_SM     + 50)   //�㏸

#define TIT_DOUBLE		(TIT_RISE		+ 180)	//2�摜�ň�U�Î~

#define TIT_RUN       (TIT_DOUBLE   + 75)   //����
#define TIT_NON       (TIT_RUN    + 30)   //�^�C�g���Ȃ�
#define RETIT         (TIT_NON    + 180)   //�ēx�o�Ă���
#define RETIT_SH      (RETIT      + 60)   //�܂��������

#define TIT_FURA      (RETIT_SH   + 140)  //�t���t�������Ă���

//	�ǉ���	2/14	�T�c
#define	LOOP_TITLE_MOVE	( TIT_FURA + 120 )	//�^�C�g���̓���̌J��Ԃ��̃^�C�~���O
#define TIT_END       72 * 60  //�^�C�g���G���h (OP�̉��y���������܂�) 

#define TASP          5                  //���̋󂭊Ԋu

#define DEF_X         300.0f            //X�̏����l(�^�C�g���C�e��)
#define DEF_Y         100.0f            //Y�̏����l(�^�C�g���C�e��)

#define MENU_X        482.0f            //X�̏����l(���j���[)
#define MENU_Y        900.0f            //Y�̏����l(���j���[)


#define RISE_X        3.2f              //X�̈ړ��l(�㏸)
#define RISE_Y        1.0f              //Y�̈ړ��l(�㏸)

#define R_X           20.0f             //������X�s�[�h


#define RE_X_R        -460.0f           //X�̏����l(�^�C�g���Ȃ��C�E)
#define RE_X_L        1380.0f           //X�̏����l(�^�C�g���Ȃ��C��)
#define RE_Y          650.0f            //Y�̏����l(�^�C�g���Ȃ�)

#define RERISE_X      10.0f              //X�̖߂��Ă����X�s�[�h
#define RERISE_Y      6.5f              //Y�̖߂��Ă����X�s�[�h

//	�ǉ���	2/14	�T�c	
#define POINT_OF_BUTTON_X		WIN_WIDTH / 3
#define POINT_OF_BUTTON_Y		WIN_HEIGHT / 2

#define	GAP_OF_BUTTON	30

extern bool BreakFlag;		//���S��ʂŁA�r���ŃN���b�N���ꂽ

				//	���g�������C�����܂����B
int titleCount;	//	�u���̃J�E���^���g���ă��S�֖߂�B�v���u�^�C�g���̓����̐���J�E���g�v

//	�ǉ����@2/14	�T�c
int	iEndCount;	//	�^�C�g���I���p�̃J�E���g

#define TARGET_SCALE 0.25f	///<	�^�[�Q�b�g�̃J�[�\���T�C�Y

//	�^�C�g���̏�����
//	�\�������������̂�ǂݍ��񂾂�A�������W�����߂Ă������J�E���^��������Ԃɂ���B
void CL_TITLE::Init ()
{
	int	iTempX = 0, iTempY = 0;	//�摜�T�C�Y���ۑ� 

	LoadTexture ( "Texture\\Image\\menu.png", TEX_MENU, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_MENU, MENU_X, MENU_Y, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\Image\\title.png", TEX_TITLE, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_TITLE, DEF_X, DEF_Y, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\Image\\dankon.png", TEX_DANKON, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_DANKON, DEF_X, DEF_Y, NULL, NULL, NULL, NULL );
	//���������t�@�C���摜�@�k��
	LoadTexture ( "Texture\\Image\\number.png", TEX_NUM_SET, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_NUM_SET, -1000, -1000, NULL, NULL, NULL, NULL );

	//	�e�V�[���ւ̃{�^��
	LoadTexture ( "Texture\\Image\\start_B.png", TEX_GAME_START, 0, 255, 0 );

	//iTempX = GetTexWidth ( TEX_GAME_START );
	iTempY = GetTexHeight ( TEX_GAME_START ) + GAP_OF_BUTTON;	//�@�摜�T�C�Y�̎擾�ƃ{�^����Y���W�̊Ԋu������
	
	SetVertex ( NORMAL, TEX_GAME_START, POINT_OF_BUTTON_X, POINT_OF_BUTTON_Y, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\Image\\credit_B.png", TEX_CREDIT, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_CREDIT, POINT_OF_BUTTON_X , POINT_OF_BUTTON_Y + iTempY, NULL, NULL, NULL, NULL );

	iTempY = GetTexHeight ( TEX_CREDIT ) * 2 + GAP_OF_BUTTON * 2;	

	LoadTexture ( "Texture\\Image\\end_B.png", TEX_GAME_END, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_GAME_END, POINT_OF_BUTTON_X, POINT_OF_BUTTON_Y + iTempY, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\Image\\makar.png", TEX_TARGET , 0, 0, 0 );
	SetVertex ( NORMAL, TEX_TARGET, 0, 0, NULL, NULL, NULL, NULL );	/**	@details	�ǉ���2015/07/01	�}�E�X������t�H�A�O���E���h�ɂ������߁A
																	�J�[�\���̕\���ݒ���ς���K�v�����������߁A�^�[�Q�b�g�J�[�\���̃e�N�X�`�����^�C�g���ł��ǂݍ���*/
	float tsx = GetTexWidth( TEX_TARGET ) * TARGET_SCALE;
	float tsy = GetTexHeight( TEX_TARGET ) * TARGET_SCALE;
	SetTexSize( TEX_TARGET , tsx , tsy );	
		
	
	

	LoadSoundFile("Sound\\SE\\HundGun.wav", SE_HNG);
	LoadSoundFile("Sound\\BGM\\pl_OP.wav", BGM_01);

	SoundPlay( BGM_01, true);

	for ( int i = 0; i < DANKON; i++ ){
		tama[i].x = DEF_X;
		tama[i].y = DEF_Y;
		
		Rand_X[i] = (float)(rand()%500);
		Rand_Y[i] = (float)(rand()%360);

		tama[i].x += Rand_X[i];
		tama[i].y += Rand_Y[i];
		tama[i].Hit = false;
		tama[i].Scall = 1.0f;		
	}

	t_cnt = 0;

	h = 1;

	tl_x = DEF_X;
	tl_y = DEF_Y;
	Alpha = 0;
	t_Scall = 0.8f;


	menu_x = MENU_X;
	menu_y = MENU_Y;

	Run = rand() % 2;

	titleCount = 0;

	iEndCount = 0;
}


//	�^�C�g���̏���
//	�����ŕ\�����Ă���̂̓����Ƃ���t�������Ă����B
void CL_TITLE::Control ()
{
	SetVertex ( CENTER, TEX_TARGET, poCurrentCursor.x, poCurrentCursor.y, NULL, NULL, NULL, NULL );///<	�^�[�Q�b�g�J�[�\�����W�̍X�V

//\\\\\\�^�C�g���t�F�[�h�C��\\\\\\\\\\\\\
	
	if ( titleCount <= TIT_FI){
		SetAlpha ( TEX_TITLE, Alpha);
		Alpha += 11;
		if ( Alpha > 255 ) Alpha = 255;
	}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//**////�^�C�g���\����\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_DS   ){
	}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//**////���G�t�F�N�g\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_SH   ){

		if ( titleCount == TIT_DS + TASP ){
			tama[0].Hit = true;
			SoundPlay( SE_HNG, false);
		}
		else if ( titleCount == TIT_DS + TASP * 2 ){
			tama[1].Hit = true;
			SoundPlay( SE_HNG, false);
		}
		else if ( titleCount == TIT_DS + TASP * 3 ){
			tama[2].Hit = true;
			SoundPlay( SE_HNG, false);
		}
		else if ( titleCount == TIT_DS + TASP * 4 ){
			tama[3].Hit = true;
			SoundPlay( SE_HNG, false);
		}
		else if ( titleCount == TIT_DS + TASP * 5 ){
			tama[4].Hit = true;
			SoundPlay( SE_HNG, false);
		}

	}

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//**////�^�C�g���\����(����)\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_DS_BS){
	}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//\\\\\\\\\\�^�C�g���k��\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_SM   ){
			for ( int i = 0; i < 8; i++ ){
				tama[i].Scall -= 0.01f;
				tama[i].x = DEF_X + (Rand_X[i] / h);
				tama[i].y = DEF_Y + (Rand_Y[i] / h);
			}
			if ( h <= 2 ){
				h += 0.02f;
			}
			t_Scall -= 0.008f;
	}

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//\\\\\\\\\\�^�C�g���㏸\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_RISE ){
		tl_x += RISE_X;
		tl_y -= RISE_Y;

		for ( int i = 0; i < DANKON; i++ )
		{
			tama[i].x += RISE_X;
			tama[i].y -= RISE_Y;
		}

		menu_y -= 8.0f; //���j���[

		t_bX = tl_x;    // �^�C�g�����W�̊i�[
		t_bY = tl_y;    // �^�C�g�����W�̊i�[
		
	}

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount == TIT_DOUBLE){
		//SoundPlay( BGM_01, true);
	}



//\\\\\\\\\\\\�^�C�g������\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_RUN  ){
		//30�J�E���g�����X�g�b�v
		if ( titleCount < TIT_RISE+30 ){
		}


		else{

			//�E�Ɉړ�
			if ( Run == 0 ){
				tl_x += R_X;
				for ( int i = 0; i < DANKON; i++ )
				{
					tama[i].x += R_X;

			    }
			}

			//���Ɉړ�
			else{
				tl_x -= R_X;
				for ( int i = 0; i < DANKON; i++ )
				{
					tama[i].x -= R_X;
				}
			}
		}
	}


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//\\\\\\\\\\�^�C�g���Ȃ�\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_NON  ){
	//�^�C�g���ƒe���̍��W���ēx������

		//�������̂��E�̏ꍇ
		if ( Run == 0 ){
			tl_x = RE_X_R;
			tl_y = RE_Y;
			for ( int i = 0; i < DANKON; i++ )
			{
				tama[i].x = RE_X_R + (Rand_X[i] / h);
				tama[i].y = RE_Y + (Rand_Y[i] / h);
			}
		}

		//�������̂����̏ꍇ
		else{
			tl_x = RE_X_L;
			tl_y = RE_Y;
			for ( int i = 0; i < DANKON; i++ )
			{
				tama[i].x = RE_X_L + (Rand_X[i] / h);
				tama[i].y = RE_Y + (Rand_Y[i] / h);
			}
		}
		
	}

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//\\\\\\\\�^�C�g���o��\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < RETIT   ) {
		if ( Run == 0 ){
			if ( TIT_NON + 30 < titleCount && titleCount < TIT_NON + 60 ){
			}
			else if ( TIT_NON + 60 < titleCount && titleCount < TIT_NON + 90 ){
				tl_x -= RERISE_X;
				tl_y += RERISE_Y;
				for ( int i = 0; i < DANKON; i++ )
				{
					tama[i].x -= RERISE_X;
					tama[i].y += RERISE_Y;
				}
			}
			else{
				tl_x += RERISE_X;
				tl_y -= RERISE_Y;

				for ( int i = 0; i < DANKON; i++ )
				{
					tama[i].x += RERISE_X;
					tama[i].y -= RERISE_Y;
				}
			}
		}
		else{
			if ( TIT_NON + 30 < titleCount && titleCount < TIT_NON + 60 ){
			}
			else if ( TIT_NON + 60 < titleCount && titleCount < TIT_NON + 90 ){
				tl_x += RERISE_X;
				tl_y += RERISE_Y;
				for ( int i = 0; i < DANKON; i++ )
				{
					tama[i].x += RERISE_X;
					tama[i].y += RERISE_Y;
				}
			}
			else{
				tl_x -= RERISE_X;
				tl_y -= RERISE_Y;

				for ( int i = 0; i < DANKON; i++ )
				{
					tama[i].x -= RERISE_X;
					tama[i].y -= RERISE_Y;
				}
			}
		}

		
	}

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//\\\\\\\\\\\\\\\\������x�������\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < RETIT_SH) { 
		if ( titleCount > RETIT + TASP * 10 && t_cnt < 2 ){
			tama[5+t_cnt].Hit = true;
			Run = rand() % 2;
			t_cnt++;
			titleCount = TIT_RISE;

			SoundPlay( SE_HNG, false);
		}

		tama[ DANKON - 1 ].Hit = true;

	}


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//\\\\\\\\\\\\\\\�t���t�������Ă���\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_FURA) {
		

		if ( rand() % 2 == 0 ){
			tl_x += 5.0f;
			for ( int i = 0; i < DANKON; i++ )
			{
				tama[i].x += 5.0f;
			}
		}
		else{
			tl_x -= 5.0f;
			for ( int i = 0; i < DANKON; i++ )
			{
				tama[i].x -= 5.0f;
			}
		}

		tl_y += 5.0f;
		for ( int i = 0; i < DANKON; i++ )
			{
				tama[i].y += 5.0f;
			}
	}

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//	�ǉ���	2/14	�T�c
//	�^�C�g���̃��[�V�����̌J��Ԃ�
	if ( titleCount >= LOOP_TITLE_MOVE ) { titleCount = TIT_RISE; }

//	���S�ɖ߂�
	if ( iEndCount >= TIT_END ) { ChangeScene ( S_LOGO ); }

	//	�e���[�h�ւ̉�����
	if ( titleCount >= TIT_RISE )
	{
		if ( HitOfTexture ( poCurrentCursor.x, poCurrentCursor.y, TEX_CREDIT ))
		{
			ChangeColorKey ( ON_OF_BUTTON, TEX_CREDIT );
			if ( MouseStCheck ( MOUSE_L, PUSH) )
			{
				ChangeScene ( S_GALLERY );	//	���݂̓N���W�b�g
			}
		}
		else
		{
			ChangeColorKey ( OUT_OF_BUTTON, TEX_CREDIT );
		}

		if ( HitOfTexture ( poCurrentCursor.x, poCurrentCursor.y, TEX_GAME_END ) )
		{
			ChangeColorKey ( ON_OF_BUTTON, TEX_GAME_END );
			if ( MouseStCheck ( MOUSE_L, PUSH) )
			{
				PostQuitMessage (0);
			}
		}
		else
		{
			ChangeColorKey ( OUT_OF_BUTTON, TEX_GAME_END );
		}

		if ( HitOfTexture ( poCurrentCursor.x, poCurrentCursor.y, TEX_GAME_START ) )
		{
			ChangeColorKey ( ON_OF_BUTTON, TEX_GAME_START );
			if ( MouseStCheck ( MOUSE_L, PUSH) )
			{
				ChangeScene ( S_GAME );
			}
		}
		else
		{
			ChangeColorKey ( OUT_OF_BUTTON, TEX_GAME_START );
		}
	}
	titleCount++;
	iEndCount++;
}

//�@�^�C�g����3D�`��
void CL_TITLE::Render ()
{

}

//�@�^�C�g����2D�`��
void CL_TITLE::Draw ()
{

	//SetVertex ( NORMAL, TEX_MENU, MENU_X, menu_y, NULL, NULL, NULL, NULL );
	//TextureDraw( TEX_MENU );
	
	SetVertex ( NORMAL, TEX_TITLE, tl_x, tl_y, NULL, NULL, NULL, NULL );
	TextureScallDraw( TEX_TITLE, t_Scall );

	for ( int i = 0 ; i < 8 ; i++ )
	{
		if ( tama[i].Hit == true )
		{
			SetVertex ( NORMAL, TEX_DANKON, tama[i].x, tama[i].y, NULL, NULL, NULL, NULL );
			TextureScallDraw( TEX_DANKON, tama[i].Scall );
		}
	}
	if ( titleCount >= TIT_RISE )
	{
		TextureDraw( TEX_GAME_START );
		TextureDraw( TEX_CREDIT		);
		TextureDraw( TEX_GAME_END	);
	}
	TextureDraw ( TEX_TARGET );	
}

void CL_TITLE::Release()
{
	ReleaseAllTexture();
	ReleaseAllSoundFile();
}