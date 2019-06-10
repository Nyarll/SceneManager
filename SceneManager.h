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

	// <シーンの追加>
	void AddScene(SceneID scene_id, SceneFactory factory_method);
	// <開始シーンの設定>
	void SetStartScene(SceneID scene_id);

	// <現在のシーンの更新>
	void UpdateActiveScene();
	// <現在のシーンの描画>
	void RenderActiveScene();

	// <シーン変更要求>
	void RequestScene(SceneID scene_id);

	// <現在のシーンに、さらにシーンを重ねる>
	void RequestStackUpScene(SceneID id);

	// <重ねてあるシーンの最後のシーンを消す>
	void DeleteStackScene();

private:
	// <シーン変更>
	void ChangeScene(SceneID id);
};

