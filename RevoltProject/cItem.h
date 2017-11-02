#pragma once

#include "Object.h"

class cItem : public Object
{
private:
	int m_id;

public:
	cItem();
	virtual ~cItem();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

protected:
	LPD3DXMESH				m_pObjMesh;		// ������Ʈ�� �׸� �޽� ����
	std::vector<MtlTex*>		m_vecObjMtlTex;	// ������Ʈ�� ���͸��� �����ϴ� ����
	std::vector<Thing*>		 m_vecChild;					// �ڽ� ����

};

