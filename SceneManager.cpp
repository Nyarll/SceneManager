#include "SceneManager.h"

#include <cassert>

SceneManager::SceneManager()
{
	m_activeScene.clear();
	m_nextScene = SceneID::SCENE_NONE;
	for (int i = 0; i < SceneID::SCENE_NUM; i++)
	{
		m_sceneFactory[i] = nullptr;
	}
}

SceneManager::~SceneManager()
{
	m_activeScene.clear();
}

void SceneManager::AddScene(SceneID scene_id, SceneFactory factory_method)
{
	assert(scene_id >= 0 && scene_id < SceneID::SCENE_NUM && "シーンIDが不正です。");
	assert(factory_method && "生成用関数が指定されていません。");

	m_sceneFactory[scene_id] = factory_method;
}

void SceneManager::SetStartScene(SceneID scene_id)
{
	assert(scene_id >= 0 && scene_id < SceneID::SCENE_NUM && "シーンIDが不正です");

	this->ChangeScene(scene_id);
}

void SceneManager::UpdateActiveScene()
{
	assert(m_activeScene[m_activeScene.size() - 1] && "活動中シーンがありません");
	if (m_nextScene != SceneID::SCENE_NONE)
	{
		this->ChangeScene(m_nextScene);
		m_nextScene = SceneID::SCENE_NONE;
	}
	m_activeScene[m_activeScene.size() - 1]->Update();
}

void SceneManager::RenderActiveScene()
{
	assert(m_activeScene[m_activeScene.size() - 1] && "活動中シーンがありません");
	
	for (int i = 0; i < m_activeScene.size(); i++)
	{
		m_activeScene[i]->Render();
	}
}

void SceneManager::RequestScene(SceneID scene_id)
{
	assert(scene_id >= 0 && scene_id < SceneID::SCENE_NUM && "シーンIDが不正です");
	m_nextScene = scene_id;
}

void SceneManager::RequestStackUpScene(SceneID id)
{
	assert(id >= 0 && id < SceneID::SCENE_NUM && "シーンIDが不正です");
	assert(m_sceneFactory[id] && "生成用関数が登録されていません");
	
	std::unique_ptr<Scene> value;
	value.reset(m_sceneFactory[id]());
	m_activeScene.push_back(value);
	m_activeScene[m_activeScene.size() - 1]->Initialize();
}

void SceneManager::DeleteStackScene()
{
	if (m_activeScene.size() > 1)
	{
		m_activeScene[m_activeScene.size() - 1]->Finalize();
		m_activeScene[m_activeScene.size() - 1].reset();
		m_activeScene.erase(m_activeScene.end());
	}
}

void SceneManager::ChangeScene(SceneID id)
{
	assert(id >= 0 && id < SceneID::SCENE_NUM && "シーンIDが不正です");
	assert(m_sceneFactory[id] && "生成用関数が登録されていません");

	for (int i = 0; i < m_activeScene.size(); i++)
	{
		m_activeScene[i]->Finalize();
		m_activeScene[i].reset();
	}
	m_activeScene.clear();

	std::unique_ptr<Scene> value;
	value.reset(m_sceneFactory[id]());
	m_activeScene.push_back(value);
	m_activeScene[0]->Initialize();
}
