#include "HitCheck.h"
#include "graphic.h"
#include "main.h"
#include <cstdio>
#include <vector>
#include <math.h>

//	HRESULT InitBBox(LPDIRECT3DDEVICE9 pDevice,THING* pThing)
//	�����蔻��p�̃{�b�N�X�����
HRESULT InitBBox ( CL_THING* pThing )
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	VOID* pVertices = NULL;
	D3DXVECTOR3 vecMax, vecMin;


	//	���b�V���̒��_�o�b�t�@�[�����b�N
	if ( FAILED ( pThing -> pMesh -> GetVertexBuffer ( &pVB ) ) )
	{
		return E_FAIL;
	}
	if ( FAILED ( pVB -> Lock ( 0, 0, &pVertices, 0 ) ) )
	{
		SAFE_RELEASE ( pVB );
		return E_FAIL;
	}

	//	���b�V���̊O�ډ~�̒��S�Ɣ��a���v�Z���Ă����
	hr = D3DXComputeBoundingBox ( (D3DXVECTOR3*) pVertices, pThing -> pMesh -> GetNumVertices(),
								D3DXGetFVFVertexSize ( pThing -> pMesh ->GetFVF ()), &vecMin, &vecMax );
	pVB -> Unlock();
	SAFE_RELEASE ( pVB );

	if ( FAILED ( hr ))
	{
		return hr;
	}
	pThing -> BBox.vecMax = vecMax;
	pThing -> BBox.vecMin = vecMin;

	//	���ŏo�����S�Ɣ��a���烁�b�V���Ƃ��Ẵ{�b�N�X����낤
	hr = D3DXCreateBox ( pD3Device, vecMax.x * 2, vecMax.y * 2, vecMax.z * 2, &pThing -> BBox.pBBoxMesh, NULL );
	
	if ( FAILED ( hr ) )
	{
		return hr;
	}
	//�{�b�N�X���b�V���̃}�e���A���@���F�A�������A����
	pThing -> BBox.pBBoxMeshMaterials = new D3DMATERIAL9;
	pThing -> BBox.pBBoxMeshMaterials -> Diffuse.r = 1.0f;
	pThing -> BBox.pBBoxMeshMaterials -> Diffuse.g = 1.0f;
	pThing -> BBox.pBBoxMeshMaterials -> Diffuse.b = 1.0f;	
	pThing -> BBox.pBBoxMeshMaterials -> Diffuse.a = 0.5f;
	pThing -> BBox.pBBoxMeshMaterials -> Ambient = pThing -> BBox.pBBoxMeshMaterials -> Diffuse;	
	pThing -> BBox.pBBoxMeshMaterials -> Specular.r = 1.0f;
	pThing -> BBox.pBBoxMeshMaterials -> Specular.g = 1.0f;
	pThing -> BBox.pBBoxMeshMaterials -> Specular.b = 1.0f;
	pThing -> BBox.pBBoxMeshMaterials -> Emissive.r = 0.1f;
	pThing -> BBox.pBBoxMeshMaterials -> Emissive.g = 0.1f;
	pThing -> BBox.pBBoxMeshMaterials -> Emissive.b = 0.1f;
	pThing -> BBox.pBBoxMeshMaterials -> Power = 120.0f;	

	return S_OK;
}

//	BOOL Impact ( THING* pBullet, THING* pTarget )
//	�Փ˔���������蔻��
BOOL Impact ( CL_THING* pBullet, CL_THING* pTarget )
{
	//	�^�[�Q�b�g(�Gor���@)�p��2�̒��_��p�ӂ��ď�����
	D3DXVECTOR3 vecMaxTage, vecMinTage;
	vecMaxTage = pTarget -> BBox.vecMax	+ pTarget -> vecPosition;
	vecMinTage = pTarget -> BBox.vecMin + pTarget -> vecPosition;

	//	�e�e�̒��S�_���A�^�[�Q�b�g�̃{�����[���������ׂĂ�

	if ( pBullet->vecPosition.x >= vecMinTage.x && pBullet->vecPosition.x <= vecMaxTage.x )
	{
		if( pBullet->vecPosition.y >= vecMinTage.y && pBullet->vecPosition.y <= vecMaxTage.y )
		{
			if( pBullet->vecPosition.z >= vecMinTage.z && pBullet->vecPosition.z <= vecMaxTage.z )
			{
				return TRUE;
			}
		}
	}
		return FALSE;
	
}

