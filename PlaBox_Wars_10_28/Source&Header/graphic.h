#pragma once
#ifndef	_GRAPHIC_H_
#define _GRAPHIC_H_

#include <d3d9.h>
#include <d3dx9tex.h>
#include <d3dx9math.h>
#include <vector>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#define WIN_WIDTH	1280	//実際のウインドウ横幅
#define WIN_HEIGHT	720		//実際のウインドウ縦幅
#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define FVF_CUSTOM ( D3DFVF_XYZRHW | D3DFVF_TEX1 )

extern	IDirect3D9*			pDirect3D;
extern	IDirect3DDevice9*	pD3Device; //デバイスオブジェクト


//	追加日	2/14	亀田
#define ON_OF_BUTTON	254, 110, 254
#define OUT_OF_BUTTON	254, 254, 254
#define TITLE_BUTTON_X	( WIN_WIDTH / 3 ) * 2
#define TITLE_BUTTON_Y	30

// 使用するテクスチャ
// 使いたいテクスチャがあれば列挙子内に追加していく
enum eTEXTURE
{
	TEX_LOGO,

	TEX_TITLE,
	TEX_DANKON,	//植村追加分@title

	//	追加日	2/14	亀田
	TEX_GAME_START,
	TEX_CREDIT,
	TEX_GAME_END,
	TEX_GO_TO_TITLE,
	//

	TEX_GAME,

	TEX_MENU,

	TEX_GALLERY,

	TEX_OPTION,

	TEX_PLAYER_UI1,
	
	//2/10　石川追加 GAGE2種類
	TEX_PLAYER_HP,		

	TEX_PLAYER_SP,

	TEX_PLAYER_HP_GAGE,

	TEX_PLAYER_SP_GAGE,

	TEX_PLAYER_UITE_KIND,

	TEX_PLAYER_UITE_BOTTLE,

	TEX_RADAR,

	TEX_TARGET,
	//--------------

	TEX_RESULT,  //
	TEX_R_TIME,  //
	TEX_R_SCORE, //村越追加分@result
	TEX_R_RANK,  //
	TEX_R_OSSAN, //
	TEX_R_SERIFU,//
	TEX_RANK_A,  //
	TEX_RANK_B,  //
	TEX_RANK_C,  //
	TEX_RANK_S,  //
	TEX_R_ONE,
	TEX_R_TWO,
	TEX_R_THREE,
	TEX_R_FOUR,
	TEX_R_FIVE,
	TEX_R_SIX,
	TEX_R_SEVEN,
	TEX_R_EIGHT,
	TEX_R_NINE,
	TEX_R_ZERO,
	TEX_NUM_SET,

	ICON_NONE,
	ICON_RIFLE,
	ICON_MG,
	ICON_BAZOOKA,
	ICON_GATLING,

	TEX_GAMEOVER,
	TEX_R_BUCK,
	TEX_SRANK,
	TEX_ARANK,
	TEX_BRANK,
	TEX_CRANK,
	TEX_R_BAZU,
	TEX_R_SMG,
	TEX_R_GATO,

	TEX_EFF_DEBRIS,
	TEX_EFF_EXPROSION,

	TEXTURE_MAX
};

//	SetVertex関数の通常移動、回転、アニメーションの切り替え用
enum eSETVERTEX_PATTERN
{
	NORMAL,

	CENTER,
	
	ROTATE,

	ANIMATION,

	SETVERTEX_PATTERN_MAX
};



// テクスチャの番号とテクスチャ全体の縦横の大きさ
struct TEXTUREINFO
{
	// テクスチャの格納ポインタ
	LPDIRECT3DTEXTURE9	pTexture;

	int		width, height;
};

// 画像の頂点座標などの構造体
struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;

	DWORD	color;

	FLOAT	tu, tv;
};

