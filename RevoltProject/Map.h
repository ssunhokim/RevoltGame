#pragma once

class MtlTex;
class Thing;

//===================================================================
// - ## 10.15.20 ##
// - written by �輱ȣ
// - ���� �����ϴ� �� Ŭ���� �߰�
//===================================================================

class Map
{
private:
	int m_stage;
	std::vector<std::string> m_vecMapName;							// �� �̸��� �����ϴ� ���� ����
	std::map<int, ST_MAP*> m_map;		// ���̶� ������Ʈ�� �����ϴ� STL ����

public:
	Map();
	~Map();

	static LOBBY* g_LobbyState;

	/*   �⺻ ���� �� �޼���   */
	void Setup();
	void Update();
	void Render();

	void SetupThing();
};

