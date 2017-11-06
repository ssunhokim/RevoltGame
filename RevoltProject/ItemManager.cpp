#include "stdafx.h"
#include "ItemManager.h"
#include "cItem.h"
#include "ObjectLoader.h"
#include "cImpact.h"
#include "cGravityball.h"
#include "cWbomb.h"
#include "cCar.h"

ItemManager::ItemManager()
	: box1(NULL)
	, box2(NULL)
	, box3(NULL)
	, m_max(50)
	, m_index(0)
{
}

ItemManager::~ItemManager()
{
}

void ItemManager::Init()
{
	MgrPhysXScene->setUserTriggerReport(new TriggerCallback());

	USERDATA* user1 = new USERDATA;
	user1->USER_TAG = E_PHYSX_TAG_NONE;

	box1 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(6, 0, 5), NULL, NxVec3(3.0f, 3.0f, 3.0f), E_PHYSX_MATERIAL_CAR, user1);
	box2 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(5, 0, 0), NULL, NxVec3(3.0f, 3.0f, 3.0f), E_PHYSX_MATERIAL_CAR, user1);
	box3 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(4, 0, 3), NULL, NxVec3(1.0f, 1.0f, 1.0f), E_PHYSX_MATERIAL_CAR, user1);
	box4 = MgrPhysX->CreateActor(NX_SHAPE_BOX, NxVec3(20, 0, 3), NULL, NxVec3(1.0f, 1.0f, 1.0f), E_PHYSX_MATERIAL_CAR, user1);

	m_vecItem.resize(20);

	for (int i = 0;i < 10;i++)
	{
		cItem* pItem = new cWbomb;
		pItem->Setup();
		pItem->SetItemTag(ITEM_WBOMB);
		m_vecItem.push_back(pItem);
	}

	for (int i = 0;i < 10;i++)
	{
		cItem* pItem = new cGravityball;
		pItem->Setup();
		pItem->SetIsUse(false);
		m_vecItem.push_back(pItem);
	}

	InitCollisionGroup();
}

void ItemManager::Update()
{
	for (int i = 0;i < m_index;++i)
	{
		m_vecItem[i]->Update();
	}
	for (int i = 0;i < m_index;++i)
	{
		m_vecItem[i]->LastUpdate();
	}
}

void ItemManager::Render()
{
	for (int i = 0;i < m_index;++i)
	{
		m_vecItem[i]->Render();
	}
}

void ItemManager::SetFire(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{
}

void ItemManager::SetActorGroup(NxActor * actor, NxCollisionGroup group)
{
	NxU32 nbShapes = actor->getNbShapes();
	NxShape** shapes = (NxShape**)actor->getShapes();

	while (nbShapes--)
	{
		shapes[nbShapes]->setGroup(group);
	}
}

void ItemManager::InitCollisionGroup()
{
	SetActorGroup(box1, 1);
	SetActorGroup(box2, 1);
	SetActorGroup(box3, 1);
	SetActorGroup(box4, 1);

	MgrPhysXScene->setGroupCollisionFlag(1, 2, false);
	MgrPhysXScene->setGroupCollisionFlag(2, 2, false);
}

void ItemManager::FireItem(eITEM_LIST tag/*아이템종류*/, cCar* car/*자동차 포인터*/)
{
	D3DXVECTOR3 carPos = car->GetPosition(); // 자동차 위치
	D3DXMATRIXA16 matR;
	D3DXMatrixIdentity(&matR);
	matR = car->GetCarRotMatrix();
	D3DXVECTOR3 carDir = { 1,0,0 }; // 자동차 정면 방향벡터
	D3DXVec3TransformNormal(&carDir, &carDir, &matR);
	
	if (m_index == m_vecItem.size())
		m_index = 0;

	switch (tag)
	{
		case ITEM_WBOMB:
		{
			m_vecItem[m_index]->Create(carDir, carPos);
			m_vecItem[m_index]->SetIsUse(true);
		}
		break;
		case ITEM_FIREWORK:
		{

		}
		break;
		case ITEM_GRAVITY:
		{
			m_vecItem[m_index + 10]->Create(carDir, carPos);
			m_vecItem[m_index + 10]->SetIsUse(true);
		}
		break;
		default: break;
	}

	m_index++;

	if (m_index == 10)
		m_index = 0;
}
