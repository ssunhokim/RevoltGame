#pragma once
#include "cAI.h"
class cAI_CtrlSpeed :
	public cAI
{
private:
	//	cPhysX* pCollider;

	NxRaycastHit* rayHitFront;
	NxRaycastHit* rayHitBack;

	float frontDistPrev;
	float frontDistCurr;
	float frontDelta;

	float backDistPrev;
	float backDistCurr;
	float backDelta;


	enum AISpeedState { E_SpeedStateFront, E_SpeedStateBack };
	AISpeedState aiState;


	float AI_distanceFront;// = 5;		//�������� 
	float AI_distanceBack;// = 3;		//�������� 
	float AI_value;// = 0.2f;		//delta �� ��������
	float AI_distanceMin;// = 2.f;	//������ �����Ϸ��� �Ÿ�


public:
	cAI_CtrlSpeed();
	~cAI_CtrlSpeed();

	void Update();
};

