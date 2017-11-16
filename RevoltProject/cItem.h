#pragma once

#include "Object.h"
class cCar;

class cItem : public Object
{
protected:
	eITEM_LIST m_eTag;

	int m_id;				// ������ ���̵�
	int m_fTime;			// ������ �ð�
	USERDATA*	m_pUser;	// ���� ������
	ST_PHYSX*	m_pPhysX;	// �������� ����

	SYNTHESIZE(bool, m_isEnd, IsEnd);		// ȿ���� ��������
	SYNTHESIZE(bool, m_isUse, IsUse);		// ��� ������ ���������� Ȯ��
	SYNTHESIZE(bool, m_isInit, IsInit);		// �ʱ�ȭ ���� ������ Ȯ��
	SYNTHESIZE(cCar*, m_pCar, Car);
	SYNTHESIZE(bool, m_isFw, IsFw);
	SYNTHESIZE(D3DXVECTOR3, m_Target, Target);
public:
	cItem();
	virtual ~cItem();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	virtual void Destroy();

	void SetActorGroup(NxActor * actor, NxCollisionGroup group);
	void SetItemTag(eITEM_LIST tag) { m_eTag = tag; }
};

