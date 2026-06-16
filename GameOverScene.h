#pragma once
#include "BaseScene.h"
class SceneManager;
class InputManager; 

class GameOverScene :public BaseScene
{
private:
    int gameOverImage = -1;
    SceneManager* sceneManager = nullptr;
public:
    GameOverScene() {}
    virtual ~GameOverScene() {}

    void Initialize() override;
    void Update() override;
    void Draw() override;
    bool Release(void);
    void SetSceneManager(SceneManager* sm) { sceneManager = sm; }
};
