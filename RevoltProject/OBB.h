#pragma once

class SkinnedMesh;

class OBB
{
private:
	D3DXVECTOR3 m_vOrgCenterPos;
	D3DXVECTOR3 m_vOrgAxisDir[3];

	D3DXVECTOR3 m_vCenterPos;		/// :  �ڽ� �߽�r ��ǥ
	D3DXVECTOR3 m_vAxisDir[3];		/// :  �ڽ��� ������ �� ���� ��������
	float		m_fAxisLen[3];				/// :  �ڽ��� ������ �� ���� ���� fAxisLen[n]�� vAxisDir[n]�� ���� �����Ѵ�.
	float		m_fAxisHalfLen[3];

	D3DXMATRIXA16 m_matWorldTM;
public:
	OBB();
	~OBB();

	void Setup(SkinnedMesh* pSkinnedMesh);
	void Update(D3DXMATRIXA16* pmatWorld);
	static bool IsCollision(OBB* pOBB1, OBB* pOBB2);

	void OBBBox_Render(D3DCOLOR c);
};

