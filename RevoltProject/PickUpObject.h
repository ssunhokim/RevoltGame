#pragma once

#include "Thing.h"

class PickUpObject : public Thing
{
public:
	PickUpObject();
	virtual ~PickUpObject();

	/*   �⺻ ���� �޼���   */
	void Setup();
	void Update();
	void Render();
};

