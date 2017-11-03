#pragma once
#include "Object.h"
#include "Thing.h"
#include "Camera.h"

#include "cCar.h"

typedef std::map<std::string, Object*> MAP_STR_OBJ;
typedef std::map<std::string, Object*>::iterator MAP_STR_OBJ_iter;

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
	SYNTHESIZE(std::vector<Object*>, m_vecObject, Object);
	//std::vector<Object*>	m_vecObject;
	//�㿡 �ִ� üũ�ڽ�
	//std::map<std::string, Object*>	m_mapCheckBox;

	SYNTHESIZE(MAP_STR_OBJ, m_mapCheckBox, CheckBoxs);
	MAP_STR_OBJ* GetCheckBoxsPt() { return  &m_mapCheckBox; }
	//NxVehicle* pVeh;

	void Update();
	void LastUpdate();
	void Render();

	void SetData();
	void LoadTrack(std::string FileName);
	void CreateTrackPhysX();

	int GetTrackCheckBoxSize() { return m_mapCheckBox.size(); }



	void TEST()
	{
		
	}
};

