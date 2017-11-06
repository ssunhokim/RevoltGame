#include "stdafx.h"
#include "cCar.h"
#include "cWheel.h"
#include "cAI.h"
#include "cPhysXManager.h"
#include "cTrack.h"
#include "cSkidMark.h"
#include "cCheckBox.h"

#include <fstream>

cCar::cCar()
	:m_pSkidMark(NULL)
{
	m_countRapNum = -1;
	m_currCheckBoxID = -1;
	m_rapTimeCount = 0.f;
	m_totlaTimeCount = 0.f;
	m_bastRapTimeCount = -1.0f;
	isFliping = false;
}

cCar::~cCar()
{

}

void cCar::LoadCar(std::string carName)
{
	std::string FullPath = "Cars/" + carName + "/" + carName + ".car";

	std::fstream LOAD;
	LOAD.open(FullPath);

	if (LOAD.is_open())
	{
		char szTemp[1024];

		while (1)
		{
			if (LOAD.eof()) break;

			LOAD >> szTemp;


			if (strcmp(szTemp, " ") == 0 || strcmp(szTemp, "\n") == 0)
			{
				continue;
			}
			else if (strcmp(szTemp, "NAME") == 0)
			{
				LOAD >> szTemp;

				LoadMesh(szTemp);
				LoadWheel(szTemp);
			}
			else if (strcmp(szTemp, "SPECIFICATION") == 0)
			{
				float maxRpm;
				float moterPower;
				float moterAcc;
				float breakPower;
				float wheelAngle;
				float wheelAcc;

				while (1)
				{
					LOAD >> szTemp;

					if (strcmp(szTemp, "MaxRPM") == 0)
					{
						LOAD >> szTemp;
						maxRpm = atof(szTemp);
					}
					else if (strcmp(szTemp, "MoterPower") == 0)
					{
						LOAD >> szTemp;
						moterPower = atof(szTemp);
					}
					else if (strcmp(szTemp, "MoterAcc") == 0)
					{
						LOAD >> szTemp;
						moterAcc = atof(szTemp);
					}
					else if (strcmp(szTemp, "BreakPower") == 0)
					{
						LOAD >> szTemp;
						breakPower = atof(szTemp);
					}
					else if (strcmp(szTemp, "WheelAngle") == 0)
					{
						LOAD >> szTemp;
						wheelAngle = NxPi*atof(szTemp);
					}
					else if (strcmp(szTemp, "WheelAcc") == 0)
					{
						LOAD >> szTemp;
						wheelAcc = atof(szTemp);
					}
					else if (strcmp(szTemp, "#") == 0)
					{
						break;
					}
				} // while
				SetCarValue(maxRpm, moterPower, moterAcc, breakPower, wheelAngle, wheelAcc);
			}
			else if (strcmp(szTemp, "MODEL") == 0)
			{
				stCARSPEC spec;
				ZeroMemory(&spec, sizeof(stCARSPEC));
				while (1)
				{
					LOAD >> szTemp;

					if (strcmp(szTemp, "BOX") == 0)
					{
						NxBoxShapeDesc boxDesc;
						while (1)
						{

							LOAD >> szTemp;

							if (strcmp(szTemp, "Dimensions") == 0)
							{
								LOAD >> szTemp;
								float x = atof(szTemp);
								LOAD >> szTemp;
								float y = atof(szTemp);
								LOAD >> szTemp;
								float z = atof(szTemp);

								boxDesc.dimensions.set(x, y, z);
							}
							else if (strcmp(szTemp, "LocalPose") == 0)
							{
								LOAD >> szTemp;
								float x = atof(szTemp);
								LOAD >> szTemp;
								float y = atof(szTemp);
								LOAD >> szTemp;
								float z = atof(szTemp);

								boxDesc.localPose.t.set(x, y, z);
							}
							else if (strcmp(szTemp, "MaterialIndex") == 0)
							{
								LOAD >> szTemp;

								boxDesc.materialIndex = atoi(szTemp);
							}
							else if (strcmp(szTemp, "#") == 0)
							{
								spec.vecBoxDesc.push_back(boxDesc);
								break;
							}
						} // while
					}
					else if (strcmp(szTemp, "WHEEL") == 0)
					{
						D3DXVECTOR3 pos;
						while (1)
						{
							LOAD >> szTemp;
							if (strcmp(szTemp, "Position") == 0)
							{
								LOAD >> szTemp;
								pos.x = atof(szTemp);
								LOAD >> szTemp;
								pos.y = atof(szTemp);
								LOAD >> szTemp;
								pos.z = atof(szTemp);

								spec.vecWheelPos.push_back(pos);
							}
							else if (strcmp(szTemp, "#") == 0)
							{
								break;
							}
						} // while;
					}
					else if (strcmp(szTemp, "#") == 0)
					{
						break;
					}
				} // while

				CreatePhsyX(spec);
			}
		} // << while
	}

	m_pSkidMark = new cSkidMark;
	m_pSkidMark->LinkCar(this);
}

