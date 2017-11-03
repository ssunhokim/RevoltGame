#pragma once
#include "GameNode.h"

class cTrack;
class cLight;
class cCar;


class RacingScene : public GameNode
{
private:
	int playerIndex = 0;

	cTrack* m_pTrack;
	std::vector<cCar*> vecCars;

	cLight* m_pLightSun;
	int m_nLightIDCount;

	//
	D3DXVECTOR3* camPos = new D3DXVECTOR3(0, 10, 0);
	D3DXVECTOR3* camLookTarget = new D3DXVECTOR3(0, 0, 0);

	//TrackEndCount ���ƾ� �Ǵ� ��Ƣ ��
	const int m_trackEndCount = 3;
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
};

