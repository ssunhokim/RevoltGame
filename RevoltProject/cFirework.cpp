#include "stdafx.h"
#include "cFirework.h"
#include "ObjectLoader.h"

cFirework::cFirework()
{
}


cFirework::~cFirework()
{
}

void cFirework::Setup()
{
	cItem::Setup();
}

void cFirework::Update()
{
	cItem::Update();
}

void cFirework::Render()
{
	cItem::Render();

	for (int i = 0; i < m_vecPhysX.size(); ++i)
		m_vecPhysX[i]->pMesh->Render();
}

void cFirework::Create(D3DXVECTOR3 angle, D3DXVECTOR3 pos)
{
	ST_PHYSX* pPhysX = new ST_PHYSX;

	USERDATA* user1 = new USERDATA;
	user1->USER_TAG = ePhysXTag::E_PHYSX_TAG_FIREWORK;

	pPhysX->pos = NxVec3(5, 0, 3);

	pPhysX->pPhysX = new cPhysX;
	pPhysX->pTrigger = new cPhysX;
	pPhysX->pMesh = new cMesh;

	ObjectLoader::LoadMesh(pPhysX->pMesh, "Objects/firework", "firework.obj");

	pPhysX->pPhysX->m_pActor = MgrPhysX->CreateActor(NX_SHAPE_SPHERE, pPhysX->pos, NULL, NxVec3(1.0f, 0.0f, 0.0f),E_PHYSX_MATERIAL_NONE, user1);
	pPhysX->pPhysX->m_pActor->addForce(NxVec3(10000, 7000, 0));


	this->SetPhysXData(pPhysX->pPhysX);

	SetActorGroup(pPhysX->pPhysX->m_pActor, 1);

	m_vecPhysX.push_back(pPhysX);
}