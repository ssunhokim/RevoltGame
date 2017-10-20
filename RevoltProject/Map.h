#pragma once

class MtlTex;
class Thing;

struct ST_MAP
{
	LPD3DXMESH				m_pObjMesh;		// ���� �޽��� �����ϴ� ��� ����
	std::vector<MtlTex*>		m_vecObjMtlTex;	// ������Ʈ�� ���͸��� �����ϴ� ��� ����
	std::vector<Thing*>		m_vecThing;			
};

class Map
{
private:
	int m_stage;
	std::map<int, ST_MAP*> m_map;
public:
	Map();
	~Map();

	static LOBBY g_LobbyState;

	/*   �⺻ ���� �� �޼���   */
	void Setup();
	void Update();
	void Render();

	void SetupThing();
};

