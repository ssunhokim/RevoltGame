#pragma once
#include "Object.h"

class cWheel;
enum cWheel_ID
{
	fl,	//�ڵ��� ��Ƣ ��ġ
	fr,	//
	bl,	//
	br,	//
};

class cCar :public Object
{
	std::vector<cWheel*> mapWheels;

public:
	cCar();
	~cCar();

	void RegisteWheel(cWheel_ID id, cWheel* pWheel);
	void LoadMesh(std::string carName);
};