//	BOOL Impact ( THING* pBullet, THING* pTarget )
//�@�����m�̏Փ˔���
BOOL BoxImpact ( CL_THING* pA, CL_THING* pB ,int _check)
{
	//����A�p�ɂQ�̒��_��p�ӂ�����������
	D3DXVECTOR3 vecMaxA,vecMinA;
	vecMaxA = pA -> BBox.vecMax + pA -> vecPosition;
	vecMinA = pA -> BBox.vecMin + pA -> vecPosition;
	//����B�p�ɂW�̒��_��p�ӂ�����������
	
	D3DXVECTOR3 vecB[8];
	vecB[0].x = pB -> BBox.vecMin.x;
	vecB[0].y = pB -> BBox.vecMin.y;
	vecB[0].z = pB -> BBox.vecMin.z;
	vecB[1].x = pB -> BBox.vecMax.x;
	vecB[1].y = pB -> BBox.vecMin.y;
	vecB[1].z = pB -> BBox.vecMin.z;
	vecB[2].x = pB -> BBox.vecMin.x;
	vecB[2].y = pB -> BBox.vecMax.y;
	vecB[2].z = pB -> BBox.vecMin.z;
	vecB[3].x = pB -> BBox.vecMin.x;
	vecB[3].y = pB -> BBox.vecMin.y;
	vecB[3].z = pB -> BBox.vecMax.z;
	vecB[4].x = pB -> BBox.vecMax.x;
	vecB[4].y = pB -> BBox.vecMax.y;
	vecB[4].z = pB -> BBox.vecMin.z;
	vecB[5].x = pB -> BBox.vecMax.x;
	vecB[5].y = pB -> BBox.vecMin.y;
	vecB[5].z = pB -> BBox.vecMax.z;
	vecB[6].x = pB -> BBox.vecMin.x;
	vecB[6].y = pB -> BBox.vecMax.y;
	vecB[6].z = pB -> BBox.vecMax.z;
	vecB[7].x = pB -> BBox.vecMax.x;
	vecB[7].y = pB -> BBox.vecMax.y;
	vecB[7].z = pB -> BBox.vecMax.z;

	// ����B�̂W�̒��_�S�Ăɂ��āA����A�̃{�����[�����ł��邩�ǂ������ׂ�
	for(DWORD i=0;i<8;i++)
	{
		vecB[i] += pB -> vecPosition;
		if(vecB[i].x >= vecMinA.x && vecB[i].x <= vecMaxA.x)
		{
			if(vecB[i].y >= vecMinA.y && vecB[i].y <= vecMaxA.y)
			{
				if(vecB[i].z >= vecMinA.z && vecB[i].z <= vecMaxA.z)
				{
					return TRUE;
				}
			}
		}
	}


	if( _check == 0 )
		return BoxImpact(pB,pA,1);
	else if( _check == 1 )
		return FALSE;
	else 
		return FALSE;
}


