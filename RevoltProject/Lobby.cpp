#include "stdafx.h"
#include "Lobby.h"

/*   UI������� ����   */
#include "UIObject.h"
#include "UIImageView.h"
#include "UITextImageView.h"

#include "ObjectLoader.h"
#include "MtlTex.h"
#include "Camera.h"
#include "SelectMap.h"
#include "InGameUI.h"

/*      */
#include "Map.h"
#include "Thing.h"
#include "CarBox.h"
#include "WheelTire.h"

/*   �κ� â ����   */
#include "ProfileList.h"
#include "UserFileLoader.h"
#include "cSelectCarLob.h"
#include "cCreateProfile.h"
#include "cViewCarLob.h"

/*   ��Ƽ �÷��̾� �۾�   */
#include "cNetworkLobby.h"
#include "cNetworkCreateRoom.h"
#include "cNetworkInRoom.h"

Lobby::Lobby()
	: m_pSprite(NULL)
	, m_pObjMesh(NULL)
	, m_stateLobby(INTRO1)
	, m_time(0.0f)
	, m_select(0)
	, m_leftAndrightSelect(0)
	, m_stateMapType(NONE)
	, m_PlayerName("")
	, m_isCreate(false)
	, m_isEnterName(false)
	, m_pfileList(NULL)
	, m_isflag(false)
{
}

Lobby::~Lobby()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pObjMesh);
	SAFE_DELETE(m_pSelectMap);
	SAFE_DELETE(m_pInGameUI);
	SAFE_DELETE(m_multiLobby);
	SAFE_DELETE(m_pCreateProfileLobby);
	SAFE_DELETE(m_pSelectCarLobbby);

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
	UITextImageView::m_LeftAndRightSelect = &m_leftAndrightSelect;
	UITextImageView::m_PlayerName = m_PlayerName;
	UITextImageView::m_isCreate = &m_isCreate;
	UITextImageView::m_isflag = &m_isflag;
	Thing::g_LobbyState = &m_stateLobby;
	CarBox::g_select = &m_leftAndrightSelect;
	Map::g_LobbyState = &m_stateLobby;

	iLobby::m_gLobbyState = &m_stateLobby;

	m_pSelectMap = new SelectMap;
	m_pSelectMap->Setup();

	m_pInGameUI = new InGameUI;
	m_pInGameUI->Setup();

	m_multiLobby = new cNetworkLobby;
	m_multiLobby->Setup();

	m_pCreateProfileLobby = new cCreateProfile;
	m_pCreateProfileLobby->Setup();

	m_pSelectCarLobbby = new cSelectCarLob;
	m_pSelectCarLobbby->Setup();

	m_pViewCarLobby = new cViewCarLob;
	m_pViewCarLobby->Setup();

	m_pCreateRoom = new cNetworkCreateRoom;
	m_pCreateRoom->Setup();

	m_pInRoom = new cNetworkInRoom;
	m_pInRoom->Setup();

	SetUpUI();
}

void Lobby::Update()
{

	// Set Map Type Update
	if (m_stateLobby == SELECT_MAP_LOBBY)
	{
		m_pSelectMap->SetMapType(&m_stateMapType, m_leftAndrightSelect);
	}

	if (m_stateLobby == MARKET_MAP)
		m_pInGameUI->UpdateTimeLab();


	TimeUpdate();   // �ð� ���� �޼���
	KeyUpdate();   // Ű �̺�Ʈ ���� �޼���


	if (m_mapLobby[m_stateLobby]->m_pObject)
		m_mapLobby[m_stateLobby]->m_pObject->Update();
}

void Lobby::Render()
{
	if (m_mapLobby[m_stateLobby]->m_pObject)
		m_mapLobby[m_stateLobby]->m_pObject->Render(m_pSprite);
}

