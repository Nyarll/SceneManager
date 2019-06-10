#pragma once
#include <memory>
#include <vector>
#include <stack>

#include "Scene.h"

#include "Singleton.h"

enum SceneID
{
	SCENE_NONE = (-1),
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_RESULT,
	SCENE_PAUSE,

	SCENE_NUM
};

class SceneManager : public Singleton<SceneManager>
{
private:
	friend class Singleton<SceneManager>;
	using SceneFactory = Scene*(*)();

private:
	std::vector<std::unique_ptr<Scene>> m_activeScene;
	SceneFactory m_sceneFactory[SceneID::SCENE_NUM];

	SceneID m_nextScene;

public:
	SceneManager();
	~SceneManager();

	// <�V�[���̒ǉ�>
	void AddScene(SceneID scene_id, SceneFactory factory_method);
	// <�J�n�V�[���̐ݒ�>
	void SetStartScene(SceneID scene_id);

	// <���݂̃V�[���̍X�V>
	void UpdateActiveScene();
	// <���݂̃V�[���̕`��>
	void RenderActiveScene();

	// <�V�[���ύX�v��>
	void RequestScene(SceneID scene_id);

	// <���݂̃V�[���ɁA����ɃV�[�����d�˂�>
	void RequestStackUpScene(SceneID id);

	// <�d�˂Ă���V�[���̍Ō�̃V�[��������>
	void DeleteStackScene();

private:
	// <�V�[���ύX>
	void ChangeScene(SceneID id);
};

