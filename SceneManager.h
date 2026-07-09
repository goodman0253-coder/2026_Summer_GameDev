#pragma once
#include "BaseScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "StageSelectScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"

enum SceneType
{
    SCENE_NONE,
    SCENE_TITLE,
    SCENE_STAGESELECT,
    SCENE_GAME,
    SCENE_GAMECLEAR,
    SCENE_GAMEOVER,
};

class SceneManager 
{
private:


    TitleScene* titleScene = nullptr;
    GameScene* gameScene = nullptr;
    StageSelectScene* stageSlectScene = nullptr;
    GameClearScene* gameClearScene = nullptr;
    GameOverScene* gameOverScene = nullptr;

    BaseScene* currentScene = nullptr;

    int selectStageNum = 1;

    SceneType nextScene = SCENE_NONE;

    void ProcChangeScene();
public:

    SceneManager();
    ~SceneManager();


    // ƒV[ƒ“‚ðØ‚è‘Ö‚¦‚éŠÖ”
    void ChangeScene(SceneType type);

    void Update();
    void Draw() { if (currentScene) currentScene->Draw(); }
    void SetSelectStageNum(int num) { selectStageNum = num; }
    int GetSelectStageNum() const { return selectStageNum; }
};
