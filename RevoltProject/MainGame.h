#pragma once

class Camera;
class Grid;
class MtlTex;

class Lobby;

class XFileLoader;

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
	void SetAddThing();

private:
	/*   �⺻ ����   */
	Camera* m_pCamera;
	Grid*	m_pGrid;

	Lobby* m_pLobby;
};

