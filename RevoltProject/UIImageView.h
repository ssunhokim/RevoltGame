#pragma once
#include "UIObject.h"

#define MAX_ID 11

class UIImageView : public UIObject
{
protected:
	/*   �� ������ ����   */
	float LeftNoiseX;
	float RightNoiseX;
	float UpNoiseY;
	float DownNoiseY;

	/*   ������ â �߰� �ϱ� ���� �۾�   */
	int m_itemPrevID;	// �������� ���� ���̵�
	int m_itemID;		// �������� ���� ���̵�
	int m_alpha;			// ���� �� ��������ֱ�
	int m_fTime;			// ���� �� ���� ���ֱ� ���� �ð� ��
	int m_updateTIme;

	LPDIRECT3DTEXTURE9		m_pTexture;			// �̹��� �׸��� �۾�
public:
	UIImageView();
	virtual ~UIImageView();
	virtual void SetTexture(char* szFullPath);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite) override;

	SYNTHESIZE(bool, m_isMove, IsMove);
	SYNTHESIZE(bool, m_isBoard, IsBoard);		
	SYNTHESIZE(bool, m_isNoise, IsNoise);
	SYNTHESIZE(bool, m_isItem, IsItem);
	SYNTHESIZE(float, m_xSize, XSize);
	SYNTHESIZE(float, m_ySize, YSize);
	SYNTHESIZE(D3DXCOLOR, m_color, Color);

};

