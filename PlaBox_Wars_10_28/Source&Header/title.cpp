#include "Lib.h"
#include "title.h"
#include "graphic.h"
#include "input.h"
#include "logo.h"
#include "Audio.h"

#define TIT_FI	      (102		+ 24)   //タイトルフェードイン

//	変更日	2/14	亀田			↓120→30に
#define TIT_DS        (TIT_FI     + 60)  //タイトル表示
#define TIT_SH        (TIT_DS     + 60)   //穴エフェクト
#define TIT_DS_BS     (TIT_SH     + 60)   //穴エフェクト表示
#define TIT_SM        (TIT_DS_BS  + 50)   //縮小
#define TIT_RISE      (TIT_SM     + 50)   //上昇

#define TIT_DOUBLE		(TIT_RISE		+ 180)	//2画像で一旦静止

#define TIT_RUN       (TIT_DOUBLE   + 75)   //逃走
#define TIT_NON       (TIT_RUN    + 30)   //タイトルなし
#define RETIT         (TIT_NON    + 180)   //再度出てくる
#define RETIT_SH      (RETIT      + 60)   //また撃たれる

#define TIT_FURA      (RETIT_SH   + 140)  //フラフラ落ちていく

//	追加日	2/14	亀田
#define	LOOP_TITLE_MOVE	( TIT_FURA + 120 )	//タイトルの動作の繰り返しのタイミング
#define TIT_END       72 * 60  //タイトルエンド (OPの音楽が一周するまで) 

#define TASP          5                  //穴の空く間隔

#define DEF_X         300.0f            //Xの初期値(タイトル，弾痕)
#define DEF_Y         100.0f            //Yの初期値(タイトル，弾痕)

#define MENU_X        482.0f            //Xの初期値(メニュー)
#define MENU_Y        900.0f            //Yの初期値(メニュー)


#define RISE_X        3.2f              //Xの移動値(上昇)
#define RISE_Y        1.0f              //Yの移動値(上昇)

#define R_X           20.0f             //逃げるスピード


#define RE_X_R        -460.0f           //Xの初期値(タイトルなし，右)
#define RE_X_L        1380.0f           //Xの初期値(タイトルなし，左)
#define RE_Y          650.0f            //Yの初期値(タイトルなし)

#define RERISE_X      10.0f              //Xの戻っていくスピード
#define RERISE_Y      6.5f              //Yの戻っていくスピード

//	追加日	2/14	亀田	
#define POINT_OF_BUTTON_X		WIN_WIDTH / 3
#define POINT_OF_BUTTON_Y		WIN_HEIGHT / 2

#define	GAP_OF_BUTTON	30

extern bool BreakFlag;		//ロゴ画面で、途中でクリックされた

				//	↓使い方を修正しました。
int titleCount;	//	「このカウンタを使ってロゴへ戻る。」→「タイトルの動きの制御カウント」

//	追加日　2/14	亀田
int	iEndCount;	//	タイトル終了用のカウント

#define TARGET_SCALE 0.25f	///<	ターゲットのカーソルサイズ

