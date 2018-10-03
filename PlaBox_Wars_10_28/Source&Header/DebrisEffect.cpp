#include "DebrisEffect.h"
#include <math.h>

//	�j�ЃG�t�F�N�g�̃R���X�g���N�^
CDebrisEffect::CDebrisEffect( D3DXVECTOR3 _pos, D3DXVECTOR3 _vec, 
	eTEXTURE _textureNum ) : CEffect( _pos, _vec, _textureNum )
{
	ParticleInstance();
}

//	�p�[�e�B�N���I�u�W�F�N�g�̃C���X�^���X
void CDebrisEffect::ParticleInstance()
{
	for( int i = 0; i < _DEBRIS_PARTICLE_VOL_; i++ )
		parVertex.push_back( new CParticle( GetVec(VEC3_POS), GetVec(VEC3_VEC) ));
}

//	�p�[�e�B�N���ŗL�̏���
bool CDebrisEffect::ParticleControl()
{
	int arrayIndex = parVertex.size();
	for( int i = 0; i < arrayIndex; i++ )
	{
		parVertex[i]->m_rot.x = rand()%5;
		parVertex[i]->m_rot.y = rand()%5;
		parVertex[i]->m_rot.z = rand()%5;
		parVertex[i]->m_pos.x -= parVertex[i]->m_vec.x / (rand()%5-2);
		parVertex[i]->m_pos.y += (rand()%5-2)/10;
		parVertex[i]->m_pos.z -= parVertex[i]->m_vec.z / (rand()%5-2);
		parVertex[i]->m_alpha--;
		if( parVertex[i]->m_alpha < 100 )
		{
			return false;
		}
	}
	

	return true;
}