void cCar::SetCarValue(float maxRpm, float moterPower, float moterAcc, float breakPower, float wheelAngle, float wheelAcc, bool isAI)
{
	m_maxRpm = maxRpm;
	m_maxMoterPower = moterPower;
	m_moterAcc = moterAcc;
	//	m_breakPower = breakPower;
	m_maxWheelAngle = wheelAngle;
	m_wheelAcc = wheelAcc;

	m_wheelAngle = 0;
	m_moterPower = 0;
	m_eHoldItem = ITEM_NONE;
	m_nItemCount = 0;
	m_isAI = isAI;

	m_vecAI.clear();
	if (isAI)
	{
		m_vecAI.push_back(new cAI);
	}
}
void cCar::CreateItem()
{
	if (!m_eHoldItem)
	{
		while (1)
		{
			m_eHoldItem = eITEM_LIST(rand() % (eITEM_LIST::ITEM_LAST));
			if (m_eHoldItem) break;
		}
		m_nItemCount = 1;
	}
}
void cCar::CreatePhsyX(stCARSPEC carspec)
{
	USERDATA* pUserdata = new USERDATA(E_PHYSX_TAG_CAR);
	m_carNxVehicle = MgrPhysX->createCarWithDesc(NxVec3(0, 1, 0), carspec, pUserdata, true, true);
	if (m_carNxVehicle)
	{
		cPhysX* physX = new cPhysX;
		physX->m_pActor = m_carNxVehicle->getActor();
		physX->m_pUserData = (USERDATA*)m_carNxVehicle->getActor()->userData;

		physX->m_pUserData->CheckBoxID = -1;

		SetPhysXData(physX);
		physX->SetPosition(NxVec3(0, 0, 0));
	}
}
void cCar::LoadMesh(std::string carName)
{
	GetMeshData()->LoadCarMesh("Cars/" + carName, carName + ".obj");
}

void cCar::LoadWheel(std::string carName)
{
	if (vecWheels.empty())
	{
		vecWheels.push_back(new cMesh);
		vecWheels.push_back(new cMesh);
		vecWheels.push_back(new cMesh);
		vecWheels.push_back(new cMesh);
	}
	else
	{
		for each(cMesh* p in vecWheels)
		{
			p->Destory();
		}
		vecWheels.clear();
	}

	vecWheels[0]->LoadMesh("Cars/" + carName, carName + "fl.obj");
	vecWheels[1]->LoadMesh("Cars/" + carName, carName + "fr.obj");
	vecWheels[2]->LoadMesh("Cars/" + carName, carName + "bl.obj");
	vecWheels[3]->LoadMesh("Cars/" + carName, carName + "br.obj");
}

