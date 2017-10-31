#pragma once
#include "Object.h"

class cWheel;
enum cWheel_ID
{
	fl,	//�ڵ��� ���� ��ġ
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

	void SetNxVehicle(NxVehicle* pVehicle) { m_carNxVehicle = pVehicle; }
	NxVehicle* GetNxVehicle() { return m_carNxVehicle; }

	void SetCarValue(float moterPower, float moterAcc, float breakPower, float WheelAngle, float m_wheelAcc);
	void CreatePhsyX();
	void LoadMesh(std::string carName);

	void Update();
	void LastUpdate();
	void Render();
	void Destory();

};

