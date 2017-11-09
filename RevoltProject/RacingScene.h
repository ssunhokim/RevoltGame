#pragma once
#include "GameNode.h"

//TrackEndCount ���ƾ� �Ǵ� ���� ��
#define m_trackEndCount 3

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

	
	
	//������??����Ʈ??
	LPD3DXSPRITE m_Sprite;

	bool m_isDrift;

	cSkyBox* m_pSkyBox;

	SYNTHESIZE(eRACE_PROG, m_eRaceProg, RaceProg);

public:

	RacingScene();
	~RacingScene();

	void Setup();
	void Destroy();
	void Update();
	void Render();
	void LastUpdate();
	void UpdateCamera();

	//�ڵ����� ��� �޷����ϴ����� üũ
	bool IsCarRunTrue(cCar* pCar);


//	void CreateCar(int carId) {}
	void CreateCar(D3DXVECTOR3 setPos, int playerID, std::string carName, bool isAI);
	void CreateCar(int playerID, std::string carName);
	void LinkUI(int playerID);
};

