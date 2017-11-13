#pragma once

#define NAME_SIZE 20
#define BUF_SIZE 1024

#define g_pNetworkManager cNetworkManager::GetInstance()
#define USER_SIZE 20

struct ST_KEYSET
{
	bool up;
	bool down;
	bool left;
	bool right;
	bool r_key;
	bool f_key;
	bool ctrl;
};

struct ST_NETUSER
{
	std::string userIP;
	std::string userID;
	std::string carName;
	bool IsReady;
	bool IsUse;
	int index;
};

class cNetworkManager
{
private:
	ST_KEYSET m_keyEvent;
	SOCKET m_hSock;
	ST_NETUSER m_user;						// Ŭ���̾�Ʈ ����
	std::vector<std::string> m_vecMyIP;		// Ŭ���̾�Ʈ IP
	ST_NETUSER m_vecUserIP[USER_SIZE];		// Ŭ���̾�Ʈ�� ������ ���� IP

	std::string m_serverIP;		// ���� IP �ּ�
	std::string m_vPosition;	// Ŭ���̾�Ʈ ��ġ ����

	std::string m_msg;			// ������ ���� ����
public:
	SINGLETONE(cNetworkManager);

	void Start();
	void Release();

	DWORD SendMsg(const char* msg);		// ������ ������ ������
	bool RecvMsg();		// ���̼� ������ �ޱ�
	void ErrorHandling(char* msg);

	void SetRoomName(std::string str);

	SYNTHESIZE(bool, m_isNetwork, IsNetwork);
	SYNTHESIZE(bool, m_isInNetwork, IsInGameNetwork);

	std::string GetMsg() { return m_msg; }

	std::string GetKeYString();
	std::string GetClientIP() { return m_user.userIP; };

	void SetClientPosition(NxVec3 v);
	std::string GetClientPosition();

	void SetServerIP(std::string str) { m_serverIP = str; }

	void SetClientName(std::string str) { m_user.userID = str; };
	std::string GetClientName() { return m_user.userID; };

	void SetCarName(std::string str) { m_user.carName = str; };
	std::string GetCarName() { return m_user.carName; };

	bool GetReady(int index) { return m_vecUserIP[index].IsReady; };

	std::string GetClientList(int index) { return m_vecUserIP[index].userID; };
	bool GetIsUse(int index) { return m_vecUserIP[index].IsUse; };

	int GetUserIndex() { return m_user.index; };
	bool GetIsReady() { return m_user.IsReady; };

	bool GetUserReady(int index) { return m_vecUserIP[index].IsReady; };
	void SetUserReady();

	void SetUpKey(bool b) { m_keyEvent.up = b; };
	void SetDownKey(bool b) { m_keyEvent.down = b; };
	void SetLeftKey(bool b) { m_keyEvent.left = b; };
	void SetRightKey(bool b) { m_keyEvent.right = b; };
	void SetRKey(bool b) { m_keyEvent.r_key = b; };
	void SetFKey(bool b) { m_keyEvent.f_key = b; };
	void SetCtrlKey(bool b) { m_keyEvent.ctrl = b; };

	void SetResetKeyEvent();
	sockaddr_in GetDefaultMyIP();
};

