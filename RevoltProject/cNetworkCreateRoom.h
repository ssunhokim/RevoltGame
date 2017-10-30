#pragma once

#include "iLobby.h"

class UIImageView;
class UITextImageView;

class cNetworkCreateRoom : public iLobby
{
private:
	UIImageView*		m_pMapImage;			// �� �̹��� ����
	UITextImageView*	m_pMapName;				// �� �̸� ����
	UITextImageView*	m_pMapDifficult;		// �� ���̵� ����
	UITextImageView*	m_pMapLength;			// �� ���� ����
	UITextImageView*	m_pRoomName;			// �� �̸� ����

	std::vector<std::string>	m_vecMap;		// �� �̸��� �����ϴ� ����
public:
	cNetworkCreateRoom();
	virtual ~cNetworkCreateRoom();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	std::string GetRoomName();
	std::string GetImageName();
};

