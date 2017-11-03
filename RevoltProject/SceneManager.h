#pragma once
#define g_SceneManager SceneManager::GetInstance()

class Camera;

class GameNode;

class SceneManager
{
	SINGLETONE(SceneManager);

public:
	typedef std::map<std::string, GameNode*> mapSceneList;
	typedef std::map<std::string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _scCurrent;			//�����
	static GameNode* _scLoading;		//�ε���
	static GameNode* _scReady;			//��ü ����

	mapSceneList _mSceneList;			//�� ����Ʈ
	mapSceneIter _miSceneList;
	mapSceneList _mLoadingSceneList;	//�ε��� ����Ʈ

	DWORD _LoadThreadID;

	Camera* m_pCam;

public:

	void Setup();
	void Update();
	void Render();
	void Destroy();

	//���߰� �Լ�
	GameNode* AddScene(std::string sceneName, GameNode* scene);
	//�ε��� �߰�
	GameNode* AddLoadingScene(std::string loadingSceneName, GameNode* scene);


	//�� ��ü �Լ�
	HRESULT ChangeScene(std::string sceneName);
	HRESULT ChangeScene(std::string sceneName, std::string loadingSceneName);

	//���߿� ����� ���� ���
	friend DWORD CALLBACK LoadingThread(LPVOID prc);
};

