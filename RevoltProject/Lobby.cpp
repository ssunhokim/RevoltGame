#include "stdafx.h"
#include "Lobby.h"

/*   UI헤더파일 선언   */
#include "UIObject.h"
#include "UIImageView.h"
#include "UITextImageView.h"

#include "ObjectLoader.h"
#include "MtlTex.h"
#include "Camera.h"

#include "TextLoader.h"

Lobby::Lobby()
	: m_pSprite(NULL)
	, m_pObjMesh(NULL)
	, m_stateLobby(INTRO1)
	, m_time(0.0f)
	, m_select(0)
{
}

Lobby::~Lobby()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pObjMesh);

	for each(auto a in m_mapLobby)
	{
		delete[] a.second->m_pNextLob;
		SAFE_DELETE(a.second->m_pObject);
	}
}

void Lobby::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	UITextImageView::m_Select = &m_select;

	SetUpUI();

	ObjectLoader loader;
	m_pObjMesh = loader.LoadMesh(
		m_vecObjMtlTex,
		"Maps/Front", "Front.obj");
}

void Lobby::Update()
{
	if (m_time > m_mapLobby[m_stateLobby]->m_time)
	{
		m_time = 0.0f;

		if (m_stateLobby == INTRO1)
			m_stateLobby = INTRO2;
		else if (m_stateLobby == INTRO2)
			m_stateLobby = INTRO3;
		else if (m_stateLobby == INTRO3)
		{
			m_stateLobby = START_LOBBY;
			m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);
		}
	}
	else
	{
		m_time++;
	}

	KeyEvent();

	m_mapLobby[m_stateLobby]->m_pObject->Update();
}

void Lobby::Render()
{
	if (m_stateLobby > INTRO3)
	{
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

		D3DXMATRIXA16	matWorld, matS, matR;

		D3DXMatrixIdentity(&matWorld);

		g_pD3DDevice->SetTransform(D3DTS_WORLD,
			&matWorld);

		for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
		{
			g_pD3DDevice->SetMaterial(
				&m_vecObjMtlTex[i]->GetMaterial());

			if (m_vecObjMtlTex[i]->GetTexture() != NULL)
			{
				g_pD3DDevice->SetTexture(
					0,
					m_vecObjMtlTex[i]->GetTexture());
			}
			m_pObjMesh->DrawSubset(i);
		}
	}
	if (m_mapLobby[m_stateLobby]->m_pObject)
		m_mapLobby[m_stateLobby]->m_pObject->Render(m_pSprite);
}

void Lobby::KeyEvent()
{
	if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
	{
		m_select++;

		if (m_mapLobby[m_stateLobby]->m_count <= m_select)
			m_select = 0;
		g_pSoundManager->Play("menuUpDown.wav", 1.0f);
	}
	
	if (g_pKeyManager->isOnceKeyDown(VK_UP))
	{
		m_select--;

		if (m_select < 0)
			m_select = m_mapLobby[m_stateLobby]->m_count - 1;

		g_pSoundManager->Play("menuUpDown.wav", 1.0f);
	}

	/*   엔터 키 눌렀을 때 다음 로비로 들어가는 이벤트   */
	if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		m_stateLobby = m_mapLobby[m_stateLobby]->m_pNextLob[m_select];
		m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);		// 카메라 변경
		m_time = 0.0f;

		if(m_stateLobby > INTRO3)
			g_pSoundManager->Play("menuNext.wav", 1.0f);
	}

	/*   ESC 키 눌렀을 때 이전 로비로 들어가는 이벤트   */
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		m_stateLobby = m_mapLobby[m_stateLobby]->m_prevLob;
		m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);
		g_pSoundManager->Play("menuNext.wav", 1.0f);
	}

	if (g_pKeyManager->isStayKeyDown(VK_CONTROL))
	{
		m_stateLobby = START_LOBBY;
		m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);
	}
}

