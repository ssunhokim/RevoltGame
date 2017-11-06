#pragma once

#include "iLobby.h"

class UIObject;
class UITextImageView;
class UIImageView;
class cCar;

//===================================================================
// - written by 김선호
// - 자동차가 달리는 인게임 내의 클래스 구현
// - 인게임의 이 UI가 실행이 된다.
//===================================================================

class InGameUI : public iLobby
{
private:
	UIImageView*	m_pItemImage;
	LOBBY*			m_pLobby;
	int m_select;
	int m_WorldDotOneth;

	//Lab
	int m_Lab;

	/*          Timer UiTextImageView          */

	//Lab
	UITextImageView* m_pLab;

	//Last Time
	UITextImageView* m_pLastDotOneTh;
	UITextImageView* m_pLastDotTenth;
	UITextImageView* m_pLastDotMilth;
	UITextImageView* m_pLastSecOneth;
	UITextImageView* m_pLastSecTenth;
	UITextImageView* m_pLastMinOneth;
	UITextImageView* m_pLastMinTenth;


	//Best Time
	UITextImageView* m_pBestDotOneTh;
	UITextImageView* m_pBestDotTenth;
	UITextImageView* m_pBestDotMilth;
	UITextImageView* m_pBestSecOneth;
	UITextImageView* m_pBestSecTenth;
	UITextImageView* m_pBestMinOneth;
	UITextImageView* m_pBestMinTenth;

	//Lab Time
	UITextImageView* m_pLabElapseTime;
	UITextImageView* m_pLabDotTenth;
	UITextImageView* m_pLabDotMilth;
	UITextImageView* m_pLabSecOneth;
	UITextImageView* m_pLabSecTenth;
	UITextImageView* m_pLabMinOneth;
	UITextImageView* m_pLabMinTenth;

	//Race Time
	UITextImageView* m_pElapseTime;   
	UITextImageView* m_pDotTenth;	  
	UITextImageView* m_pDotMilth;	  
	UITextImageView* m_pSecOneth;	  
	UITextImageView* m_pSecTenth;	  
	UITextImageView* m_pMinOneth;	  
	UITextImageView* m_pMinTenth;	  

	// 속도계
	UITextImageView* pSpeed;
	UITextImageView* pSpeed2;
	UIImageView* pSpeedometerImage;

	// 등수, 방향 화살표
	UITextImageView* pITV_Rank;
	UITextImageView* pITV_Rank2;
	UIImageView* pIV_arrowDir;

	int arrowIndex;

	// 차 정보
	cCar* m_pCar;

public:
	InGameUI();
	virtual ~InGameUI();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	UIObject* GetUIObject() { return m_pRootUI; }
	void SetLobby(LOBBY* lobby) { m_pLobby = lobby; }
	

	void UpdateSpeed();
	void CompareBestTime();
	void UpdateLastTime();
	void UpdateRaceTime();									// UpdateRaceTimer
	void UpdateLabTime();									// UpdateLabTimer
	void UpdateArrowDir();									// 화살표 방향




	/*          SYNTHESIZE          */

	// Lab Count
	SYNTHESIZE(int, m_LabCnt, LabCnt);

	// LastTime
	SYNTHESIZE(int, m_LastDotOneTh, LastDotOneTh);
	SYNTHESIZE(int, m_LastDotTenth, LastDotTenth);
	SYNTHESIZE(int, m_LastDotMilth, LastDotMilth);
	SYNTHESIZE(int, m_LastSecOneth, LastSecOneth);
	SYNTHESIZE(int, m_LastSecTenth, LastSecTenth);
	SYNTHESIZE(int, m_LastMinOneth, LastMinOneth);
	SYNTHESIZE(int, m_LastMinTenth, LastMinTenth);

	// BestTime
	SYNTHESIZE(int, m_BestDotOneTh, BestDotOneTh);
	SYNTHESIZE(int, m_BestDotTenth, BestDotTenth);
	SYNTHESIZE(int, m_BestDotMilth, BestDotMilth);
	SYNTHESIZE(int, m_BestSecOneth, BestSecOneth);
	SYNTHESIZE(int, m_BestSecTenth, BestSecTenth);
	SYNTHESIZE(int, m_BestMinOneth, BestMinOneth);
	SYNTHESIZE(int, m_BestMinTenth, BestMinTenth);

	// Lab
	SYNTHESIZE(float, m_LabElapseTime, LabElapseTime);
	SYNTHESIZE(int, m_LabDotTenth, LabDotTenth);
	SYNTHESIZE(int, m_LabDotMilth, LabDotMilth);
	SYNTHESIZE(int, m_LabSecOneth, LabSecOneth);
	SYNTHESIZE(int, m_LabSecTenth, LabSecTenth);
	SYNTHESIZE(int, m_LabMinOneth, LabMinOneth);
	SYNTHESIZE(int, m_LabMinTenth, LabMinTenth);

	// Race
	SYNTHESIZE(float, m_ElapseTime, ElapseTime);
	SYNTHESIZE(int, m_DotTenth, DotTenth);
	SYNTHESIZE(int, m_DotMilth, DotMilth);
	SYNTHESIZE(int, m_SecOneth, SecOneth);
	SYNTHESIZE(int, m_SecTenth, SecTenth);
	SYNTHESIZE(int, m_MinOneth, MinOneth);
	SYNTHESIZE(int, m_MinTenth, MinTenth);

	void LinkCarPt(cCar* car) { m_pCar = car; }

};

