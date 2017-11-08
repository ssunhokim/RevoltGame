#include "stdafx.h"
#include "MainGame.h"
#include "Grid.h"

#include "LobbyScene.h"
#include "RacingScene.h"

#include "cCar.h"

//======================================
// - written by �輱ȣ
// - MainGame -> ���ӽ���
//======================================

MainGame::MainGame()
	:m_pGrid(NULL)
{
}

MainGame::~MainGame()
{

}

void MainGame::Setup()
{
	//PhysX �ʰ�ȭ
	g_pPhysX->InitNxPhysX();


	//======================================
	// - written by �輱ȣ
	// - MainGame -> �ʱ�ȭ �۾�
	//======================================

	//======================================
	// - written by ���¼�
	// - MainGame -> 
	// ������ ���ΰ��ӿ��� �ҷ����� Lobby�� Map�� LobbyScene���� ����
	// SceneManager���� ���� ��ó��
	// Camera Ŭ���� �Ŵ����� ���
	//======================================

	//m_pGrid = new Grid;
	//m_pGrid->Setup();

	g_SceneManager->AddScene("Lobby", new LobbyScene);
	g_SceneManager->AddScene("Race", new RacingScene);
	g_SceneManager->ChangeScene("Race");

	g_pCamManager->Setup(NULL);
	g_pItemManager->Init();
	g_pTimeManager->Setup();
	//
	//	SetAddSound();
	//	MgrPhysXScene->setUserTriggerReport(new TriggerCallback());
	IsUpdate = false;

	g_pTextManager->AddFont(L"����ü", "����ü_7", 7);
}

void MainGame::Update()
{
	if (IsUpdate == true) return;
	IsUpdate = true;
	SAFE_UPDATE(g_pTimeManager);

	SAFE_UPDATE(g_SceneManager);
	SAFE_UPDATE(g_pLightManager);
	SAFE_UPDATE(g_pItemManager);

	//PhysX �ù� ��
	//g_pTimeManager->GetElapsedTime());//
//	MgrPhysXScene->simulate((1.f/60.f));	//������ ����

	MgrPhysXScene->simulate((float)(1.f/60.f));	//������ ����
	MgrPhysXScene->flushStream();
	MgrPhysXScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
	//	MgrPhysXScene->checkResults(NX_RIGID_BODY_FINISHED, true);


		//PhysX�� ���� ����ȭ
	if (g_SceneManager) g_SceneManager->LastUpdate();
	SAFE_UPDATE(g_pCamManager);
}

void MainGame::Render()
{
	if (IsUpdate == false) return;
	IsUpdate = false;

	SAFE_RENDER(g_pTimeManager);

	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(47, 121, 112), 1.0F, 0);
		// �׸��� ����
	g_pD3DDevice->BeginScene();

	SAFE_RENDER(g_SceneManager);

	g_pItemManager->Render();

	g_pPhysX->Render();

	// Ÿ�� �Ŵ��� ���� �ؾ���

	g_pTimeManager->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void MainGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

}

void MainGame::SetAddSound()
{
	g_pSoundManager->LoadSound("Sound", "menuUpDown.wav", false);
	g_pSoundManager->LoadSound("Sound", "menuNext.wav", false);
	g_pSoundManager->LoadSound("Sound", "menuPrev.wav", false);
	g_pSoundManager->LoadSound("Sound", "menuLeftRight.wav", false);
	g_pSoundManager->LoadSound("Sound", "boxslide.wav", false);
	g_pSoundManager->LoadSound("Sound", "honkgood.wav", false);
}