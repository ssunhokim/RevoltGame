#pragma once
class cBillBoardEffect
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;			// �ڵ��� �ڽ��� ���� �ؽ���
	LPD3DXMESH				m_pMesh;			// �޽� ����
public:
	cBillBoardEffect();
	~cBillBoardEffect();

	void Setup();
	void Update();
	void Render();

	void SetFileTexture(char* szFile);
};

