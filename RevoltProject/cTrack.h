#pragma once
#include "Object.h"
#include "Thing.h"
#include "Camera.h"

class cTrack : public Object
{
public:
	cTrack();
	~cTrack();
public:
	int trackNum = 0;
	std::string trackName;

	int m_nLightIdx;

	//�ΰ��� �� �� ��ֹ� ���
	std::vector<Object*>	m_vecObject;

	void Update();
	void LastUpdate();
	void Render();

	void LoadTrack(std::string FileName);
	void CreateTrackPhysX();
};

