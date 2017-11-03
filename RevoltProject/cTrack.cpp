#include "stdafx.h"
#include "cTrack.h"
#include "cLight.h"
#include "cCheckBox.h"
#include "cStuff.h"
#include "cFollowPoint.h"
#include "cPickUp.h"



cTrack::cTrack()
	:m_nLightIdx(11)
{
	//	pVeh = NULL;

		//�ӽ� ��� ������
	cTrack::SetData();

	//	*camPos = D3DXVECTOR3(0 - 5, 0 + 5, 0);
	//	*camLookTarget = D3DXVECTOR3(0, 0, 0);
	//
	//	g_pCamManager->SetCamPos(camPos);
	//	g_pCamManager->SetLookAt(camLookTarget);
}


cTrack::~cTrack()
{
}

void cTrack::Update()
{
	for each(Object* pObj in m_vecObject)
	{
		pObj->Update();
	}

}

void cTrack::LastUpdate()
{
	for each(Object* pObj in m_vecObject)
	{
		pObj->LastUpdate();
	}
}

void cTrack::Render()
{
	Object::Render();
	for each(Object* pObj in m_vecObject)
	{
		pObj->Render();
	}
}

void cTrack::SetData()
{

}

void cTrack::LoadTrack(std::string FileName)
{
	Destroy();// ������ ������ �ִ� ���� ������

	std::string fullpath = "Maps/" + FileName + ".scn";
	std::fstream Load;
	Load.open(fullpath);

	char szTemp[1024];
	if (Load.is_open())
	{
		while (1)
		{
			if (Load.eof()) break;

			Load.getline(szTemp, 1024);
			if (szTemp[0] == ' ' || szTemp[0] == '\t') continue;
			else if (szTemp[0] == '/') continue;
			else if (szTemp[0] == 'M') // Map Load
			{
				char szMapFile[1024];
				sscanf_s(szTemp, "%*s %s", szMapFile, 1024);
				std::string Folder = "Maps/" + FileName;
				std::string Name = FileName + ".obj";
				SetMeshData(new cMesh);
				GetMeshData()->LoadMesh(Folder, Name);
				CreateTrackPhysX();
			}
			else if (szTemp[0] == 'O') //Object Load
			{
				Object* Obj = NULL;

				int tag;
				Load.getline(szTemp, 1024);
				sscanf_s(szTemp, "%*s %d", &tag);

				ePhysXTag physxTag = E_PHYSX_TAG_NONE;
				switch (tag)
				{
				case E_OBJECT_CHECKBOX:
				{
					Obj = new cCheckBox;
					physxTag = ePhysXTag::E_PHYSX_TAG_CHECKBOX;	break;
				}
				case E_OBJECT_FOLLOWPOINT:   Obj = new cFollowPoint;	physxTag = ePhysXTag::E_PHYSX_TAG_NONE;	break;
				case E_OBJECT_CAR: break;
				case E_OBJECT_MAP: break;
				case E_OBJECT_LIGHT:		Obj = new cLight;			physxTag = ePhysXTag::E_PHYSX_TAG_NONE;	break;
				case E_OBJECT_STUFF:		Obj = new cStuff;			physxTag = ePhysXTag::E_PHYSX_TAG_NONE;	break;
				case E_OBJECT_CAMERA: break;
				case E_OBJECT_PICKUP:		Obj = new cPickUp;			physxTag = ePhysXTag::E_PHYSX_TAG_PICKUP;	break;
				case E_OBJECT_END: break;
				case E_OBJECT_NONE:   break;
				default: break;
				}

				Obj->SetTag((eOBJECT_TAG)tag);
				USERDATA* pUserData = new USERDATA;
				pUserData->USER_TAG = physxTag;
				cPhysX* physx = new cPhysX;
				NxShapeType type((NxShapeType)0);
				NxVec3 position(0, 0, 0);
				NxVec3 sizeValue(0, 0, 0);
				NxF32 matR[9] = { 1,0,0,0,1,0,0,0,1 };

				bool isTrigger = false;
				bool isStatic_ = false;
				bool isGravity = true;

				NxVec3 worldPosition(0, 0, 0);
				NxVec3 localPosition(0, 0, 0);

				//Obj->SetPhysXData(physx);

				std::string strName;
				Load >> strName;
				Load >> strName;
				Obj->SetObjName(strName);

				while (1)
				{
					Load.getline(szTemp, 1024);
					if (szTemp[0] == 'I') // Attribute
					{
						int nID = 0;
						sscanf_s(szTemp, "%*s %d", &nID);
						Obj->SetID((eOBJECT_ID)nID);
						cMesh* mesh;
						if (Obj->GetTag() == E_OBJECT_CHECKBOX || nID == E_OBJECT_FOLLOWPOINT)
						{
							mesh = NULL;
						}
						else
						{
							mesh = new cMesh;
							std::string folder = "Objects/" + Obj->GetObjName();
							std::string fileName = Obj->GetObjName() + ".obj";
							if (mesh) mesh->LoadMesh(folder, fileName);
						}
						Obj->SetMeshData(mesh);
					}
					else if (szTemp[0] == 'P') //Position
					{
						float x, y, z;
						sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
						Obj->SetPosition(D3DXVECTOR3(x, y, z));
						worldPosition.x = x;
						worldPosition.y = y;
						worldPosition.z = z;
					}
					else if (szTemp[0] == 'S') //Scale
					{
						float x, y, z;
						sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
						Obj->SetSize(D3DXVECTOR3(x, y, z));
					}
					else if (szTemp[0] == 'R') //Rotation
					{
						float x, y, z;
						sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
						Obj->SetQuaternion(D3DXVECTOR3(x, y, z));
					}
					else if (szTemp[0] == 'X') //Physics
					{
						//���������Է�
						if (szTemp[2] == 'A')
						{
							int isActor = 0;
							sscanf_s(szTemp, "%*s %d", &isActor);
							//	Obj->SetIsActor(isActor);
						}
						else if (szTemp[2] == 'T')
						{
							int nType = 0;
							sscanf_s(szTemp, "%*s %d", &nType);
							type = (NxShapeType)nType;
						}
						else if (szTemp[2] == 'O')
						{
							int t, s, g;
							sscanf_s(szTemp, "%*s %d %d %d", &t, &s, &g);
							isTrigger = t;
							isStatic_ = s;
							isGravity = g;
						}
						else if (szTemp[2] == 'P')
						{
							float x, y, z;
							sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
							position.x = x;
							position.y = y;
							position.z = z;

							localPosition.x = x;
							localPosition.y = y;
							localPosition.z = z;

						}
						else if (szTemp[2] == 'S')
						{
							float x, y, z;
							sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
							sizeValue.x = x;
							sizeValue.y = y;
							sizeValue.z = z;
						}
						else if (szTemp[2] == 'F')
						{
							float F[9];
							sscanf_s(szTemp, "%*s %f %f %f %f %f %f %f %f %f",
								&F[0], &F[1], &F[2], &F[3], &F[4], &F[5], &F[6], &F[7], &F[8]);
							for (int i = 0; i < 9; i++)
							{
								matR[i] = F[i];
							}
						}
					}
					else if (szTemp[0] == '#') //Push
					{
						if (Obj->GetTag() == E_OBJECT_LIGHT)
						{
							// Light Manager�� ���
							cLight* light = (cLight*)Obj;
							light->SetupPoint(m_nLightIdx++, C_WHITE, light->GetPosition(), 20);
							g_pLightManager->AddLight(light->GetLightIndex(), light);
						}
						else if (Obj->GetTag() == E_OBJECT_PICKUP)
						{
							NxActor* pActor = MgrPhysX->CreateActor(
								type,
								position + worldPosition + localPosition,
								matR,
								sizeValue,
								E_PHYSX_MATERIAL_NONE,
								pUserData,
								isTrigger,
								isStatic_,
								isGravity);
							if (pActor)
							{
								physx->m_pActor = pActor;
								physx->m_pUserData = pUserData;
								Obj->SetPhysXData(physx);
							}

							m_vecObject.push_back(Obj);

							//�Ⱦ�������Ʈ�� ��� ������ �ʿ��ϱ⶧���� �������ش�.
							cLight* light = new cLight;
							light->SetupPoint(m_nLightIdx++, C_YELLOW, light->GetPosition(), 5);
							g_pLightManager->AddLight(light->GetLightIndex(), light);
						}
						else if (Obj->GetTag() == E_OBJECT_CHECKBOX)
						{
							//�ʿ� ��ġ�Ǿ��ִ� ��ֹ���...
							NxActor* pActor = MgrPhysX->CreateActor(
								type,
								position + worldPosition + localPosition,
								matR,
								sizeValue,
								E_PHYSX_MATERIAL_NONE,
								pUserData,
								isTrigger,
								isStatic_,
								isGravity);
							if (pActor)
							{
								physx->m_pActor = pActor;
								physx->m_pUserData = pUserData;
								Obj->SetPhysXData(physx);
							}
							std::string id = Obj->GetObjName();
							m_mapCheckBox[id] = Obj;
						}
						else
						{
							//�ʿ� ��ġ�Ǿ��ִ� ��ֹ���...
							NxActor* pActor = MgrPhysX->CreateActor(
								type,
								position + worldPosition + localPosition,
								matR,
								sizeValue,
								E_PHYSX_MATERIAL_03,
								pUserData,
								isTrigger,
								isStatic_,
								isGravity);
							if (pActor)
							{
								physx->m_pActor = pActor;
								Obj->SetPhysXData(physx);
							}

							m_vecObject.push_back(Obj);
						}
						break;

					}
				} // << : while Object
			}
		} // << : while ����
		Load.close();
	}
	else //���� ���� ����
	{
		std::string pritfOut(FileName + ": ������ ã�� �� �����ϴ�");
		MessageBoxA(g_hWnd, pritfOut.c_str(), "����", MB_OK);
	}

	int i = 0;
	for (std::map<std::string, Object*>::iterator it = m_mapCheckBox.begin(); it != m_mapCheckBox.end(); it++)
	{
		it->second->GetPhysXData()->m_pUserData->CheckBoxID = i++;
	}
	//for each(Object* pCheck in m_mapCheckBox)
//{
//
//}
}

