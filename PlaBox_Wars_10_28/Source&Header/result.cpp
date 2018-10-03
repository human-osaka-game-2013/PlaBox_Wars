#include "game.h"
#include "result.h"
#include "graphic.h"
#include "input.h"
#include "Audio.h"



#define	RESULT_X	0.0f	//X�̏����ʒu(���U���g�w�i)
#define	RESULT_Y	0.0f	//Y�̏����ʒu(���U���g�w�i)

#define	RESULT_TIME_X	11.0f	//X�̏����ʒu(�^�C��)
#define	RESULT_TIME_Y	43.0f	//Y�̏����ʒu(�^�C��)

#define	RESULT_SCORE_X	11.0f	//X�̏����ʒu(�X�R�A)
#define	RESULT_SCORE_Y	381.0f	//Y�̏����ʒu(�X�R�A)

#define	RESULT_RANK_X	558.0f	//X�̏����ʒu(�����N)
#define	RESULT_RANK_Y	43.0f	//Y�̏����ʒu(�����N)

#define	RESULT_OSSAN_X	919.0f	//X�̏����ʒu(��������)
#define	RESULT_OSSAN_Y	43.0f	//Y�̏����ʒu(��������)

#define	RESULT_SERIFU_X	919.0f	//X�̏����ʒu(��������̃Z���t)
#define	RESULT_SERIFU_Y	525.0f	//Y�̏����ʒu(��������̃Z���t)

#define RESULT_FI	60											//���U���g��ʃt�F�[�h�C���J�n
#define RESULT_TIME_FI			( RESULT_FI			+ 30 )		//�^�C���t�F�[�h�C���J�n
#define RESULT_SCORE_FI			( RESULT_TIME_FI	+ 30 )		//�X�R�A�t�F�[�h�C���J�n
#define RESULT_RANK_FI			( RESULT_SCORE_FI	+ 30 )		//�����N�t�F�[�h�C���J�n
#define RESULT_OSSAN_FI			( RESULT_RANK_FI	+ 30 )		//��������ƃZ���t�t�F�[�h�C���J�n
#define RESULT_TIMES_NUMBER_FI  ( RESULT_OSSAN_FI	+ 30 )		//�^�C���̐����t�F�[�h�C���J�n
#define RESULT_RANK_PUTERN_FI   ( RESULT_TIMES_NUMBER_FI	+ 30 )		//�^�C���̐����t�F�[�h�C���J�n

#define RANK_S_X 480.0f//�M�͏����ʒu
#define RANK_S_Y 100.0f//�M�͏����ʒu

#define S_RANK_TIME r_timer<3600
#define A_RANK_TIME r_timer>=3600&&r_timer<4800
#define B_RANK_TIME r_timer>=4800&&r_timer<6000
#define C_RANK_TIME r_timer>=6000

#define TIMES_ONE_X		250.0f						//�^�C���̐��������ʒu(���̈�)
#define TIMES_TWO_X		(TIMES_ONE_X	+ 50.0f)	//�^�C���̐��������ʒu(��̈�)
#define TIMES_THREE_X	(TIMES_TWO_X	+ 50.0f)	//�^�C���̐��������ʒu(�S�̈�)
#define TIMES_FOUR_X	(TIMES_THREE_X	+ 50.0f)	//�^�C���̐��������ʒu(�\�̈�)
#define TIMES_FIVE_X	(TIMES_FOUR_X	+ 50.0f)	//�^�C���̐��������ʒu(��̈�)
#define TIMES_Y			150.0f //�^�C���̐��������ʒuY
#define SCORES_Y		480.0f //�^�C���̐��������ʒuY

//( �t���[���� �| ���Đ� )���X�R�A
#define RANK_S 8000 //�����_�ȏ�Ń����NS
#define RANK_A 7000 //�����_�ȏ�Ń����NA
#define RANK_B 6000 //�����_�ȏ�Ń����NB
#define RANK_C	  0 //�����_�ȏ�Ń����NC

#define TIMEPOS_Y 340.f
#define TIMEPOS1_X 410.f
#define TIMEPOS2_X 330.f
#define TIMEPOS3_X 190.f
#define TIMEPOS4_X 110.f
#define TIMEX_SIZE 80.f
#define TIMEY_SIZE 80.f

