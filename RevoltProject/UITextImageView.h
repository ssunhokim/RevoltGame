#pragma once

#include "UIObject.h"

#define CURSORRENDER 10

//======================================
// - ## 10.11.17 ##
// - written by �輱ȣ
// - �̹�������(png����)�� �� �ؽ�Ʈ�� �о�� ����ϴ� UI Ŭ����
//======================================

class UITextImageView : public UIObject
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;						// �ؽ���
	POINT				m_textPos;						// �ؽ�Ʈ �̹��� ������ ��ġ�� ����ϴ� ����
	FONTFILE			m_fontFileType;					// ��Ʈ ������ Ÿ��
	std::vector<std::string>	m_vecText;				// ��ư ���� �� �ٲ�� �ؽ�Ʈ�� �����ϱ� ���� ���� ����
	std::string m_chatText;								// ä�� �ؽ�Ʈ�� �����ϱ� ���� string����

	int			m_cursorTime;							// Ŀ���� Update�ϴ� ����
	bool		m_isCursorRender;						// Ŀ���� ���̰� �ϴ� ����
public:
	UITextImageView();
	virtual ~UITextImageView();

	static int*			m_Select;						// ���� �ؽ�Ʈ�� ���õ� ��ġ
	static int*			m_LeftAndRightSelect;			// ���� ������ ���� ���õ� ��ġ

	SYNTHESIZE(std::string, m_sText, Text);				// �ؽ�Ʈ�� ������ �����ϴ� ����
	SYNTHESIZE(int, m_index, Index);					// ���� ��ġ���� �ؽ�Ʈ�� ��ġ
	SYNTHESIZE(D3DXCOLOR, m_color, Color);				// �ؽ�Ʈ ���� ����
	SYNTHESIZE(float, m_xSize, XSize);					// X��Ʈ ������ ����
	SYNTHESIZE(float, m_ySize, YSize);					// Y��Ʈ ������ ����
	SYNTHESIZE(bool, m_isVectorText, IsVectorText);		// ���� �ؽ�Ʈ�� ��� �� ������ Ȯ���ϴ� �۾�
	SYNTHESIZE(bool, m_isChatingText, IsChatingText);	// Ű �Է��� ���� ������ Ȯ���ϴ� �۾�


	/*   �ؽ�Ʈ�� ���ͷ� ����� �� ���� �޼���   */
	void SetAddText(std::string text) { m_vecText.push_back(text); }

	void KeyEvent();

	/*   UI������Ʈ���� ��ӹ��� Ŭ����   */
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite) override;
	virtual void SetTexture(char* szFullPath);	// �ؽ��� ����
};

