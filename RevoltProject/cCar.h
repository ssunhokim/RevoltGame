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
	NxVehicle* m_carNxVehicle;

	float m_moterPower;		//
	float m_maxMoterPower;	//
	float m_moterAcc;		//

//	float m_breakPower;		// ���� ���� ������ �ڵ����� �ɸ��� �Ѵ�.

	float m_wheelAngle;		//������ ���� ����. (���)
	float m_maxWheelAngle;	//������ ���̴� �ִ밪.
	float m_wheelAcc;		//���̴� �ӵ�	(������ �������� ��)

public:
	cCar();
	~cCar();

	void SetCarValue(float moterPower, float moterAcc, float breakPower, float WheelAngle, float m_wheelAcc);
	void CreatePhsyX();
	void LoadMesh(std::string carName);
	
	void Update();
	void LastUpdate();
	void Render();
	void Destory();

};

