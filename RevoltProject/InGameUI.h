#pragma once

class UIObject;
class UITextImageView;
class UIImageView;

//===================================================================
// - written by �輱ȣ
// - �ڵ����� �޸��� �ΰ��� ���� Ŭ���� ����
// - �ΰ����� �� UI�� ������ �ȴ�.
//===================================================================

class InGameUI 
{
private:
	UIObject*		m_pRootUI;
	UIImageView*	m_pItemImage;

	LOBBY*			m_pLobby;

	float m_ElapseTime;
	int m_DotTenth;
	int m_DotMilth;

	int m_SecOneth;
	int m_SecTenth;
	int	m_MinOneth;
	int	m_MinTenth;
	
	int m_SecColon;
	int m_MinColon;

	UITextImageView* m_pElapseTime;
	UITextImageView* m_pDotTenth;
	UITextImageView* m_pDotMilth;

	UITextImageView* m_pSecOneth;
	UITextImageView* m_pSecTenth;

	UITextImageView* m_pMinOneth;
	UITextImageView* m_pMinTenth;

public:
	InGameUI();
	virtual ~InGameUI();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	UIObject* GetUIObject() { return m_pRootUI; }
	void SetLobby(LOBBY* lobby) { m_pLobby = lobby; }
	void UpdateTimeLab();

};

