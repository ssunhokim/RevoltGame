#pragma once
#include "cAI.h"
class cAI_CtrlSpeed :
	public cAI
{
public:

	float F___DistRange;		//�������� 
	float B___DistRange;		//�������� 

	float Min_DistRange;		//������ �����Ϸ��� �Ÿ�
	float Min_LRDistRange;		
	//AISpeedState aiState;
	float SpeedValue;

	bool isBack;

	float BackTime;
	float ReposTime;

	bool isRepos;

public:
	cAI_CtrlSpeed(AI_DATA pData);
	~cAI_CtrlSpeed();

	void Update();
};

