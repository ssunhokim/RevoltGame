#pragma once

#include "iLobby.h"

class UIObject;
class UITextImageView;
class UIImageView;
class cNetwork;

class cNetworkLobby : public iLobby
{
private:
	UITextImageView* m_pUserName;
	UITextImageView* m_pCarName;
	UITextImageView* pImageView4;
	UITextImageView* pImageView8;
	UITextImageView* pImageView9;
	UITextImageView* pImageView10;
	UIImageView*	 pImageView1;
	UIImageView*	 pImageView2;
	UIImageView*	 pImageView3;
	UIImageView*	 pImageView5;
	UIImageView*	 pImageView6;
	UIImageView*	 pImageView7;


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

