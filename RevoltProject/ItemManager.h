#pragma once

class cItem;
class cContactUser;
class cImpact;

#define g_pItemManager ItemManager::GetInstance()

struct ST_PHYSX
{
	cPhysX* pPhysX;
	cPhysX* pTrigger;
	NxVec3 pos;
};

struct ST_USERDATA
{
	int id;
	int events;
};

//===================================================================
// - written by �輱ȣ
// - ###������ �������� �����ִ� ������ �Ŵ���###
// - ��� �����۵��� ���⼭ ��������ش�
//===================================================================

class ItemManager
{
private:
	std::vector<cItem*> m_vecItem;				// �����۵��� �����ϴ� Ŭ����

	NxActor* box1;
	NxActor* box2;
	NxActor* box3;

public:
	SINGLETONE(ItemManager);

	void Init();
	void Update();
	void Render();

	void SetActorGroup(NxActor* actor, NxCollisionGroup group);
	void InitCollisionGroup();

	void MoveActorOnPath(NxActor* actor, int index);
};

