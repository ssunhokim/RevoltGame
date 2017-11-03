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

	/*	�ӵ���	*/
	int m_speedAlpha[7];
	int m_alphaValue;		// ���İ� ����

	float m_fArrowDir;

	LPDIRECT3DTEXTURE9		m_pTexture;			// �̹��� �׸��� �۾�
public:
	UIImageView();
	virtual ~UIImageView();
	virtual void SetTexture(char* szFullPath);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite) override;

	void SetRpmGauge(int rpm) { m_alphaValue = rpm; }


	SYNTHESIZE(bool, m_isMove, IsMove);
	SYNTHESIZE(bool, m_isBoard, IsBoard);		
	SYNTHESIZE(bool, m_isNoise, IsNoise);
	SYNTHESIZE(bool, m_isItem, IsItem);
	SYNTHESIZE(bool, m_isSpeedFrame, IsSpeedFrame);
	SYNTHESIZE(bool, m_isSpeed, IsSpeed);
	SYNTHESIZE(bool, m_isArrowDir, IsArrowDir);
	SYNTHESIZE(bool, m_isFrameRender, FrameRender);
	SYNTHESIZE(bool, m_isBomb, Bomb);
	SYNTHESIZE(float, m_xSize, XSize);
	SYNTHESIZE(float, m_ySize, YSize);
	SYNTHESIZE(D3DXCOLOR, m_color, Color);

};

