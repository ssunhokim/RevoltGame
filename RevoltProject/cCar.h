#pragma once
#include "Object.h"

class cAI;
class TriggerCallback;
class cTrack;

struct stCARSPEC
{
	std::vector<NxBoxShapeDesc> vecBoxDesc;
	std::vector<D3DXVECTOR3> vecWheelPos;
};

class cCar : public Object
{
	//�ڵ��� �ɷ�ġ ����
	NxVehicle* m_carNxVehicle;

	std::vector<cMesh*> vecWheels;

	float m_moterPower;		// ���� ���� �Ŀ� 0~1 ������
	float m_maxMoterPower;	// �ִ� �Ŀ���
	float m_moterAcc;		// ���� 0~1

	float m_maxRpm;
	float m_breakPower;		// ���� ���� ������ �ڵ����� �ɸ��� �Ѵ�.

	float m_wheelAngle;		//������ ���� ����. (���) 
	float m_maxWheelAngle;	//������ ���̴� �ִ밪. 
	float m_wheelAcc;		//���̴� �ӵ�	(������ �������� ��)

	SYNTHESIZE(float, m_fCurrentSpeed, CurrentSpeed);
	D3DXVECTOR3 m_szPrevPos[5];

	//�ڵ��� ������?
	bool isFliping;

	//AI
	std::vector<cAI*> m_vecAI;
	bool m_isAI = false;

	//track ����
	bool m_trackOn = true;
	SYNTHESIZE(int, totalCheckBoxNum, TotalCheckBoxNum);
	SYNTHESIZE(int, countCheckBox, CountCheckBox);
	SYNTHESIZE(int, countTrack,CountTrackRun);
	
	SYNTHESIZE(float, m_rapTimeCount, RapTimeCount);
	SYNTHESIZE(float, m_totlaTimeCount, TotlaTimeCount);

	//Item ����
	SYNTHESIZE(eITEM_LIST, m_eHoldItem, HoldItem);
	SYNTHESIZE(int, m_nItemCount, ItemCount);
	
	int countCheckTrack;

	cTrack* m_pTrack;

public:
	cCar();
	~cCar();

	void SetNxVehicle(NxVehicle* pVehicle) { m_carNxVehicle = pVehicle; }
	NxVehicle* GetNxVehicle() { return m_carNxVehicle; }

	void LoadCar(std::string carName);
	void SetCarValue(float maxRpm, float moterPower, float moterAcc, float breakPower, float wheelAngle, float wheelAcc , bool isAI = false);
	
	void CreateItem();

	void CreatePhsyX(stCARSPEC carspec);
	void LoadMesh(std::string carName);
	void LoadWheel(std::string carName);

	void Update();
	void LastUpdate();
	void Render();
	void Destory();


	void CtrlPlayer();
	void CtrlAI();

	void GetRpm();
	void TrackCheck();
	void RunEnd();
	void CarFlip();
	void CarRunStop();
	void LinkTrackPt(cTrack* track) { m_pTrack = track; }
//	void RunStart();

};