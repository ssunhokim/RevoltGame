#pragma once
#include "Object.h"
#include "Thing.h"

class cTrack : public Object
{
public:
	cTrack();
	~cTrack();
public:
	int trackNum = 0;
	//�ΰ��� �� �� ��ֹ� ���
	//�ΰ��� �� �� ��ֹ� ���
	std::vector<Object*>	m_vecObject;

	void Update();
	void Render();
};

