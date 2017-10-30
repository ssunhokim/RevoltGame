#pragma once
#include "GameNode.h"

class cTrack;
class cLight;
class cCar;


class RacingScene : public GameNode
{
private:

	cTrack* m_pTrack;
	cLight* m_pLightSun;
	int m_nLightIDCount;

	//
	D3DXVECTOR3* camPos = new D3DXVECTOR3(0, 10, 0);
	D3DXVECTOR3* camLookTarget = new D3DXVECTOR3(0, 0, 0);
	cCar* pCar1;
	NxVehicle* pVeh;

public:

	RacingScene();
	~RacingScene();

	void Setup();
	void Destroy();
	void Update();
	void Render();
	
};

