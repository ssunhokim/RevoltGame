#pragma once

#include "PSystem.h"

//===================================================================
// - written by ������
// - �Ҳɳ��� ��ƼŬ ����Ʈ
//===================================================================


class PFirework : public PSystem
{
public:
	// �ý��� ��õ(������ ���)������ ������, �ý����� ���� ��ƼŬ�� ��
	PFirework(D3DXVECTOR3* origin, int numParticles);
	virtual void ResetParticle(ST_Attribute* attribute);
	virtual void Update(float timeDelta);
	virtual void PreRender();
	virtual void PostRender();
};

