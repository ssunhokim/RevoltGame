#pragma once

class UIObject;					// UI������Ʈ�� ����ϱ� ���� ���漱�� Ŭ����
class MtlTex;					// ������ ����ϱ� ���� ���漱�� Ŭ����
class Camera;					// ī�޶� Ŭ������ ����ϱ� ���� ���漱�� Ŭ����
class UIObject;					// UI������Ʈ�� ����ϱ� ���� ���漱�� Ŭ����
class MtlTex;					// ������ ����ϱ� ���� ���漱�� Ŭ����
class Camera;					// ī�޶� Ŭ������ ����ϱ� ���� ���漱�� Ŭ����
class Thing;					// ������Ʈ Ŭ����
class UITextImageView;			// TextImageView Class
class UIImageView;				// ImageView Class


//===================================================================
// - ## 10.15.17 ##
// - written by �輱ȣ
// - �κ� â ����
// - �κ� ���� �� �� �� Ŭ���� ���ο����� ó���� ��
//===================================================================

//===================================================================
// - ## 10.15.17 ##
// - written by �輱ȣ
// - @@ �ؽ�Ʈ �ε����� ������ 4���̸� ó�������� 0���� �����ϰ� ���� 3�̴�.
//===================================================================

struct ST_Object
{
	LOBBY*				m_pNextLob;					// ����Ű�� ������ �� ���� �κ����
	LOBBY				m_prevLob;					// ESCŰ�� ������ �� ���� �κ����
	float				m_time;						// ȭ���� �ٲ� �ð�
	int					m_count;					// �޴� �ؽ�Ʈ ���Ʒ� �ε����� ������ 
	int					m_selectCnt;				// �޴� ������ ���� �ε��� ������

	D3DXVECTOR3			m_target;					// ī�޶� ����
	UIObject*			m_pObject;					// �ش� UI Object
	D3DXVECTOR3			m_camLookAt;				// Camera LookAt

	ST_Object()
	{
		m_time = 0.0f;
		m_count = 0;
		m_target = D3DXVECTOR3(0, 0, 0);
		m_camLookAt = D3DXVECTOR3(0, 0, 0);
	}
};

class Lobby
{
private:
	std::map<LOBBY, ST_Object*>	m_mapLobby;		// UI �̹������� �����ϴ� map STL
	LPD3DXSPRITE				m_pSprite;		// UI �̹����� ����ϴ� sprite����

	LPD3DXMESH					m_pObjMesh;		// �κ� ������Ʈ�� �׸��� ���� Mesh ����
	std::vector<MtlTex*>		m_vecObjMtlTex;	// ������Ʈ�� ���͸��� �����ϴ� ����

	LOBBY	m_stateLobby;						// �κ� ���� �� �����ϴ� ����
	float	m_time;								// ���� �ð��� ��Ÿ���� Ÿ�� ����
	int		m_select;							// ���� ���Ʒ� Ŀ���� ��ġ
	int		m_leftAndrightSelect;				// ���� ������ ���� Ŀ���� ��ġ;

	//===================================================================
	// - written by ������
	// - �� ����
	// - �κ� ���� �� �� �� Ŭ���� ���ο����� ó���� ��
	//===================================================================

	int		m_selectMapType;					// Select Map Type
	int		m_LockedTime;						// Update Locked Time

	bool	m_isUnLocked;						// Check Locked
	bool	m_isLockedRender;					// Show Lock Image

	bool	m_isOpenHood;						// Open Hood Map
	bool	m_isOpenMuse;						// Open Muse Map
	bool	m_isOpenShip;						// Open Ship Map

	Camera*				m_pCamera;				// ī�޶� Ŭ����

	UIImageView*		m_mapImage;				// Map Image
	UITextImageView*	m_mapName;				// Map Name
	UITextImageView*	m_mapLength;			// Map Length
	UITextImageView*	m_mapDifficulty;		// Map Difficulty

	UIImageView*		m_LockedRing;
	UITextImageView*	m_LockedTextImage;

	std::vector<std::string> m_vString;
public:
	Lobby();
	~Lobby();

	/*   �⺻���� ���� �޼���   */
	void Setup();					// �ʱ�ȭ �۾� �޼���
	void Update();					// ����ȭ �۾��� �޼���
	void Render();					// ���������� �׸� �޼���

	/*   Ŭ���� �ȿ� ����� ���� �޼���   */
	void KeyUpdate();				// Ű �̺�Ʈ �߻� ���� �޼���
	void TimeUpdate();				// �ð��� �带 �� ���� �߻� �ϴ� �̺�Ʈ�� �����ϴ� �޼���
	void SetUpUI();					// UI �¾��۾�
	void MapTypeUpdate();			// Map Update;

	D3DXVECTOR3 GetTarget() { return m_mapLobby[START_LOBBY]->m_target; }		// ī�޶� ���� ������ ��ȯ���ִ� �޼���
	void SetUpCamera(Camera* camera) { m_pCamera = camera; }		// ó�� ī�޶� ������ �����ϴ� �޼���
};

