#include "stdafx.h"
#include "RacingScene.h"
#include "cTrack.h"
#include "cLight.h"
#include "cCar.h"
#include "InGameUI.h"
#include "UITextImageView.h"
#include "cSkyBox.h"
#include "c321GO.h"
#include "cAI_Master.h"

RacingScene::RacingScene()
	: m_select(99)
	, m_pSkyBox(NULL)
	, m_isPlayBGM(false)
{}

RacingScene::~RacingScene() {}

void RacingScene::Setup()
{
	playerIndex = 0;
	m_eRaceProg = RACE_PROG_READY;

	//TrackEndCount ���ƾ� �Ǵ� ���� ��	
	m_trackEndCount = 3;

	//ī�޶� �ʱⰪ
	m_camPos = new D3DXVECTOR3(70, 5, 0);
	m_camLookTarget = new D3DXVECTOR3(0, 0, 0);

	UITextImageView::m_Select = &m_select;

	D3DXCreateSprite(g_pD3DDevice, &m_Sprite);
	g_pCamManager->SetLookAt(&D3DXVECTOR3(0, 0, 0));

	m_pTrack = new cTrack;
	if (m_pTrack)
	{
		m_pTrack->Setup();
		m_pTrack->LoadTrack(g_pDataManager->mapName);
	}
	m_nLightIDCount = 0;

	m_pLightSun = new cLight;
	m_pLightSun->SetupDirectional(0, D3DCOLOR_XRGB(192,192,192), { 0,-1,0 });
	m_pLightSun->Switch(true);

	g_pCamManager->SetCamPos(m_camPos);
	g_pCamManager->SetLookAt(m_camLookTarget);

	//�ں��Ʈ
	g_pD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));

	m_pSkyBox = new cSkyBox;
	m_pSkyBox->Setup("Maps/SkyBox", "SkyBox.obj");

	int i = 0;
	for each(cPlayerData* p in g_pDataManager->vecPlayerData)
	{
		if (i  == m_pTrack->GetStartPositions().size()) break;
		CreateCar(m_pTrack->GetStartPositions()[i], i,p->ID, p->CAR_NAME, m_trackEndCount, p->IsAI, p->isUser);
		i++;
	}

	m_pInGameUI = new InGameUI;
	LinkUI(0); // �ΰ��� InGameUI::Setup(); ���� ��ġ�ؾ���, new InGameUI �� ����Ǿ� �־�� ��.
	m_pInGameUI->Setup();
	
	g_pNetworkManager->SetResetKeyEvent();


	
//	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

void RacingScene::Destroy()
{
	SAFE_DESTROY(m_pTrack);
	SAFE_DELETE(m_pTrack);

	m_pLightSun->Destroy();
	SAFE_DELETE(m_pLightSun);

	//������ ���� �ּ�ó��
	//m_pInGameUI->Destroy();
	//SAFE_DELETE(m_pInGameUI);
	SAFE_DESTROY(m_pSkyBox);
	SAFE_DELETE(m_pSkyBox);
	SAFE_DELETE(m_camPos);
	SAFE_DELETE(m_camLookTarget);

	for each(cCar* p in vecCars)
	{
		p->Destroy();
		SAFE_DELETE(p);
	}
	vecCars.clear();

	g_pDataManager->Reset();
}

void RacingScene::Update()
{
	GameNode::Update();
	SAFE_UPDATE(m_pTrack);

	if (!m_isPlayBGM)
	{
		g_pSoundManager->Play("BGM_RACE", 0.5f);
		m_isPlayBGM = true;
	}

	if (g_pNetworkManager->GetIsInGameNetwork())
		NetworkLoop();		// ��Ʈ��ũ ������ �޴� �޼���

	switch (m_eRaceProg)
	{
	case RACE_PROG_READY:
	case RACE_PROG_SET:
	case RACE_PROG_GO:
	{
		if (m_eRaceProg == RACE_PROG_GO)
		{
			m_pInGameUI->UpdateRaceTime();

			for (int i = 0; i < vecCars.size(); i++)
			{
				vecCars[i]->m_isCtl = true;;
			}
		}
		if (g_pNetworkManager->GetIsInGameNetwork())
		{
			SetNetworkCarData();
			//m_pInGameUI->UpdateRaceTime();
		}
		else
		{
			for (int i = 0; i < vecCars.size(); i++)
			{
				if (IsCarRunTrue(vecCars[i])) vecCars[i]->Update();

				if (!IsCarRunTrue(vecCars[0])) m_eRaceProg = RACE_PROG_FINISH;
			}
		}

		UpdateRnak();
	}
	break;
	case RACE_PROG_FINISH:
	{
		for (int i = 0; i < vecCars.size(); i++)
		{
			vecCars[i]->RunEnd();
		}
	}
	break;
	default: break;
	}

	if (m_pInGameUI)
	{
		m_pInGameUI->Update();
	}


	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		m_eRaceProg = RACE_PROG_FINISH;
		g_SceneManager->ChangeScene("Lobby");
	}

}

