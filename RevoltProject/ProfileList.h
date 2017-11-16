#pragma once

class UIImageView;

class ProfileList
{
private:
	std::vector<std::string> m_vProfileList;

public:
	ProfileList();
	~ProfileList();

	void Destroy();
	void ListLoad();								// ���� �˻��ؼ� ����Ʈ ���
	UIImageView*			  GetProfileList();		// ����Ʈ UI ��������
	std::vector<std::string>  GetUpdateList() { return m_vProfileList; }	// ����Ʈ ������Ʈ

	SYNTHESIZE(std::string, m_CarName, CarName);
	SYNTHESIZE(std::string, m_UserName, UserNameText);
	SYNTHESIZE(std::string, m_MapName, MapName);
};

