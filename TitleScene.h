#pragma once
#include "BaseScene.h"

class TitleScene:public BaseScene
{
private:
    int titleImage = -1;
    int fontTitle = -1;

    int stringWidth = 0;
    int stringHeight = 0;

public:
    TitleScene() {}
    virtual ~TitleScene() {}

    void Initialize() override;
    void Update() override;
    void Draw() override;
    bool Release(void);

};

