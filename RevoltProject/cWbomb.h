#pragma once

#include "cItem.h"

class cWbomb : public cItem
{
private:
	std::vector<ST_PHYSX*>	m_vecPhysX;		// ������ �������� ����
public:
	cWbomb();
	virtual ~cWbomb();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Create();
};

