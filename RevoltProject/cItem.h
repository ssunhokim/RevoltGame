#pragma once

#include "Object.h"

class cItem : public Object
{
protected:
	LPD3DXMESH					m_pObjMesh;				// ������Ʈ�� �׸� �޽� ����
	std::vector<MtlTex*>		m_vecObjMtlTex;			// ������Ʈ�� ���͸��� �����ϴ� ����
	
	std::vector<cItem*>			m_vecChild;				// �ڽ� ����
	
	D3DXMATRIXA16				m_matWorld;

public:
	cItem();
	~cItem();

	virtual void Setup() = 0;
	virtual void Update();
	virtual void Render();

	void AddChild(cItem* child);

	SYNTHESIZE(cItem*, m_pParent, Parent);
};

