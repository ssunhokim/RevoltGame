#pragma once
#include "Thing.h"

#define SELECT_YANGLE 3.7f

class WheelTire : public Thing
{
public:
	static float g_xRotAngle;		// �κ񿡼� ��,������ Ű ������ �� ȸ����

	WheelTire();
	virtual ~WheelTire();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();
};

