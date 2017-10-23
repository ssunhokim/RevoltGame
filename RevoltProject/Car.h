#pragma once
#include "Thing.h"

class MtlTex;

//===================================================================
// - ## 10.15.23 ##
// - written by �輱ȣ
// - �ڵ����� ���� �������� Ŭ����
//===================================================================

class Car : public Thing
{
private:
	ST_CAR					m_car;				// �ڵ����� ������ ����
	D3DXMATRIXA16		m_matWorld;			// ������Ʈ�� ���� ���
	LPD3DXMESH			m_pObjMesh;		// ������Ʈ�� �׸� �޽� ����
	std::vector<MtlTex*>		m_vecObjMtlTex;	// ������Ʈ�� ���͸��� �����ϴ� ����
	D3DXVECTOR3 m_vPosition;		// �ڵ����� ��ġ
public:
	Car();
	~Car();

	/*   �⺻���� �ڵ��� ���� �޼���   */
	void Setup();
	void Update();
	void Render();

	void KeyEvent();
};

