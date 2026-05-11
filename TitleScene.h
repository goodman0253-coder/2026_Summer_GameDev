#pragma once
#include "BaseScene.h"

class TitleScene:public BaseScene
{
public:
    TitleScene() {}
    virtual ~TitleScene() {}

    // 親クラスの宿題（純粋仮想関数）をここで宣言する
    void Initialize() override;
    void Update() override;
    void Draw() override;
};

