#pragma once

class MtlTex;
class Car;

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
	D3DXMATRIXA16			m_matWorld;			// ������Ʈ�� ���� ���
	D3DXMATRIXA16			m_matRX, m_matRY, m_matT, m_matR;			// ������Ʈ�� Xȸ��, Yȸ��, ������ ȸ��, ���� Rotationȸ��
	LPD3DXMESH				m_pObjMesh;		// ������Ʈ�� �׸� �޽� ����
	std::vector<MtlTex*>		m_vecObjMtlTex;	// ������Ʈ�� ���͸��� �����ϴ� ����
	std::vector<Thing*>		 m_vecChild;					// �ڽ� ����

	float m_xAngle;		// ��ư ������ �� x������ ȸ�� ��Ű�� ���� ȸ�� ����
	float m_yAngle;		// ������Ʈ�� ������ ���� y�� ȸ�� ����
	float m_prevYAngle;	// ���� y������
	float m_prevXAngle;			// ���� x������

	D3DXVECTOR3 m_vPosition;		// ������Ʈ ��ġ
	D3DXVECTOR3 m_vTarget;			// ������Ʈ�� ���� ��ġ
	D3DXVECTOR3 m_vPrevPosition;	// ������ ������Ʈ ��ġ
public:
	/*   �ʱ�ȭ ���� �Ű�����   */
	static LOBBY* g_LobbyState;	// �κ��� ����

	/*    �ʱ�ȭ �޼���    */
	Thing();
	virtual ~Thing();
	virtual void SetPosition(float x, float y, float z);
	virtual void SetRotationX(float angle);
	virtual void SetRotationY(float angle);
	virtual void SetTarget(float x, float y, float z);
	virtual void SetMesh(char* szFolder, char* szFile);
	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	virtual void AddChild(Thing* pChild);

	/*    ����, ������ �޼���    */
	virtual void Update();
	virtual void Render();
	virtual void Destroy();
};

