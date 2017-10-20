#pragma once

#include "Object.h"

class MtlTex;

class Thing : public Object
{
protected:
	std::vector<Thing*>	m_vecChild;			//	������Ʈ�� �ڽ�(����)���� ������ ����
	D3DXMATRIXA16		m_matWorld;
	LPD3DXMESH			m_pObjMesh;		// ������Ʈ�� �׸� �޽� ����
	std::vector<MtlTex*>		m_vecObjMtlTex;	// ������Ʈ�� ���͸��� �����ϴ� ����

	float m_xAngle;		// ��ư ������ �� x������ ȸ�� ��Ű�� ���� ȸ�� ����
	float m_yAngle;		// ������Ʈ�� ������ ���� y�� ȸ�� ����
	bool m_isMove;	// �����̴� ������Ʈ���� üũ
	bool m_isRot;		// x�� ȸ�� ���� 
	D3DXVECTOR3 m_vPosition;

public:
	/*   �ʱ�ȭ �޼���   */
	Thing();
	virtual ~Thing();
	virtual void SetPosition(float x, float y, float z);
	virtual void SetRotationX(float angle);
	virtual void SetRotationY(float angle);
	void SetMesh(char* szFolder, char* szFile);
	void SetIsMove(bool isMove);
	void SetIsRot(bool isRot);

	virtual void Update();
	virtual void Render();
	virtual void Destroy();
};

