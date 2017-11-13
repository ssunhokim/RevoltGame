#pragma once

#include "iLobby.h"

class UIImageView;
class UITextImageView;
class UITextView;

class cNetworkInRoom : public iLobby
{
private:
	UIImageView*		m_pMap;			// �濡 ������ �� �̹���
	UITextImageView*	m_pMapName;		// �濡 ������ �� �̸�
	UITextImageView*	m_pChating;		// ä�� ����
	UITextImageView*	m_pText;		// ȭ�鿡 ������ ä�� ����
	UIImageView*		pImageView1;
	UIImageView*		pImageView3;
	UITextImageView*	pImageView4;
	UIImageView*		pImageView5;
	UIImageView*		pImageView6;
	UIImageView*		pImageView7;



	std::string m_userName;

	std::vector<UITextImageView*>	m_vecText;
	int m_index;
	int m_sizeY;
public:
	cNetworkInRoom();
	virtual ~cNetworkInRoom();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	void SetMap(std::string mapName);

	std::string GetMsg();
	void SetResetCharText();
	void SetText(std::string str);
	void SetUserName(std::string name) { m_userName = name; };
};

