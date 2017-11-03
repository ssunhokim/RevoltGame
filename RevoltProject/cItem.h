#pragma once

#include "Object.h"

class cItem : public Object
{
protected:
	int m_id;				// ������ ���̵�
	int m_fTime;			// ������ �ð�
	USERDATA*	m_pUser;	// ���� ������
	ST_PHYSX*	m_pPhysX;	// �������� ����
public:
	cItem();
	virtual ~cItem();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);

	SYNTHESIZE(bool, m_isUse, Use);		// ��� ������ ���������� Ȯ��
	SYNTHESIZE(bool, m_isInit, IsInit);	// �ʱ�ȭ ���� ������ Ȯ��
	void SetActorGroup(NxActor * actor, NxCollisionGroup group);
};