/**	
*	@brief	�����Ǝl�p�����f���Ƃ̓����蔻��
*/
bool SegmentHitcheck( CL_THING* pA, CL_THING* pB, 
	D3DXVECTOR3* pHitVec, D3DXVECTOR3* pHitNomal, float* pHitFaceSita )
{
	int hitCount = 0;		//	���������ʂ̐�
	D3DXVECTOR3 HitPoint[CHECK_HIT_POINT];//	���e�_
	D3DXVECTOR3	tmpVec[NUM_PRISM_VERTEX];	//	pA�p�̒��_�ϐ�
	float t = 0.f;			//	�����蔻��֐��p�ɕK�v�Ȉ���
	
	//	pA��localVec�����[���h���W�ϊ����āAtmpVec�ɑ��
	for( int i = 0; i < NUM_PRISM_VERTEX; i++ )
	{
		tmpVec[i] = pA->LocalToWarldTransform( pA->vecRotate.x, pA->vecRotate.y, pA->vecRotate.z,
										pA->vecScall.x, pA->vecScall.y, pA->vecScall.z,
										pA->vecPosition.x, pA->vecPosition.y, pA->vecPosition.z,
										pA->localVec[i].x, pA->localVec[i].y, pA->localVec[i].z);
		
	}

	HitRect tmpRect[NUM_PRISM_FACE];		//	tmpVec�����Ɏl�p�����𐶐�	
	HitRect* pHitRect[CHECK_HIT_POINT] = {NULL}; //	�����������肪�������z��̃|�C���^�����Ă���
	
	//	���
	tmpRect[0].a = tmpVec[0]; 
	tmpRect[0].b = tmpVec[2]; 
	tmpRect[0].c = tmpVec[3]; 
	tmpRect[0].d = tmpVec[1];
	//	���
	tmpRect[1].a = tmpVec[4]; 
	tmpRect[1].b = tmpVec[6]; 
	tmpRect[1].c = tmpVec[7]; 
	tmpRect[1].d = tmpVec[5];
	//	���ʁi�������j
	tmpRect[2].a = tmpVec[0]; 
	tmpRect[2].b = tmpVec[4]; 
	tmpRect[2].c = tmpVec[6]; 
	tmpRect[2].d = tmpVec[2];

	tmpRect[3].a = tmpVec[1];
	tmpRect[3].b = tmpVec[3];
	tmpRect[3].c = tmpVec[7];
	tmpRect[3].d = tmpVec[5];
	//	���ʁi�L�����j
	tmpRect[4].a = tmpVec[0]; 
	tmpRect[4].b = tmpVec[1]; 
	tmpRect[4].c = tmpVec[5]; 
	tmpRect[4].d = tmpVec[4];

	tmpRect[5].a = tmpVec[2];
	tmpRect[5].b = tmpVec[6];
	tmpRect[5].c = tmpVec[7];
	tmpRect[5].d = tmpVec[3];
	
	//	6�ʁi����12�ʁj�S�ă`�F�b�N
	//�i���e�ʂ̕��т͔����v�����abcd�ɑ�����Ă���̂Ń��[�v�ł����Ȃ��j
	for( int i = 0; i < NUM_PRISM_FACE; i++ )
	{
		//	��abcd����2�ɕ����Ĕ�������
		//	pB��2�_�Ɓ�abc�̔���
		if( IntersectSegmentTriangle( pB->vecPosition, pB->vecBeforePos, 
			tmpRect[i].a, tmpRect[i].b, tmpRect[i].c,
			HitPoint[hitCount].x, HitPoint[hitCount].y, HitPoint[hitCount].z, t) )
		{
			pHitRect[hitCount] = &tmpRect[i];	//	���������ʂ̍s��|�C���^���m��
			hitCount++;	//	����J�E���^++
		}
		//	pB��2�_�Ɓ�acd�̔���
		else if( IntersectSegmentTriangle( pB->vecPosition, pB->vecBeforePos,
			tmpRect[i].a, tmpRect[i].c, tmpRect[i].d,
			HitPoint[hitCount].x, HitPoint[hitCount].y, HitPoint[hitCount].z, t) )
		{
			pHitRect[hitCount] = &tmpRect[i]; 
			hitCount++;
		}
		

		if( hitCount >= CHECK_HIT_POINT )	//	2�_�ȏ�������鎖�͂قږ����̂Ń��[�v�𔲂���
			break;
	}

	//	�������Ă��Ȃ������̂�false
	if( hitCount == 0 )
	{
		return false;
	}

	//	�\�ʂɓ������Ă����̂ŁApHitVec��pHitFaceSita�ɕK�v�ȏ�������
	*pHitVec = HitPoint[0] - pA->vecPosition;
	D3DXVECTOR3 vecNomal(GetPolygonNormal( pHitRect[0]->a, pHitRect[0]->b, pHitRect[0]->c ));
	D3DXVECTOR3 _vecTemp(0,0,1);
	*pHitNomal = vecNomal;
	float lengthN = GetVectorLength(vecNomal);
	float lengthT = GetVectorLength(_vecTemp);
	float _dot = D3DXVec3Dot(&_vecTemp, &vecNomal);
	float cosSita = _dot/( lengthN * lengthT );
	if(vecNomal.x >= 0)
		*pHitFaceSita = acos(cosSita);
	else
		*pHitFaceSita = -acos(cosSita);
	return true;	
}
/*
	����pq���O�p�`abc�ƌ�_���Ă��邩�ǂ�����n��
	�������Ă���ꍇ�A�����_�̍��W(u,v,w)��Ԃ�
*/
bool IntersectSegmentTriangle( D3DXVECTOR3 p, D3DXVECTOR3 q,
	D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c,
	float &u, float &v, float &w, float &t )
{
	D3DXVECTOR3 ab = b-a;	//	�O�p�`�̕ӂ̃x�N�g�������߂�
	D3DXVECTOR3 ac = c-a;
	D3DXVECTOR3 qp = p-q;	//	�����̃x�N�g�������߂�

	//	�O�p�`�̖@�����v�Z�B�����O�p�`�ɑ΂��ĕ����̐�������������ꍇ��
	//	�\�ߌv�Z���Ă������A���邢�̓L���b�V�����c���Ă������Ƃ��\
	D3DXVECTOR3 n;	//	�O�ڂ̌v�Z����
	D3DXVec3Cross( &n, &ab, &ac );

	//	����d���v�Z�Bd<=0�̏ꍇ�A�����͎O�p�`�ɕ��s�ł��邩�A
	//	���邢�͎O�p�`���痣��Ă����������w���Ă���̂ŁA�����ɏI��
	float d = D3DXVec3Dot( &qp, &n );
	if( d <= 0.0f )	return false;

	//	pq�ƎO�p�`�̕��ʂ̌����̒lt���v�Z
	//	0<=t �̏ꍇ�͌����Ɍ����B������ 0<=t<=1 �̏ꍇ�Ɍ����B
	//	�������O�p�`���ђʂ��邱�Ƃ�������܂�d�ɂ�鏜�Z��x��
	D3DXVECTOR3 ap = p-a;
	t = D3DXVec3Dot( &ap, &n );
	if( t < 0.0f )	return false;
	if( t > d )	return false;	//	�����ɑ΂��āB
							//	�����ɑ΂��锻��ł̓R�[�h�̂��̍s�͏��O

	//	�d�S���W�̐������v�Z���͈͓��ɂ��邩�ǂ�������
	D3DXVECTOR3 e;
	D3DXVec3Cross( &e, &qp, &ap );
	v = D3DXVec3Dot( &ac, &e );
	if( v < 0.0f || v > d )	return false;
	w = -D3DXVec3Dot( &ab, &e );
	if( w < 0.0f || v + w > d )	return false;

	//	����/�����͎O�p�`�ƌ����B�x���������Z�����s��
	//	�Ō�ɏd�S���W�̐������v�Z
	float ood = 1.0f / d;
	t *= ood;
	v *= ood;		//	b�̍��W�l
	w *= ood;		//	c�̍��W�l
	u = 1.0f-v-w;	//	a�̍��W�l

	D3DXVECTOR3 tmpBarycentric(0,0,0);	//	��_�̌v�Z�p
	tmpBarycentric = (a*u)+(b*v)+(c*w);	//	�d�S�l�����Ɍ�_���v�Z
	//	�v�Z���ʂ���
	u = tmpBarycentric.x;	v = tmpBarycentric.y;	w = tmpBarycentric.z;
	return true;
}

