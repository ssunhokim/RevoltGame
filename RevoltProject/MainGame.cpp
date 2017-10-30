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

	g_pCamManager->Setup(NULL);
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

	g_SceneManager->ChangeScene("Race"); // ���� ������ �κ�
	//g_SceneManager->ChangeScene("Race");

	/*   ���� �ʱ�ȭ �۾�   */
	SetAddSound();



	D3DLIGHT9 light;
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0);
	light.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0);
	light.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0);
	D3DXVECTOR3 dir = { 0,-1,1 };
	D3DXVec3Normalize(&dir, &dir);
	light.Direction = dir;
	
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
//	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &TestMesh, NULL);

	pCar = new cCar;
	pCar->LoadMesh("tc1");
}

void MainGame::Update()
{
	SAFE_UPDATE(g_pLightManager);
	SAFE_UPDATE(g_pCamManager);
	SAFE_UPDATE(g_SceneManager);
}

void MainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL,	D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,	D3DCOLOR_XRGB(47, 121, 112),1.0F, 0);
	g_pD3DDevice->BeginScene();
	// �׸��� ����

	//SAFE_RENDER(m_pGrid);
	SAFE_RENDER(g_SceneManager);

	SAFE_RENDER(m_pGrid);




	g_pPhysX->Render();
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);




	//PhysX �ù� ��
	MgrPhysXScene->simulate((float)(1.0f/60.f));	//������ ����
	MgrPhysXScene->flushStream();
	MgrPhysXScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
}

void MainGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
}

void MainGame::SetAddSound()
{
	g_pSoundManager->LoadSound("Sound", "menuUpDown.wav", false);
	g_pSoundManager->LoadSound("Sound", "menuNext.wav",false);
	g_pSoundManager->LoadSound("Sound", "menuPrev.wav", false);
	g_pSoundManager->LoadSound("Sound", "menuLeftRight.wav", false);
	g_pSoundManager->LoadSound("Sound", "boxslide.wav", false);
	g_pSoundManager->LoadSound("Sound", "honkgood.wav", false);
}


