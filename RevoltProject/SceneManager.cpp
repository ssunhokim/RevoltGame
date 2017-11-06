#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::_scCurrent = NULL;
GameNode* SceneManager::_scLoading = NULL;
GameNode* SceneManager::_scReady = NULL;

SceneManager::SceneManager(){}

SceneManager::~SceneManager(){}

void SceneManager::Setup()
{
	_scCurrent = NULL;
	_scLoading = NULL;
	_scReady = NULL;
}

void SceneManager::Update()
{
	if (_scCurrent) _scCurrent->Update();
}

void SceneManager::LastUpdate()
{
	if (_scCurrent) _scCurrent->LastUpdate();
}

void SceneManager::Render()
{
	if (_scCurrent) _scCurrent->Render();
}

void SceneManager::Destroy()
{
	for each(auto sc in _mSceneList)
	{
		sc.second->Destroy();
	}
	_mSceneList.clear();

	SAFE_DESTROY(_scCurrent);
	_scCurrent = NULL;
}

GameNode * SceneManager::AddScene(std::string sceneName, GameNode * scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

GameNode * SceneManager::AddLoadingScene(std::string loadingSceneName, GameNode * scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(std::string sceneName)
{
	//�ٲٷ� �ϴ� ���� �ִ��� ã�´�.
	mapSceneIter find = _mSceneList.find(sceneName);

	//������ false
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ� �ϴ� ���� ������ ���� ������ OK
	if (find->second == _scCurrent) return S_OK;

	
	{
		//���Ӱ� ����Ǵ� ���� Setup����
		find->second->Setup();

		//���� �ٲ����� ����� ����
		if (_scCurrent) _scCurrent->Destroy();

		_scCurrent = find->second;

		return S_OK;
	}

	return E_FAIL;
}


HRESULT SceneManager::ChangeScene(std::string sceneName, std::string loadingSceneName)
{
	////�ٲٷ� �ϴ� ���� �ִ��� ã�´�.
	//mapSceneIter find = _mSceneList.find(sceneName);

	////������ false
	//if (find == _mSceneList.end()) return E_FAIL;

	//if (find->second == _scCurrent) return S_OK;

	////�ε��Ϸ��� �� ������ �־���
	//mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);


	//{

	//	find->second->Setup();

	//	if (_scCurrent) _scCurrent->Destroy();

	//	//�ε����� ���� Ʋ��
	//	_scLoading = findLoading->second;

	//	//���� �� �غ�
	//	_scReady = find->second;

	//	//������ ����
	//	CloseHandle(CreateThread(NULL, 0, LoadingThread, NULL, 0, &_LoadThreadID));
	//}

	return E_FAIL;
}

