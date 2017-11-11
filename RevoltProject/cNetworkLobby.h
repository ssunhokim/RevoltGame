#pragma once

#include "iLobby.h"

class UIObject;
class UITextImageView;
class cNetwork;

class cNetworkLobby : public iLobby
{
private:
	UITextImageView* m_pServerIP;
public:
	cNetworkLobby();
	virtual ~cNetworkLobby();

	/*   �⺻ ��Ʈ �޼���   */
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	std::string GetServerIP();
};

// ChatClient.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

