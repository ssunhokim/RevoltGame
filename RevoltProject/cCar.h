#pragma once
#include "Object.h"

class cAI;
class TriggerCallback;
class cTrack;
class cSkidMark;
class InGameUI;

struct stCARSPEC
{
	std::vector<NxBoxShapeDesc> vecBoxDesc;
	std::vector<D3DXVECTOR3> vecWheelPos;
};

enum eBITE_KEY
{
	E_BITE_NONE = -1
	, E_BITE_LEFT = 0
	, E_BITE_RIGHT
	, E_BITE_UP
	, E_BITE_DOWN
	, E_BITE_FLIP
	, E_BITE_REPOS
	, E_BITE_ITEM
	, E_BITE_07
	, E_BITE_08
};

class cCar : public Object
{
<<<<<<< HEAD
	std::bitset<BITESET_8_SIZE> INPUT_KEY;
=======
	ST_KEYDONW m_keySet;
>>>>>>> 2043831021ea01154eeaf0ba9ad476945cbb1e76

	//���� �Ž��� ����
	std::vector<cMesh*> vecWheels;

	//�ڵ��� �ɷ�ġ ����
	NxVehicle* m_carNxVehicle;

	//float m_moterPower;		
	SYNTHESIZE(float, m_moterPower, MoterPower); // ���� ���� �Ŀ� 0~1 ������
	float m_maxMoterPower;	// �ִ� �Ŀ���
	float m_moterAcc;		// ���� 0~1

	float m_maxRpm;
	float m_breakPower;		// ���� ���� ������ �ڵ����� �ɸ��� �Ѵ�.

	//float m_wheelAngle;		
	SYNTHESIZE(float, m_wheelAngle, WheelAngle); //������ ���� ����. (���) 
	float m_maxWheelAngle;	//������ ���̴� �ִ밪. 
	float m_wheelAcc;		//���̴� �ӵ�	(������ �������� ��)

	//�ӵ� ���
	SYNTHESIZE(float, m_fCurrentSpeed, CurrentSpeed);
	D3DXVECTOR3 m_szPrevPos[5];

	SYNTHESIZE(D3DXMATRIX, m_matCarRotation, CarRotMatrix); // �ڵ��� ���� ��Ȯ�� ȸ�� ��Ʈ����

	//�ڵ��� ������?
	bool isFliping;

	//AI
	std::vector<cAI*> m_vecAI;
	bool m_isAI = false;

	//Track ����
	cTrack* m_pTrack;
	SYNTHESIZE(int, m_currCheckBoxID, CurrCheckBoxID);			//�ֱٿ� üũ�� �ڽ�
	SYNTHESIZE(int, m_nextCheckBoxID, NextCheckBoxID);			//������ üũ�� �ڽ�
	SYNTHESIZE(int, m_countRapNum, CountRapNum);				//�� ������

	SYNTHESIZE(float, m_rapTimeCount, RapTimeCount);			//���� �� �ð�
	SYNTHESIZE(float, m_bastRapTimeCount, BastRapTimeCount);	//���� ¬�� �� �ð�
	SYNTHESIZE(float, m_totlaTimeCount, TotlaTimeCount);		//�� ����� �� �ð�

	//Item ����
	SYNTHESIZE(eITEM_LIST, m_eHoldItem, HoldItem);
	SYNTHESIZE(int, m_nItemCount, ItemCount);

	cSkidMark* m_pSkidMark;

	//InGame UI
	InGameUI* m_pInGameUI;

public:
	cCar();
	~cCar();

	void SetNxVehicle(NxVehicle* pVehicle) { m_carNxVehicle = pVehicle; }
	NxVehicle* GetNxVehicle() { return m_carNxVehicle; }

	void LoadCar(std::string carName);
	void SetCarValue(float maxRpm, float moterPower, float moterAcc, float breakPower, float wheelAngle, float wheelAcc, bool isAI = false);

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

	//	void GetRpm();
	void TrackCheck();
	void RunEnd();
	void CarRunStop();
	void DrawSkidMark();
	void LinkTrackPt(cTrack* track) { m_pTrack = track; }
	eITEM_LIST* GetHoldItemPt() { return &m_eHoldItem; }
	void LinkUI(InGameUI* ingameUi) { m_pInGameUI = ingameUi; }
	//	void RunStart();

	void SpeedMath();
	void CreateSkidMark();
	void CollidePickUp();
	void SettingCarPos();

	void CarMove();
	void UsedItem();
	void RePosition();
	void CarFlip();


	/*   �輱ȣ   */
	void SetResetNetworkKey();
	void SetNetworkKey(std::string);

	SYNTHESIZE(bool, m_isUser, IsUser);
};