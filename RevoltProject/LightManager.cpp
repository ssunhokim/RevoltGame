#include "stdafx.h"
#include "LightManager.h"
#include "cLight.h"

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
}

void LightManager::Setup()
{
}

void LightManager::Update()
{
}

void LightManager::Destroy()
{
	for each(auto p in m_mapLight)
	{
		p.second->Destroy();
		delete(p.second);
	}
	m_mapLight.clear();
}

void LightManager::AddLight(int index, cLight * light)
{
	
	if (m_mapLight.find(index) == m_mapLight.end())
	{
		//Ű���� �ߺ����� ������ ����Ѵ�.
		m_mapLight.insert(std::make_pair(index, light));
	}
	else
	{
		//Ű���� �ߺ��Ǹ� ����� ����Ѵ�.
		m_mapLight[index]->Destroy();
		delete(m_mapLight[index]);
		m_mapLight.erase(index);

		m_mapLight.insert(std::make_pair(index, light));
	}
}

void LightManager::DeleteLight(int index)
{
	//ã�� Ű���� ������ �����.
	if (m_mapLight.find(index) != m_mapLight.end())
	{
		m_mapLight[index]->Destroy();
		delete(m_mapLight[index]);
		m_mapLight.erase(index);
	}
}
