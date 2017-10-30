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

	/*   기본 루트 메서드   */
	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	/*   유저 이름, 자동차 이름 셋업   */
	void SetUserName(std::string Name);
	void SetCarName(std::string pName);
	std::string GetName();
};

// ChatClient.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