extern	CUSTOMVERTEX	test[3];
// 2Dの座標計算
// 第1引数：座標計算のパターン, 第2引数：テクスチャの番号(enum eTEXTUREから), 第3,4引数：左上の頂点ｘｙ
// ここから先はANIMATIONなら入力。それ以外ならNULLで↓
// 第5,6引数：アニメーション画像のサイズ, 第7,8引数：左上のテクスチャーUV座標ｘｙ
void SetVertex ( eSETVERTEX_PATTERN setPattern, eTEXTURE TextuerNumber, float fX, float fY,
				float fSize_X, float fSize_Y, float fTu, float fTv );

// Direct3Dの初期化
// 第1引数：ウインドハンドル
bool InitRender ( HWND hWnd );

// テクスチャの読み込み
// 第1引数：("画像の名前.拡張子"), 第2引数：テクスチャの番号(enum eTEXTUREから), 透過色RGB 
bool LoadTexture ( LPCSTR lpFileName, eTEXTURE TextuerNumber, int iColorRed, int iColorGreen, int iColorBlue );

//---
// 指定したテクスチャの幅を返す
//float GetTextureWidth( eTEXTURE TextuerNumber );	// 横幅
//float GetTextureHeight( eTEXTURE TextuerNumber );	// 縦幅
//--
// テクスチャの縮小表示
// 第1引数：テクスチャの番号(enum eTEXTUREから)
// 第2引数：テクスチャの縮尺  1.0fで読み込み時の大きさ
void TextureScallDraw ( eTEXTURE TextuerNumber, float Scall );
//--
void SetAlpha ( eTEXTURE TextuerNumber, int Alpha);
//--

// レンダリング前処理
void BeginRender (void);

// 描画前処理
void BeginDraw (void);

// 描画処理
// 第1引数：テクスチャの番号(enum eTEXTUREから)
void TextureDraw ( eTEXTURE TextuerNumber );

/**
*	@brief	描画時変換行列
*	@details	射影とビュー行列は1フレーム間では変わらないので、分離させる（仮）。
*	@param[in]	変換行列更新フラグポインタ
*/
void RenderMatrix( bool* _p_bMatrixInit );

/**
*	@brief	ポリゴン描画関数
*	@details	頂点指定をして描画する。
*	@todo	現状パーティクル描画専用として作成。運用方法を考える必要あり。
*	@param[in]	_pVertex	頂点データ配列。
*	@param[in]	_refPos		平行移動行列にセットする粒子個々の基準点
*	@param[in]	_refRot		回転行列にセットする向きベクトル
*	@param[in]	_refSca		拡縮行列にセットする倍率
*	@param[in]	_TextuerNumber	セットするテクスチャ番号
*	@param[in]	_bMatrixInit	描画時射影+ビュー行列初期化フラグ
*/
void PolygonRender( CUSTOMVERTEX* _pVertex, D3DXVECTOR3 _refPos, D3DXVECTOR3 _refRot, D3DXVECTOR3 _refSca,
	eTEXTURE _TextuerNumber, bool* _p_bMatrixInit );

// 描画後処理
void EndRender (void);

// テクスチャの解放
// 第1引数：テクスチャの番号(enum eTEXTUREから)
void ReleaseTexture ( int TextuerNumber );

// 使用している全てのテクスチャの解放
void ReleaseAllTexture (void);

// Direct3Dオブジェクトの解放
void ReleaseRender (void);

void SetAlpha ( eTEXTURE TextuerNumber, int Alpha);

TEXTUREINFO GetTEXTUREINFO( int );

//画像サイズ取得
// 第1引数：テクスチャの番号(enum eTEXTUREから)
int GetTexWidth( int  );
int GetTexHeight( int  );

//画像サイズ変更
// 第1引数：テクスチャの番号(enum eTEXTUREから)
// 第2,3引数：サイズx,y
void SetTexSize( int , float , float );

//	追加日　2/14	亀田
//	点xyがiTexNum番の画像の中に入っているかの判定
bool	HitOfTexture ( int _x, int _y, int iTexNum );

//	テクスチャの色彩を変更する関数
void	ChangeColorKey ( int iR, int iG, int iB, int iTexNum );


#ifndef	_THING_CLASS_
struct BBOX
{
	D3DXVECTOR3	vecMax;
	D3DXVECTOR3	vecMin;

