#include "SceneManager.h"
#include "TitleScene.h" // これから作る
#include "GameScene.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::ChangeScene(SceneType type) 
{
    // 古いシーンを消す
    if (currentScene != nullptr)
    {
        delete currentScene;
    }

    // 新しいシーンを作る
    switch (type)
    {
    case SCENE_TITLE:
        currentScene = new TitleScene();
        break;
    case SCENE_GAME:
        currentScene = new GameScene();
        break;
    }

    currentScene->Initialize();
}

void SceneManager::Draw()
{

}