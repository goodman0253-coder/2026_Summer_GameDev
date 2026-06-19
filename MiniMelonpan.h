#pragma once
#include "BreadBase.h"

class MiniMelonpan : public BreadBase
{
private:
    float speedY; // ?? 四方八方に飛ばすために、縦の速度を独自に追加

public:
    // コンストラクタ：位置と、計算されたX/Y速度を直接受け取る
    MiniMelonpan(float startX, float startY, float vx, float vy);

    void Update() override;
    void Draw(float cameraX, float cameraY) override;
};
