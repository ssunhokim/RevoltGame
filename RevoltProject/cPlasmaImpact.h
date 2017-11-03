#pragma once

#include "cImpact.h"

#define UPDATE_TIME 3

class cPlasmaImpact : public cImpact
{
private:
	LPD3DXSPRITE	m_pSprite;			// ��������Ʈ ���
	LPDIRECT3DTEXTURE9		m_pTexture;		// �ؽ��� �̹���
	ST_SIZE							m_stSize;		// �ؽ��� ������
	int m_fTime;		// �ð�
	int m_index;		// ���� ��ġ;
	int m_currentX;		// �̹��� ���� X��ġ
	int m_currentY;		// �̹��� ���� y��ġ
public:
	cPlasmaImpact();
	virtual ~cPlasmaImpact();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void UpdateSetPosition(D3DXVECTOR3 v) { m_itemPos = v; };
};

