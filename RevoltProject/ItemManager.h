#pragma once

class cItem;

#define g_pItemManager ItemManager::GetInstance();

//===================================================================
// - written by �輱ȣ
// - ###������ �������� �����ִ� ������ �Ŵ���###
// - ��� �����۵��� ���⼭ ��������ش�
//===================================================================

class ItemManager
{
private:
	std::vector<cItem*> m_vecItem;		// �����۵��� �����ϴ� Ŭ����
public:
	SINGLETONE(ItemManager);
};

