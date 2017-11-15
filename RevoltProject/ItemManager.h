#pragma once

class cItem;
class cContactUser;
class cImpact;
class cCar;

#define g_pItemManager ItemManager::GetInstance()

struct ST_PHYSX
{
	cPhysX* pPhysX;
	cPhysX* pTrigger;
	cMesh* pMesh;
	NxVec3 pos;

	~ST_PHYSX()
	{
		pPhysX->Destroy();
		SAFE_DELETE(pPhysX);
		pTrigger->Destroy();
		SAFE_DELETE(pTrigger);
		pMesh->Destroy();
		SAFE_DELETE(pMesh);
	}
};

struct ST_USERDATA
{
	int id;
	int events;
};

enum eITEM_LIST{ 
	ITEM_NONE, 
	ITEM_WBOMB,
	ITEM_FIREWORK,
	ITEM_GRAVITY,
	ITEM_MYBOMB,
	ITEM_FAKEBOMB,
	ITEM_LAST
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
//	std::map<eITEM_LIST, std::vector<cItem*>>	m_mapItem;
	int m_max;
	int m_index;
	int m_vecIndex[4];
	eITEM_LIST m_eItemList;

public:
	SINGLETONE(ItemManager);

	void Init();
	void Update();
	void Render();

	void SetFire(D3DXVECTOR3 angle, D3DXVECTOR3 pos);
	void SetActorGroup(NxActor* actor, NxCollisionGroup group);
	void InitCollisionGroup();
	void FireItem(eITEM_LIST tag/*����������*/,cCar* car/*�ڵ��� ������*/);

	int GetItemID();
	void SetItemID(eITEM_LIST e) { m_eItemList = e; };
	void Destroy();
};

