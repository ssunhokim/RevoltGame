#pragma once
#include "Object.h"
#include "Thing.h"

class cTrack :
	public Object
{
public:
	cTrack();
	~cTrack();
public:
	LPD3DXMESH				m_pObjMesh;		// ���� �޽��� �����ϴ� ��� ����
	std::vector<MtlTex*>	m_vecObjMtlTex;	// ������Ʈ�� ���͸��� �����ϴ� ��� ����
	std::vector<Thing*>		m_vecThing;		// ������Ʈ�� �����ϱ� ���� ���� ����
	std::vector<Object*>	m_vecObject;


	void Update()
	{

		for (int i = 0; i < m_vecThing.size(); i++)
		{
			m_vecThing[i]->Update();
		}

		for each(Object* pObj in m_vecObject)
		{
			pObj->Update();
		}
	}

};

