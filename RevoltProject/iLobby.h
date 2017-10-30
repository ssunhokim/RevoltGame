#pragma once

class UIObject;

//===================================================================
// - written by �輱ȣ
// - ��� UI�� ��ӹ޴� �⺻ UI Ŭ����
//===================================================================

class iLobby
{
protected:
	UIObject* m_pRootUI;
public:
	iLobby();
	virtual ~iLobby();

	static LOBBY* m_gLobbyState;

	UIObject* GetUIRoot() { return m_pRootUI; }

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
};

