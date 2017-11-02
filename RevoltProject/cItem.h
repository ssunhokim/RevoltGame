#pragma once

#include "Object.h"

class cItem : public Object
{
protected:
	int m_id;					// ������ ���̵�
	float m_fTime;			// ������ �ð�
public:
	cItem();
	virtual ~cItem();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);

	void SetActorGroup(NxActor * actor, NxCollisionGroup group);
};

