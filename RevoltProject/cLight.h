#pragma once
#include "Object.h"

class cLight :
	public Object
{
private:
	D3DLIGHT9 m_stLight; //���� ������ ������ ����ü
	int m_nIndex;

public:
	cLight();
	~cLight();

	void Setup(int nIndex, _D3DLIGHTTYPE type, D3DXCOLOR color, D3DXVECTOR3 position);
	void Update();
	void Destroy();
	void Switch(bool on);

	D3DLIGHT9* GetLight() { return &m_stLight; }
};

