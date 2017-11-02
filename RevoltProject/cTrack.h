#pragma once
#include "Object.h"
#include "Thing.h"
#include "Camera.h"

#include "cCar.h"


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
	//�㿡 �ִ� üũ�ڽ�
	std::map<std::string, Object*>	m_mapCheckkBox;
	//NxVehicle* pVeh;

	void Update();
	void LastUpdate();
	void Render();

	void SetData();
	void LoadTrack(std::string FileName);
	void CreateTrackPhysX();

	int GetTrackCheckBox() { return m_mapCheckkBox.size(); }
};