int r_timer;
int _time[4];
int time_m;
int time_s;
void CL_RESULT::settimes( float x, float y )    
{
	for ( int i = 0 ; i < SUZI ; i++ )
	{
		//SetVertex ( NORMAL, (eTEXTURE)((int)TEX_R_ONE + (dat[i]-1)), x+50.f*i, y, NULL, NULL, NULL, NULL );
	}
	
}


//	���U���g�̏�����
void CL_RESULT::Init ()
{
	//����
	Alpha		= 0;
	TIME_Alpha	= 0;
	SCORE_Alpha = 0;
	RANK_Alpha	= 0;
	OSSAN_Alpha = 0;

	//�摜�t�@�C���ǂݍ���
	//��ʊO�ɃZ�b�g
	//����ɓ��߃[��
	//���U���g�w�i
	LoadTexture ( "Texture\\Image\\resulttemp.png", TEX_R_BUCK, 0, 255, 255 );
	LoadTexture ( "Texture\\Image\\bazu-ka.png", TEX_R_BAZU, 0, 255, 255 );
	LoadTexture ( "Texture\\Image\\sabumasingan.png", TEX_R_SMG, 0, 255, 255 );
	LoadTexture ( "Texture\\Image\\gatoringu.png", TEX_R_GATO, 0, 255, 255 );
	LoadTexture ( "Texture\\Image\\srank.png", TEX_SRANK, 0, 255, 255 );
	LoadTexture ( "Texture\\Image\\arank.png", TEX_ARANK, 0, 255, 255 );
	LoadTexture ( "Texture\\Image\\brank.png", TEX_BRANK, 0, 255, 255 );
	LoadTexture ( "Texture\\Image\\crank.png", TEX_CRANK, 0, 255, 255 );
	LoadTexture ( "Texture\\Image\\result-back.png", TEX_RESULT, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_RESULT, -2000, -2000, NULL, NULL, NULL, NULL );
	SetAlpha ( TEX_RESULT,   Alpha);

	//�^�C��
	LoadTexture ( "Texture\\Image\\time.png", TEX_R_TIME, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_R_TIME, -1000, -1000, NULL, NULL, NULL, NULL );
	SetAlpha ( TEX_R_TIME,   TIME_Alpha);

	//�X�R�A
	LoadTexture ( "Texture\\Image\\score.png", TEX_R_SCORE, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_R_SCORE, -1000, -1000, NULL, NULL, NULL, NULL );
	SetAlpha ( TEX_R_SCORE,  SCORE_Alpha);

	//�����N
	LoadTexture ( "Texture\\Image\\s.png", TEX_R_RANK, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_R_RANK, -1000, -1000, NULL, NULL, NULL, NULL );
	SetAlpha ( TEX_R_RANK,   RANK_Alpha);

	//�X��
	LoadTexture ( "Texture\\Image\\tentyo-s.png", TEX_R_OSSAN, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_R_OSSAN, -1000, -1000, NULL, NULL, NULL, NULL );
	SetAlpha ( TEX_R_OSSAN,  OSSAN_Alpha);

	//�Z���t
	LoadTexture ( "Texture\\Image\\comment-s.png", TEX_R_SERIFU, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_R_SERIFU, -1000, -1000, NULL, NULL, NULL, NULL );
	SetAlpha ( TEX_R_SERIFU, OSSAN_Alpha);

	//�����NA�̌M�͉摜
	LoadTexture ( "Texture\\Image\\a.png", TEX_RANK_A, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_RANK_A, -1000, -1000, NULL, NULL, NULL, NULL );
	//�����NB�̌M�͉摜
	LoadTexture ( "Texture\\Image\\b.png", TEX_RANK_B, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_RANK_B, -1000, -1000, NULL, NULL, NULL, NULL );
	//�����NC�̌M�͉摜
	LoadTexture ( "Texture\\Image\\c.png", TEX_RANK_C, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_RANK_C, -1000, -1000, NULL, NULL, NULL, NULL );
	//�����NS�̌M�͉摜
	LoadTexture ( "Texture\\Image\\star.png", TEX_RANK_S, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_RANK_S, -1000, -1000, NULL, NULL, NULL, NULL );

	//	�ǉ���	2/14	�T�c
	LoadTexture ( "Texture\\Image\\title_B.png", TEX_GO_TO_TITLE, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_GO_TO_TITLE, TITLE_BUTTON_X, TITLE_BUTTON_Y, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\Image\\makar.png", TEX_TARGET , 0, 0, 0 );
	SetVertex ( NORMAL, TEX_TARGET, 0, 0, NULL, NULL, NULL, NULL );	

	resultCount = 0;
	times = 0;
	scores = 0;
	resultflag = false;
	timeflag = false;
	tmp = 0;
	get = 0;
	
	for ( int i = 0 ; i < SUZI ; i++ )
	{
		time[i].x = TIMES_ONE_X;
		time[i].y = TIMES_Y;
		time[i].Scall = 0.09f;	

		score[i].x = TIMES_ONE_X;
		score[i].y = SCORES_Y;
		score[i].Scall = 0.09f;	
	}

}

//	���U���g�̏���
void CL_RESULT::Control ()
{
	SetVertex ( CENTER, TEX_TARGET, poCurrentCursor.x, poCurrentCursor.y, NULL, NULL, NULL, NULL );///<	�^�[�Q�b�g�J�[�\�����W�̍X�V

	resultCount++;
	r_timer = Gettime();
	//60�łP�b
	time_m = r_timer/60;
	time_s = time_m%60;
	time_m /= 60;
	_time[0] = time_s%10;
	_time[1] = time_s/10;
	_time[2] = time_m%10;
	_time[3] = time_m/10;
	times = 00000;//��,���Get()
	scores = 1;
	tmp = times;
	get = scores;
	
	for ( int i = 0 ; i < SUZI ; i++ )
	{
		time[i].x = TIMES_ONE_X;
		time[i].y = TIMES_Y;
		time[i].Scall = 0.09f;	
	}

	for( int i = 4 ; i >= 0 ; i-- )
	{
		dat[i] = tmp % 10;
		tmp = tmp / 10;

	}
	

	//���U���g�t�F�[�hin
	if( resultCount <= RESULT_FI )
	{
		SetVertex ( NORMAL, TEX_RESULT, RESULT_X, RESULT_Y, NULL, NULL, NULL, NULL );
		SetAlpha ( TEX_RESULT,   Alpha);
		Alpha += 10;
		if ( Alpha > 255 ) Alpha = 255;
	}
	//�^�C���t�F�[�hin
	else if( resultCount <= RESULT_TIME_FI )
	{
		SetVertex ( NORMAL, TEX_R_TIME, RESULT_TIME_X, RESULT_TIME_Y, NULL, NULL, NULL, NULL );
		SetAlpha ( TEX_R_TIME,   TIME_Alpha);
		TIME_Alpha += 10;
		if ( TIME_Alpha > 255 ) TIME_Alpha = 255;
	}
	//�X�R�A�t�F�[�hin
	else if( resultCount <= RESULT_SCORE_FI )
	{
		SetVertex ( NORMAL, TEX_R_SCORE, RESULT_SCORE_X, RESULT_SCORE_Y, NULL, NULL, NULL, NULL );
		SetAlpha ( TEX_R_SCORE,   SCORE_Alpha);
		SCORE_Alpha += 10;
		if ( SCORE_Alpha > 255 ) SCORE_Alpha = 255;
	}
	//�����N�t�F�[�hin
	else if( resultCount <= RESULT_RANK_FI )
	{
		SetVertex ( NORMAL, TEX_R_RANK, RESULT_RANK_X, RESULT_RANK_Y, NULL, NULL, NULL, NULL );
		SetAlpha ( TEX_R_RANK,   RANK_Alpha);
		RANK_Alpha += 10;
		if ( RANK_Alpha > 255 ) RANK_Alpha = 255;
	}
	//��������ƃZ���t�t�F�[�hin
	else if( resultCount <= RESULT_OSSAN_FI )
	{
		SetVertex ( NORMAL, TEX_R_OSSAN, RESULT_OSSAN_X, RESULT_OSSAN_Y, NULL, NULL, NULL, NULL );
		SetVertex ( NORMAL, TEX_R_SERIFU, RESULT_SERIFU_X, RESULT_SERIFU_Y, NULL, NULL, NULL, NULL );
		SetAlpha ( TEX_R_OSSAN,  OSSAN_Alpha);
		SetAlpha ( TEX_R_SERIFU, OSSAN_Alpha);
		OSSAN_Alpha += 10;
		if ( OSSAN_Alpha > 255 ) OSSAN_Alpha = 255;
	}
	//�^�C��in
	else if( resultCount <= RESULT_TIMES_NUMBER_FI )
	{
		timeflag = true;
		settimes( TIMES_ONE_X, TIMES_Y );
		settimes( TIMES_ONE_X, SCORES_Y );
		
	}
	//�����N�ʏ���
	else if( resultCount <= RESULT_RANK_PUTERN_FI )
	{
		if( scores > RANK_S )
		{
			SetVertex ( NORMAL, TEX_RANK_S, RANK_S_X, RANK_S_Y, NULL, NULL, NULL, NULL );
		}
		else if( scores > RANK_A )
		{
			SetVertex ( NORMAL, TEX_RANK_A, RANK_S_X, RANK_S_Y, NULL, NULL, NULL, NULL );
		}
		else if( scores > RANK_B )
		{
			SetVertex ( NORMAL, TEX_RANK_B, RANK_S_X, RANK_S_Y, NULL, NULL, NULL, NULL );
		}
		else if( scores > RANK_C )
		{
			SetVertex ( NORMAL, TEX_RANK_C, RANK_S_X, RANK_S_Y, NULL, NULL, NULL, NULL );
		}
	}
	
	//	�ǉ���	2/14	�T�c
	if ( HitOfTexture ( poCurrentCursor.x, poCurrentCursor.y, TEX_GO_TO_TITLE ) )
	{
		ChangeColorKey ( ON_OF_BUTTON, TEX_GO_TO_TITLE );
		if ( MouseStCheck ( MOUSE_L, PUSH) )
		{
			ChangeScene ( S_TITLE );
		}
	}
	else
	{
		ChangeColorKey ( OUT_OF_BUTTON, TEX_GO_TO_TITLE );
	}

}

//�@���U���g��3D�`��
void CL_RESULT::Render ()
{
	
}

//�@���U���g��2D�`��
void CL_RESULT::Draw ()
{
	////���U���g�w�i
	//TextureScallDraw( TEX_RESULT , 1.35f );
	////�^�C��
	//TextureScallDraw( TEX_R_TIME , 1.35f );
	////�X�R�A
	//TextureScallDraw( TEX_R_SCORE , 1.35f );
	////�����N
	//TextureScallDraw( TEX_R_RANK , 1.35f );
	////�X��
	//TextureScallDraw( TEX_R_OSSAN , 1.35f );
	////�Z���t
	//TextureScallDraw( TEX_R_SERIFU , 1.35f );
	////�����NS
	//TextureScallDraw( TEX_RANK_S , 1.0f );
	////�����NA
	//TextureScallDraw( TEX_RANK_A , 1.0f );
	////�����NB
	//TextureScallDraw( TEX_RANK_B , 1.0f );
	////�����NC
	//TextureScallDraw( TEX_RANK_C , 1.0f );	
	//if(timeflag == true)
	//{
	//	for ( int i = 0 ; i < SUZI ; i++ )
	//	{
	//		////�����k���\��
	//		//SetVertex ( NORMAL, (eTEXTURE)((int)TEX_R_ONE + (dat[i]-1)), TIMES_ONE_X+50.f*i, TIMES_Y, NULL, NULL, NULL, NULL );
	//		//TextureScallDraw( (eTEXTURE)((int)TEX_R_ONE + (dat[i]-1)) ,   time[i].Scall );
	//		////�����k���\��
	//		//SetVertex ( NORMAL, (eTEXTURE)((int)TEX_R_ONE + (dat[i]-1)), TIMES_ONE_X+50.f*i, SCORES_Y, NULL, NULL, NULL, NULL );
	//		//TextureScallDraw( (eTEXTURE)((int)TEX_R_ONE + (dat[i]-1)) ,   time[i].Scall );
	//	}
	//}
	CUSTOMVERTEX vertextemp[4];
	for( int ii = 0 ; ii < 4 ; ii++ )
	{
		vertextemp[ii].rhw = 1.f;
		vertextemp[ii].z = 0.f;
		vertextemp[ii].color = D3DCOLOR_ARGB(255,255,255,255);
	}
	//�w�i
	vertextemp[0].x = vertextemp[3].x = 0.f;
	vertextemp[1].x = vertextemp[2].x = 1280.f;
	vertextemp[0].y = vertextemp[1].y = 0.f;
	vertextemp[2].y = vertextemp[3].y = 720.f;

	vertextemp[0].tu = vertextemp[3].tu = 0.f;
	vertextemp[1].tu = vertextemp[2].tu = 1.f;
	vertextemp[0].tv = vertextemp[1].tv = 0.f;
	vertextemp[2].tv = vertextemp[3].tv = 1.f;

	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_R_BUCK).pTexture );

	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertextemp,
		sizeof ( CUSTOMVERTEX ) );
	if(r_timer>3600)
	{
		vertextemp[0].x = vertextemp[3].x = 555.f;
		vertextemp[1].x = vertextemp[2].x = 1280.f;
		vertextemp[0].y = vertextemp[1].y = 0.f;
		vertextemp[2].y = vertextemp[3].y = 720.f;

		vertextemp[0].tu = vertextemp[3].tu = 0.f;
		vertextemp[1].tu = vertextemp[2].tu = 1.f;
		vertextemp[0].tv = vertextemp[1].tv = 0.f;
		vertextemp[2].tv = vertextemp[3].tv = 1.f;

		pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

		if(A_RANK_TIME)pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_R_GATO).pTexture );
		if(B_RANK_TIME)pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_R_SMG).pTexture );
		if(C_RANK_TIME)pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_R_BAZU).pTexture );

		pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertextemp,
		sizeof ( CUSTOMVERTEX ) );
	}
	//��
	vertextemp[0].x = vertextemp[3].x = 980.f;
	vertextemp[1].x = vertextemp[2].x = 1280.f;
	vertextemp[0].y = vertextemp[1].y = 230.f;
	vertextemp[2].y = vertextemp[3].y = 530.f;

	vertextemp[0].tu = vertextemp[3].tu = 0.f;
	vertextemp[1].tu = vertextemp[2].tu = 1.f;
	vertextemp[0].tv = vertextemp[1].tv = 0.f;
	vertextemp[2].tv = vertextemp[3].tv = 1.f;

	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	if(S_RANK_TIME)pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_RANK_S).pTexture );
	if(A_RANK_TIME)pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_RANK_A).pTexture );
	if(B_RANK_TIME)pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_RANK_B).pTexture );
	if(C_RANK_TIME)pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_RANK_C).pTexture );
	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertextemp,
		sizeof ( CUSTOMVERTEX ) );
	
	//�p��
	vertextemp[0].x = vertextemp[3].x = 390.f;
	vertextemp[1].x = vertextemp[2].x = 500.f;
	vertextemp[0].y = vertextemp[1].y = 535.f;
	vertextemp[2].y = vertextemp[3].y = 645.f;

	vertextemp[0].tu = vertextemp[3].tu = 0.f;
	vertextemp[1].tu = vertextemp[2].tu = 1.f;
	vertextemp[0].tv = vertextemp[1].tv = 0.f;
	vertextemp[2].tv = vertextemp[3].tv = 1.f;

	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	if(S_RANK_TIME)pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_SRANK).pTexture );
	if(A_RANK_TIME)pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_ARANK).pTexture );
	if(B_RANK_TIME)pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_BRANK).pTexture );
	if(C_RANK_TIME)pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_CRANK).pTexture );
	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertextemp,
		sizeof ( CUSTOMVERTEX ) );

	//�ꌅ
	vertextemp[0].x = vertextemp[3].x = TIMEPOS1_X;
	vertextemp[1].x = vertextemp[2].x = TIMEPOS1_X + TIMEX_SIZE;
	vertextemp[0].y = vertextemp[1].y = TIMEPOS_Y;
	vertextemp[2].y = vertextemp[3].y = TIMEPOS_Y + TIMEY_SIZE;
	for( int ii = 0 ; ii < 4 ; ii++ )
	{
		vertextemp[ii].rhw = 1.f;
		vertextemp[ii].z = 0.f;
		vertextemp[ii].color = D3DCOLOR_ARGB(255,255,255,255);
	}
	vertextemp[0].tu = vertextemp[3].tu = 0.f  + (float)_time[0] / 10;
	vertextemp[1].tu = vertextemp[2].tu = 0.1f + (float)_time[0] / 10;
	vertextemp[0].tv = vertextemp[1].tv = 0.f;
	vertextemp[2].tv = vertextemp[3].tv = 1.f;

	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_NUM_SET).pTexture );

	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertextemp,
		sizeof ( CUSTOMVERTEX ) );

	//��
	vertextemp[0].x = vertextemp[3].x = TIMEPOS2_X;
	vertextemp[1].x = vertextemp[2].x = TIMEPOS2_X + TIMEX_SIZE;
	vertextemp[0].y = vertextemp[1].y = TIMEPOS_Y;
	vertextemp[2].y = vertextemp[3].y = TIMEPOS_Y + TIMEY_SIZE;
	
	vertextemp[0].tu = vertextemp[3].tu = 0.f  + (float)_time[1] / 10;
	vertextemp[1].tu = vertextemp[2].tu = 0.1f + (float)_time[1] / 10;
	vertextemp[0].tv = vertextemp[1].tv = 0.f;
	vertextemp[2].tv = vertextemp[3].tv = 1.f;

	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_NUM_SET).pTexture );

	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertextemp,
		sizeof ( CUSTOMVERTEX ) );

	//�O��
	vertextemp[0].x = vertextemp[3].x = TIMEPOS3_X;
	vertextemp[1].x = vertextemp[2].x = TIMEPOS3_X + TIMEX_SIZE;
	vertextemp[0].y = vertextemp[1].y = TIMEPOS_Y;
	vertextemp[2].y = vertextemp[3].y = TIMEPOS_Y + TIMEY_SIZE;
	
	vertextemp[0].tu = vertextemp[3].tu = 0.f  + (float)_time[2] / 10;
	vertextemp[1].tu = vertextemp[2].tu = 0.1f + (float)_time[2] / 10;
	vertextemp[0].tv = vertextemp[1].tv = 0.f;
	vertextemp[2].tv = vertextemp[3].tv = 1.f;

	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_NUM_SET).pTexture );

	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertextemp,
		sizeof ( CUSTOMVERTEX ) );

	//�l��
	vertextemp[0].x = vertextemp[3].x = TIMEPOS4_X;
	vertextemp[1].x = vertextemp[2].x = TIMEPOS4_X + TIMEX_SIZE;
	vertextemp[0].y = vertextemp[1].y = TIMEPOS_Y;
	vertextemp[2].y = vertextemp[3].y = TIMEPOS_Y + TIMEY_SIZE;
	
	vertextemp[0].tu = vertextemp[3].tu = 0.f  + (float)_time[3] / 10;
	vertextemp[1].tu = vertextemp[2].tu = 0.1f + (float)_time[3] / 10;
	vertextemp[0].tv = vertextemp[1].tv = 0.f;
	vertextemp[2].tv = vertextemp[3].tv = 1.f;

	pD3Device -> SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	pD3Device -> SetTexture ( 0, GetTEXTUREINFO(TEX_NUM_SET).pTexture );

	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		vertextemp,
		sizeof ( CUSTOMVERTEX ) );

	//	�ǉ���	2/14	�T�c
	TextureDraw ( TEX_GO_TO_TITLE );

	TextureDraw ( TEX_TARGET );	
}

void CL_RESULT::Release()
{
	ReleaseAllTexture();
	ReleaseAllSoundFile();
}