void Lobby::KeyUpdate()
{
	if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
	{
		m_select++;

		if (m_stateLobby == START_LOBBY)
		{
			if (m_vProfileList.size() <= m_select)
				m_select = 0;
		}
		else
		{
			if (m_mapLobby[m_stateLobby]->m_count <= m_select)
				m_select = 0;
		}
		g_pSoundManager->Play("menuUpDown.wav", 1.0f);
	}

	if (g_pKeyManager->isOnceKeyDown(VK_UP))
	{
		m_select--;

		if (m_stateLobby == START_LOBBY)
		{
			if (m_select < 0)
				m_select = m_vProfileList.size() - 1;
		}
		else
		{
			if (m_select < 0)
				m_select = m_mapLobby[m_stateLobby]->m_count - 1;
		}
		g_pSoundManager->Play("menuUpDown.wav", 1.0f);
	}

	if (g_pKeyManager->isOnceKeyDown(VK_RIGHT))
	{
		if (m_stateLobby == START_LOBBY ||
			m_stateLobby == SELECT_CAR_LOBBY ||
			m_stateLobby == SELECT_MAP_LOBBY)
		{
			m_leftAndrightSelect++;

			if (m_mapLobby[m_stateLobby]->m_selectCnt <= m_leftAndrightSelect)
				m_leftAndrightSelect = 0;
		
			g_pSoundManager->Play("menuLeftRight.wav", 1.0f);
		}
		else if (m_stateLobby == CREATE_PROFILE_LOBBY)
		{
			WheelTire::g_xRotAngle += D3DX_PI / 15.0f;
			g_pSoundManager->Play("menuLeftRight.wav", 1.0f);
		}

		else if (m_stateLobby == SELECT_MAP_LOBBY)
		{
			m_leftAndrightSelect--;

			m_pSelectMap->GetmagImage()->SetIsMove(true);

			if (m_leftAndrightSelect < 0)
				m_leftAndrightSelect = m_mapLobby[m_stateLobby]->m_selectCnt - 1;

			g_pSoundManager->Play("boxslide.wav", 1.0f);
		}
	}

	if (g_pKeyManager->isOnceKeyDown(VK_LEFT))
	{
		if (m_stateLobby == START_LOBBY || 
			m_stateLobby == SELECT_CAR_LOBBY)
		{
			m_leftAndrightSelect--;

			if (m_leftAndrightSelect < 0)
				m_leftAndrightSelect = m_mapLobby[m_stateLobby]->m_selectCnt - 1;

			g_pSoundManager->Play("menuLeftRight.wav", 1.0f);
		}
		else if (m_stateLobby == CREATE_PROFILE_LOBBY)
		{
			WheelTire::g_xRotAngle -= D3DX_PI / 15.0f;
			g_pSoundManager->Play("menuLeftRight.wav", 1.0f);
		}

		else if (m_stateLobby == SELECT_MAP_LOBBY)
		{
			m_leftAndrightSelect--;

			m_pSelectMap->GetmagImage()->SetIsMove(true);

			if (m_leftAndrightSelect < 0)
				m_leftAndrightSelect = m_mapLobby[m_stateLobby]->m_selectCnt - 1;

			g_pSoundManager->Play("boxslide.wav", 1.0f);
		}
	}

	/*   ���� Ű ������ �� ���� �κ�� ���� �̺�Ʈ   */
	if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		if (m_stateLobby == SELECT_MAP_LOBBY)
		{
			m_stateLobby = m_mapLobby[m_stateLobby]->m_pNextLob[m_leftAndrightSelect];
			m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);		// ī�޶� ����
			m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
			m_time = 0.0f;
			m_select = 0;
			m_leftAndrightSelect = 0;
			return;
		}

		else if (m_stateLobby == MAIN_LOBBY2)
		{
			if (m_select == 2)
				m_pViewCarLobby->SetIsNetwork(true);
		}

		else if (m_stateLobby == VIEW_CAR_LOBBY)
		{
			if (m_pViewCarLobby->GetIsNetwork())
			{
				m_mapLobby[m_stateLobby]->m_pNextLob[m_select] = NETWORK_LOBBY;
				m_multiLobby->SetUserName(m_pCreateProfileLobby->GetName());
				m_multiLobby->SetCarName(m_pSelectCarLobbby->GetCarName());
				g_pNetworkManager->Start();
			}		
		}

		else if (m_stateLobby == NETWORK_CREATE_LOBBY)
		{
			m_pInRoom->SetMap(m_pCreateRoom->GetImageName());
			m_pInRoom->SetUserName(m_multiLobby->GetName());
		}

		else if (m_stateLobby == NETWORK_IN_LOBBY)
		{
			g_pNetworkManager->SendMsg(m_pInRoom->GetMsg().c_str());
			m_pInRoom->SetResetCharText();
			g_pNetworkManager->RecvMsg();
			m_pInRoom->SetText(g_pNetworkManager->GetMsg());
			return;
		}

		m_stateLobby = m_mapLobby[m_stateLobby]->m_pNextLob[m_select];

		if (m_stateLobby > INTRO3)
		{
			g_pSoundManager->Play("menuNext.wav", 1.0f);
			m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);      // ī�޶� ����
			m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
			m_time = 0.0f;
			m_select = 0;
			if(m_stateLobby != VIEW_CAR_LOBBY)
				m_leftAndrightSelect = 0;
		}
	}
	/*   ESC Ű ������ �� ���� �κ�� ���� �̺�Ʈ   */
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		if (m_mapLobby[m_stateLobby]->m_prevLob != LOBBY_NONE)
		{
			m_stateLobby = m_mapLobby[m_stateLobby]->m_prevLob;

			if (m_stateLobby != MAIN_LOBBY2)
				m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);

			m_time = 0.0f;
			m_select = 0;
			m_leftAndrightSelect = 0;
			m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
			g_pSoundManager->Play("menuPrev.wav", 1.0f);
		}
	}
	
	if (g_pKeyManager->isOnceKeyDown(VK_F5))
	{
		if (m_stateLobby == NETWORK_LOBBY)
		{
			m_stateLobby = m_mapLobby[m_stateLobby]->m_pNextLob[0];
			m_pCamera->Setup(&m_mapLobby[m_stateLobby]->m_target);		 // ī�޶� ����

			m_time = 0.0f;
			m_select = 0;
			m_leftAndrightSelect = 0;
		}
	}

	m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
}

