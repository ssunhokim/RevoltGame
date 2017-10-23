#pragma once

class MtlTex;

#define SELECT_YANGLE 3.7f

#include "Object.h"

//===================================================================
// - ## 10.15.19 ##
// - written by �輱ȣ
// - ������Ʈ�� �����ϴ� ������Ʈ Ŭ���� �߰�
//===================================================================

class MtlTex;

class Thing : public Object
{
protected:
	std::vector<Thing*>	m_vecChild;			//	������Ʈ�� �ڽ�(����)���� ������ ����
	D3DXMATRIXA16		m_matWorld;			// ������Ʈ�� ���� ���
	LPD3DXMESH			m_pObjMesh;		// ������Ʈ�� �׸� �޽� ����
	std::vector<MtlTex*>		m_vecObjMtlTex;	// ������Ʈ�� ���͸��� �����ϴ� ����

	float m_xAngle;		// ��ư ������ �� x������ ȸ�� ��Ű�� ���� ȸ�� ����
	float m_yAngle;		// ������Ʈ�� ������ ���� y�� ȸ�� ����
	float m_prevYAngle;	// ���� y������
	bool m_isMove;	// �����̴� ������Ʈ���� üũ
	bool m_isRot;		// x�� ȸ�� �������� üũ
	D3DXVECTOR3 m_vPosition;		// ������Ʈ ��ġ
	D3DXVECTOR3 m_vTarget;			// ������Ʈ�� ���� ��ġ
	D3DXVECTOR3 m_vPrevPosition;	// ������ ������Ʈ ��ġ

	LOBBY	m_lobby;	// ��� �κ� ���¿��� �̺�Ʈ�� �߻����� ���� ����
	int		m_stage;	// ���� �������� : 0 - ����Ʈ, 1�̻� �� ��������
	int		m_index;	// ���� ���� ��ġ

public:
	/*   �ʱ�ȭ �޼���   */
	static float g_xRotAngle;
	static LOBBY* g_LobbyState;
	static int*	g_select;

	Thing();
	virtual ~Thing();
	virtual void SetPosition(float x, float y, float z);
	virtual void SetRotationX(float angle);
	virtual void SetRotationY(float angle);
	void SetTarget(float x, float y, float z);
	void SetMesh(char* szFolder, char* szFile);
	void SetIsMove(bool isMove);
	void SetIsRot(bool isRot);
	void SetLobby(LOBBY lobby);
	void SetIndex(int index);

	virtual void Update();
	virtual void Render();
	virtual void Destroy();
};

