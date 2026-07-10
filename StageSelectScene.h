#pragma once
#include "BaseScene.h"
class SceneManager;
class InputManager;

class StageSelectScene :public BaseScene
{
private:
    int stageSelectImage = -1;
    int fontStageSelect = -1;
    int fontMenu = -1;

    int currentCursor = 1;     // 現在選択中のステージ番号 (1: ステージ1, 2: ステージ2)
    const int MAX_STAGES = 3;   // 総ステージ数

    int stringWidth = 0;
    int stringHeight = 0;
    SceneManager* sceneManager = nullptr;

public:
    StageSelectScene() {}
    virtual ~StageSelectScene() {}

    void Initialize() override;
    void Update() override;
    void Draw() override;
    bool Release(void);
    void SetSceneManager(SceneManager* sm) { sceneManager = sm; }
};
