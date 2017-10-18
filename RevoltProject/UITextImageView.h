#pragma once

#include "UIObject.h"

//======================================
// - ## 10.11.17 ##
// - written by �輱ȣ
// - �̹�������(png����)�� �� �ؽ�Ʈ�� �о�� ����ϴ� UI Ŭ����
//======================================

class UITextImageView : public UIObject
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;			// �ؽ���
	POINT				m_textPos;			// �ؽ�Ʈ �̹��� ������ ��ġ�� ����ϴ� ����
	FONTFILE			m_fontFileType;		// ��Ʈ ������ Ÿ��
public:
	UITextImageView();
	virtual ~UITextImageView();

	static int*			m_Select;				// ���� �ؽ�Ʈ�� ��ġ

	SYNTHESIZE(std::string, m_sText, Text);		// �ؽ�Ʈ�� ������ �����ϴ� ����
	SYNTHESIZE(D3DXVECTOR3, m_vecPos, VecPos);	// �ؽ�Ʈ�� ��ġ
	SYNTHESIZE(int, m_index, Index);			// ���� ��ġ���� �ؽ�Ʈ�� ��ġ

	virtual void Render(LPD3DXSPRITE pSprite) override;
	virtual void SetTexture(char* szFullPath);	// �ؽ��� ����
};

