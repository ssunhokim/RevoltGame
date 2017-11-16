#pragma once
#include "GameNode.h"

class cTrack;
class cLight;
class cCar;
class cBillBoardEffect;
class InGameUI;
class cSkyBox;

enum eRACE_PROG
{
	RACE_PROG_READY, // �غ�
	RACE_PROG_SET, // ����ī��Ʈ 321go
	RACE_PROG_GO, // �����
	RACE_PROG_FINISH // ��ⳡ
};

class RacingScene : public GameNode
{
private:
	int playerIndex;

	InGameUI* m_pInGameUI;
	cTrack* m_pTrack;

	std::vector<cCar*> vecCars;

	cLight* m_pLightSun;
	int m_nLightIDCount;
	
	int m_select;
	//
	D3DXVECTOR3* m_camPos;
	D3DXVECTOR3* m_camLookTarget;

	//TrackEndCount ���ƾ� �Ǵ� ���� ��	
	SYNTHESIZE(int, m_trackEndCount, trackEndCount);
	
	//������??����Ʈ??
	LPD3DXSPRITE m_Sprite;

	bool m_isDrift;
	bool m_isPlayBGM;

	cSkyBox* m_pSkyBox;

	SYNTHESIZE(eRACE_PROG, m_eRaceProg, RaceProg);

	std::vector<int> m_vecRank;

public:

	RacingScene();
	~RacingScene();

	void Setup();
	void Destroy();
	void Update();
	void Render();
	void LastUpdate();
	void UpdateCamera();
	void UpdateSound();
	void UpdateRnak();

	//�ڵ����� ��� �޷����ϴ����� üũ
	bool IsCarRunTrue(cCar* pCar);


//	void CreateCar(int carId) {}
	void CreateCar(D3DXVECTOR3 setPos, int playerID, std::string userName, std::string carName, int trackEndCount, bool isAI, bool isUser = false);
	//void CreateCar(int playerID, std::string carName);
	void LinkUI(int playerID);

	/*   �輱ȣ   */
	void NetworkLoop();			// ��Ʈ��ũ ����ϴ� �κ�
	void SetNetworkCarData();		// �ڵ��� ������ �����ϴ� �޼���

	std::vector<int>* GetRankVectorPt() { return &m_vecRank; }
};

