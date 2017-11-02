#pragma once
#include "GameNode.h"

class cTrack;
class cLight;
class cCar;
class cBillBoardEffect;
class InGameUI;

class RacingScene : public GameNode
{
private:

	InGameUI* m_pInGameUI;
	cTrack* m_pTrack;
	cLight* m_pLightSun;
	std::vector<cCar*> vecCars;
	int m_nLightIDCount;

	//
	D3DXVECTOR3* camPos = new D3DXVECTOR3(0, 10, 0);
	D3DXVECTOR3* camLookTarget = new D3DXVECTOR3(0, 0, 0);

	LPD3DXSPRITE m_Sprite;
	cBillBoardEffect*		 m_pBillBoardEffect;

	bool m_isDrift;
public:

	RacingScene();
	~RacingScene();

	void Setup();
	void Destroy();
	void Update();
	void Render();
	void LastUpdate();
	void UpdateCamera();
};

