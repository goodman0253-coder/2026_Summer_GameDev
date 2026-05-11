#pragma once
#include "BaseScene.h"

enum SceneType
{
    SCENE_TITLE,
    SCENE_GAME,
};

class SceneManager 
{



private:

    BaseScene* currentScene; // 現在のシーンを保持



public:

    SceneManager() : currentScene(nullptr) {}
    ~SceneManager() { delete currentScene; }


    // シーンを切り替える関数
    void ChangeScene(SceneType type);

    void Update() { if (currentScene) currentScene->Update(); }
    void Draw() { if (currentScene) currentScene->Draw(); }
};