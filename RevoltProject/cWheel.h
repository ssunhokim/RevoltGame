#pragma once
#include "Object.h"
class cCar;
class cWheel : public Object
{
	// ��ϵ� �ڵ����� �����Ϸ� �ϴ� ���ð��� ������ ��.

	cCar* m_body;

public:
	cWheel();
	~cWheel();
	void SetBody(cCar* body);
};