void Lobby::TimeUpdate()
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
			m_pCamera->SetLookAt(&m_mapLobby[m_stateLobby]->m_camLookAt);
		}
	}
	else
	{
		m_time++;
	}
}

void Lobby::SetUpUI()
{
	//===================================================================
	// - written by �輱ȣ
	// - @@ UI �߰��۾��� ���⼭�� �����ؾ� �Ѵ�.
	//===================================================================

///////////////////////////////   ����   /////////////////////////////////////////
	
	/*   ��Ʈ�� �̹���   */
	UIImageView* pImageView1 = new UIImageView;
	pImageView1->SetPosition(0, 0);
	pImageView1->SetTexture("Maps/Front/Image/intro1.png");

	UIImageView* pImageView2 = new UIImageView;
	pImageView2->SetPosition(0, 0);
	pImageView2->SetTexture("Maps/Front/Image/intro2.png");

	UIImageView* pImageView3 = new UIImageView;
	pImageView3->SetPosition(0, 0);
	pImageView3->SetTexture("Maps/Front/Image/intro3.png");

	/*   Start Lobby   */

	UIImageView* pImageView4 = new UIImageView;
	pImageView4->SetPosition(40, 40);
	pImageView4->SetXSize(4.0f);
	pImageView4->SetYSize(4.0f);
	pImageView4->SetIsBoard(true);
	pImageView4->SetTexture("Maps/Front/Image/blueRing.png");

	UIImageView* pImageView5 = new UIImageView;
	pImageView5->SetPosition(120, 20);
	pImageView5->SetXSize(24.0f);
	pImageView5->SetYSize(1.2f);
	pImageView5->SetIsBoard(true);
	pImageView5->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView6 = new UITextImageView;
	pImageView6->SetIndex(INT_MAX);
	pImageView6->SetPosition(150, 40);
	pImageView6->SetXSize(1.5f);
	pImageView6->SetYSize(1.5f);
	pImageView6->SetText("SELECT PROFILE");
	pImageView6->SetTexture("Maps/Front/Image/font1.png");

	UIImageView* pImageView7 = new UIImageView;
	pImageView7->SetPosition(18, 18);
	pImageView7->SetXSize(1.2f);
	pImageView7->SetYSize(1.2f);
	pImageView7->SetTexture("Maps/Front/Image/blueflag.png");

	UIImageView* pImageView8 = new UIImageView;
	pImageView8->SetPosition(350, 180);
	pImageView8->SetXSize(15.0f);
	pImageView8->SetYSize(1.2f);
	pImageView8->SetIsBoard(true);
	pImageView8->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView9 = new UITextImageView;
	pImageView9->SetPosition(90, 25);
	pImageView9->SetIndex(INT_MAX);
	pImageView9->SetIsVectorText(true);
	pImageView9->SetAddText("Load Profile");
	pImageView9->SetAddText("Create Profile");
	pImageView9->SetAddText("Delete Profile");
	pImageView9->SetXSize(1.0f);
	pImageView9->SetYSize(1.0f);
	pImageView9->SetColor(D3DCOLOR_ARGB(255, 242, 150, 97));
	pImageView9->SetTexture("Maps/Front/Image/font2.png");

	UIImageView* pImageView10 = new UIImageView;
	pImageView10->SetPosition(220, 22);
	pImageView10->SetXSize(1.5f);
	pImageView10->SetYSize(1.5f);
	pImageView10->SetTexture("Maps/Front/Image/arrowright.png");

	UIImageView* pImageView11 = new UIImageView;
	pImageView11->SetPosition(30, 22);
	pImageView11->SetXSize(1.5f);
	pImageView11->SetYSize(1.5f);
	pImageView11->SetTexture("Maps/Front/Image/arrowleft.png");

	UIImageView* pImageView12 = new UIImageView;
	pImageView12->SetPosition(50, 100);
	pImageView12->SetIsBoard(true);
	pImageView12->SetXSize(8.0f);
	pImageView12->SetYSize(12.0f);
	pImageView12->SetTexture("Maps/Front/Image/ring.png");

	UIImageView* pImageView13 = new UIImageView;
	pImageView13->SetPosition(70, 10);
	pImageView13->SetXSize(1.5f);
	pImageView13->SetYSize(1.5f);
	pImageView13->SetTexture("Maps/Front/Image/arrowup.png");

	UIImageView* pImageView14 = new UIImageView;
	pImageView14->SetPosition(70, 190);
	pImageView14->SetXSize(1.5f);
	pImageView14->SetYSize(1.5f);
	pImageView14->SetTexture("Maps/Front/Image/arrowdown.png");

	pImageView4->AddChild(pImageView5);
	pImageView4->AddChild(pImageView6);
	pImageView4->AddChild(pImageView7);
	pImageView4->AddChild(pImageView8);
	pImageView8->AddChild(pImageView9);
	pImageView8->AddChild(pImageView10);
	pImageView8->AddChild(pImageView11);
	pImageView8->AddChild(pImageView12);
	pImageView12->AddChild(pImageView13);
	pImageView12->AddChild(pImageView14);

	/*   Main Lobby 1  */

	///////////////////////////////   ����   /////////////////////////////////////////

	UIImageView* pImageView100 = new UIImageView;
	pImageView100->SetPosition(-10, -140);
	pImageView100->SetTexture("Maps/Front/Image/revoltrogo.png");

	UIImageView* pImageView110 = new UIImageView;
	pImageView110->SetPosition(400, 250);
	pImageView110->SetIsBoard(true);
	pImageView110->SetXSize(11.5f);
	pImageView110->SetYSize(9.5f);
	pImageView110->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView120 = new UITextImageView;
	pImageView120->SetIndex(0);
	pImageView120->SetPosition(50, 25);
	pImageView120->SetText("Start Game");
	pImageView120->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView130 = new UITextImageView;
	pImageView130->SetIndex(1);
	pImageView130->SetPosition(50, 50);
	pImageView130->SetText("Best Trial Times");
	pImageView130->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView140 = new UITextImageView;
	pImageView140->SetIndex(2);
	pImageView140->SetPosition(50, 75);
	pImageView140->SetText("Progress Table");
	pImageView140->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView150 = new UITextImageView;
	pImageView150->SetIndex(3);
	pImageView150->SetPosition(50, 100);
	pImageView150->SetText("Options");
	pImageView150->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView160 = new UITextImageView;
	pImageView160->SetIndex(4);
	pImageView160->SetPosition(50, 125);
	pImageView160->SetText("Select Profile");
	pImageView160->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView170 = new UITextImageView;
	pImageView170->SetIndex(5);
	pImageView170->SetPosition(50, 150);
	pImageView170->SetText("Quit");
	pImageView170->SetTexture("Maps/Front/Image/font2.png");

	pImageView110->AddChild(pImageView120);
	pImageView110->AddChild(pImageView130);
	pImageView110->AddChild(pImageView140);
	pImageView110->AddChild(pImageView150);
	pImageView110->AddChild(pImageView160);
	pImageView110->AddChild(pImageView170);
	pImageView110->AddChild(pImageView100);

	/*   Main Lobby 2  */

	///////////////////////////////   ����   /////////////////////////////////////////

	UIImageView* pImageView18 = new UIImageView;
	pImageView18->SetPosition(-10, -140);
	pImageView18->SetTexture("Maps/Front/Image/revoltrogo.png");

	UIImageView* pImageView19 = new UIImageView;
	pImageView19->SetPosition(400, 250);
	pImageView19->SetIsBoard(true);
	pImageView19->SetXSize(11.5f);
	pImageView19->SetYSize(9.5f);
	pImageView19->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView20 = new UITextImageView;
	pImageView20->SetIndex(0);
	pImageView20->SetPosition(50, 25);
	pImageView20->SetText("Start Race");
	pImageView20->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView21 = new UITextImageView;
	pImageView21->SetIndex(1);
	pImageView21->SetPosition(50, 50);
	pImageView21->SetText("Championship");
	pImageView21->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView22 = new UITextImageView;
	pImageView22->SetIndex(2);
	pImageView22->SetPosition(50, 75);
	pImageView22->SetText("Multi-Player");
	pImageView22->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView23 = new UITextImageView;
	pImageView23->SetIndex(3);
	pImageView23->SetPosition(50, 100);
	pImageView23->SetText("Time Trial");
	pImageView23->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView24 = new UITextImageView;
	pImageView24->SetIndex(4);
	pImageView24->SetPosition(50, 125);
	pImageView24->SetText("Practice");
	pImageView24->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView25 = new UITextImageView;
	pImageView25->SetIndex(5);
	pImageView25->SetPosition(50, 150);
	pImageView25->SetText("Stunt Arena");
	pImageView25->SetTexture("Maps/Front/Image/font2.png");

	pImageView19->AddChild(pImageView20);
	pImageView19->AddChild(pImageView21);
	pImageView19->AddChild(pImageView22);
	pImageView19->AddChild(pImageView23);
	pImageView19->AddChild(pImageView24);
	pImageView19->AddChild(pImageView25);
	pImageView19->AddChild(pImageView18);

	/*   Main Lobby 3  */

	UIImageView* pImageView26 = new UIImageView;
	pImageView26->SetPosition(-10, -140);
	pImageView26->SetTexture("Maps/Front/Image/revoltrogo.png");

	UIImageView* pImageView27 = new UIImageView;
	pImageView27->SetPosition(400, 250);
	pImageView27->SetIsBoard(true);
	pImageView27->SetXSize(11.5f);
	pImageView27->SetYSize(9.5f);
	pImageView27->SetTexture("Maps/Front/Image/ring.png");

	UITextImageView* pImageView28 = new UITextImageView;
	pImageView28->SetIndex(0);
	pImageView28->SetPosition(50, 25);
	pImageView28->SetText("Simulation");
	pImageView28->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView29 = new UITextImageView;
	pImageView29->SetIndex(1);
	pImageView29->SetPosition(50, 50);
	pImageView29->SetText("Arcade");
	pImageView29->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView30 = new UITextImageView;
	pImageView30->SetIndex(2);
	pImageView30->SetPosition(50, 75);
	pImageView30->SetText("Console");
	pImageView30->SetTexture("Maps/Front/Image/font2.png");

	UITextImageView* pImageView31 = new UITextImageView;
	pImageView31->SetIndex(3);
	pImageView31->SetPosition(50, 100);
	pImageView31->SetText("Junior RC");
	pImageView31->SetTexture("Maps/Front/Image/font2.png");

	pImageView27->AddChild(pImageView28);
	pImageView27->AddChild(pImageView29);
	pImageView27->AddChild(pImageView30);
	pImageView27->AddChild(pImageView31);
	pImageView27->AddChild(pImageView26);

	/*  Select Map Lobby  */

	//=========================================== Add Lobby Ui ===========================================//

	///////////////////////////////   ����   /////////////////////////////////////////

	/*   �κ� UI �߰��ϱ�   */

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
	m_mapLobby[START_LOBBY]->m_target = D3DXVECTOR3(-1, 2, -55);
	m_mapLobby[START_LOBBY]->m_count = 1;
	m_mapLobby[START_LOBBY]->m_selectCnt = 3;
	m_mapLobby[START_LOBBY]->m_pNextLob = new LOBBY[3];
	m_mapLobby[START_LOBBY]->m_prevLob = LOBBY_NONE;
	m_mapLobby[START_LOBBY]->m_time = 50.0f;
	m_mapLobby[START_LOBBY]->m_pNextLob[0] = MAIN_LOBBY;
	m_mapLobby[START_LOBBY]->m_pNextLob[1] = CREATE_PROFILE_LOBBY;
	m_mapLobby[START_LOBBY]->m_pNextLob[2] = START_LOBBY;
	m_mapLobby[START_LOBBY]->m_pObject = pImageView4;
	m_mapLobby[START_LOBBY]->m_prevLob = START_LOBBY;

	m_mapLobby[MAIN_LOBBY] = new ST_Object;
	m_mapLobby[MAIN_LOBBY]->m_target = D3DXVECTOR3(-1, 2, -20);
	m_mapLobby[MAIN_LOBBY]->m_count = 6;
	m_mapLobby[MAIN_LOBBY]->m_time = 50.0f;
	m_mapLobby[MAIN_LOBBY]->m_pObject = pImageView110;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob = new LOBBY[6];
	m_mapLobby[MAIN_LOBBY]->m_prevLob = MAIN_LOBBY;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[0] = MAIN_LOBBY2;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[1] = LOBBY_NONE;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[2] = LOBBY_NONE;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[3] = LOBBY_NONE;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[4] = START_LOBBY;
	m_mapLobby[MAIN_LOBBY]->m_pNextLob[5] = GAME_QUIT;

	m_mapLobby[MAIN_LOBBY2] = new ST_Object;
	m_mapLobby[MAIN_LOBBY2]->m_target = D3DXVECTOR3(1, 10, -2);
	m_mapLobby[MAIN_LOBBY2]->m_count = 6;
	m_mapLobby[MAIN_LOBBY2]->m_pNextLob = new LOBBY[6];
	m_mapLobby[MAIN_LOBBY2]->m_time = 50.0f;
	m_mapLobby[MAIN_LOBBY2]->m_pObject = pImageView19;
	m_mapLobby[MAIN_LOBBY2]->m_pNextLob[0] = MAIN_LOBBY3;
	m_mapLobby[MAIN_LOBBY2]->m_pNextLob[1] = MAIN_LOBBY3;
	m_mapLobby[MAIN_LOBBY2]->m_pNextLob[2] = CREATE_PROFILE_LOBBY;
	m_mapLobby[MAIN_LOBBY2]->m_prevLob = MAIN_LOBBY;

	m_mapLobby[MAIN_LOBBY3] = new ST_Object;
	m_mapLobby[MAIN_LOBBY3]->m_target = D3DXVECTOR3(1, 10, -1);
	m_mapLobby[MAIN_LOBBY3]->m_count = 4;
	m_mapLobby[MAIN_LOBBY3]->m_pNextLob = new LOBBY[1];
	m_mapLobby[MAIN_LOBBY3]->m_time = 50.0f;
	m_mapLobby[MAIN_LOBBY3]->m_pObject = pImageView27;
	m_mapLobby[MAIN_LOBBY3]->m_pNextLob[0] = CREATE_PROFILE_LOBBY;
	m_mapLobby[MAIN_LOBBY3]->m_prevLob = MAIN_LOBBY2;

	m_mapLobby[CREATE_PROFILE_LOBBY] = new ST_Object;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_target = D3DXVECTOR3(4, 8, 12);
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_count = 1;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_time = 50.0f;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_pObject = m_pCreateProfileLobby->GetUIRoot();
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_camLookAt = D3DXVECTOR3(14, 4, 22);
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_pNextLob[0] = SELECT_CAR_LOBBY;
	m_mapLobby[CREATE_PROFILE_LOBBY]->m_prevLob = MAIN_LOBBY3;

	m_mapLobby[NETWORK_LOBBY] = new ST_Object;
	m_mapLobby[NETWORK_LOBBY]->m_target = D3DXVECTOR3(4, 8, -5);
	m_mapLobby[NETWORK_LOBBY]->m_count = 1;
	m_mapLobby[NETWORK_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[NETWORK_LOBBY]->m_time = 50.0f;
	m_mapLobby[NETWORK_LOBBY]->m_pObject = m_multiLobby->GetUIRoot();
	m_mapLobby[NETWORK_LOBBY]->m_camLookAt = D3DXVECTOR3(14, 4, 8);
	m_mapLobby[NETWORK_LOBBY]->m_pNextLob[0] = NETWORK_CREATE_LOBBY;
	m_mapLobby[NETWORK_LOBBY]->m_prevLob = MAIN_LOBBY3;

	m_mapLobby[NETWORK_CREATE_LOBBY] = new ST_Object;
	m_mapLobby[NETWORK_CREATE_LOBBY]->m_target = D3DXVECTOR3(12, 3, -18);
	m_mapLobby[NETWORK_CREATE_LOBBY]->m_count = 1;
	m_mapLobby[NETWORK_CREATE_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[NETWORK_CREATE_LOBBY]->m_time = 50.0f;
	m_mapLobby[NETWORK_CREATE_LOBBY]->m_pObject = m_pCreateRoom->GetUIRoot();
	m_mapLobby[NETWORK_CREATE_LOBBY]->m_camLookAt = D3DXVECTOR3(23, 5, -12);
	m_mapLobby[NETWORK_CREATE_LOBBY]->m_pNextLob[0] = NETWORK_IN_LOBBY;
	m_mapLobby[NETWORK_CREATE_LOBBY]->m_prevLob = NETWORK_LOBBY;

	m_mapLobby[NETWORK_IN_LOBBY] = new ST_Object;
	m_mapLobby[NETWORK_IN_LOBBY]->m_target = D3DXVECTOR3(4, 8, -5);
	m_mapLobby[NETWORK_IN_LOBBY]->m_count = 1;
	m_mapLobby[NETWORK_IN_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[NETWORK_IN_LOBBY]->m_time = 50.0f;
	m_mapLobby[NETWORK_IN_LOBBY]->m_pObject = m_pInRoom->GetUIRoot();
	m_mapLobby[NETWORK_IN_LOBBY]->m_camLookAt = D3DXVECTOR3(14, 4, 8);
	m_mapLobby[NETWORK_IN_LOBBY]->m_pNextLob[0] = IN_GAME_MAP;
	m_mapLobby[NETWORK_IN_LOBBY]->m_prevLob = NETWORK_LOBBY;

	m_mapLobby[SELECT_CAR_LOBBY] = new ST_Object;
	m_mapLobby[SELECT_CAR_LOBBY]->m_target = D3DXVECTOR3(10, 14, 8);
	m_mapLobby[SELECT_CAR_LOBBY]->m_camLookAt = D3DXVECTOR3(20, -2, 16);
	m_mapLobby[SELECT_CAR_LOBBY]->m_pObject = m_pSelectCarLobbby->GetUIRoot();
	m_mapLobby[SELECT_CAR_LOBBY]->m_count = 1;
	m_mapLobby[SELECT_CAR_LOBBY]->m_selectCnt = 6;
	m_mapLobby[SELECT_CAR_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[SELECT_CAR_LOBBY]->m_pNextLob[0] = VIEW_CAR_LOBBY;
	m_mapLobby[SELECT_CAR_LOBBY]->m_time = 50.0f;
	m_mapLobby[SELECT_CAR_LOBBY]->m_prevLob = CREATE_PROFILE_LOBBY;

	m_mapLobby[SELECT_MAP_LOBBY] = new ST_Object;
	m_mapLobby[SELECT_MAP_LOBBY]->m_target = D3DXVECTOR3(12, 3, -18);
	m_mapLobby[SELECT_MAP_LOBBY]->m_count = 1;
	m_mapLobby[SELECT_MAP_LOBBY]->m_selectCnt = 4;
	m_mapLobby[SELECT_MAP_LOBBY]->m_pNextLob = new LOBBY[2];
	m_mapLobby[SELECT_MAP_LOBBY]->m_time = 5000.0f;
	m_mapLobby[SELECT_MAP_LOBBY]->m_pObject = m_pSelectMap->GetmapParent();
	m_mapLobby[SELECT_MAP_LOBBY]->m_camLookAt = D3DXVECTOR3(23, 5, -12);
	m_mapLobby[SELECT_MAP_LOBBY]->m_prevLob = VIEW_CAR_LOBBY;
	m_mapLobby[SELECT_MAP_LOBBY]->m_pNextLob[0] = MARKET_MAP;
	m_mapLobby[SELECT_MAP_LOBBY]->m_pNextLob[1] = GARDEN_MAP;

	m_mapLobby[VIEW_CAR_LOBBY] = new ST_Object;
	m_mapLobby[VIEW_CAR_LOBBY]->m_target = D3DXVECTOR3(10, 4, 8);
	m_mapLobby[VIEW_CAR_LOBBY]->m_camLookAt = D3DXVECTOR3(20, -3, 10);
	m_mapLobby[VIEW_CAR_LOBBY]->m_pObject = m_pViewCarLobby->GetUIRoot();
	m_mapLobby[VIEW_CAR_LOBBY]->m_count = 1;
	m_mapLobby[VIEW_CAR_LOBBY]->m_pNextLob = new LOBBY[1];
	m_mapLobby[VIEW_CAR_LOBBY]->m_prevLob = SELECT_CAR_LOBBY;
	m_mapLobby[VIEW_CAR_LOBBY]->m_pNextLob[0] = SELECT_MAP_LOBBY;

	m_mapLobby[IN_GAME_MAP] = new ST_Object;
	m_mapLobby[IN_GAME_MAP]->m_target = D3DXVECTOR3(0, 0, -15);
	m_mapLobby[IN_GAME_MAP]->m_camLookAt = D3DXVECTOR3(0, 0, 0);
	m_mapLobby[IN_GAME_MAP]->m_prevLob = SELECT_MAP_LOBBY;
	m_mapLobby[IN_GAME_MAP]->m_pObject = NULL;

	m_mapLobby[MARKET_MAP] = new ST_Object;
	m_mapLobby[MARKET_MAP]->m_target = D3DXVECTOR3(0, 10, -15);
	m_mapLobby[MARKET_MAP]->m_camLookAt = D3DXVECTOR3(0, 0, 0);
	m_mapLobby[MARKET_MAP]->m_prevLob = SELECT_MAP_LOBBY;
	m_mapLobby[MARKET_MAP]->m_pObject = m_pInGameUI->GetUIRoot();

	m_mapLobby[GARDEN_MAP] = new ST_Object;
	m_mapLobby[GARDEN_MAP]->m_target = D3DXVECTOR3(0, 60, -15);
	m_mapLobby[GARDEN_MAP]->m_camLookAt = D3DXVECTOR3(0, -5, 0);
	m_mapLobby[GARDEN_MAP]->m_prevLob = SELECT_MAP_LOBBY;
	m_mapLobby[GARDEN_MAP]->m_pObject = m_pInGameUI->GetUIRoot();
}