void cCar::Update()
{
	NxVec3 pos = m_carNxVehicle->getGlobalPose().t;
	m_carNxVehicle->getActor()->addForce(NxVec3(0, 0.001, 0));



	//�ڵ��� ���� ������Ʈ
	//=================================================
	//�ڵ��� ��ġ ����
	m_position = {
		GetNxVehicle()->getGlobalPose().t.x,
		GetNxVehicle()->getGlobalPose().t.y,
		GetNxVehicle()->getGlobalPose().t.z };


	//�ڵ������� ȸ�� ��Ʈ����
	//ȸ�� ��Ʈ���� �޾ƿ�
	NxF32 mat[9];
	GetNxVehicle()->getGlobalPose().M.getColumnMajor(mat);
	D3DXMatrixIdentity(&m_matCarRotation);
	m_matCarRotation._11 = mat[0];
	m_matCarRotation._12 = mat[1];
	m_matCarRotation._13 = mat[2];
	m_matCarRotation._21 = mat[3];
	m_matCarRotation._22 = mat[4];
	m_matCarRotation._23 = mat[5];
	m_matCarRotation._31 = mat[6];
	m_matCarRotation._32 = mat[7];
	m_matCarRotation._33 = mat[8];

	//=================================================


	if (m_isAI) CtrlAI();
	else CtrlPlayer();

	//���� AI, PLAYER �� ���� ��� �Լ�

	// PickUp �浹
	if (GetPhysXData()->m_pUserData->IsPickUp == NX_TRUE)
	{
		if (m_eHoldItem == ITEM_NONE)
		{
			CreateItem();
			std::cout << m_eHoldItem << " - " << m_nItemCount << std::endl;
			//GetPhysXData()->m_pUserData->IsPickUp == NX_FALSE;
		}
	}

	//���ǵ� ���
	// : >>



	float Dist = 0;

	// ���� ��ġ��
	for (int i = 3; i >= 0; i--)
	{
		D3DXVECTOR3 pos1 = m_szPrevPos[i];
		D3DXVECTOR3 pos2 = m_szPrevPos[i + 1];

		D3DXVECTOR3 vecDist = pos1 - pos2;
		Dist += D3DXVec3Length(&vecDist);

		m_szPrevPos[i + 1] = m_szPrevPos[i];
	}

	m_szPrevPos[0] = m_position;

	m_fCurrentSpeed = (Dist * 0.25f) * 200.f;

	TrackCheck();

	CarFlip();

	if (m_pSkidMark)
	{
		m_pSkidMark->Update();
	}

}

void cCar::LastUpdate()
{
	if (GetPhysXData())
	{
		//���������Ϳ� �ڵ��� ����ȭ
		NxVec3 pos = GetPhysXData()->m_pActor->getGlobalPosition();
		D3DXVECTOR3 dPos;
		dPos.x = pos.x;
		dPos.y = pos.y;
		dPos.z = pos.z;

		NxF32 NxMat[9] = { 1,0,0,0,1,0,0,0,1 };
		GetPhysXData()->m_pActor->getGlobalPose().M.getColumnMajor(NxMat);

		cTransform::SetQuaternion(NxMat);
		cTransform::SetPosition(dPos + cTransform::GetUpVec() * 0.2f);
	}
}

void cCar::Render()
{
	Object::Render();

	//���������Ϳ� ���� ����ȭ
	for (int i = 0; i < vecWheels.size(); i++)
	{
		D3DXMATRIXA16 matW, matR, matT;
		D3DXMatrixIdentity(&matW);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);

		NxWheel* pWheel = m_carNxVehicle->getWheel(i);
		NxVec3 NxWheelPos = pWheel->getWheelPos();

		if (NxWheelPos.z < 0) NxWheelPos.z += 0.1f;
		else NxWheelPos.z -= 0.1f;
		NxWheelPos.y -= 0.2;

		D3DXMatrixTranslation(&matT, NxWheelPos.x, NxWheelPos.y, NxWheelPos.z);

		if (i < 2)	D3DXMatrixRotationY(&matR, -(D3DX_PI*0.5 + (m_wheelAngle * m_maxWheelAngle)));
		else D3DXMatrixRotationY(&matR, -D3DX_PI*0.5);
		matW = matR * matT;

		MgrD3DDevice->SetTransform(D3DTS_WORLD, &(matW * cTransform::GetMatrix(false, true, true)));
		vecWheels[i]->Render();
	}


	if (m_isAI)
	{
		for each (cAI* pAI in m_vecAI)
		{
			pAI->Render();
		}
	}

	if (m_pSkidMark)
	{
		m_pSkidMark->Render();
	}
}

void cCar::Destory()
{
	if (m_pSkidMark) m_pSkidMark->Destory();
	SAFE_DELETE(m_pSkidMark);
	Object::Destroy();
}

