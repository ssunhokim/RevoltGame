#pragma once

class UIImageView;

class ProfileList
{
private:
	std::vector<std::string> m_vProfileList;
public:
	ProfileList();
	~ProfileList();

	void ListLoad();								// ���� �˻��ؼ� ����Ʈ ���
	UIImageView*			  GetProfileList();		// ����Ʈ UI ��������
	std::vector<std::string>  GetUpdateList() { return m_vProfileList; }	// ����Ʈ ������Ʈ
};

