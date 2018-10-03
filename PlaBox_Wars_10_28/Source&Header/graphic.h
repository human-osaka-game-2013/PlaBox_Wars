#pragma once
#ifndef	_GRAPHIC_H_
#define _GRAPHIC_H_

#include <d3d9.h>
#include <d3dx9tex.h>
#include <d3dx9math.h>
#include <vector>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#define WIN_WIDTH	1280	//���ۂ̃E�C���h�E����
#define WIN_HEIGHT	720		//���ۂ̃E�C���h�E�c��
#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define FVF_CUSTOM ( D3DFVF_XYZRHW | D3DFVF_TEX1 )

extern	IDirect3D9*			pDirect3D;
extern	IDirect3DDevice9*	pD3Device; //�f�o�C�X�I�u�W�F�N�g


//	�ǉ���	2/14	�T�c
#define ON_OF_BUTTON	254, 110, 254
#define OUT_OF_BUTTON	254, 254, 254
#define TITLE_BUTTON_X	( WIN_WIDTH / 3 ) * 2
#define TITLE_BUTTON_Y	30

// �g�p����e�N�X�`��
// �g�������e�N�X�`��������Η񋓎q���ɒǉ����Ă���
enum eTEXTURE
{
	TEX_LOGO,

	TEX_TITLE,
	TEX_DANKON,	//�A���ǉ���@title

	//	�ǉ���	2/14	�T�c
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
	
	//2/10�@�ΐ�ǉ� GAGE2���
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
	TEX_R_SCORE, //���z�ǉ���@result
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

//	SetVertex�֐��̒ʏ�ړ��A��]�A�A�j���[�V�����̐؂�ւ��p
enum eSETVERTEX_PATTERN
{
	NORMAL,

	CENTER,
	
	ROTATE,

	ANIMATION,

	SETVERTEX_PATTERN_MAX
};



// �e�N�X�`���̔ԍ��ƃe�N�X�`���S�̂̏c���̑傫��
struct TEXTUREINFO
{
	// �e�N�X�`���̊i�[�|�C���^
	LPDIRECT3DTEXTURE9	pTexture;

	int		width, height;
};

// �摜�̒��_���W�Ȃǂ̍\����
struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;

	DWORD	color;

	FLOAT	tu, tv;
};

extern	CUSTOMVERTEX	test[3];
// 2D�̍��W�v�Z
// ��1�����F���W�v�Z�̃p�^�[��, ��2�����F�e�N�X�`���̔ԍ�(enum eTEXTURE����), ��3,4�����F����̒��_����
// ����������ANIMATION�Ȃ���́B����ȊO�Ȃ�NULL�Ł�
// ��5,6�����F�A�j���[�V�����摜�̃T�C�Y, ��7,8�����F����̃e�N�X�`���[UV���W����
void SetVertex ( eSETVERTEX_PATTERN setPattern, eTEXTURE TextuerNumber, float fX, float fY,
				float fSize_X, float fSize_Y, float fTu, float fTv );

// Direct3D�̏�����
// ��1�����F�E�C���h�n���h��
bool InitRender ( HWND hWnd );

// �e�N�X�`���̓ǂݍ���
// ��1�����F("�摜�̖��O.�g���q"), ��2�����F�e�N�X�`���̔ԍ�(enum eTEXTURE����), ���ߐFRGB 
bool LoadTexture ( LPCSTR lpFileName, eTEXTURE TextuerNumber, int iColorRed, int iColorGreen, int iColorBlue );

//---
// �w�肵���e�N�X�`���̕���Ԃ�
//float GetTextureWidth( eTEXTURE TextuerNumber );	// ����
//float GetTextureHeight( eTEXTURE TextuerNumber );	// �c��
//--
// �e�N�X�`���̏k���\��
// ��1�����F�e�N�X�`���̔ԍ�(enum eTEXTURE����)
// ��2�����F�e�N�X�`���̏k��  1.0f�œǂݍ��ݎ��̑傫��
void TextureScallDraw ( eTEXTURE TextuerNumber, float Scall );
//--
void SetAlpha ( eTEXTURE TextuerNumber, int Alpha);
//--

