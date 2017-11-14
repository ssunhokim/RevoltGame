#pragma once
#include "cItem.h"

#define FIREWORKEFFECT 80

class PSystem;

class cFirework : public cItem
{
private:
	ST_PHYSX* m_pPhysX;
	bool m_isSleep;
	bool m_isTarget;		// Ÿ���� �ִ���
	
	PSystem* m_pEffect;		// ���� ������ ��ƼŬ
	PSystem* m_pTail;		// ���� ���� ��ƼŬ

	D3DXVECTOR3 fwPos;		// ���� �ڽ��� ������
	D3DXVECTOR3 dir;		// ������ ���ư��� ����
public:
	cFirework();
	virtual ~cFirework();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	virtual void Destroy();

};

