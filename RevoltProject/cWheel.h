#pragma once
#include "Object.h"
class cCar;
class cWheel : public Object
{
	// ��ϵ� �ڵ����� �����Ϸ� �ϴ� ���ð��� ������ ��.(cTransform)
	// ��� �Ǿ��ִ� �ڵ���.
	cCar* m_body;

public:
	cWheel();
	~cWheel();
	void SetBody(cCar* body);
	void Update();
	void Render();

};

