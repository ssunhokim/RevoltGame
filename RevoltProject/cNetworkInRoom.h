#pragma once

#include "iLobby.h"

class UIImageView;
class UITextImageView;
class UITextView;

class cNetworkInRoom : public iLobby
{
private:
	UITextImageView*	m_pChating;		// ä�� ����
	UITextImageView*	m_pText;		// ȭ�鿡 ������ ä�� ����

	std::vector<UITextImageView*>	m_vecText;		// ȭ�鿡 ������ ä�� ����
	std::vector<UITextImageView*>	m_vecUser;		// ȭ�鿡 ������ ������
	int m_index;
	int m_sizeY;
public:
	cNetworkInRoom();
	virtual ~cNetworkInRoom();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	std::string GetMsg();
	void SetResetCharText();
	void SetText(std::string str);
	void SetUserText(std::string str, int index, D3DXCOLOR color);
};

