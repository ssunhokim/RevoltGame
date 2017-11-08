#pragma once
#include "cAI.h"
class cAI_CtrlSpeed :
	public cAI
{
private:
//	cPhysX* pCollider;

	NxRaycastHit* rayHitFront;
	NxRaycastHit* rayHitBack;

	float frontPointPrev;
	float frontPointCurr;
	float frontDelta;

	float backPointPrev;
	float backPointCurr;
	float backDelta;

	bool goFront;
	bool goback;


	const float AI_distance = 5;		//�������� 
	const float AI_value = 0.2f;		//delta �� ��������
	const float AI_distanceMin = 2.f;	//������ �����Ϸ��� �Ÿ�
public:
	cAI_CtrlSpeed();
	~cAI_CtrlSpeed();

	void Update();
};

