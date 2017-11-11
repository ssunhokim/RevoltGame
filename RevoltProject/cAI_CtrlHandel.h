#pragma once
#include "cAI.h"
class cAI_CtrlHandel :
	public cAI
{
public:

	float LRF_F_RateValue;
	float LRF_D_RateVAlue;
	float LR__F_RateValue;
	float LR__D_RateVAlue;

	// ~ -1 ~ 0 ~ 1 ~
	float HandleValue;
	
	//CheckBoxPoint() �ּ� �ѹ��� ������ üũ�� üũ�ڽ��� �� (1~3) �� ���� ���� (return 0)
	int FindDirNum;

	//�ڵ� üũ�� ���е�
	float HandleDistance;

	//üũ�ڽ� ��ġ�� �����ϱ� ���� ����

	D3DXVECTOR3 BoxDir;
	D3DXVECTOR3 RealDir;

	bool isPoint;


	cAI_CtrlHandel(AI_DATA pData);
	~cAI_CtrlHandel();

	void Update();
	void Render();

	//ray �Ÿ��� ���� ������

	float CheckBoxPoint(D3DXVECTOR3 dir );
	float CheckBoxPoint(NxVec3 dir );
};

