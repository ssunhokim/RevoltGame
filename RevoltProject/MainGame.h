#pragma once

class Camera;
class Grid;
class MtlTex;

class Lobby;
class Map;

class cCar;
//======================================
// - ## 10.03.17 ##
// - written by �輱ȣ
// -  ���� ���� �������
// - �Ŵ��� ��Ģ - g_pŬ�����̸�
//======================================

class MainGame
{
public:
	MainGame();
	~MainGame();

	/*   �⺻ ����   */
	void Setup();
	void Update();
	void Render();
	void MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	/*   ���� Ʈ�� �߰� �޼���   */
	void SetAddSound();


	ID3DXMesh* TestMesh;

	

private:
	/*   �⺻ ����   */
	Camera* m_pCamera;
	Grid*	m_pGrid;

	Map* m_pMap;
	Lobby* m_pLobby;


//	cCar* pCar;
};

