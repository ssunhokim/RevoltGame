#pragma once

#define UPDATETIME 300

class cMybombImapct;

#include "cItem.h"

class cMyBomb : public cItem
{
private:
	cMybombImapct* m_pImpact;	// ����Ʈ ����
	bool m_isSleep;		// �浹�� ���� üũ
public:
	cMyBomb();
	virtual ~cMyBomb();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	void MoveActorOnPath();
};