/*	�x�N�g��v�ɑ΂��Ē��_abc�|���S�����\���ǂ�������������߂�
	abc�ɂ͕K�������v���̕��тœ���鎖
	�֐�SegmentHitcheck����tmpRect�ł́uabc�v���́uacd�v�̏��ő�����邱��
	�߂�l	0�F��	1�F�\	-1�F�G���[
*/
int PolygonSideCheck( D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c, D3DXVECTOR3 v )
{
	D3DXVECTOR3 ab = b-a;	//	�O�p�`�̕ӂ̃x�N�g�������߂�
	D3DXVECTOR3 bc = c-a;

	D3DXVECTOR3 n(0.f,0.f,0.f);	//	�O�ڂ̌v�Z����
	float t = 0.f;	//	���ڂ̌v�Z����

	//	ab bc�̊O��
	D3DXVec3Cross( &n, &ab, &bc );

	//	v�Ƃ̓���
	t = D3DXVec3Dot( &v, &n );

	if( t < 0.0f )	//�|���S���̓x�N�g��v���猩�ĕ\��
	{
		return 1;
	}
	else if( t > 0.0f )	//�|���S���̓x�N�g��v���猩�ė���
	{
		return 0;
	}

	//	d=0	���s
	return -1;
}

/*
	���_abc����Ȃ�|���S���̖@�����v�Z
*/
D3DXVECTOR3 GetPolygonNormal( D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c )
{
	D3DXVECTOR3 ab = b-a;
	D3DXVECTOR3 bc = c-b;
	D3DXVECTOR3 n;	//	�@��

	D3DXVec3Cross( &n, &ab, &bc );	//	ab bc�̊O��
	D3DXVec3Normalize( &n, &n );	//	n�̒P�ʉ�
	return n;
}