#pragma once

#include "Thing.h"

class Car;

class CarBox : public Thing
{
private:
	IDirect3DVertexBuffer9* VB;								// �ڵ��� �ڽ��� ǥ���� �׸� ���ؽ� ����
	LPDIRECT3DTEXTURE9	m_carboxTexture;			// �ڵ��� �ڽ��� ���� �ؽ���
	int m_index;													// ������Ʈ�� �ش� �ε���
	Car*	m_car;					// �ڵ���
public:
	CarBox();
	virtual ~CarBox();

	static int*	g_select;										// �κ񿡼� ���õ� �ε���
	static std::vector<ST_CAR>	g_vecCar;				// �ڵ����� ������ ��� �ִ� ���� ����

	/*   �⺻ ���� �޼���   */
	virtual void Setup();
	virtual void Update();
	virtual void Render();

	void SetTextFile(char* szFile);
	void SetIndex(int index);
};