void cCar::CtrlPlayer()
{
	if (m_carNxVehicle)
	{
		//����
		float targetPower = 0.f;
		bool power = false;
		m_breakPower = 0.f;
		if (g_pKeyManager->isStayKeyDown(KEY_ACCELERATOR))
		{
			m_moterPower += m_moterAcc;
			if (m_moterPower > 1.f) m_moterPower = 1.f;
			targetPower = m_moterPower * m_maxMoterPower;
			power = true;
		}
		if (g_pKeyManager->isStayKeyDown(KEY_REVERSE))
		{
			m_moterPower -= m_moterAcc;
			if (m_moterPower < -1.f) m_moterPower = -1.f;
			targetPower = m_moterPower * m_maxMoterPower;
			power = true;
		}
		if (!power)
		{
			m_moterPower = 0.f;
			targetPower = m_moterPower * m_maxMoterPower;
			m_breakPower = m_maxMoterPower*0.5f;
		}

		//�ڵ�
		float targetAngle = m_wheelAngle * m_maxWheelAngle;
		bool handle = false;
		if (g_pKeyManager->isStayKeyDown(KEY_MOVE_LEFT))
		{
			m_wheelAngle += (m_wheelAcc);
			if (m_wheelAngle > 1.f) m_wheelAngle = 1.f;
			targetAngle = m_wheelAngle * m_maxWheelAngle;
			handle = true;
		}
		if (g_pKeyManager->isStayKeyDown(KEY_MOVE_RIGHT))
		{
			m_wheelAngle -= (m_wheelAcc);
			if (m_wheelAngle < -1.f) m_wheelAngle = -1.f;
			targetAngle = m_wheelAngle * (m_maxWheelAngle);
			handle = true;
		}
		if (!handle)
		{
			if (abs(m_wheelAngle) <= m_wheelAcc * 2) m_wheelAngle = 0.0f;
			else if (m_wheelAngle > 0) m_wheelAngle -= m_wheelAcc * 2;
			else if (m_wheelAngle < 0) m_wheelAngle += m_wheelAcc * 2;

			targetAngle = m_wheelAngle * m_maxWheelAngle;
		}

		//�̵�
		for (int i = 0; i < 4; i++)
		{
			NxWheel* wheel = m_carNxVehicle->getWheel(i);

			if (i < 2)
			{
				float value = (1 - (wheel->getRpm() / m_maxRpm));
				if (value < 0.5) value = 0.5f;
				wheel->setAngle(targetAngle * value);
			}
			if (wheel->getRpm() < m_maxRpm)	wheel->tick(false, targetPower, m_breakPower, g_pTimeManager->GetElapsedTime());
			else wheel->tick(false, 0, m_breakPower, g_pTimeManager->GetElapsedTime());
		}

		//�����ۻ��
		if (g_pKeyManager->isOnceKeyDown(KEY_FIRE_ITEM))
		{
			if (m_eHoldItem != ITEM_NONE)
			{
				//������ ��� �Լ� ȣ��
				g_pItemManager->FireItem(m_eHoldItem, this);
				m_nItemCount--;
				if (m_nItemCount == 0)
				{
					m_eHoldItem = ITEM_NONE;
					GetPhysXData()->m_pUserData->IsPickUp = NX_FALSE;
				}
				std::cout << "FIRE!" << std::endl;
			}
		}

		//RePosition
		if (g_pKeyManager->isOnceKeyDown(KEY_REPOSITION))
		{
			CarRunStop();
			if (m_countRapNum == -1)
			{
				GetPhysXData()->SetPosition(D3DXVECTOR3(0, 1, 0));
			}
			else
			{
				std::vector<Object*>* chexkBox = m_pTrack->GetCheckBoxsPt();
				D3DXVECTOR3 pos(0, 0, 0);
				pos = (*chexkBox)[m_currCheckBoxID]->GetPosition();
				pos.y = 1;
				GetPhysXData()->SetPosition(pos);
			}
		}

		//Fliping
		NxQuat quat = GetPhysXData()->m_pActor->getGlobalOrientationQuat();
		NxVec3 carUp = quat.transform(NxVec3(0, 1, 0), NxVec3(0, 0, 0));
		if (carUp.y < 0.0f)
		{
			if (g_pKeyManager->isOnceKeyDown(KEY_CAR_FLIP) && isFliping == false)
			{
				isFliping = true;
				CarRunStop();
			}
		}

		//SkidTest

		//�����ʱ�ȭ
		NxRay RayCar;
		RayCar.orig = NxVec3(m_position);
		RayCar.orig.y += 0.2f;
		RayCar.dir = NxVec3(0,-1,0);

		NxRaycastHit RayCarHit;
		RayCarHit.shape = NULL;
		g_pPhysXScene->raycastClosestShape(RayCar, NxShapesType::NX_ALL_SHAPES, RayCarHit);

		float rpm = GetNxVehicle()->getWheel(0)->getRpm() / m_maxRpm;
		if (fabsf(rpm) > 0.8f && fabs(m_wheelAngle) > 0.9f)
		{
			if (RayCarHit.distance < 0.2f)
			{
				m_pSkidMark->DrawSkidMark();
			}
		}

		if (g_pKeyManager->isStayKeyDown(VK_SHIFT))
		{
			if (RayCarHit.distance < 0.2f)
			{
				m_pSkidMark->DrawSkidMark();
			}
		}
		if (g_pKeyManager->isStayKeyDown(VK_SPACE))
		{
			m_pSkidMark->Destory();
		}

	}
}

