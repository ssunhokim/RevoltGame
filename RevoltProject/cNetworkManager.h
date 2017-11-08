#pragma once

#define NAME_SIZE 20
#define BUF_SIZE 1024

#define g_pNetworkManager cNetworkManager::GetInstance()

class cNetworkManager
{
private:
	SOCKET m_hSock;
	std::vector<std::string> m_vecMyIP;
	
	char name[NAME_SIZE];		// �ڵ��� �̸�
	char roomName[NAME_SIZE];
	int data[BUF_SIZE];

	std::string m_serverIP;
	std::string m_msg;			// ������ �̸�
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

	std::string GetMsg() { return m_msg; }
	

	sockaddr_in GetDefaultMyIP();
};

