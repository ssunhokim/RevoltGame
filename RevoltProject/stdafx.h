#pragma once

#include "targetver.h"
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
//======================================
// - ## 10.11.17 ##
// - written by �輱ȣ
// - ������� ���� �� ������ ����Լ� ����
// - using ���� ������ �� -> �̸��浹 �߻��� �� ����
//======================================

//======================================
// - ## ������� ���� �� ���� ����
//======================================

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:

//======================================
// - written by �̰ǹ�
// - <windows.h>�� PhysX������ <nxmath.h> ���� max �� min�� �ߺ����� ������̱⿡ ������ �߻��� �����ϱ� ���� ��ũ�� ����
//======================================

#define NOMINMAX	// <windows.h>�� PhysX������ <nxmath.h> ���� max �� min�� �ߺ����� ������̱⿡ ������ �߻��Ѵ�.
#ifdef max				// �̸� ���� {#define NOMINMAX ~ } �� �̿��� �ߺ������ �����ش�. 
	#undef max		
#endif min			
	#undef min		
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

/*   C++ �������   */
#include <iostream>
#include <fstream>
#include <mmsystem.h>
#include <istream>

/*   STL �������   */
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <bitset>

/*   ���μ��� ���� �������   */
#include <assert.h>
#include <thread>
#include <process.h>

/*   ���̷�Ʈ3D ���� �������   */
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

/*   PhysX���� ������� ����   */
#include <NxPhysics.h>
#include <NxPhysicsSDK.h>
#include <NxDebugRenderable.h>
#include <NxCooking.h>
#include <NxStream.h>
#include <NxUserContactReport.h>

/*   ���� ���� �������   */
#pragma comment (lib, "fmodlib/fmodex_vc.lib")
#include "fmodinc/fmod.hpp"

/*   �����찡 �������� �ð��� �˷��ִ� ���̺η���   */
#pragma comment(lib, "winmm.lib")

/*   ��Ʈ��ũ ���� ���� ���̺귯��   */
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>

/*   �������� ����   */
extern HWND			g_hWnd;
extern HINSTANCE	g_hInst;
extern POINT		g_ptMouse;

/*   ����ü �� ����   */
/*   ���� �κ���¸� �����ϴ� ������ ����ü   */

enum LOBBY {
	LOBBY_NONE = 1001
	, INTRO1
	, INTRO2
	, INTRO3
	, START_LOBBY
	, MAIN_LOBBY
	, MAIN_LOBBY2
	, MAIN_LOBBY3
	, MAIN_LOBBY4
	, CREATE_PROFILE_LOBBY
	, NETWORK_LOBBY
	, NETWORK_CREATE_LOBBY
	, NETWORK_IN_LOBBY
	, GAME_QUIT
	, SELECT_MAP_LOBBY
	, SELECT_CAR_LOBBY
	, VIEW_CAR_LOBBY
	, IN_GAME_MAP
	, MARKET_MAP
	, GARDEN_MAP
};
enum CAR_CLASS { CLASS_NONE, CAR_ELECTRIC, CAR_GLOW, CAR_OTHER };
enum CAR_RATING { RATING_NONE, RATING_ROOKIE, RATING_AMATEUR, RATING_SEMI_PRO, RATING_PRO };
enum MAP_TYPE { NONE = 0, SUPERMARKET, GARDEN, MUSEUM, SHIP };
enum FONTFILE{FONT1=2001, FONT2};
//======================================
// - ## 10.14.17 ##
// - written by �輱ȣ
// - ## ��ũ�� �Լ� �� ���� ##
// - ## ���������� ����� ����ü ����
// - ## �ζ��� �Լ� ����
//======================================
#include "MacroFunction.h"
#include "StandardStructure.h"
#include "InlineFunction.h"

//======================================
// - ## 10.14.17 ##
// - written by ���¼�
// -  ##���� ��ũ�� ���� ����
//======================================
#define C_RED      D3DCOLOR_XRGB(255,0,0)
#define C_BLUE      D3DCOLOR_XRGB(0,0,255)
#define C_GREEN      D3DCOLOR_XRGB(0,255,0)
#define C_BLACK      D3DCOLOR_XRGB(0,0,0)
#define C_WHITE      D3DCOLOR_XRGB(255,255,255)
#define C_MAGENTA   D3DCOLOR_XRGB(255,0,255)
#define C_CYAN      D3DCOLOR_XRGB(0,255,255)
#define C_YELLOW   D3DCOLOR_XRGB(255,255,0)
#define C_GRAY      D3DCOLOR_XRGB(128, 128, 128)

// = D3DXCOLOR
#define CX_RED     D3DXCOLOR(1,0,0,0.1f)
#define CX_BLUE    D3DXCOLOR(0,0,1,1)
#define CX_GREEN   D3DXCOLOR(0,1,0,1)
#define CX_YELLOW  D3DXCOLOR(1,1,0,1)
#define CX_BLACK   D3DXCOLOR(0,0,0,1)
#define CX_WHITE   D3DXCOLOR(1,1,1,1)
#define CX_GRAY    D3DXCOLOR(0.5,0.5,0.5,1)

#define WINSIZEX 1024
#define WINSIZEY 760

// = FONT2NUMBER
#define FONT2_START 47
#define FONT2_NUM0	48
#define FONT2_NUM1	49
#define FONT2_NUM2	50
#define FONT2_NUM3	51
#define FONT2_NUM4	52
#define FONT2_NUM5	53
#define FONT2_NUM6	54
#define FONT2_NUM7	55
#define FONT2_NUM8	56
#define FONT2_NUM9	57


//======================================
// - ## �Ŵ��� ������� ���� ##
//======================================
#include "DeviceManager.h"
#include "Object.h"
#include "KeyManager.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "TimeManager.h"
#include "cNetworkManager.h"
#include "cPhysXManager.h"
#include "SceneManager.h"
#include "CameraManager.h"
#include "LightManager.h"
#include "ItemManager.h"
#include "TextManager.h"
#include "cDataManager.h"

//UTIL
#include "cStringUtil.h"