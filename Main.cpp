#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stack>

#include "Scene.h"
#include "SceneManager.h"

class SceneLogo : public Scene
{
public:
	SceneLogo() {};
	~SceneLogo() {};
	void Initialize() {};
	void Update() { std::cout << "Logo update"; };
	void Render() { std::cout << "Logo render"; };
	void Finalize() {};

	static Scene* Create() { return{ new SceneLogo }; }
};

class SceneTitle : public Scene
{
public:
	SceneTitle() {};
	~SceneTitle() {};
	void Initialize() {};
	void Update() { std::cout << "Title update"; };
	void Render() { std::cout << "Title render"; };
	void Finalize() {};

	static Scene* Create() { return{ new SceneTitle }; }
};

class ScenePlay : public Scene
{
public:
	ScenePlay() {};
	~ScenePlay() {};
	void Initialize() {};
	void Update() { std::cout << "Play update"; };
	void Render() { std::cout << "Play render"; };
	void Finalize() {};

	static Scene* Create() { return{ new ScenePlay }; }
};

class SceneResult : public Scene
{
public:
	SceneResult() {};
	~SceneResult() {};
	void Initialize() {};
	void Update() { std::cout << "Result update"; };
	void Render() { std::cout << "Result render"; };
	void Finalize() {};

	static Scene* Create() { return{ new SceneResult }; }
};

class ScenePause : public Scene
{
public:
	ScenePause() {};
	~ScenePause() {};
	void Initialize() {};
	void Update() { std::cout << "Pause update"; };
	void Render() { std::cout << "Pause render"; };
	void Finalize() {};

	static Scene* Create() { return{ new ScenePause }; }
};

int main()
{
	SceneManager& manager = SceneManager::GetInstanceRef();
	manager.AddScene(SCENE_LOGO, SceneLogo::Create);
	manager.AddScene(SCENE_TITLE, SceneTitle::Create);
	manager.AddScene(SCENE_PLAY, ScenePlay::Create);
	manager.AddScene(SCENE_RESULT, SceneResult::Create);
	manager.AddScene(SCENE_PAUSE, ScenePause::Create);

	manager.SetStartScene(SCENE_LOGO);

	std::cout << "- - - Scene Manager Test - - -" << std::endl << std::endl;

	manager.UpdateActiveScene();
	manager.RenderActiveScene();

	std::cout << "Request Scene Check" << std::endl << std::endl;
	manager.RequestScene(SceneID::SCENE_PLAY);

	manager.UpdateActiveScene();
	manager.RenderActiveScene();

	std::cout << "Request Stack Scene Check" << std::endl << std::endl;
	manager.RequestStackUpScene(SceneID::SCENE_PAUSE);

	manager.UpdateActiveScene();
	manager.RenderActiveScene();

	std::cout << "Delete Stack Scene Check" << std::endl << std::endl;
	manager.DeleteStackScene();

	manager.UpdateActiveScene();
	manager.RenderActiveScene();

	std::cin.get();
	return 0;
}