void RacingScene::Render()
{
	if (m_pSkyBox)
	{
		m_pSkyBox->Render();
	}

	if (m_pTrack)
	{
		m_pTrack->Render();
	}

	for each(cCar* p in vecCars)
	{
		p->Render();
	}

	m_pInGameUI->Render(m_Sprite);
}

void RacingScene::LastUpdate()
{
	m_pTrack->LastUpdate();

	for each(cCar* p in vecCars)
	{
		p->LastUpdate();
	}

	UpdateCamera();
	UpdateSound();
}

void RacingScene::UpdateCamera()
{

#define CAM_X (*m_camPos).x
#define CAM_Y (*m_camPos).y
#define CAM_Z (*m_camPos).z
#define CAM_POS (*m_camPos)

	//ȸ�� ��Ʈ���� �޾ƿ�
	//D3DXMATRIXA16 matR = vecCars[0]->GetCarRotMatrix();
	D3DXMATRIXA16 matR;
	matR = vecCars[0]->GetMatrix(false, true, false); //�̰� ����ϸ� �ణ ����Ȯ��

	float distToCar = 5; //������ �Ÿ�
	float Height = 1; //ī�޶� ����
	float LerpSpd = 0.02f;

	D3DXVECTOR3 carDir = { 1,0,0 };
	D3DXVec3TransformNormal(&carDir, &carDir, &matR);

	//�ڵ��� ������
	D3DXVECTOR3 carPos = {
		vecCars[0]->GetPosition().x,
		vecCars[0]->GetPosition().y + 0.5f ,
		vecCars[0]->GetPosition().z };

	*m_camLookTarget = carPos;//D3DXVECTOR3(pos.x, pos.y + 2.f, pos.z);

	D3DXVECTOR3 camDir = (*m_camLookTarget) - CAM_POS;
	D3DXVec3Normalize(&camDir, &camDir);

	//�����ʱ�ȭ
	NxRay RayCam;
	RayCam.orig = NxVec3(carPos);
	RayCam.dir = NxVec3(-carDir);

	NxRaycastHit RayCamHit;
	RayCamHit.shape = NULL;
	g_pPhysXScene->raycastClosestShape(RayCam, NxShapesType::NX_ALL_SHAPES, RayCamHit, 0xffffffff, distToCar);

	//�����ʱ�ȭ
	NxRay RayCamVertical;
	RayCamVertical.orig = NxVec3(carPos);
	RayCamVertical.dir = NxVec3(0, 1, 0);

	NxRaycastHit RayCamVerticalHit;
	RayCamVerticalHit.shape = NULL;

	g_pPhysXScene->raycastClosestShape(RayCamVertical, NxShapesType::NX_ALL_SHAPES, RayCamVerticalHit, 0xffffffff, Height);

	float x = carPos.x - (carDir.x * distToCar);
	float y = carPos.y - (carDir.y * distToCar) + Height;
	float z = carPos.z - (carDir.z * distToCar);

	float fCamHeight = Height;

	if (RayCamHit.shape)
	{
		if (RayCamHit.shape->getActor().getName())
		{
			std::string str = RayCamHit.shape->getActor().getName();

			if (str == "map")
			{
				x = RayCamHit.worldImpact.x;
				//y = carPos.y + Height;//RayCamHit.worldImpact.y;
				y = carPos.y + fCamHeight;
				z = RayCamHit.worldImpact.z;
			}
		}
	}

	if (RayCamVerticalHit.shape)
	{
		if (RayCamVerticalHit.shape->getActor().getName())
		{
			std::string str = RayCamVerticalHit.shape->getActor().getName();
			if (str == "map")
			{
				fCamHeight = RayCamVerticalHit.distance;
				y = carPos.y + fCamHeight;
			}
		}
	}

	// ī�޶� ������
	D3DXVECTOR3 vDest = { x,y,z };

	// ī�޶� ����

	if(m_eRaceProg == RACE_PROG_READY)
	{
		LerpSpd = 0.02f;
		D3DXVECTOR3 dist = *m_camPos - vDest;
		float fDist = D3DXVec3Length(&dist);
		if (fDist < 0.1)
		{
			m_pInGameUI->Get321goPt()->StartCount();
			m_eRaceProg = RACE_PROG_SET;
		}
	}
	else if (m_eRaceProg == RACE_PROG_SET)
	{
		LerpSpd = 0.05f;
	}
	else
	{
		LerpSpd = 0.2f;
	}

	D3DXVec3Lerp(m_camPos, m_camPos, &vDest, LerpSpd);
	//CAM_POS = vDest;
	g_pCamManager->SetCamPos(m_camPos);
	g_pCamManager->SetLookAt(m_camLookTarget);
}