	LPD3DXMESH			pBBoxMesh;
	D3DMATERIAL9*		pBBoxMeshMaterials;
};

//	メッシュや3D座標などの構造体
class CL_THING 
{
public:
	LPD3DXMESH			pMesh;			//	メッシュデータの格納
	D3DMATERIAL9*		pMeshMaterials;	//	マテリアルのデータ
	LPDIRECT3DTEXTURE9*	pMeshTextures;	//	テクスチャのデータ
	DWORD				dwNumMaterials;	//
	D3DXVECTOR3			vecPosition;	//	位置
	D3DXVECTOR3			vecScall;		//　拡縮（倍率）
	D3DXVECTOR3			vecRotate;		//	向き

	D3DXVECTOR3			vecBeforePos;	//	前フレームの時の位置

	BBOX				BBox;			//	HitCheck.cpp用のメンバー
	std::vector <D3DXVECTOR3> localVec;//	メッシュデータのポリゴンの頂点データを格納用変数

	CL_THING()	{	ZeroMemory(this,sizeof(CL_THING));	}

	// xファイル読み込み時のワールド座標、倍率、方向。の格納関数
	bool LoadThingFile(CL_THING*, LPCSTR, D3DXVECTOR3*, D3DXVECTOR3*, D3DXVECTOR3*);

	//	3D描画処理
	void Transform(CL_THING* pThing);

	//倍率変更
	void SetScall(D3DXVECTOR3 _scall ){ vecScall = _scall; }

	//	ビルボード描画処理
	void BillboardingTransform(CL_THING* pThing);

	//	頂点取得
	void GetMeshVertex();

		
	//	モデルの頂点座標のワールド座標変換(test)
	//	モデルの回転度：rx,ry,rz
	//	モデルの拡縮：sx,sy,sz
	//	モデルの基準点(親)：px,py,pz
	//	モデルの頂点(子)：l_v_px,l_v_py,l_v_pz
	D3DXVECTOR3 LocalToWarldTransform( float rx, float ry, float rz,
								float sx, float sy, float sz,
								float px, float py, float pz,
								float l_v_px, float l_v_py, float l_v_pz );

	//	解放
	virtual void FreeMesh() = 0;
};
#endif

//------------------------------------------------------------------
//	スクリーン座標をワールド座標に変換する
//	制作日	12/12	
//------------------------------------------------------------------

//	スクリーン座標とXZ平面のワールド座標交点算出
//	XZ平面とスクリーン座標の交点算出関数
D3DXVECTOR3* CalcScreenToXZ
(
	D3DXVECTOR3* pout,
	int Sx,				//	スクリーン座標ｘ
	int Sy,				//	スクリーン座標ｙ
	int Screen_w,		//	スクリーンの横幅
	int Screen_h,		//	スクリーンの縦幅
	D3DXMATRIXA16* View,//	ビュー行列
	D3DXMATRIXA16* Prj	//	射影変換行列
);

//	スクリーン座標をワールド座標に変換
// スクリーン座標をワールド座標に変換
D3DXVECTOR3* CalcScreenToWorld
(
   D3DXVECTOR3* pout,	
   int Sx,				//	スクリーン座標内ｘ
   int Sy,				//	スクリーン座標内ｙ
   float fZ,			//	射影空間でのZ値（0～1）
   int Screen_w,		//	スクリーンの横幅
   int Screen_h,		//	スクリーンの縦幅
   D3DXMATRIXA16* View,	//	ビュー行列
   D3DXMATRIXA16* Prj		//	射影変換行列
);

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// 指定したベクトルへ向かせる行列算出関数
D3DXMATRIX* CalcLookAtMatrix(
   D3DXMATRIX* pout,
   D3DXVECTOR3* pPos,
   D3DXVECTOR3* pLook,
   D3DXVECTOR3* pUp);

//	Y軸回転行列
D3DXVECTOR3	RotateYMatrix( D3DXVECTOR3* , float _y );

float GetVectorLength( D3DXVECTOR3 _v );

#endif