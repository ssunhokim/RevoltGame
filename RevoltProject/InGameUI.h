#pragma once

#include "RevoltUIObject.h"

class UIObject;
class UITextImageView;
class UIImageView;

//===================================================================
// - written by �輱ȣ
// - �ڵ����� �޸��� �ΰ��� ���� Ŭ���� ����
// - �ΰ����� �� UI�� ������ �ȴ�.
//===================================================================

class InGameUI : public RevoltUIObject
{
private:
	UIObject*		m_pRootUI;
	UIImageView*	m_pItemImage;

	LOBBY*			m_pLobby;
public:
	InGameUI();
	virtual ~InGameUI();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	UIObject* GetUIObject() { return m_pRootUI; }
	void SetLobby(LOBBY* lobby) { m_pLobby = lobby; }
};