//	タイトルの初期化
//	表示させたいものを読み込んだり、初期座標を決めてやったりカウンタを初期状態にする。
void CL_TITLE::Init ()
{
	int	iTempX = 0, iTempY = 0;	//画像サイズ仮保存 

	LoadTexture ( "Texture\\Image\\menu.png", TEX_MENU, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_MENU, MENU_X, MENU_Y, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\Image\\title.png", TEX_TITLE, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_TITLE, DEF_X, DEF_Y, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\Image\\dankon.png", TEX_DANKON, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_DANKON, DEF_X, DEF_Y, NULL, NULL, NULL, NULL );
	//数字統合ファイル画像　北川
	LoadTexture ( "Texture\\Image\\number.png", TEX_NUM_SET, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_NUM_SET, -1000, -1000, NULL, NULL, NULL, NULL );

	//	各シーンへのボタン
	LoadTexture ( "Texture\\Image\\start_B.png", TEX_GAME_START, 0, 255, 0 );

	//iTempX = GetTexWidth ( TEX_GAME_START );
	iTempY = GetTexHeight ( TEX_GAME_START ) + GAP_OF_BUTTON;	//　画像サイズの取得とボタンのY座標の間隔分足す
	
	SetVertex ( NORMAL, TEX_GAME_START, POINT_OF_BUTTON_X, POINT_OF_BUTTON_Y, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\Image\\credit_B.png", TEX_CREDIT, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_CREDIT, POINT_OF_BUTTON_X , POINT_OF_BUTTON_Y + iTempY, NULL, NULL, NULL, NULL );

	iTempY = GetTexHeight ( TEX_CREDIT ) * 2 + GAP_OF_BUTTON * 2;	

	LoadTexture ( "Texture\\Image\\end_B.png", TEX_GAME_END, 0, 255, 0 );
	SetVertex ( NORMAL, TEX_GAME_END, POINT_OF_BUTTON_X, POINT_OF_BUTTON_Y + iTempY, NULL, NULL, NULL, NULL );

	LoadTexture ( "Texture\\Image\\makar.png", TEX_TARGET , 0, 0, 0 );
	SetVertex ( NORMAL, TEX_TARGET, 0, 0, NULL, NULL, NULL, NULL );	/**	@details	追加日2015/07/01	マウス制御をフォアグラウンドにしたため、
																	カーソルの表示設定も変える必要があったため、ターゲットカーソルのテクスチャをタイトルでも読み込み*/
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


//	タイトルの処理
//	ここで表示してるものの動きとかを付け足していく。
void CL_TITLE::Control ()
{
	SetVertex ( CENTER, TEX_TARGET, poCurrentCursor.x, poCurrentCursor.y, NULL, NULL, NULL, NULL );///<	ターゲットカーソル座標の更新

//\\\\\\タイトルフェードイン\\\\\\\\\\\\\
	
	if ( titleCount <= TIT_FI){
		SetAlpha ( TEX_TITLE, Alpha);
		Alpha += 11;
		if ( Alpha > 255 ) Alpha = 255;
	}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//**////タイトル表示中\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_DS   ){
	}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//**////穴エフェクト\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

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

//**////タイトル表示中(穴空き)\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_DS_BS){
	}
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//\\\\\\\\\\タイトル縮小\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

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

//\\\\\\\\\\タイトル上昇\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_RISE ){
		tl_x += RISE_X;
		tl_y -= RISE_Y;

		for ( int i = 0; i < DANKON; i++ )
		{
			tama[i].x += RISE_X;
			tama[i].y -= RISE_Y;
		}

		menu_y -= 8.0f; //メニュー

		t_bX = tl_x;    // タイトル座標の格納
		t_bY = tl_y;    // タイトル座標の格納
		
	}

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount == TIT_DOUBLE){
		//SoundPlay( BGM_01, true);
	}



//\\\\\\\\\\\\タイトル逃走\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_RUN  ){
		//30カウントだけストップ
		if ( titleCount < TIT_RISE+30 ){
		}


		else{

			//右に移動
			if ( Run == 0 ){
				tl_x += R_X;
				for ( int i = 0; i < DANKON; i++ )
				{
					tama[i].x += R_X;

			    }
			}

			//左に移動
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

//\\\\\\\\\\タイトルなし\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	else if ( titleCount < TIT_NON  ){
	//タイトルと弾痕の座標を再度初期化

		//逃げたのが右の場合
		if ( Run == 0 ){
			tl_x = RE_X_R;
			tl_y = RE_Y;
			for ( int i = 0; i < DANKON; i++ )
			{
				tama[i].x = RE_X_R + (Rand_X[i] / h);
				tama[i].y = RE_Y + (Rand_Y[i] / h);
			}
		}

		//逃げたのが左の場合
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

//\\\\\\\\タイトル登場\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

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

//\\\\\\\\\\\\\\\\もう一度撃たれる\\\\\\\\\\\\\\\\\\\\\\\\\

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

//\\\\\\\\\\\\\\\フラフラ落ちていく\\\\\\\\\\\\\\\\\\\\\\\\\

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

//	追加日	2/14	亀田
//	タイトルのモーションの繰り返し
	if ( titleCount >= LOOP_TITLE_MOVE ) { titleCount = TIT_RISE; }

//	ロゴに戻る
	if ( iEndCount >= TIT_END ) { ChangeScene ( S_LOGO ); }

	//	各モードへの仮分岐
	if ( titleCount >= TIT_RISE )
	{
		if ( HitOfTexture ( poCurrentCursor.x, poCurrentCursor.y, TEX_CREDIT ))
		{
			ChangeColorKey ( ON_OF_BUTTON, TEX_CREDIT );
			if ( MouseStCheck ( MOUSE_L, PUSH) )
			{
				ChangeScene ( S_GALLERY );	//	現在はクレジット
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

//　タイトルの3D描画
void CL_TITLE::Render ()
{

}

//　タイトルの2D描画
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