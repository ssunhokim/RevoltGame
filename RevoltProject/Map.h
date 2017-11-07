#pragma once
#include "Camera.h"

#define WHELLTIRE_POSITION D3DXVECTOR3(10.0f, 4.8f, 18.0f)

class MtlTex;
class Thing;

class cTrack;


//===================================================================
// - ## 10.15.20 ##
// - written by �輱ȣ
// - ���� �����ϴ� �� Ŭ���� �߰�
//===================================================================


class Map
{
private:
	
	int m_stage;

	std::vector<std::string> m_vecMapName;		// �� �̸��� �����ϴ� ���� ����

		// �� �̸��� �����ϴ� ���� ����
	Camera* m_pCamera;
	//Front ���� ��
	LPD3DXMESH				m_pObjMesh;
	std::vector<MtlTex*>	m_vecObjMtlTex;
	std::vector<Thing*>		m_vecThing;

//	cTrack* m_map;				

	//Ʈ�� ���� ��
	std::map<int, cTrack*> m_track;

public:
	Map();
	~Map();

	static LOBBY* g_LobbyState;

	/*   �⺻ ���� �� �޼���   */
	void Setup();
	void Update();
	void Render();

	void SetupThing();
	void SetUpCamera(Camera* camera) { m_pCamera = camera; }

	std::map<int, cTrack*> GetMapName() { return m_track; }
};