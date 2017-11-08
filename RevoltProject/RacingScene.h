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
	RACE_PROG_READY,
	RACE_PROG_SET,
	RACE_PROG_GO,
	RACE_PROG_FINISH
};

class RacingScene : public GameNode
{
private:
	int playerIndex = 0;

	InGameUI* m_pInGameUI;
	cTrack* m_pTrack;

	std::vector<cCar*> vecCars;

	cLight* m_pLightSun;
	int m_nLightIDCount;
	
	int m_select;
	//
	D3DXVECTOR3* camPos = new D3DXVECTOR3(0, 10, 0);
	D3DXVECTOR3* camLookTarget = new D3DXVECTOR3(0, 0, 0);

	//TrackEndCount ���ƾ� �Ǵ� ���� ��
	const int m_trackEndCount = 1;

	//������??����Ʈ??
	LPD3DXSPRITE m_Sprite;
	cBillBoardEffect*		 m_pBillBoardEffect;

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
	void LinkUI(int playerID);
};

