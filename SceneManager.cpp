#include "SceneManager.h"
#include "TitleScene.h" 
#include "GameScene.h"
#include "StageSelectScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"




SceneManager::SceneManager()
{
    nextScene = SCENE_NONE;
}

SceneManager::~SceneManager()
{

    if (currentScene != nullptr)
    {
        delete currentScene;
        currentScene = nullptr;
    }
}

void SceneManager::ChangeScene(SceneType type)
{
    nextScene = type;
    ProcChangeScene();
    
}

void SceneManager::ProcChangeScene()
{
    if (nextScene == SCENE_NONE) return;
    // 古いシーンを消す
    if (currentScene != nullptr)
    {
        delete currentScene;
        currentScene = nullptr; 
    }

    // 新しいシーンを作る
    switch (nextScene)
    {
    case SCENE_TITLE:
    {
        TitleScene* tScene = new TitleScene();
        tScene->SetSceneManager(this);

        // 最後に管理用の「currentScene」に代入する
        currentScene = tScene;
        break;
    }
    case SCENE_STAGESELECT:
    {
        StageSelectScene* sScene = new StageSelectScene();
        sScene->SetSceneManager(this);
        currentScene = sScene;
        break;
    }
    case SCENE_GAME:
    {
        GameScene* gScene = new GameScene();

        gScene->SetSceneManager(this);
        gScene->SetStageNum(this->GetSelectStageNum());
        gScene->GameInit();

        // 最後に管理用の「currentScene」に代入する
        currentScene = gScene;
        break;
    }
    case SCENE_GAMECLEAR:
    {
        // ゲームクリアシーン
        GameClearScene* cScene = new GameClearScene();
        cScene->SetSceneManager(this);
        currentScene = cScene;
        break;
    }
    case SCENE_GAMEOVER:
    
        GameOverScene* oScene = new GameOverScene();
        oScene->SetSceneManager(this);
        currentScene = oScene;
        break;
    }

    // 各シーン共通の Initialize 処理（GameScene以外）
    if (currentScene != nullptr && nextScene != SCENE_GAME)
    {
        currentScene->Initialize();
    }
}

void SceneManager::Update()
{

    if (nullptr != currentScene)
    {
        currentScene->Update();
    }

}
