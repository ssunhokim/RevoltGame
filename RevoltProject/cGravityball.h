#pragma once
#include "cItem.h"

#define UPDATETIME 200

class GravityBallImpact;
class cPlasmaImpact;

class cGravityball : public cItem
{
private:
	std::vector<GravityBallImpact*> m_vecImpact;			// ����Ʈ�� �����ϴ� Ŭ����
	cPlasmaImpact* m_pPlasma;
	int m_impactIndex;								// ����Ʈ ���� �ε���
	bool m_isSleep;
public:
	cGravityball();
	virtual ~cGravityball();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	void MoveActorOnPath();
};

