#include "stdafx.h"
#include "cAI.h"
#include "cCar.h"
#include "cCheckBox.h"
#include "cTrack.h"


#include "cAI_CtrlHandel.h"
#include "cAI_CtrlSpeed.h"
#include "cAI_CtrlFlip.h"

AI_DATA::AI_DATA(cCar* pCar, cTrack* pTrack, std::vector<cCar*>* pCars)
{
	if (pCar)
			this->pCar = pCar;
	if (pTrack)
		this->pTrack = pTrack;
	if (pCars)
		this->pCars = pCars;
}

//

cAI::cAI()
{
	AI_Data = NULL;
	familyAI = NULL;
	AI_Mesh = NULL;
}


cAI::~cAI()
{
}

void cAI::Setup()
{
}

void cAI::Destory()
{
	if (AI_Mesh) AI_Mesh->Release();
	if(AI_Data) AI_Data->Destory();

	AI_Mesh = NULL;
	
	//�Ʒ� �ΰ����� �ܺ� ���� �޾ƿ��� ������ Delete�� �ʿ� ����.
	// ���� �������(NULL)
	AI_Data = NULL;
	familyAI = NULL;
}

void cAI::Update()
{
}

void cAI::Render()
{
}

cCheckBox * cAI::CurrentCheckBox()
{
	return (cCheckBox*)(*(AI_Data->pTrack)->GetCheckBoxsPt())[AI_Data->pCar->GetAICheckBoxID()];
}

float cAI::ScaleValue(float value, float Total, float multiValue)
{
	float rate = (value * multiValue / Total);
//	rate = fmin(rate, 1.0f);
//	rate = fmax(rate, -1.0f);
	return rate;
}

float cAI::GetRpmRate()
{
	return AI_Data->pCar->GetRpmRate();
}