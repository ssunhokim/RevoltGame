#pragma once

#include "iLobby.h"

class UIImageView;
class UITextImageView;

class cNetworkCreateRoom : public iLobby
{
private:
	UITextImageView*	m_pMapName;				// �� �̸� ����
	UITextImageView*	m_pMapDifficult;		// �� ���̵� ����
	UITextImageView*	m_pMapLength;			// �� ���� ����
	UITextImageView*	m_pRoomName;			// �� �̸� ����
	UITextImageView*	m_pTitleFont;
	UITextImageView*	m_pLength;
	UITextImageView*	m_pDifficulty;


	UIImageView* m_pTitleRing;
	UIImageView* m_pFlag;
	UIImageView* m_pBoardRing;
	UIImageView* m_pMapRing;
	UIImageView* m_pRing;


	std::vector<std::string>	m_vecMap;		// �� �̸��� �����ϴ� ����
public:
	cNetworkCreateRoom();
	virtual ~cNetworkCreateRoom();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	std::string GetRoomName();
	std::string GetImageName();
};