// �����_�����O�O����
void BeginRender (void);

// �`��O����
void BeginDraw (void);

// �`�揈��
// ��1�����F�e�N�X�`���̔ԍ�(enum eTEXTURE����)
void TextureDraw ( eTEXTURE TextuerNumber );

/**
*	@brief	�`�掞�ϊ��s��
*	@details	�ˉe�ƃr���[�s���1�t���[���Ԃł͕ς��Ȃ��̂ŁA����������i���j�B
*	@param[in]	�ϊ��s��X�V�t���O�|�C���^
*/
void RenderMatrix( bool* _p_bMatrixInit );

/**
*	@brief	�|���S���`��֐�
*	@details	���_�w������ĕ`�悷��B
*	@todo	����p�[�e�B�N���`���p�Ƃ��č쐬�B�^�p���@���l����K�v����B
*	@param[in]	_pVertex	���_�f�[�^�z��B
*	@param[in]	_refPos		���s�ړ��s��ɃZ�b�g���闱�q�X�̊�_
*	@param[in]	_refRot		��]�s��ɃZ�b�g��������x�N�g��
*	@param[in]	_refSca		�g�k�s��ɃZ�b�g����{��
*	@param[in]	_TextuerNumber	�Z�b�g����e�N�X�`���ԍ�
*	@param[in]	_bMatrixInit	�`�掞�ˉe+�r���[�s�񏉊����t���O
*/
void PolygonRender( CUSTOMVERTEX* _pVertex, D3DXVECTOR3 _refPos, D3DXVECTOR3 _refRot, D3DXVECTOR3 _refSca,
	eTEXTURE _TextuerNumber, bool* _p_bMatrixInit );

// �`��㏈��
void EndRender (void);

// �e�N�X�`���̉��
// ��1�����F�e�N�X�`���̔ԍ�(enum eTEXTURE����)
void ReleaseTexture ( int TextuerNumber );

// �g�p���Ă���S�Ẵe�N�X�`���̉��
void ReleaseAllTexture (void);

// Direct3D�I�u�W�F�N�g�̉��
void ReleaseRender (void);

void SetAlpha ( eTEXTURE TextuerNumber, int Alpha);

TEXTUREINFO GetTEXTUREINFO( int );

//�摜�T�C�Y�擾
// ��1�����F�e�N�X�`���̔ԍ�(enum eTEXTURE����)
int GetTexWidth( int  );
int GetTexHeight( int  );

//�摜�T�C�Y�ύX
// ��1�����F�e�N�X�`���̔ԍ�(enum eTEXTURE����)
// ��2,3�����F�T�C�Yx,y
void SetTexSize( int , float , float );

//	�ǉ����@2/14	�T�c
//	�_xy��iTexNum�Ԃ̉摜�̒��ɓ����Ă��邩�̔���
bool	HitOfTexture ( int _x, int _y, int iTexNum );

//	�e�N�X�`���̐F�ʂ�ύX����֐�
void	ChangeColorKey ( int iR, int iG, int iB, int iTexNum );


#ifndef	_THING_CLASS_
struct BBOX
{
	D3DXVECTOR3	vecMax;
	D3DXVECTOR3	vecMin;

	LPD3DXMESH			pBBoxMesh;
	D3DMATERIAL9*		pBBoxMeshMaterials;
};

//	���b�V����3D���W�Ȃǂ̍\����
class CL_THING 
{
public:
	LPD3DXMESH			pMesh;			//	���b�V���f�[�^�̊i�[
	D3DMATERIAL9*		pMeshMaterials;	//	�}�e���A���̃f�[�^
	LPDIRECT3DTEXTURE9*	pMeshTextures;	//	�e�N�X�`���̃f�[�^
	DWORD				dwNumMaterials;	//
	D3DXVECTOR3			vecPosition;	//	�ʒu
	D3DXVECTOR3			vecScall;		//�@�g�k�i�{���j
	D3DXVECTOR3			vecRotate;		//	����

