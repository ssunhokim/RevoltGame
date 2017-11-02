#pragma once
#include "cItem.h"

class cGravityball : public cItem
{
private:
	std::vector<cImpact*> m_vecImpact;			// ����Ʈ�� �����ϴ� Ŭ����
	std::vector<ST_PHYSX*>	m_vecPhysX;		// ������ �������� ����
	int m_impactIndex;								// ����Ʈ ���� �ε���
public:
	cGravityball();
	virtual ~cGravityball();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	void MoveActorOnPath(NxActor* actor, int index);
};

