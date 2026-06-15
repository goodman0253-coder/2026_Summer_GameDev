#pragma once
#include "BaseScene.h"
class SceneManager;
class InputManager;

class TitleScene:public BaseScene
{
private:
    int titleImage = -1;
    int fontTitle = -1;

    int stringWidth = 0;
    int stringHeight = 0;
    SceneManager* sceneManager = nullptr;

public:
    TitleScene() {}
    virtual ~TitleScene() {}

    void Initialize() override;
    void Update() override;
    void Draw() override;
    bool Release(void);
    void SetSceneManager(SceneManager* sm) { sceneManager = sm; }
};