	D3DXVECTOR3			vecBeforePos;	//	�O�t���[���̎��̈ʒu

	BBOX				BBox;			//	HitCheck.cpp�p�̃����o�[
	std::vector <D3DXVECTOR3> localVec;//	���b�V���f�[�^�̃|���S���̒��_�f�[�^���i�[�p�ϐ�

	CL_THING()	{	ZeroMemory(this,sizeof(CL_THING));	}

	// x�t�@�C���ǂݍ��ݎ��̃��[���h���W�A�{���A�����B�̊i�[�֐�
	bool LoadThingFile(CL_THING*, LPCSTR, D3DXVECTOR3*, D3DXVECTOR3*, D3DXVECTOR3*);

	//	3D�`�揈��
	void Transform(CL_THING* pThing);

	//�{���ύX
	void SetScall(D3DXVECTOR3 _scall ){ vecScall = _scall; }

	//	�r���{�[�h�`�揈��
	void BillboardingTransform(CL_THING* pThing);

	//	���_�擾
	void GetMeshVertex();

		
	//	���f���̒��_���W�̃��[���h���W�ϊ�(test)
	//	���f���̉�]�x�Frx,ry,rz
	//	���f���̊g�k�Fsx,sy,sz
	//	���f���̊�_(�e)�Fpx,py,pz
	//	���f���̒��_(�q)�Fl_v_px,l_v_py,l_v_pz
	D3DXVECTOR3 LocalToWarldTransform( float rx, float ry, float rz,
								float sx, float sy, float sz,
								float px, float py, float pz,
								float l_v_px, float l_v_py, float l_v_pz );

	//	���
	virtual void FreeMesh() = 0;
};
#endif

//------------------------------------------------------------------
//	�X�N���[�����W�����[���h���W�ɕϊ�����
//	�����	12/12	
//------------------------------------------------------------------

//	�X�N���[�����W��XZ���ʂ̃��[���h���W��_�Z�o
//	XZ���ʂƃX�N���[�����W�̌�_�Z�o�֐�
D3DXVECTOR3* CalcScreenToXZ
(
	D3DXVECTOR3* pout,
	int Sx,				//	�X�N���[�����W��
	int Sy,				//	�X�N���[�����W��
	int Screen_w,		//	�X�N���[���̉���
	int Screen_h,		//	�X�N���[���̏c��
	D3DXMATRIXA16* View,//	�r���[�s��
	D3DXMATRIXA16* Prj	//	�ˉe�ϊ��s��
);

//	�X�N���[�����W�����[���h���W�ɕϊ�
// �X�N���[�����W�����[���h���W�ɕϊ�
D3DXVECTOR3* CalcScreenToWorld
(
   D3DXVECTOR3* pout,	
   int Sx,				//	�X�N���[�����W����
   int Sy,				//	�X�N���[�����W����
   float fZ,			//	�ˉe��Ԃł�Z�l�i0�`1�j
   int Screen_w,		//	�X�N���[���̉���
   int Screen_h,		//	�X�N���[���̏c��
   D3DXMATRIXA16* View,	//	�r���[�s��
   D3DXMATRIXA16* Prj		//	�ˉe�ϊ��s��
);

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// �w�肵���x�N�g���֌�������s��Z�o�֐�
D3DXMATRIX* CalcLookAtMatrix(
   D3DXMATRIX* pout,
   D3DXVECTOR3* pPos,
   D3DXVECTOR3* pLook,
   D3DXVECTOR3* pUp);

//	Y����]�s��
D3DXVECTOR3	RotateYMatrix( D3DXVECTOR3* , float _y );

float GetVectorLength( D3DXVECTOR3 _v );

#endif