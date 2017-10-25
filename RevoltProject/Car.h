#pragma once
#include "Thing.h"

class MtlTex;

struct ST_WHEEL
{
	LPD3DXMESH				m_pObjMesh;		// ���� ������Ʈ�� �׸� �޽� ����
	std::vector<MtlTex*>		m_vecObjMtlTex;	// ������Ʈ�� ���͸��� �����ϴ� ����
	D3DXVECTOR3				m_vPos;				// ���� ������Ʈ�� ����� ��ġ
};

//===================================================================
// - ## 10.15.23 ##
// - written by �輱ȣ
// - �ڵ����� ���� �������� Ŭ����
//===================================================================

class Car : public Thing
{
private:
	ST_CAR	m_stCar;				// �ڵ����� ���� ������ ����
public:
	Car();
	virtual ~Car();

	/*   �⺻���� �ڵ��� ���� �޼���   */
	virtual void Setup();
	virtual void Update();
	virtual void Render();

	void SetSTCar(ST_CAR car);
	void SetMeshWheel(char* szFolder, char* szName);
	void WheelRender();
	void KeyEvent();
};

