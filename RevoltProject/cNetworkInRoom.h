#pragma once

#include "iLobby.h"

class UIImageView;
class UITextImageView;
class UITextView;

class cNetworkInRoom : public iLobby
{
private:
	UIImageView*		m_pMap;			// 방에 보여줄 맵 이미지
	UITextImageView*	m_pMapName;		// 방에 보여줄 맵 이름
	UITextImageView*	m_pChating;		// 채팅 구현
	UITextImageView*	m_pText;		// 화면에 보여줄 채팅 내용

	std::string m_userName;

	std::vector<UITextImageView*>	m_vecText;
	UIImageView* pImageView5;
	int m_index;
public:
	cNetworkInRoom();
	virtual ~cNetworkInRoom();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	void SetMap(std::string mapName);

	std::string GetMsg();
	void SetResetCharText();
	void SetText(std::string str);
	void SetUserName(std::string name) { m_userName = name; };
};

