#pragma once

#include "cImpact.h"

#define UPDATE_TIME 2
#define MAX_XSIZE 20

class cFakeImpact : public cImpact
{
private:
	LPDIRECT3DTEXTURE9		m_pTexture;					// �ؽ��� �̹���
	ST_SIZE							m_stSize;			// �̹��� ������
	LPD3DXSPRITE					m_pSprite;			// ��������Ʈ �̹���
	int m_fTime;		// �ð�
	int m_index;		// ���� ��ġ;
	int m_currentX;		// �̹��� ���� X��ġ
	int m_currentY;		// �̹��� ���� y��ġ
public:
	cFakeImpact();
	virtual ~cFakeImpact();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();
};

