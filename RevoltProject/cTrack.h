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

	//�ΰ��� �� �� ��ֹ� ���
	std::vector<Object*>	m_vecObject;
	Camera* pCamera;

	void Update();
	void LastUpdate();
	void Render();

	void LoadTrack(std::string FileName , Camera* pCam);
	void CreateTrackPhysX();
};

