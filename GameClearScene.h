#pragma once
#include "BaseScene.h"
class SceneManager;
class InputManager;

class GameClearScene :public BaseScene
{
    int gameClearImage = -1;
    SceneManager* sceneManager = nullptr;
public:
    GameClearScene() {}
    virtual ~GameClearScene() {}

    void Initialize() override;
    void Update() override;
    void Draw() override;
    bool Release(void);
    void SetSceneManager(SceneManager* sm) { sceneManager = sm; }
};

