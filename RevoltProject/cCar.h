#pragma once
#include "Object.h"
#include "cAI.h"

class cAI_Master;
class TriggerCallback;
class cTrack;
class cSkidMark;
class InGameUI;

struct stCARSPEC
{
	std::vector<NxBoxShapeDesc> vecBoxDesc;
	std::vector<D3DXVECTOR3> vecWheelPos;
};

class cCar : public Object
{
	ST_KEYSET m_keySet;
public:
	std::bitset<BITESET_8_SIZE> INPUT_KEY;
private:
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
	cAI_Master* familyAI;
	bool m_isAI = false;

	bool m_isCtl;
	bool m_isDrift;

	SYNTHESIZE(int, m_nPlayerID, PlayerID);

	//���� ����
	std::string m_strMotorKey;
	std::string m_strDriftKey;

	//Track ����
	cTrack* m_pTrack;
	SYNTHESIZE(int, m_aICheckBoxID, AICheckBoxID);				//Ʈ�� ������ ������� �׻� üũ�� �ڽ��� ��ȣ�� �ö�´�.
	SYNTHESIZE(int, m_currCheckBoxID, CurrCheckBoxID);			//�ֱٿ� üũ�� �ڽ�
	SYNTHESIZE(int, m_nextCheckBoxID, NextCheckBoxID);			//������ üũ�� �ڽ�
	SYNTHESIZE(int, m_countRapNum, CountRapNum);				//�� ������
	SYNTHESIZE(int*, m_pEndRapNum, EndRapNum);					//���ƾ� �ϴ� ���� ��

	SYNTHESIZE(float, m_LabTimeCount, LabTimeCount); //���� �� �ð�
	SYNTHESIZE(float, m_bastLabTimeCount, BastLabTimeCount);	//���� ¬�� �� �ð�
	SYNTHESIZE(float, m_totlaTimeCount, TotlaTimeCount);		//�� ����� �� �ð�
	SYNTHESIZE(float, m_finishTime, FinishTime);


	//m_aICheckBoxID���� ���� üũ�ڽ��� ����Ű�� ����
//	SYNTHESIZE(D3DXVECTOR3, m_nextDir, NextCheckDir);

	//Item ����
	SYNTHESIZE(eITEM_LIST, m_eHoldItem, HoldItem);
	SYNTHESIZE(int, m_nItemCount, ItemCount);

	cSkidMark* m_pSkidMark;

	//InGame UI
	InGameUI* m_pInGameUI;

	/*          Ray Cast          */
	std::vector<D3DXVECTOR3>	m_vecProjVertex;
	std::vector<D3DXVECTOR3>	m_vecWorldVertex;
	std::vector<D3DXPLANE>		m_vecPlane;


	SYNTHESIZE(cCar*, m_pTarget, Target);

	//Rank����
	float m_fRankPoint;

	SYNTHESIZE(int, m_nCurRank, CurRank);

	bool m_itemEable;
	int m_itemEableTime;


	//wheelrotangle
	float wheelRotAngle;
public:
	cCar();
	~cCar();

	void SetNxVehicle(NxVehicle* pVehicle) { m_carNxVehicle = pVehicle; }
	NxVehicle* GetNxVehicle() { return m_carNxVehicle; }

	void LoadCar(std::string carName);
	void SetCarValue(float maxRpm, float moterPower, float moterAcc, float breakPower, float wheelAngle, float wheelAcc, bool isAI = false);
	void SetAI(bool isAI , AI_DATA aiData);
	void CreateItem();

	void CreatePhsyX(stCARSPEC carspec);
	void LoadMesh(std::string carName);
	void LoadWheel(std::string carName);

	void Update();
	void LastUpdate();
	void Render();
	void Destroy();


	void CtrlPlayer();
	void CtrlAI();

	float GetRpm();
	float GetRpmRate();

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

	void CarMove();
	void UsedItem();
	void RePosition();
	void CarFlip();

	/*          Ray Cast          */
	void SetFrustum();
	void UpdateFrustum(D3DXVECTOR3 pv);
	void UpdateFrustum();
	bool IsIn(D3DXVECTOR3* pv);



	void UpdateSound();

	void UpdateRankPoint();

	float GetRankPoint() { return m_fRankPoint; }
	/*   �輱ȣ   */
	///////////////////////////////////////
private:
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 m_pNameTexture;
	D3DXCOLOR m_textIDColor;
public:
	void SetResetNetworkKey();
	void SetNetworkKey(std::string);
	void RenderBillboardID();

	SYNTHESIZE(NxVec3, m_carPos, CarSunPos);
	SYNTHESIZE(bool, m_isUser, IsUser);
	SYNTHESIZE(float, m_yAngle, YAngle);
	SYNTHESIZE(std::string, m_userName, UserName);
	////////////////////////////////////////
	//e
	NxVec3 CarArrow(float degAngle = 0);
	NxVec3 WheelArrow(float degAngle = 0 , bool back = false);
};