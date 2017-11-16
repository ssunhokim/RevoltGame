#pragma once
#include "cAI.h"

class cPickUp;

class cAI_CtrlCompete :
	public cAI
{
public:
	D3DXVECTOR3 POS_ITEMPOS;
	D3DXVECTOR3 POS_THISPOSDIR;
	D3DXVECTOR3 POS_CARPOSDIR;

	float maxDistance;
	
	cPickUp* closePickup;
	float HandleValue;


	float PickupAngle;

	float PickupValue;
	float CarsValue;

	//�ٸ����� �����Ϸ��� ��ġ��
	//���� ���� �������� ������ ���ų� 
	//�ٸ� ���� ������ ������ �Ѵ�.
	//0~1;
	float Competitive;


	cAI_CtrlCompete();
	~cAI_CtrlCompete();

	void Update();
	void Render();
};