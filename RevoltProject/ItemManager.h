#pragma once

class cItem;
class cContactUser;
class cImpact;

#define g_pItemManager ItemManager::GetInstance()

struct ST_PHYSX
{
	cPhysX* pPhysX;
	cPhysX* pTrigger;
	cMesh* pMesh;
	NxVec3 pos;
};

struct ST_USERDATA
{
	int id;
	int events;
};

enum ITEM_LIST{ WBOMEB=3001, FIREWORK, GRAVITY, ITEMLAST};

//===================================================================
// - written by �輱ȣ
// - ###������ �������� �����ִ� ������ �Ŵ���###
// - ��� �����۵��� ���⼭ ��������ش�
//===================================================================

class ItemManager
{
private:
	std::vector<cItem*> m_vecItem;				// �����۵��� �����ϴ� Ŭ����
	std::map<ITEM_LIST, std::vector<cItem*>>	m_mapItem;
	int m_max;
	int m_index;

	NxActor* box1;
	NxActor* box2;
	NxActor* box3;
	NxActor* box4;

public:
	SINGLETONE(ItemManager);

	void Init();
	void Update();
	void Render();

	void SetFire(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	void SetActorGroup(NxActor* actor, NxCollisionGroup group);
	void InitCollisionGroup();
};

