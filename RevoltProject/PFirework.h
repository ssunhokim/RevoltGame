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
	PFirework(int numParticles);

	virtual void SetPosition(D3DXVECTOR3* origin) { _origin = *origin; }
	virtual void ResetParticle(ST_Attribute* attribute);
	virtual void Update(float timeDelta);
	virtual void PreRender();
	virtual void PostRender();
};

