#pragma once
#include "UIObject.h"

class UIImageView : public UIObject
{
protected:
	LPDIRECT3DTEXTURE9		m_pTexture;
public:
	UIImageView();
	virtual ~UIImageView();
	virtual void SetTexture(char* szFullPath);
	virtual void Render(LPD3DXSPRITE pSprite) override;

	SYNTHESIZE(bool, m_isBoard, IsBoard);		
	SYNTHESIZE(float, m_xSize, XSize);
	SYNTHESIZE(float, m_ySize, YSize);
};