void Lobby::SetUpUI()
{
	UIImageView* pImageView1 = new UIImageView;
	pImageView1->SetPosition(0, 0);
	pImageView1->SetTexture("Maps/Front/Image/intro1.png");

	UIImageView* pImageView2 = new UIImageView;
	pImageView2->SetPosition(0, 0);
	pImageView2->SetTexture("Maps/Front/Image/intro2.png");

	UIImageView* pImageView3 = new UIImageView;
	pImageView3->SetPosition(0, 0);
	pImageView3->SetTexture("Maps/Front/Image/intro3.png");

	UITextImageView* pImageView4 = new UITextImageView;
	pImageView4->SetIndex(0);
	pImageView4->SetText("APPLE");
	pImageView4->SetVecPos(D3DXVECTOR3(225, 130, 0));
	pImageView4->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView5 = new UITextImageView;
	pImageView5->SetIndex(1);
	pImageView5->SetText("BANANA");
	pImageView5->SetVecPos(D3DXVECTOR3(225, 150, 0));
	pImageView5->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView6 = new UITextImageView;
	pImageView6->SetIndex(2);
	pImageView6->SetText("MELON");
	pImageView6->SetVecPos(D3DXVECTOR3(225, 170, 0));
	pImageView6->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView7 = new UITextImageView;
	pImageView7->SetIndex(3);
	pImageView7->SetText("ORANGE");
	pImageView7->SetVecPos(D3DXVECTOR3(225, 190, 0));
	pImageView7->SetTexture("Maps/Front/Image/font2.png");

	pImageView4->AddChild(pImageView5);
	pImageView4->AddChild(pImageView6);
	pImageView4->AddChild(pImageView7);

	UITextImageView* pImageView8 = new UITextImageView;
	pImageView8->SetIndex(0);
	pImageView8->SetText("ORANGE");
	pImageView8->SetVecPos(D3DXVECTOR3(225, 130, 0));
	pImageView8->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView9 = new UITextImageView;
	pImageView9->SetIndex(1);
	pImageView9->SetText("ORANGE");
	pImageView9->SetVecPos(D3DXVECTOR3(225, 150, 0));
	pImageView9->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView10 = new UITextImageView;
	pImageView10->SetIndex(2);
	pImageView10->SetText("ORANGE");
	pImageView10->SetVecPos(D3DXVECTOR3(225, 170, 0));
	pImageView10->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView11 = new UITextImageView;
	pImageView11->SetIndex(3);
	pImageView11->SetText("ORANGE");
	pImageView11->SetVecPos(D3DXVECTOR3(225, 190, 0));
	pImageView11->SetTexture("Maps/Front/Image/font2.png");

	pImageView8->AddChild(pImageView9);
	pImageView8->AddChild(pImageView10);
	pImageView8->AddChild(pImageView11);

	m_mapLobby[INTRO1] = new ST_Object;
	m_mapLobby[INTRO1]->m_time = 100.0f;
	m_mapLobby[INTRO1]->m_pObject = pImageView1;
	m_mapLobby[INTRO1]->m_pNextLob = new LOBBY[1];
	m_mapLobby[INTRO1]->m_pNextLob[0] = INTRO2;

	m_mapLobby[INTRO2] = new ST_Object;
	m_mapLobby[INTRO2]->m_time = 100.0f;
	m_mapLobby[INTRO2]->m_pObject = pImageView2;
	m_mapLobby[INTRO2]->m_pNextLob = new LOBBY[1];
	m_mapLobby[INTRO2]->m_pNextLob[0] = INTRO3;

	m_mapLobby[INTRO3] = new ST_Object;
	m_mapLobby[INTRO3]->m_time = 100.0f;
	m_mapLobby[INTRO3]->m_pObject = pImageView3;
	m_mapLobby[INTRO3]->m_pNextLob = new LOBBY[1];
	m_mapLobby[INTRO3]->m_pNextLob[0] = START_LOBBY;

	m_mapLobby[START_LOBBY] = new ST_Object;
	m_mapLobby[START_LOBBY]->m_target = D3DXVECTOR3(-1, 2, -90);
	m_mapLobby[START_LOBBY]->m_count = 4;
	m_mapLobby[START_LOBBY]->m_pNextLob = new LOBBY[4];
	m_mapLobby[START_LOBBY]->m_pNextLob[0] = MAIN_LOBBY;
	m_mapLobby[START_LOBBY]->m_pNextLob[1] = MAIN_LOBBY2;
	m_mapLobby[START_LOBBY]->m_pNextLob[2] = MAIN_LOBBY3;
	m_mapLobby[START_LOBBY]->m_pNextLob[3] = MAIN_LOBBY4;
	m_mapLobby[START_LOBBY]->m_pObject = pImageView4;

	m_mapLobby[MAIN_LOBBY] = new ST_Object;
	m_mapLobby[MAIN_LOBBY]->m_target = D3DXVECTOR3(0, 20, 0);
	m_mapLobby[MAIN_LOBBY]->m_count = 4;
	m_mapLobby[MAIN_LOBBY]->m_pObject = pImageView8;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob = new LOBBY[4];
	m_mapLobby[MAIN_LOBBY]->m_prevLob = START_LOBBY;
}
