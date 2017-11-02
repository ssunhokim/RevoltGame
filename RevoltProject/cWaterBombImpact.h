#pragma once

#define MAX_XSIZE 16
#define UPDATE_TIME 3

#include "cImpact.h"

class cWaterBombImpact : public cImpact
{
private:
	LPDIRECT3DTEXTURE9		m_pTexture;			// �ؽ��� �̹���
	ST_SIZE							m_stSize;				// �̹��� ������
	LPD3DXSPRITE					m_pSprite;			// ��������Ʈ �̹���
	int m_fTime;
	int m_index;		// ���� ��ġ;
public:
	cWaterBombImpact();
	virtual ~cWaterBombImpact();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

