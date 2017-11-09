#pragma once

#define NAME_SIZE 20
#define BUF_SIZE 1024

#define g_pNetworkManager cNetworkManager::GetInstance()

struct ST_KEYDONW
{
	bool up;
	bool down;
	bool left;
	bool right;
	bool ctrl;
	bool r_key;
	bool f_key;
};

class cNetworkManager
{
private:
	SOCKET m_hSock;
	ST_KEYDONW m_keyEvent;
	std::vector<std::string> m_vecMyIP;
	
	char name[NAME_SIZE];		// �ڵ��� �̸�
	char roomName[NAME_SIZE];
	int data[BUF_SIZE];

	std::string m_serverIP;		// ���� IP �ּ�
	std::string m_vPosition;	// Ŭ���̾�Ʈ ��ġ ����
	std::string m_msg;			// ������ �̸�
	char* m_charMsg;
public:
	SINGLETONE(cNetworkManager);

	void Start();
	void Release();

	DWORD SendMsg(const char* msg);		// ������ ������ ������
	bool RecvMsg();		// ���̼� ������ �ޱ�
	void ErrorHandling(char* msg);

	void SetRoomName(std::string str);
	void SetName(std::string str);
	void SetServerIP(std::string str) { m_serverIP = str; };

	SYNTHESIZE(bool, m_isNetwork, IsNetwork);
	SYNTHESIZE(bool, m_isInNetwork, IsInGameNetwork);		// �ΰ��ӿ����� ��Ʈ��ũ���� Ȯ��
	std::string GetMsg() { return m_msg; }
	
	void SetUpKey(bool t) { m_keyEvent.up = t; };
	void SetDownKey(bool t) { m_keyEvent.down = t; };
	void SetLeftKey(bool t) { m_keyEvent.left = t; };
	void SetRightKey(bool t) { m_keyEvent.right = t; };
	void SetCtrlKey(bool t) { m_keyEvent.ctrl = t; };
	void SetFKey(bool t) { m_keyEvent.f_key = t; };
	void SetRKey(bool t) { m_keyEvent.r_key = t; };

	void SetResetKeyEvent();

	std::string GetKeYString();
	std::string GetClientIP() { return m_vecMyIP[m_vecMyIP.size() - 1]; };
	void SetClientPosition(NxVec3 v);
	std::string GetClientPosition();
	char* GetCharMsg() { return m_charMsg; };
	sockaddr_in GetDefaultMyIP();
};

