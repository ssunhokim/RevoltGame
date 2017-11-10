#pragma once

#include "iLobby.h"

class UIObject;
class UITextImageView;
class cNetwork;

class cNetworkLobby : public iLobby
{
private:
	UITextImageView* m_pUserName;
	UITextImageView* m_pCarName;
public:
	cNetworkLobby();
	virtual ~cNetworkLobby();

	/*   �⺻ ��Ʈ �޼���   */
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	/*   ���� �̸�, �ڵ��� �̸� �¾�   */
	void SetUserName(std::string Name);
	void SetCarName(std::string pName);
	std::string GetName();
};

// ChatClient.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

