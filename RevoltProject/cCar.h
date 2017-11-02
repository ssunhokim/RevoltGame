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

	std::vector<Object*> vecWheels;

	float m_moterPower;		// ���� ���� �Ŀ� 0~1 ������
	float m_maxMoterPower;	// �ִ� �Ŀ���
	float m_moterAcc;		// ���� 0~1

	float m_maxRpm;
	float m_breakPower;		// ���� ���� ������ �ڵ����� �ɸ��� �Ѵ�.

	float m_wheelAngle;		//������ ���� ����. (���) 
	float m_maxWheelAngle;	//������ ���̴� �ִ밪. 
	float m_wheelAcc;		//���̴� �ӵ�	(������ �������� ��)


public:
	cCar();
	~cCar();

	void SetNxVehicle(NxVehicle* pVehicle) { m_carNxVehicle = pVehicle; }
	NxVehicle* GetNxVehicle() { return m_carNxVehicle; }

	void SetCarValue(float maxRpm, float moterPower, float moterAcc, float breakPower, float wheelAngle, float wheelAcc);
	void CreatePhsyX();
	void LoadMesh(std::string carName);

	void Update();
	void LastUpdate();
	void Render();
	void Destory();

};