void cTrack::CreateTrackPhysX()
{
	if (GetMeshData()->m_pMesh)	//���� Ư���� ���ڰ��� �ְ� ���� �ʴ´�. (���� �ִٸ� ������ ����)
	{
		cPhysX* physx = new cPhysX;

		USERDATA* userData = new USERDATA;
		NxActorDesc actorDesc;	actorDesc.setToDefault();
		NxBodyDesc  bodyDesc;	bodyDesc.setToDefault();

		//bodyDesc.flags |= NX_BF_KINEMATIC;

		NxTriangleMeshShapeDesc shapeDesc = MgrPhysX->CreateTringleMesh(GetMeshData()->m_pMesh);
		shapeDesc.materialIndex = 1; // ���� : 0 (default)��
		shapeDesc.localPose.t = NxVec3(0, 0, 0);

		actorDesc.shapes.pushBack(&shapeDesc);
		//actorDesc.body = &bodyDesc;

		actorDesc.globalPose.t = NxVec3(0, 0, 0);
		actorDesc.userData = (userData);
		actorDesc.name = "map";

		physx->m_pActor = MgrPhysXScene->createActor(actorDesc);

		Object::SetPhysXData(physx);
		//���� ���� ������ �ְ� ���� �ʱ� ������  SetActor(NULL) �̴�.
	}
}
