#include "stdafx.h"
#include "cCar.h"
#include "cWheel.h"

cCar::cCar()
{
}


cCar::~cCar()
{
}

void cCar::RegisteWheel(cWheel_ID id, cWheel* pWheel)
{
	if (pWheel)
	{
		mapWheels[id] = pWheel;
		pWheel->SetBody(this);
	}
}

void cCar::LoadMesh(std::string carName)
{
	GetMeshData()->LoadMesh("Cars", carName);
	std::string texturePach = "Cars/" + carName + "/car.png";
	for (int i = 0; GetMeshData()->m_vecMtlTex.size(); i++)
	{
		GetMeshData()->m_vecMtlTex[i]->SetTexture(g_pTextureManager->GetTexture(texturePach));
		//���ϸ� ������ �ؽ��ĸ� �ٽ��ѹ� ������.
	}

}