void RacingScene::UpdateSound()
{
	D3DXVECTOR3 forward = *g_pCamManager->GetCamPos() - *g_pCamManager->GetLookAt();
	D3DXVec3Normalize(&forward, &forward);

	g_pSoundManager->Setup3DCamera(*g_pCamManager->GetCamPos(), forward);
}

void RacingScene::UpdateRnak()
{
	m_vecRank.clear();
	std::map<float, std::string> mapRank;

	for (int i = 0; i < vecCars.size(); i++)
	{
		mapRank.insert(std::make_pair(vecCars[i]->GetRankPoint(), vecCars[i]->GetUserNameW()));
	}

	std::map<float, std::string>::iterator iter;
	for (iter = mapRank.begin();
		iter != mapRank.end();
		iter++)
	{
		m_vecRank.insert(m_vecRank.begin(),iter->second);
	}
	
	if (g_pKeyManager->isOnceKeyDown('U'))
	{
		for (int i = 0; i < m_vecRank.size(); i++)
		{
			std::cout << m_vecRank[i] << std::endl;
		}
		std::cout << std::endl;
	}
}

bool RacingScene::IsCarRunTrue(cCar* pCar)
{
	return m_trackEndCount > pCar->GetCountRapNum();
}

void RacingScene::CreateCar(D3DXVECTOR3 setPos, int playerID, std::string userName, std::string carName, int trackEndCount, bool isAI, bool isUser)
{
	cCar* pCar = new cCar;
	AI_DATA aiData(pCar, m_pTrack, &vecCars);
	pCar->SetPlayerID(playerID);
	pCar->LoadCar(carName);
	pCar->SetAI(isAI, aiData);
	pCar->SetIsUser(isUser);
	pCar->SetUserName(userName);
	pCar->SetEndRapNum(&trackEndCount);

	vecCars.push_back(pCar);

	pCar->GetPhysXData()->SetPosition(m_pTrack->GetStartPositions()[playerID]);
}

void RacingScene::LinkUI(int playerID)
{
	m_pInGameUI->LinkCarPt(vecCars[playerID]);
	vecCars[playerID]->LinkUI(m_pInGameUI);
	m_pInGameUI->LinkTrack(m_pTrack);
	m_pInGameUI->LinkRacingScene(this);
	for (int i = 0; i < vecCars.size(); i++)
	{
		vecCars[i]->LinkTrackPt(m_pTrack);
	}
}

void RacingScene::NetworkLoop()
{
	std::string str = "";

	char* pchIP = NULL;
	char* pchKEY = NULL;
	char* pchPOS = NULL;
	char* pchX = NULL;
	char* pchY = NULL;
	char* pchZ = NULL;

	str = "$" + g_pNetworkManager->GetUserIP() + "$" + g_pNetworkManager->GetKeYString();
	g_pNetworkManager->SendMsg(str.c_str());

	if (g_pNetworkManager->RecvMsg())
	{
		str = g_pNetworkManager->GetMsg();
	}

	pchIP = strtok((char*)str.c_str(), "$");
	pchKEY = strtok(NULL, "$");

	////pchPOS = strtok(NULL, "@");
	//
	if (pchIP != NULL && g_pNetworkManager->GetUserIP().find(pchIP) == -1)
	{
		//
		printf("%s\n", pchKEY);
	}
}

void RacingScene::SetNetworkCarData()
{
	g_pNetworkManager->SetResetKeyEvent();

	if (IsCarRunTrue(vecCars[g_pNetworkManager->GetCarIndex()])) vecCars[g_pNetworkManager->GetCarIndex()]->Update();
	if (!IsCarRunTrue(vecCars[g_pNetworkManager->GetCarIndex()])) m_eRaceProg = RACE_PROG_FINISH;

	for (int i = 0; i < vecCars.size(); i++)
	{
		if (IsCarRunTrue(vecCars[i])) vecCars[i]->Update();

		if (!IsCarRunTrue(vecCars[i])) m_eRaceProg = RACE_PROG_FINISH;
	}
}
