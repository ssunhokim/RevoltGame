#pragma once

class Thing;

class ThingManager
{
private:
	std::map<std::string, Thing*>	m_mapThing;		// ������Ʈ ���� �����ϴ� map STL
public:
	SINGLETONE(ThingManager);

	/*   ������Ʈ�� �߰��ϴ� �޼���   */
	void AddThing(std::string strKey, char* szFolder, char* szFile, bool isMove = false, bool isRot = false, float angle = 0.0f);

	void Render(std::string strKey);
};