void cCar::CtrlAI()
{
	for each (cAI* pAI in m_vecAI)
	{
		if (m_carNxVehicle) pAI->Update();
	}
}

//void cCar::GetRpm()
//{
//	float rpm;
//}

void cCar::TrackCheck()
{
	//üũ�ڽ� �� Ʈ�� ī����
	int checkId = GetPhysXData()->m_pUserData->CheckBoxID;
	//���� üũ
	if (m_currCheckBoxID == -1)
	{
		if (checkId == (*m_pTrack->GetCheckBoxsPt())[0]->GetPhysXData()->m_pUserData->CheckBoxID)
		{
			std::cout << "START" << std::endl;
			m_nextCheckBoxID = 1;
			m_currCheckBoxID = 0;	//üũ ����
			m_countRapNum = 0;
			m_rapTimeCount = 0.f;
		}
		return;
	}

	cCheckBox* pCheckBox = (cCheckBox*)(*m_pTrack->GetCheckBoxsPt())[m_nextCheckBoxID];
	int checkNextId = pCheckBox->GetPhysXData()->m_pUserData->CheckBoxID;

	//�浹�� ������ ���� üũ�ڽ� ������ ��ġ�ϴ� �� Ȯ��
	if (checkId == checkNextId)
	{

		cCheckBox* pCheckBox = (cCheckBox*)(*m_pTrack->GetCheckBoxsPt())[m_nextCheckBoxID];
		m_currCheckBoxID = m_nextCheckBoxID;
		m_nextCheckBoxID = pCheckBox->GetNextCheckBox()->GetPhysXData()->m_pUserData->CheckBoxID;

		if (m_currCheckBoxID == 0)
		{
			m_countRapNum++;
			if (m_bastRapTimeCount > m_rapTimeCount || m_bastRapTimeCount < 0.0f)
			{
				m_bastRapTimeCount = m_rapTimeCount;

			}
			std::cout << "Rap::" << m_countRapNum
				<< "\t rapTime::" << m_rapTimeCount
				<< "\t bastRapTime::" << m_bastRapTimeCount
				<< std::endl;
			m_rapTimeCount = 0.f;
		}

		std::cout << "Track::" << m_countRapNum
			<< "\t CcheckBox::" << m_currCheckBoxID
			<< "\t NcheckBox::" << m_nextCheckBoxID
			<< std::endl;
	}
	//�ð��� ���� ������.
	if (m_countRapNum < 3)
	{
		m_rapTimeCount += g_pTimeManager->GetElapsedTime();
		m_totlaTimeCount += g_pTimeManager->GetElapsedTime();
	}
}

void cCar::RunEnd()
{
	for (int i = 0; i < 4; i++)
	{
		NxWheel* wheel = m_carNxVehicle->getWheel(i);
		if (wheel->getRpm() < m_maxRpm)	wheel->tick(false, 0, m_maxMoterPower, 1.f / 60.f);
	}
}

void cCar::CarFlip()
{
	if (isFliping)
	{
		CarRunStop();

		NxQuat quat = m_carNxVehicle->getActor()->getGlobalOrientationQuat();
		NxVec3 carFront = quat.transform(NxVec3(1, 0, 0), NxVec3(0, 0, 0));
		NxF32 angle = carFront.dot(NxVec3(1, 0, 0));
		angle = acosf(angle);

		NxVec3 arrow = carFront.cross(NxVec3(1, 0, 0));
		if (arrow.y > 0)
		{
			angle *= -1;
		}

		NxQuat quat_;
		quat.zero();
		quat.fromAngleAxisFast(angle, NxVec3(0, 1, 0));

		NxActor* p = m_carNxVehicle->getActor();
		p->setGlobalOrientationQuat(quat);

		NxVec3 carPos = p->getGlobalPose().t;
		p->getGlobalPose().t.add(carPos, NxVec3(0, 3, 0));

		isFliping = false;
	}
}

void cCar::CarRunStop()
{
	if (GetPhysXData())
	{
		GetPhysXData()->m_pActor->putToSleep();
		for (int i = 0; i < 4; i++)
		{
			m_carNxVehicle->getWheel(i)->getWheelShape()->getActor().putToSleep();
		}
	}
}
